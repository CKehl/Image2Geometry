/*
 * DCSiftDescriptorExtractor.h
 *
 *  Created on: Dec 16, 2015
 *      Author: christian
 */

#ifndef DCSIFTDESCRIPTOREXTRACTOR_H_
#define DCSIFTDESCRIPTOREXTRACTOR_H_

#include "opencv_includes.h"

namespace cv {

class CV_EXPORTS DCSiftDescriptorExtractor : public DescriptorExtractor {
public:
	explicit DCSiftDescriptorExtractor(int patch_size = 21, int probs = 25, int scalef = 5.0, double sigma = 21/4.0, bool fast = false);
	DCSiftDescriptorExtractor( const DCSiftDescriptorExtractor& rhs );
	DCSiftDescriptorExtractor& operator=( const DCSiftDescriptorExtractor& );

    virtual ~DCSiftDescriptorExtractor();

    /** returns the descriptor length in bytes */
    virtual int descriptorSize() const;

    /** returns the descriptor type */
    virtual int descriptorType() const;

    AlgorithmInfo* info() const;

protected:
    virtual void computeImpl( const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors ) const;

    CV_PROP_RW int _patchsize;
    CV_PROP_RW int _probs;	//EQUALS descriptor size
    CV_PROP_RW int _scalef;
    CV_PROP_RW double _sigma;
    CV_PROP_RW bool _fast;
};

} /* namespace cv */
#endif /* DCSIFTDESCRIPTOREXTRACTOR_H_ */
