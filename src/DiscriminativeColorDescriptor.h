/*
 * DiscriminativeColorDescriptor.h
 *
 *  Created on: Dec 14, 2015
 *      Author: christian
 */

#ifndef DISCRIMINATIVECOLORDESCRIPTOR_H_
#define DISCRIMINATIVECOLORDESCRIPTOR_H_

#include "opencv_includes.h"

namespace cv {

class CV_EXPORTS DiscriminativeColorDescriptor : public DescriptorExtractor {
public:
	explicit DiscriminativeColorDescriptor(int patch_size = 21, int probs = 25, int scalef = 5.0, double sigma = 21/4.0, bool fast = false);
	DiscriminativeColorDescriptor( const DiscriminativeColorDescriptor& rhs );
	DiscriminativeColorDescriptor& operator=( const DiscriminativeColorDescriptor& );

    virtual ~DiscriminativeColorDescriptor();

    /** returns the descriptor length in bytes */
    virtual int descriptorSize() const;

    /** returns the descriptor type */
    virtual int descriptorType() const;

    /** select the 512 "best description pairs"
         * @param images grayscale images set
         * @param keypoints set of detected keypoints
         * @param corrThresh correlation threshold
         * @param verbose print construction information
         * @return list of best pair indexes
    */
    vector<int> selectPairs( const vector<Mat>& images, vector<vector<KeyPoint> >& keypoints,
                      const double corrThresh = 0.7, bool verbose = true );

    AlgorithmInfo* info() const;

protected:
    virtual void computeImpl( const Mat& image, vector<KeyPoint>& keypoints, Mat& descriptors ) const;

    CV_PROP_RW int _patchsize;
    CV_PROP_RW int _probs;	//EQUALS descriptor size
    CV_PROP_RW int _scalef;
    CV_PROP_RW double _sigma;
    CV_PROP_RW bool _fast;

    Mat w2c;
    int w2cRows,w2cCols;

    /* For multi-descriptor extraction */
    bool extAll; // true if all pairs need to be extracted for pairs selection

private:
    void ReadLookUpTable(void);
};

} /* namespace cv */
#endif /* DISCRIMINATIVECOLORDESCRIPTOR_H_ */
