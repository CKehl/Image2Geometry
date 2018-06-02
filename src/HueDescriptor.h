/*
 * HueDescriptor.h
 *
 *  Created on: Feb 4, 2016
 *      Author: christian
 */

#ifndef HUEDESCRIPTOR_H_
#define HUEDESCRIPTOR_H_

#include "opencv_includes.h"

namespace cv {

class CV_EXPORTS HueDescriptor : public DescriptorExtractor {
public:
	explicit HueDescriptor(int patchsize = 21, int scale = 5.0, double sig = 21/4.0, int bins = 36, int smooth = 0);
	HueDescriptor( const HueDescriptor& rhs );
	HueDescriptor& operator=( const HueDescriptor& );
	virtual ~HueDescriptor();

    /** returns the descriptor length in bytes */
    virtual int descriptorSize() const;

    /** returns the descriptor type */
    virtual int descriptorType() const;

    AlgorithmInfo* info() const;

protected:
    virtual void computeImpl( const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors ) const;

    CV_PROP_RW int patch_size;
    CV_PROP_RW int scalef;
    CV_PROP_RW double sigma;
    CV_PROP_RW int num_bins;
    CV_PROP_RW int smooth_flag;

	//int w2cRows,w2cCols;
	//cv::Mat w2c;
};

}
#endif /* HUEDESCRIPTOR_H_ */
