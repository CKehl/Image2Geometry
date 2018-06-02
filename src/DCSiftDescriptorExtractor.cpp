/*
 * DCSiftDescriptorExtractor.cpp
 *
 *  Created on: Dec 16, 2015
 *      Author: christian
 */

#include "DCSiftDescriptorExtractor.h"

#include "DiscriminativeColorDescriptor.h"

namespace cv {

CV_INIT_ALGORITHM(DCSiftDescriptorExtractor, "Feature2D.DCSiftDescriptorExtractor",
                  obj.info()->addParam(obj, "patchsize", obj._patchsize);
                  obj.info()->addParam(obj, "probs", obj._probs);
                  obj.info()->addParam(obj, "scalef", obj._scalef);
                  obj.info()->addParam(obj, "sigma", obj._sigma);
                  obj.info()->addParam(obj, "fast", obj._fast))

DCSiftDescriptorExtractor::DCSiftDescriptorExtractor(int patch_size, int probs, int scalef, double sigma, bool fast) :	_patchsize(patch_size),
																														_probs(probs),
																														_scalef(scalef),
																														_sigma(sigma),
																														_fast(fast)
{
	// TODO Auto-generated constructor stub

}

DCSiftDescriptorExtractor::~DCSiftDescriptorExtractor() {
	// TODO Auto-generated destructor stub

}

void DCSiftDescriptorExtractor::computeImpl( const Mat& image, std::vector<KeyPoint>& keypoints, Mat& descriptors ) const
{
	Mat desc_dc, desc_sift;
	cv::Ptr<cv::DescriptorExtractor> e_dc = new DiscriminativeColorDescriptor(_patchsize, _probs, _scalef, _sigma, _fast);
	cv::Ptr<cv::DescriptorExtractor> e_sift = new cv::SiftDescriptorExtractor();
	e_dc->compute(image, keypoints, desc_dc);
	e_sift->compute(image, keypoints, desc_sift);
	short sift_size = 0;
	switch(_probs)
	{
	case 11:
		sift_size = 16;
		break;
	case 25:
		sift_size = 38;
		break;
	case 50:
		sift_size = 75;
		break;
	}
	descriptors = Mat::zeros(keypoints.size(), _probs+sift_size, CV_32F);
	for(uint m = 0; m < keypoints.size(); m++)
	{
		memcpy(descriptors.ptr<float>(m), desc_dc.ptr<float>(m), _probs*sizeof(float));
		memcpy(descriptors.ptr<float>(m,_probs), desc_sift.ptr<float>(m), sift_size*sizeof(float));
	}
}

int DCSiftDescriptorExtractor::descriptorSize() const
{
    return _probs*sizeof(float); // descriptor length in bytes
}

int DCSiftDescriptorExtractor::descriptorType() const
{
    return CV_32F;
}

} /* namespace cv */
