/*
 * DiscriminativeColorDescriptor.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: christian
 */

#include "DiscriminativeColorDescriptor.h"

//#include <cvconfig.h>
#include <unistd.h>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <cmath>

//using namespace cv;
using namespace std;

// used to sort pairs during pairs selection
struct PairStat
{
    double mean;
    int idx;
};

struct sortMean
{
    bool operator()( const PairStat& a, const PairStat& b ) const
    {
        return a.mean < b.mean;
    }
};

namespace cv {

CV_INIT_ALGORITHM(DiscriminativeColorDescriptor, "Feature2D.DiscriminativeColorDescriptor",
                  obj.info()->addParam(obj, "patchsize", obj._patchsize);
                  obj.info()->addParam(obj, "probs", obj._probs);
                  obj.info()->addParam(obj, "scalef", obj._scalef);
                  obj.info()->addParam(obj, "sigma", obj._sigma);
                  obj.info()->addParam(obj, "fast", obj._fast))

DiscriminativeColorDescriptor::DiscriminativeColorDescriptor(int patch_size, int probs, int scalef, double sigma, bool fast) :	_patchsize(patch_size),
																																_probs(probs),
																																_scalef(scalef),
																																_sigma(sigma),
																																_fast(fast),
																																extAll(false)
{
	// TODO Auto-generated constructor stub
	//std::cout << _patchsize << " " << _probs << " " << _scalef << " " << _sigma << " " << _fast << " " << std::endl;
	ReadLookUpTable();
}

DiscriminativeColorDescriptor::~DiscriminativeColorDescriptor() {
	// TODO Auto-generated destructor stub
	//w2c.release();
}

void DiscriminativeColorDescriptor::ReadLookUpTable(void)
{
	ifstream fdin;
	// Read Lookup Table for DCD
	switch (_probs)
	{
		case 11:
			if (_fast) { fdin.open("/home/christian/w2c/DD11_w2c_fast.txt"); }
			else { fdin.open("/home/christian/w2c/DD11_w2c.txt"); }
			break;
		case 25:
			if (_fast) { fdin.open("/home/christian/w2c/DD25_w2c_fast.txt"); }
			else { fdin.open("/home/christian/w2c/DD25_w2c.txt"); }
			break;
		case 50:
			if (_fast) { fdin.open("/home/christian/w2c/DD50_w2c_fast.txt"); }
			else { fdin.open("/home/christian/w2c/DD50_w2c.txt"); }
			break;
		default:
			fdin.open("/home/christian/w2c/DD25_w2c.txt");
			break;
	}
	if(fdin.fail())
	{
		printf("Cannot read lookup table file\n");
		return;
	}
	fdin >> w2cRows;
	fdin >> w2cCols;

	double d = 0.0;
	w2c = Mat::zeros(w2cRows,w2cCols,CV_64F);
	for(int m=0; m<w2cRows; m++)
	{
		for(int k=0; k<w2cCols; k++)
		{
			fdin >> d;
			w2c.at<double>(m,k) = d;
		}
	}
	fdin.close();
}

void DiscriminativeColorDescriptor::computeImpl( const Mat& image, std::vector<KeyPoint>& keypoints, Mat& descriptors ) const
{
	int m,k,n,p,index_px,blue,green,red,cont;
	int cx,cy,x,y,r,side,w,h,xi,yi,imgM,imgN;
	int border;//,outCols,hue_bin;
	double scalex,scaley,px,py,dx,dy,weight,sum;//,d,hue,sat,lumEnergy;
	//,detCols2,detRows,detCols;
	Mat superImage,gaussian,superMask,descriptors_out;//,smooth,out,det;
	string s;
	Vec3b pixel;

	imgM = image.rows;
	imgN = image.cols;

	// det = keypoints
	//det.create(detRows,detCols,CV_64F);
	// outCols = (detCols+probs); our case: outCols = _probs



	// Detectors out of image boundaries
	border = 0;
	for(m=0; m<keypoints.size(); m++)
	{
		r = round(keypoints.at(m).size*_scalef);
		if(r>border)
		{
			border = r;
		}
	}
	border = 3*border;

	// Create Super Image for treating detectors out of image bounds
	//superImage.create(imgM+2*border,imgN+2*border,CV_8UC3);
	//superMask.create(imgM+2*border,imgN+2*border,CV_64F);
	superImage = Mat::zeros(imgM+2*border,imgN+2*border,CV_8UC3);
	superMask = Mat::zeros(imgM+2*border,imgN+2*border,CV_64F);

	for(m=0; m<border; m++)
	{
		for(k=0; k<border; k++)
		{
			// top-left
			superImage.at<Vec3b>(m,k) = image.at<Vec3b>(0,0);
			superMask.at<double>(m,k) = 0.;
			// bottom-left
			superImage.at<Vec3b>(m+border+imgM,k) = image.at<Vec3b>(imgM-1,0);
			superMask.at<double>(m+border+imgM,k) = 0.;
			// top-right
			superImage.at<Vec3b>(m,k+border+imgN) = image.at<Vec3b>(0,imgN-1);
			superMask.at<double>(m,k+border+imgN) = 0.;
			// bottom-right
			superImage.at<Vec3b>(m+border+imgM,k+border+imgN) = image.at<Vec3b>(imgM-1,imgN-1);
			superMask.at<double>(m+border+imgM,k+border+imgN) = 0.;
		}
	}
	for(m=0; m<imgM; m++)
	{
		for(k=0; k<border; k++)
		{
			// middle-left
			superImage.at<Vec3b>(m+border,k) = image.at<Vec3b>(m,0);
			superMask.at<double>(m+border,k) = 0.;
			// middle-right
			superImage.at<Vec3b>(m+border,k+border+imgN) = image.at<Vec3b>(m,imgN-1);
			superMask.at<double>(m+border,k+border+imgN) = 0.;
		}
	}
	for(m=0; m<border; m++)
	{
		for(k=0; k<imgN; k++)
		{
			// top-center
			superImage.at<Vec3b>(m,k+border) = image.at<Vec3b>(0,k);
			superMask.at<double>(m,k+border) = 0.;
			// bottom-center
			superImage.at<Vec3b>(m+border+imgM,k+border) = image.at<Vec3b>(imgM-1,k);
			superMask.at<double>(m+border+imgM,k+border) = 0.;
		}
	}
	for(m=0; m<imgM; m++)
	{
		for(k=0; k<imgN; k++)
		{
			// middle-center
			superImage.at<Vec3b>(m+border,k+border) = image.at<Vec3b>(m,k);
			superMask.at<double>(m+border,k+border) = 1.;
		}
	}
	//image.release();

	// Gaussian
	//gaussian.create(_patchsize,_patchsize,CV_64F);
	gaussian = Mat::zeros(_patchsize,_patchsize,CV_64F);
	for(m=0; m<gaussian.rows; m++)
	{
		for(k=0; k<gaussian.cols; k++)
		{
			if(_sigma == 0)
			{
				gaussian.at<double>(m,k) = 1.;
			}
			else
			{
				gaussian.at<double>(m,k) = exp((-(pow(m - ((_patchsize - 1)/2.0), 2) + pow(k - ((_patchsize - 1)/2.0), 2)))/(2*_sigma*_sigma));
			}
		}
	}

	// Output matrix
	Mat imoutR = Mat::zeros(_patchsize,_patchsize,CV_64F), imoutG = Mat::zeros(_patchsize,_patchsize,CV_64F), imoutB = Mat::zeros(_patchsize,_patchsize,CV_64F), patchMask = Mat::zeros(_patchsize,_patchsize,CV_64F);
	//imoutR.create(_patchsize,_patchsize,CV_64F);
	//imoutG.create(_patchsize,_patchsize,CV_64F);
	//imoutB.create(_patchsize,_patchsize,CV_64F);
	//patchMask.create(_patchsize,_patchsize,CV_64F);

	//out.create(keypoints.size(),_probs,CV_64F);
	//descriptors.create(keypoints.size(),_probs,CV_32F);
	descriptors = Mat::zeros(keypoints.size(),_probs,CV_32F);
	//descriptors_out.create(keypoints.size(),_probs,CV_64F);
	descriptors_out = Mat::zeros(keypoints.size(),_probs,CV_64F);

	// Apply to every ROI
	for(m=0; m<descriptors_out.rows; m++)
	{
		// Initialize output row
		//for(k=0; k<detCols; k++)
		//{
		//	out.at<double>(m,k) = det.at<double>(m,k);
		//}
		for(k=0; k<_probs; k++)
		{
			descriptors_out.at<double>(m,k) = 0.0;
		}
		// The -1 is because the descriptor comes from MatLab and starts at position 1 instead of 0
		cx = keypoints.at(m).pt.x + border;
		cy = keypoints.at(m).pt.y + border;
		r = round(keypoints.at(m).size*_scalef);
		x = cx - r;
		y = cy - r;
		side = (int) 2*r+1;
		scalex  = (double) side / _patchsize;
		scaley  = (double) side / _patchsize;

		// Check if the roi is not totally inside the image
		if((x+side>superImage.cols) || (y+side>superImage.rows) || (x<0) || (y<0))
		{
			//printf("Completely outside of the image detection\n");
			std::cout << "Completely outside of the image detection" << std::endl;
			continue;
		}

		if(side==_patchsize)
		{
			for (k=y; k<y+side; k++)
			{
				for (n=x; n<x+side; n++)
				{
					pixel = superImage.at<Vec3b>(k,n);
					imoutR.at<double>(k-y,n-x) = pixel.val[2];
					imoutG.at<double>(k-y,n-x) = pixel.val[1];
					imoutB.at<double>(k-y,n-x) = pixel.val[0];
					patchMask.at<double>(k-y,n-x) = superMask.at<double>(k,n);
				}
			}
		}
		else
		{
			// Separate the image to resize into 3 channels
			Mat imgR_blk = Mat::zeros(side,side,CV_64F), imgG_blk = Mat::zeros(side,side,CV_64F), imgB_blk = Mat::zeros(side,side,CV_64F), mask = Mat::zeros(side,side,CV_64F);
			//imgR_blk.create(side,side,CV_64F);
			//imgG_blk.create(side,side,CV_64F);
			//imgB_blk.create(side,side,CV_64F);
			//mask.create(side,side,CV_64F);

			for (k=y; k<y+side; k++)
			{
				for (n=x; n<x+side; n++)
				{
					pixel = superImage.at<Vec3b>(k,n);
					imgR_blk.at<double>(k-y,n-x) = pixel.val[2];
					imgG_blk.at<double>(k-y,n-x) = pixel.val[1];
					imgB_blk.at<double>(k-y,n-x) = pixel.val[0];
					mask.at<double>(k-y,n-x) = superMask.at<double>(k,n);
				}
			}

			w = side-1;
			h = side-1;

			// Resize roi to patch
			for(k=0; k<_patchsize; k++)
			{
				py = k*scaley;
				yi = (int) py;
				dy = py-yi;
				for(n=0 ; n<_patchsize; n++)
				{
					px = n*scalex;
					xi = (int) px;
					dx = px-xi;
					if( (xi<w) && (yi<h) )
					{
						imoutR.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgR_blk.at<double>(yi,xi)+dx*imgR_blk.at<double>(yi,xi+1)) + dy * ((1.-dx)*imgR_blk.at<double>(yi+1,xi)+dx*imgR_blk.at<double>(yi+1,xi+1));
						imoutG.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgG_blk.at<double>(yi,xi)+dx*imgG_blk.at<double>(yi,xi+1)) + dy * ((1.-dx)*imgG_blk.at<double>(yi+1,xi)+dx*imgG_blk.at<double>(yi+1,xi+1));
						imoutB.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgB_blk.at<double>(yi,xi)+dx*imgB_blk.at<double>(yi,xi+1)) + dy * ((1.-dx)*imgB_blk.at<double>(yi+1,xi)+dx*imgB_blk.at<double>(yi+1,xi+1));
						patchMask.at<double>(k,n) = (1.-dy) * ((1.-dx)*mask.at<double>(yi,xi)+dx*mask.at<double>(yi,xi+1)) + dy * ((1.-dx)*mask.at<double>(yi+1,xi)+dx*mask.at<double>(yi+1,xi+1));
					}
					else if( (xi<=w) && (yi<h) )
					{
						imoutR.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgR_blk.at<double>(yi,w) +dx*imgR_blk.at<double>(yi,w))    + dy * ((1.-dx)*imgR_blk.at<double>(yi+1,w) +dx*imgR_blk.at<double>(yi+1,w));
						imoutG.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgG_blk.at<double>(yi,w) +dx*imgG_blk.at<double>(yi,w))    + dy * ((1.-dx)*imgG_blk.at<double>(yi+1,w) +dx*imgG_blk.at<double>(yi+1,w));
						imoutB.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgB_blk.at<double>(yi,w) +dx*imgB_blk.at<double>(yi,w))    + dy * ((1.-dx)*imgB_blk.at<double>(yi+1,w) +dx*imgB_blk.at<double>(yi+1,w));
						patchMask.at<double>(k,n) = (1.-dy) * ((1.-dx)*mask.at<double>(yi,w) +dx*mask.at<double>(yi,w))    + dy * ((1.-dx)*mask.at<double>(yi+1,w) +dx*mask.at<double>(yi+1,w));
					}
					else if( (xi<w) && (yi<=h) )
					{
						imoutR.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgR_blk.at<double>(yi,xi)+dx*imgR_blk.at<double>(yi,xi+1)) + dy * ((1.-dx)*imgR_blk.at<double>(h,xi)+dx*imgR_blk.at<double>(h,xi+1));
						imoutG.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgG_blk.at<double>(yi,xi)+dx*imgG_blk.at<double>(yi,xi+1)) + dy * ((1.-dx)*imgG_blk.at<double>(h,xi)+dx*imgG_blk.at<double>(h,xi+1));
						imoutB.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgB_blk.at<double>(yi,xi)+dx*imgB_blk.at<double>(yi,xi+1)) + dy * ((1.-dx)*imgB_blk.at<double>(h,xi)+dx*imgB_blk.at<double>(h,xi+1));
						patchMask.at<double>(k,n) = (1.-dy) * ((1.-dx)*mask.at<double>(yi,xi)+dx*mask.at<double>(yi,xi+1)) + dy * ((1.-dx)*mask.at<double>(h,xi)+dx*mask.at<double>(h,xi+1));
					}
					else if( (xi<=w) && (yi<=h) )
					{
						imoutR.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgR_blk.at<double>(yi,w) +dx*imgR_blk.at<double>(yi,w))    + dy * ((1.-dx)*imgR_blk.at<double>(h,w) +dx*imgR_blk.at<double>(h,w));
						imoutG.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgG_blk.at<double>(yi,w) +dx*imgG_blk.at<double>(yi,w))    + dy * ((1.-dx)*imgG_blk.at<double>(h,w) +dx*imgG_blk.at<double>(h,w));
						imoutB.at<double>(k,n) = (1.-dy) * ((1.-dx)*imgB_blk.at<double>(yi,w) +dx*imgB_blk.at<double>(yi,w))    + dy * ((1.-dx)*imgB_blk.at<double>(h,w) +dx*imgB_blk.at<double>(h,w));
						patchMask.at<double>(k,n) = (1.-dy) * ((1.-dx)*mask.at<double>(yi,w) +dx*mask.at<double>(yi,w))    + dy * ((1.-dx)*mask.at<double>(h,w) +dx*mask.at<double>(h,w));
					}

					if(patchMask.at<double>(k,n)<0.5)
					{
						patchMask.at<double>(k,n) = 0.;
					}
					else
					{
						patchMask.at<double>(k,n) = 1.;
					}
				}
			}

			//mask.release();
			//imgB_blk.release();
			//imgG_blk.release();
			//imgR_blk.release();
		}

		// Apply CN to all pixels
		cont=0;
		sum=0;
		for(k=0; k<_patchsize; k++)
		{
			for(n=0; n<_patchsize; n++)
			{
				if(patchMask.at<double>(k,n)==1)
				{
					weight = gaussian.at<double>(k,n);
					blue = imoutB.at<double>(k,n);
					green = imoutG.at<double>(k,n);
					red = imoutR.at<double>(k,n);
					index_px = floor(red/8)+32*floor(green/8)+32*32*floor(blue/8);
					// Add CN probs
					if (_fast)
					{
						p = (int) w2c.at<double>(index_px,3);
						p = (p-1);
						descriptors_out.at<double>(m,p) = descriptors_out.at<double>(m,p) + weight;
					}
					else
					{
						for(p=5; p<_probs; p++)
						{
							descriptors_out.at<double>(m,p) = descriptors_out.at<double>(m,p) + weight * w2c.at<double>(index_px,p-2);
						}
					}
					cont++;
					sum = sum + weight;
				}
			}
		}
		// Normalize gaussian
		if(cont>0)
		{
			for(k=0; k<_probs; k++)
			{
				descriptors.at<float>(m,k) = float(descriptors_out.at<double>(m,k)/sum);
			}
		}
