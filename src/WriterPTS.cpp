#include "WriterPTS.h"

WriterPTS::WriterPTS(void)
{

}

WriterPTS::~WriterPTS(void)
{

}

void WriterPTS::write(std::vector<osg::Vec3>* points, std::string filename)
{
	std::string fname = filename;
	std::ofstream pts_file;
	pts_file.open(fname.c_str(), std::ios::out|std::ios::trunc);
	if(pts_file.is_open())
	{
		for(uint idx = 0; idx < (points->size()); idx++)
		{
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).x() << " ";
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).y() << " ";
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).z() << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).r << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).g << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).b << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).a;
			pts_file << std::endl;
		}
		pts_file.close();
	}
	else
		std::cout << "Cannot open file." << std::endl;
}

void WriterPTS::write(std::vector<cv::Point3f>* points, std::string filename)
{
	std::string fname = filename;
	std::ofstream pts_file;
	pts_file.open(fname.c_str(), std::ios::out|std::ios::trunc);
	if(pts_file.is_open())
	{
		for(uint idx = 0; idx < (points->size()); idx++)
		{
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).x << " ";
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).y << " ";
			pts_file << std::fixed << std::setprecision(5) << points->at(idx).z << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).r << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).g << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).b << " ";
			//pts_file << std::fixed << std::setprecision(5) << points->at(idx).a;

			//if(idx < (points->size()-1))
				pts_file << std::endl;
		}
		pts_file.close();
	}
	else
		std::cout << "Cannot open file." << std::endl;
}


