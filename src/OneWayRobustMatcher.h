/*
 * OneWayRobustMatcher.h
 *
 *  Created on: Feb 12, 2016
 *      Author: christian
 */

#ifndef ONEWAYROBUSTMATCHER_H_
#define ONEWAYROBUSTMATCHER_H_

#include "opencv_includes.h"

class OneWayRobustMatcher {

private:
	// pointer to the feature point detector object
	cv::Ptr<cv::FeatureDetector> detector;
	// pointer to the feature descriptor extractor object
	cv::Ptr<cv::DescriptorExtractor> extractor;
	// pointer to the matcher object
	cv::Ptr<cv::DescriptorMatcher > matcher;
	float ratio; // max ratio between 1st and 2nd NN
	bool refineF; // if true will refine the F matrix
	double confidence; // confidence level (probability)
	double distance; // min distance to epipolar
	uint syn_total_points, real_total_points;
	std::vector<int> inliers_syn, inliers_ref;
public:
	OneWayRobustMatcher();
	virtual ~OneWayRobustMatcher();
	// Set the feature detector
	inline void setFeatureDetector(cv::Ptr<cv::FeatureDetector>& detect) { detector= detect; }
	// Set the descriptor extractor
	inline void setDescriptorExtractor(cv::Ptr<cv::DescriptorExtractor>& desc) { extractor= desc; }
	// Set the matcher
	inline void setDescriptorMatcher(cv::Ptr<cv::DescriptorMatcher>& match) { matcher= match; }
	//Set MinDistanceToEpipolar
	inline void setMinDistanceToEpipolar(double dist) { distance= dist; }
	// Get number of inliers after matching
	inline int getNumberOfInliers() { return inliers_syn.size(); }

	// Clear matches for which NN ratio is > than threshold
	// return the number of removed points
	// (corresponding entries being cleared,
	// i.e. size will be 0)
	int ratioTest(std::vector<std::vector<cv::DMatch> > &matches);

	// Insert symmetrical matches in symMatches vector
	void symmetryTest(const std::vector<std::vector<cv::DMatch> >& matches1, const std::vector<std::vector<cv::DMatch> >& matches2, std::vector<cv::DMatch>& symMatches);

	bool RemoveDistractors(const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches);
	bool trim(std::vector<cv::DMatch>& matches_inPlace);
	bool trim(const std::vector<cv::DMatch>& matches_in, std::vector<cv::DMatch>& matches_out);

	// Identify good matches using RANSAC
	// Return fundemental matrix
	cv::Mat ransacTest(const std::vector< std::vector<cv::DMatch> >& matches, const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches);
	// Match feature points using symmetry test and RANSAC
	// returns fundemental matrix
	cv::Mat match(cv::Mat& image1, cv::Mat& image2, std::vector<cv::DMatch>& matches, std::vector<cv::KeyPoint>& keypoints1, std::vector<cv::KeyPoint>& keypoints2);
};

#endif /* ONEWAYROBUSTMATCHER_H_ */
