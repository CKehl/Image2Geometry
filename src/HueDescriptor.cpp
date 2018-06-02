/*
 * HueDescriptor.cpp
 *
 *  Created on: Feb 4, 2016
 *      Author: christian
 */

#include "HueDescriptor.h"

namespace cv {

CV_INIT_ALGORITHM(HueDescriptor, "Feature2D.HueDescriptor",
                  obj.info()->addParam(obj, "patchsize", obj.patch_size);
                  obj.info()->addParam(obj, "scalef", obj.scalef);
                  obj.info()->addParam(obj, "sigma", obj.sigma);
                  obj.info()->addParam(obj, "bins", obj.num_bins);
                  obj.info()->addParam(obj, "smooth", obj.smooth_flag))

HueDescriptor::HueDescriptor(int patchsize = 21, int scale = 5.0, double sig = 21/4.0, int bins = 36, int smooth = 0) : patch_size(patchsize),
																														scalef(scale),
																														sigma(sig),
																														num_bins(bins),
																														smooth_flag(smooth)
{
	// TODO Auto-generated constructor stub

}

HueDescriptor::~HueDescriptor() {
	// TODO Auto-generated destructor stub
}

void HueDescriptor::computeImpl( const Mat& image, std::vector<KeyPoint>& keypoints, Mat& descriptors ) const
{

	int m,k,n,p,index_px,blue,green,red,cont;
	int cx,cy,x,y,r,side,w,h,xi,yi,imgM,imgN;
	int outCols,border,hue_bin;
	double d,scalex,scaley,px,py,dx,dy,weight,hue,sat,lumEnergy,sum;
	int detRows,detCols,detCols2;
	cv::Mat superImage,det,gaussian,superMask,smooth;
	Vec3b pixel;

	imgM = image.rows;
	imgN = image.cols;

	detRows = keypoints.size();

	detCols = 5;
	det.create(detRows,detCols,CV_64F);
	for(m=0; m<detRows; m++)
	{
		det.at<double>(m,0) = keypoints.at(m).pt.x;
		det.at<double>(m,1) = keypoints.at(m).pt.y;
		det.at<double>(m,2) = keypoints.at(m).size;
		det.at<double>(m,3) = keypoints.at(m).angle;
		det.at<double>(m,4) = keypoints.at(m).response;
		// "<CIRCLE x y scale orientation cornerness>;;"
	}

	// Output number of columns depending on descriptor
	outCols = detCols+num_bins;

	// Detectors out of image boundaries
	border = 0;
	for(m=0; m<detRows; m++)
	{
		r = round(det.at<double>(m,2)*scalef);
		if(r>border)
		{
			border = r;
		}
	}
	border = 3*border;

	// Create Super Image for treating detectors out of image bounds
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

	// Gaussian
	gaussian = Mat::zeros(patch_size,patch_size,CV_64F);
	for(m=0; m<gaussian.rows; m++)
	{
		for(k=0; k<gaussian.cols; k++)
		{
			if(sigma == 0)
			{
				gaussian.at<double>(m,k) = 1.;
			}
			else
			{
				gaussian.at<double>(m,k) = exp((-(pow(m - ((patch_size - 1)/2.0), 2) + pow(k - ((patch_size - 1)/2.0), 2)))/(2*sigma*sigma));
				//gaussian.at<double>(m,k) = exp((-(pow(m - ((_patchsize - 1)/2.0), 2) + pow(k - ((_patchsize - 1)/2.0), 2)))/(2*_sigma*_sigma));
			}
		}
	}

	// Output matrix
	Mat imoutR, imoutG, imoutB, patchMask;
	imoutR = Mat::zeros(patch_size,patch_size,CV_64F);
	imoutG = Mat::zeros(patch_size,patch_size,CV_64F);
	imoutB = Mat::zeros(patch_size,patch_size,CV_64F);
	patchMask = Mat::zeros(patch_size,patch_size,CV_64F);

	smooth = Mat::zeros(1,num_bins,CV_64F);
	descriptors = Mat::zeros(detRows, num_bins, CV_64F);

	// Apply to every ROI
	for(m=0; m<detRows; m++)
	{
		// The -1 is because the descriptor comes from MatLab and starts at position 1 instead of 0
		cx = det.at<double>(m,0) + border -1;
		cy = det.at<double>(m,1) + border -1;
		r = round(det.at<double>(m,2)*scalef);
		x = cx - r;
		y = cy - r;
		side = (int) 2*r+1;
		scalex  = (double) side / patch_size;
		scaley  = (double) side / patch_size;

		// Check if the roi is not totally inside the image
		if((x+side>superImage.cols) || (y+side>superImage.rows) || (x<0) || (y<0))
		{
			printf("Completely outside of the image detection\n");
			continue;
		}

		if(side==patch_size)
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
			Mat imgR_blk, imgG_blk, imgB_blk, mask;
			imgR_blk = Mat::zeros(side,side,CV_64F);
			imgG_blk = Mat::zeros(side,side,CV_64F);
			imgB_blk = Mat::zeros(side,side,CV_64F);
			mask = Mat::zeros(side,side,CV_64F);

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
			for(k=0; k<patch_size; k++)
			{
				py = k*scaley;
				yi = (int) py;
				dy = py-yi;
				for(n=0 ; n<patch_size; n++)
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

		// Apply HUE to all pixels
		lumEnergy=0;
		cont=0;
		sum=0;
		for(k=0; k<patch_size; k++)
		{
			for(n=0; n<patch_size; n++)
			{
				if(patchMask.at<double>(k,n)==1)
				{
					weight = gaussian.at<double>(k,n);
					blue = imoutB.at<double>(k,n);
					green = imoutG.at<double>(k,n);
					red = imoutR.at<double>(k,n);
					hue = atan2(red+green-2*blue,sqrt(3)*(red-green))+M_PI;
					hue = (hue/(2*M_PI))*num_bins;
					hue_bin = (int) hue;
					if(hue_bin >= num_bins)
					{
						hue_bin = 0;
					}
					sat = (2./3.)*(red*red + green*green + blue*blue - red*green - red*blue - green*blue)+0.01;
					lumEnergy = lumEnergy + (red*red + green*green + blue*blue)*weight;
					// Interpolation
					/*for(p=hue_bin;p<hue_bin+2;p++) {
						if(p >= num_bins)
						{
							out.at<double>(m,detCols) = out.at<double>(m,detCols) + (1.-abs(hue-p))*sat*weight;
						}
						else
						{
							out.at<double>(m,p+detCols) = out.at<double>(m,p+detCols) + (1.-abs(hue-p))*sat*weight;
						}
					}*/
					if(hue_bin < num_bins)
					{
						descriptors.at<double>(m,hue_bin) = descriptors.at<double>(m,hue_bin) + sat*weight;
					}
					else
					{
						descriptors.at<double>(m,0) += sat*weight;
					}
					cont++;
					sum = sum + weight;
				}
			}
		}

		// Normalize gaussian
		lumEnergy = lumEnergy/sum;
		if(cont>0)
		{
			for(k=0; k<num_bins; k++)
			{
				descriptors.at<double>(m,k) = sqrt( (descriptors.at<double>(m,k)/sum) /(lumEnergy+0.000001));
				// If there is any '-nan'
				if(descriptors.at<double>(m,k) != descriptors.at<double>(m,k))
				{
					descriptors.at<double>(m,k) = 0;
				}

			}
		}

		// Smooth - if 3 bins or more
		if((smooth_flag>0) and (num_bins>2))
		{
			// Apply Smoothing
			for(k=0; k<smooth_flag; k++)
			{
				// Initialize
				for(n=0; n<num_bins; n++)
				{
					smooth.at<double>(0,n) = 0.0;
				}
				// first hue_bin
				smooth.at<double>(0,0) = (2.0*descriptors.at<double>(m,0) + descriptors.at<double>(m,1) + descriptors.at<double>(m,num_bins-1))/4.0;
				// last hue_bin
				smooth.at<double>(0,num_bins-1) = (2.0*descriptors.at<double>(m,num_bins-1) + descriptors.at<double>(m,0) + descriptors.at<double>(m,num_bins-2))/4.0;
				// other hue_bins
				for(n=1; n<(num_bins-1); n++)
				{
					smooth.at<double>(0,n) = (2*descriptors.at<double>(m,n) + descriptors.at<double>(m,n+1) + descriptors.at<double>(m,n-1))/4;
				}
				// Copy to Output
				for(n=0; n<num_bins; n++)
				{
					descriptors.at<double>(m,n) = smooth.at<double>(0,n);
				}
			}
		}
	}
	//smooth.release();
	//patchMask.release();
	//imoutR.release();
	//imoutG.release();
	//imoutB.release();
	//superMask.release();
	//gaussian.release();
	//det.release();
	//superImage.release();
}

int HueDescriptor::descriptorSize() const
{
    return num_bins*sizeof(double); // descriptor length in bytes
}

int HueDescriptor::descriptorType() const
{
    return CV_64F;
}

}