#ifdef DEBUG
//		std::cout << "keypoint. " << m+1 << " of " << descriptors_out.rows << " ready." << std::endl;
#endif
	}
	//descriptors_out.release();
	//patchMask.release();
	//imoutR.release();
	//imoutG.release();
	//imoutB.release();
	//superMask.release();
	//gaussian.release();
	//w2c.release();
	//superImage.release();

}

// pair selection algorithm from a set of training images and corresponding keypoints
vector<int> DiscriminativeColorDescriptor::selectPairs(const std::vector<Mat>& images
                                        , std::vector<std::vector<KeyPoint> >& keypoints
                                        , const double corrTresh
                                        , bool verbose )
{
    extAll = true;
    // compute descriptors with all pairs
    Mat descriptors;

    if( verbose )
        std::cout << "Number of images: " << images.size() << std::endl;

    Mat _mean = Mat::zeros(1,_probs,CV_64F), _lmean = Mat::zeros(1,_probs,CV_64F);
    for( size_t i = 0;i < images.size(); ++i )
    {
        Mat descriptorsTmp;
        computeImpl(images[i],keypoints[i],descriptorsTmp);
        descriptors.push_back(descriptorsTmp);
        //_mean += cv::mean(descriptorsTmp).val[0];
        cv::reduce(descriptorsTmp,_lmean,0,CV_REDUCE_AVG, CV_64F);
        _mean += _lmean;
    }
    _mean /= images.size();

    if( verbose )
        std::cout << "number of keypoints: " << descriptors.rows << std::endl;



    std::vector<PairStat> pairStat;
    for( int n = _probs; n--; )
    {
        // the higher the variance, the better --> mean = 0.5
        PairStat tmp = { fabs( mean(descriptors.col(n))[0]-_mean.at<double>(0,n) ) ,n};
        pairStat.push_back(tmp);
    }

    std::sort( pairStat.begin(),pairStat.end(), sortMean() );

    std::vector<PairStat> bestPairs;
    for( int m = 0; m < _probs; ++m )
    {
        if( verbose )
            std::cout << m << ":" << bestPairs.size() << " " << std::flush;
        double corrMax(0);

        for( size_t n = 0; n < bestPairs.size(); ++n )
        {
            int idxA = bestPairs[n].idx;
            int idxB = pairStat[m].idx;
            double corr(0);
            // compute correlation between 2 pairs
            corr = fabs(compareHist(descriptors.col(idxA), descriptors.col(idxB), CV_COMP_CORREL));

            if( corr > corrMax )
            {
                corrMax = corr;
                if( corrMax >= corrTresh )
                    break;
            }
        }

        if( corrMax < corrTresh/*0.7*/ )
            bestPairs.push_back(pairStat[m]);

        if( bestPairs.size() >= 512 )
        {
            if( verbose )
                std::cout << m << std::endl;
            break;
        }
    }

    std::vector<int> idxBestPairs;
    if( (int)bestPairs.size() >= 512 )
    {
        for( int i = 0; i < 512; ++i )
            idxBestPairs.push_back(bestPairs[i].idx);
    }
    else
    {
        if( verbose )
            std::cout << "correlation threshold too small (restrictive)" << std::endl;
        CV_Error(CV_StsError, "correlation threshold too small (restrictive)");
    }
    extAll = false;
    return idxBestPairs;
}

int DiscriminativeColorDescriptor::descriptorSize() const
{
    return _probs*sizeof(float); // descriptor length in bytes
}

int DiscriminativeColorDescriptor::descriptorType() const
{
    return CV_32F;
}

} /* namespace cv */
