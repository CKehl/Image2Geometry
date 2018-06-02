/*
 * ConstrainedMatcher.cpp
 *
 *  Created on: 2 jan. 2016
 *      Author: christian
 */

#include "ConstrainedMatcher.h"

ConstrainedMatcher::ConstrainedMatcher() : ratio(1.0), refineF(true), confidence(0.99), distance(3.0), syn_total_points(0), real_total_points(0), _constraints(NULL)
{
	// TODO Auto-generated constructor stub
	detector= new cv::OrbFeatureDetector();
	extractor= new cv::OrbDescriptorExtractor();
	matcher= new cv::BFMatcher(cv::NORM_HAMMING2, true);
}

ConstrainedMatcher::~ConstrainedMatcher() {
	// TODO Auto-generated destructor stub
}

void ConstrainedMatcher::symmetryTest(const std::vector<cv::DMatch>& matches1, const std::vector<cv::DMatch>& matches2, std::vector<cv::DMatch>& symMatches)
{
	if(matches1.empty() || matches2.empty())
		return;
    // for all matches image 1 -> image 2
    for (std::vector<cv::DMatch>::const_iterator matchIterator1= matches1.begin();matchIterator1!= matches1.end(); ++matchIterator1) {
    	// for all matches image 2 -> image 1
    	for (std::vector<cv::DMatch>::const_iterator matchIterator2= matches2.begin(); matchIterator2!= matches2.end(); ++matchIterator2) {
    		// Match symmetry test
    		if ( (*matchIterator1).queryIdx == (*matchIterator2).trainIdx && (*matchIterator2).queryIdx ==(*matchIterator1).trainIdx) {
    			// add symmetrical match
    			symMatches.push_back(cv::DMatch((*matchIterator1).queryIdx, (*matchIterator1).trainIdx, (*matchIterator1).distance));
    			break; // next match in image 1 -> image 2
    		}
    	}
    }
}

cv::Mat ConstrainedMatcher::ransacTest(const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches)
{
	// Convert keypoints into Point2f
	std::vector<cv::Point2f> points1, points2;
	cv::Mat fundemental;
	for (std::vector<cv::DMatch>:: const_iterator it= matches.begin(); it!= matches.end(); ++it) {
		// Get the position of left keypoints
		float x= keypoints1[it->queryIdx].pt.x;
		float y= keypoints1[it->queryIdx].pt.y;
		points1.push_back(cv::Point2f(x,y));
		// Get the position of right keypoints
		x= keypoints2[it->trainIdx].pt.x;
		y= keypoints2[it->trainIdx].pt.y;
		points2.push_back(cv::Point2f(x,y));
	}
	// Compute F matrix using RANSAC
	std::vector<uchar> inliers(points1.size(),0);
	if (points1.size()>0&&points2.size()>0){
		cv::Mat fundemental= cv::findFundamentalMat(cv::Mat(points1),cv::Mat(points2), // matching points
				inliers,       // match status (inlier or outlier)
				cv::FM_RANSAC, // RANSAC method
				distance,      // distance to epipolar line
				confidence); // confidence probability
		// extract the surviving (inliers) matches
		std::vector<uchar>::const_iterator itIn= inliers.begin();
		std::vector<cv::DMatch>::const_iterator itM= matches.begin();
		// for all matches
		for ( ;itIn!= inliers.end(); ++itIn, ++itM) {
			if (*itIn) { // it is a valid match
				outMatches.push_back(*itM);
			}
		}
		if (refineF) {
			// The F matrix will be recomputed with
			// all accepted matches
			// Convert keypoints into Point2f
			// for final F computation
			points1.clear();
			points2.clear();
			for (std::vector<cv::DMatch>::const_iterator it= outMatches.begin(); it!= outMatches.end(); ++it) {
				// Get the position of left keypoints
				float x= keypoints1[it->queryIdx].pt.x;
				float y= keypoints1[it->queryIdx].pt.y;
				points1.push_back(cv::Point2f(x,y));
				// Get the position of right keypoints
				x= keypoints2[it->trainIdx].pt.x;
				y= keypoints2[it->trainIdx].pt.y;
				points2.push_back(cv::Point2f(x,y));
			}
			// Compute 8-point F from all accepted matches
			if (points1.size()>0&&points2.size()>0){
				fundemental= cv::findFundamentalMat(
						cv::Mat(points1),cv::Mat(points2), // matches
						cv::FM_8POINT); // 8-point method
			}
		}
	}
	return fundemental;
}

