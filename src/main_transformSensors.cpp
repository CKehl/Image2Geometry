/*
 * main_transformSensors.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Christian Kehl
 */

#include "main.h"

#include <gdal/ogr_spatialref.h>

int main(int argc, char* argv[])
{
	std::string input_filepath;
	std::string base_path;
	cv::Mat center = cv::Mat::zeros(3,1,CV_32FC1);

	options_description desc("Allowed options", strlen("Allowed options"));
	desc.add_options()
	    ("help", "produce help message")
	    ("input", value<std::string>()->required(), "mobile sensor .txt file")
	    ("X", value<double>(), "origin X")
	    ("Y", value<double>(), "origin Y")
	    ("Z", value<double>(), "origin Z");

	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	if (vm.count("help")) {
	    std::cout << desc << "\n";
	    return 1;
	}

	if(vm.count("input"))
	{
		input_filepath = vm["input"].as<std::string>();
		int slashpos = input_filepath.find_last_of("/");
		base_path = input_filepath.substr(0, slashpos+1);
		std::cout << "Base path: " << base_path << std::endl;
	}
	else
	{
		std::cout << "No filepath given - EXITING ..." << std::endl;
	}

	if(vm.count("X"))
	{
		center.at<float>(0,0) = float(vm["X"].as<double>());
		std::cout << "X set to " << center.at<float>(0,0) << std::endl;
	}
	else
	{
		std::cout << "No center X explicit given - X set to " << center.at<float>(0,0) << std::endl;
	}

	if(vm.count("Y"))
	{
		center.at<float>(1,0) = float(vm["Y"].as<double>());
		std::cout << "Y set to " << center.at<float>(1,0) << std::endl;
	}
	else
	{
		std::cout << "No center Y explicit given - Y set to " << center.at<float>(1,0) << std::endl;
	}

	if(vm.count("Z"))
	{
		center.at<float>(2,0) = float(vm["Z"].as<double>());
		std::cout << "Z set to " << center.at<float>(2,0) << std::endl;
	}
	else
	{
		std::cout << "No center Z explicit given - Z set to " << center.at<float>(2,0) << std::endl;
	}

	SensorReader mReader;
	mReader.SetFileName(input_filepath);
	mReader.read();

	for(uint i = 0; i < mReader.data().size(); i++)
	{
#ifdef DEBUG
		std::cout << "Retrieving rotation matrix from rodriguez vector ..." << std::endl;
#endif
		cv::Mat rotmat = cv::Mat::eye(3,3,CV_32FC1);
		cv::Rodrigues(mReader.data().at(i).rotation_vec(), rotmat);

#ifdef DEBUG
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
            	std::cout << rotmat.at<float>(i,j) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Generated reorientation matrix: " << std::endl;
#endif
		std::cout << "Reorientation_angle: " << mReader.data().at(i).reorientation_angle() << std::endl;
		cv::Mat reorientation_matrix = cv::Mat::eye(3,3,CV_32FC1);
		reorientation_matrix.at<float>(0,0) = cos(mReader.data().at(i).reorientation_angle());
		reorientation_matrix.at<float>(0,1) = sin(mReader.data().at(i).reorientation_angle());
		reorientation_matrix.at<float>(1,0) = -sin(mReader.data().at(i).reorientation_angle());
		reorientation_matrix.at<float>(1,1) = cos(mReader.data().at(i).reorientation_angle());
#ifdef DEBUG
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
            	std::cout << reorientation_matrix.at<float>(i,j) << " ";
            }
            std::cout << std::endl;
        }
		std::cout << "Computing R = R_reorient * R_sensor" << std::endl;
#endif
		cv::Mat R = reorientation_matrix * rotmat;

#ifdef DEBUG
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
            	std::cout << R.at<float>(i,j) << " ";
            }
            std::cout << std::endl;
        }
	std::cout << "Computing R = R * R_adapt" << std::endl;
#endif

	R = R.t();
        float data[] = {-1,0,0,   0,1,0,   0,0,-1};
        cv::Mat adapt = cv::Mat::zeros(3,3,CV_32FC1);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
            	adapt.at<float>(i,j) = data[i*3+j];
            }
        }

        rotmat = R*adapt;

#ifdef DEBUG
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
            	std::cout << rotmat.at<float>(i,j) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "Getting spatial reference ...." << std::endl;
#endif
        OGRSpatialReference oSRS, oDST;
        oSRS.importFromEPSG(4326);
        // England
        oDST.importFromEPSG(32630);
        // Bergen
        //oDST.importFromEPSG(32632);
        cv::Mat& gps = mReader.data().at(i).gps_vec();
        double x=double(gps.at<float>(0,0)),y=double(gps.at<float>(1,0)),z = double(gps.at<float>(2,0));
        OGRCoordinateTransformation *poCT;
        poCT = OGRCreateCoordinateTransformation(&oSRS,&oDST);
        if( poCT == NULL || !poCT->Transform( 1, &x, &y, &z ) )
		std::cout << "Transformation failed." << std::endl;
        else
        {
        	gps.at<float>(0,0) = float(x);
        	gps.at<float>(1,0) = float(y);
        	gps.at<float>(2,0) = float(z);
        }
#ifdef DEBUG
	std::cout << "GPS vector " << gps.at<float>(0,0) << ", " <<  gps.at<float>(1,0) << ", " <<  gps.at<float>(2,0) << "." << std::endl;
#endif


        gps.at<float>(0,0) = gps.at<float>(0,0) - center.at<float>(0,0);
        gps.at<float>(1,0) = gps.at<float>(1,0) - center.at<float>(1,0);
        gps.at<float>(2,0) = gps.at<float>(2,0) - center.at<float>(2,0);
#ifdef DEBUG
	std::cout << "GPS vector " << gps.at<float>(0,0) << ", " <<  gps.at<float>(1,0) << ", " <<  gps.at<float>(2,0) << "." << std::endl;
#endif

#ifdef DEBUG
        std::cout << "Storing final matrix ..." << std::endl;
#endif
        cv::Mat transformation = cv::Mat::eye(4,4,CV_32FC1);
    	for(int m = 0; m<3; m++)
    	{
    		for(int n = 0; n<3; n++)
    		{
    			transformation.at<float>(m,n) = rotmat.at<float>(m,n);
    		}
    		transformation.at<float>(m,3) = gps.at<float>(m,0);
    	}

    	uint slashpos = mReader.data().at(i).filepath().find_last_of("/");
    	uint dotpos = mReader.data().at(i).filepath().find_last_of(".");
    	std::string filename = mReader.data().at(i).filepath().substr(slashpos+1,(dotpos-slashpos-1));
    	filename.append(".dat");
    	std::cout << filename << std::endl;
    	std::string path = base_path+filename;
#ifdef DEBUG
    	std::cout << "Matrix path: " << path << std::endl;
#endif

    	OCVtoDAT mWriter;
    	mWriter.SetFileName(path);
    	mWriter.SetMatrix(transformation);
    	mWriter.write();

    	filename = mReader.data().at(i).filepath().substr(slashpos+1,(dotpos-slashpos-1));
    	filename.append("_declination");
    	filename.append(".dat");
    	path = base_path+filename;
#ifdef DEBUG
    	std::cout << "Declination path: " << path << std::endl;
#endif
    	std::ofstream dec_file;
    	dec_file.open(path.c_str(), std::ios::out|std::ios::trunc);
    	if(dec_file.is_open())
    	{
    		dec_file << mReader.data().at(i).declination();
			dec_file.close();
		}
		else
			std::cout << "Cannot open DAT file." << std::endl;
	}

	return 0;
}