cv::Mat ConstrainedMatcher::match(cv::Mat& image1, cv::Mat& image2, std::vector<cv::DMatch>& matches, std::vector<cv::KeyPoint>& keypoints1, std::vector<cv::KeyPoint>& keypoints2)
{
	assert(_constraints!=NULL);

	// 1a. Detection of the SURF features
#ifdef DEBUG
	std::cout << "Feature Detection ... " << std::endl;
#endif /* DEBUG */
	detector->detect(image1,keypoints1);
	detector->detect(image2,keypoints2);
	if( keypoints1.empty() || keypoints2.empty() )
		return cv::Mat();

#ifdef DEBUG
	std::cout << "Feature Description ... " << std::endl;
#endif /* DEBUG */
	// 1b. Extraction of the descriptors
	cv::Mat descriptors1, descriptors2;
	extractor->compute(image1,keypoints1,descriptors1);
#ifdef DEBUG
	std::cout << "FD syn done ... " << std::endl;
#endif /* DEBUG */
	extractor->compute(image2,keypoints2,descriptors2);
#ifdef DEBUG
	std::cout << "FD real done ... " << std::endl;
#endif /* DEBUG */
#ifdef DEBUG
	std::cout << "vector sizes: img1 - " << descriptors1.rows << "x" <<descriptors1.cols << ", img2 - " << descriptors2.rows << "x" << descriptors2.cols << ", type: " << type2str(descriptors1.type()) << " ... " << std::endl;
#endif /* DEBUG */
	if( (descriptors1.rows == 0) || (descriptors1.cols == 0) || (descriptors2.rows == 0) || (descriptors2.cols == 0) )
		return cv::Mat();
	if( (descriptors1.rows < 2) || (descriptors2.rows < 2) )
		return cv::Mat();

	std::vector<cv::DMatch> symMatches;
	std::vector<cv::DMatch> localMatches;
	cv::Mat local_syn_descriptor = cv::Mat::zeros(descriptors1.rows, descriptors1.cols, descriptors1.type()), local_real_descriptor = cv::Mat::zeros(descriptors2.rows, descriptors2.cols, descriptors2.type());
	// mapping global index -> local index
	typedef std::pair<uint, uint> IndexPair;
	std::vector< IndexPair > mapping_d1, mapping_d2;
	uint local_constraint_matches = 0;

#ifdef DEBUG
	std::cout << "# constraints: " << _constraints->size() << std::endl;
#endif /* DEBUG */

	size_t dc_cols = descriptors1.cols;
	size_t dc_bytes = 0;
	if(descriptors1.type()==CV_32F)
		dc_bytes = sizeof(float);
	else if(descriptors1.type()==CV_8U)
		dc_bytes = sizeof(uchar);
	assert(descriptors1.type()==descriptors2.type());

	for(uint constraint_iter = 0; constraint_iter < _constraints->size(); constraint_iter++)
	{
		local_syn_descriptor = cv::Mat::zeros(descriptors1.rows, descriptors1.cols, descriptors1.type());
		local_real_descriptor = cv::Mat::zeros(descriptors2.rows, descriptors2.cols, descriptors2.type());
		mapping_d1.clear();
		mapping_d2.clear();
		localMatches.clear();
		local_constraint_matches = 0;
		for(uint kp1_iter = 0; kp1_iter < keypoints1.size(); kp1_iter++)
		{
			if(_constraints->at(constraint_iter).first.insideCircle(keypoints1.at(kp1_iter).pt))
			{
				//local_syn_descriptor.row(local_constraint_matches) = descriptors1.row(kp1_iter);
				mapping_d1.push_back(IndexPair(kp1_iter, local_constraint_matches));
				local_constraint_matches++;
			}
		}
		if(local_constraint_matches==0)
			continue;
		local_syn_descriptor = cv::Mat::zeros(local_constraint_matches, dc_cols, descriptors1.type());
		for(uint dc1_iter = 0; dc1_iter < mapping_d1.size(); dc1_iter++)
		{
			memcpy(local_syn_descriptor.ptr<float>(mapping_d1.at(dc1_iter).second), descriptors1.ptr<float>(mapping_d1.at(dc1_iter).first), dc_cols*dc_bytes);
		}
#ifdef DEBUG
		std::cout << "Matches syn image, constraint " << constraint_iter << ": " << local_syn_descriptor.rows << "x" <<local_syn_descriptor.cols << std::endl;
#endif /* DEBUG */
		local_constraint_matches = 0;


		for(uint kp2_iter = 0; kp2_iter < keypoints2.size(); kp2_iter++)
		{
			if(_constraints->at(constraint_iter).second.insideCircle(keypoints2.at(kp2_iter).pt))
			{
				//local_real_descriptor.row(local_constraint_matches) = descriptors2.row(kp2_iter);
				mapping_d2.push_back(IndexPair(kp2_iter, local_constraint_matches));
				local_constraint_matches++;
			}
		}
		if(local_constraint_matches==0)
			continue;
		local_real_descriptor = cv::Mat::zeros(local_constraint_matches, dc_cols, descriptors1.type());
		for(uint dc2_iter = 0; dc2_iter < mapping_d2.size(); dc2_iter++)
		{
			memcpy(local_real_descriptor.ptr<float>(mapping_d2.at(dc2_iter).second), descriptors1.ptr<float>(mapping_d2.at(dc2_iter).first), dc_cols*dc_bytes);
		}
#ifdef DEBUG
		std::cout << "Matches ref image, constraint " << constraint_iter << ": " << local_real_descriptor.rows << "x" << local_real_descriptor.cols << std::endl;
#endif /* DEBUG */
		local_constraint_matches = 0;

		// 2. Match the two image descriptors
		// Construction of the matcher
		//cv::BruteForceMatcher<cv::L2<float>> matcher;
#ifdef DEBUG
		std::cout << "Matching features img1->img2 ..." << std::endl;
#endif
		// from image 1 to image 2
		// based on k nearest neighbours (with k=2)
		std::vector<cv::DMatch> matches1;
		//matcher->match(descriptors1, descriptors2, matches1);
		matcher->match(local_syn_descriptor, local_real_descriptor, matches1);
#ifdef DEBUG
		std::cout << "Matching features img1->img2 done. Matches: " << matches1.size() << std::endl;
#endif
		if(matches1.empty())
			continue;

#ifdef DEBUG
		std::cout << "Matching features img2->img1 ..." << std::endl;
#endif
		// from image 2 to image 1
		// based on k nearest neighbours (with k=2)
		std::vector<cv::DMatch> matches2;
		//matcher->match(descriptors2, descriptors1, matches2);
		matcher->match(local_real_descriptor, local_syn_descriptor, matches2);
#ifdef DEBUG
		std::cout << "Matching features img2->img1 done. Matches: " << matches2.size() << std::endl;
#endif
		if(matches2.empty())
			continue;

#ifdef DEBUG
		std::cout << "Symmetry-test ... " << std::endl;
#endif
		// 4. Remove non-symmetrical matches; returns synthetics -> real
		symmetryTest(matches1,matches2,localMatches);
		//cv::DMatch local_match;
		for(uint localIter = 0; localIter<localMatches.size(); localIter++)
		{
			cv::DMatch local_match = localMatches.at(localIter);
			local_match.queryIdx = mapping_d1.at(local_match.queryIdx).first;
			local_match.trainIdx = mapping_d2.at(local_match.trainIdx).first;
			symMatches.push_back(local_match);
		}
#ifdef DEBUG
		std::cout << "points in constraint " << constraint_iter << " left: " << localMatches.size() << std::endl;
#endif /* DEBUG */
	}

	// from here on unify matches and continue with the check

#ifdef DEBUG
	std::cout << "Homography-test ... " << std::endl;
#endif
	// 5. Validate matches using RANSAC
	cv::Mat fundemental= ransacTest(symMatches,keypoints1, keypoints2, matches);
	// return the found fundemental matrix
	return fundemental;
}
