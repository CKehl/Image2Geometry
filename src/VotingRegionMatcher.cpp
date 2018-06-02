/*
 * VotingRegionMatcher.cpp
 *
 *  Created on: Jan 12, 2016
 *      Author: christian
 */

#include "VotingRegionMatcher.h"

VotingRegionMatcher::VotingRegionMatcher() : ratio(1.0), refineF(true), confidence(0.99), distance(3.0), syn_total_points(0), real_total_points(0) {
	// TODO Auto-generated constructor stub
	// ORB is the default feature
	detector= new cv::OrbFeatureDetector();
	extractor= new cv::OrbDescriptorExtractor();
	matcher= new cv::BFMatcher(cv::NORM_HAMMING2, true);
}

VotingRegionMatcher::~VotingRegionMatcher() {
	// TODO Auto-generated destructor stub
}

void VotingRegionMatcher::symmetryTest(const std::vector<cv::DMatch>& matches1, const std::vector<cv::DMatch>& matches2, std::vector<cv::DMatch>& symMatches)
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

cv::Mat VotingRegionMatcher::ransacTest(const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches)
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

cv::Mat VotingRegionMatcher::match(cv::Mat& image1, cv::Mat& image2, std::vector<cv::DMatch>& matches, std::vector<cv::KeyPoint>& keypoints1, std::vector<cv::KeyPoint>& keypoints2, uint max_matches)
{
	if(max_matches==0)
		max_matches=UINT_MAX;
	// 1a. Detection of the SURF features
#ifdef DEBUG
	std::cout << "Feature Detection ... " << std::endl;
#endif
	std::vector<cv::KeyPoint> kp1, kp2;

	detector->detect(image1,kp1);
	detector->detect(image2,kp2);
	if( kp1.empty() || kp2.empty() )
		return cv::Mat();

	std::vector<cv::KeyPoint> regions1, regions2;
	cv::Ptr<cv::MSER> region_detect = new cv::MSER(3, 6000, 400000, 0.3, 0.2, 255, 1.01, 0.003, 7);
	region_detect->detect(image1, regions1, cv::Mat());
	region_detect->detect(image2, regions2, cv::Mat());
	std::vector<uint> PtToReg1, PtToReg2;
	std::vector<uint> regionSize1(regions1.size(),0);
	//std::vector<uint> regionSize2(regions2.size(),0);
	uint current_id = 0; cv::Point2f D;
//#ifdef DEBUG
//	for(uint i = 0; i < regions1.size(); i++)
//	{
//		std::cout<<"Angle "<<regions1.at(i).angle<<" Size "<<regions1.at(i).size<<" Center ("<<regions1.at(i).pt.x<<","<<regions1.at(i).pt.y<<")"<<std::endl;
//	}
//#endif
	for(uint i = 0; i < kp1.size(); i++)
	{
		current_id = regions1.size()+1;
		for(uint j = 0; j < regions1.size(); j++)
		{
			D = kp1.at(i).pt-regions1.at(j).pt;
			if((D.x*D.x+D.y*D.y) < (regions1.at(j).size*regions1.at(j).size))
			{
				current_id = j;
				break;
			}
		}
		if((current_id < regions1.size()) && (keypoints1.size()<max_matches))
		{
			PtToReg1.push_back(current_id);
			keypoints1.push_back(kp1.at(i));
			regionSize1.at(current_id)++;
		}
	}
	kp1.clear();
#ifdef DEBUG
	std::cout << "Keypoints 1: "<<keypoints1.size()<<std::endl;
#endif
	for(uint i = 0; i < kp2.size(); i++)
	{
		current_id = regions2.size()+1;
		for(uint j = 0; j < regions2.size(); j++)
		{
			D = kp2.at(i).pt-regions2.at(j).pt;
			if((D.x*D.x+D.y*D.y) < (regions2.at(j).size*regions2.at(j).size))
			{
				current_id = j;
				break;
			}
		}
		if((current_id < regions2.size()) && (keypoints2.size()<max_matches))
		{
			PtToReg2.push_back(current_id);
			keypoints2.push_back(kp2.at(i));
			//regionSize2.at(current_id)++;
		}
	}
	kp2.clear();
#ifdef DEBUG
	std::cout << "Keypoints 2: "<<keypoints2.size()<<std::endl;
#endif

#ifdef DEBUG
	std::cout << "Feature Description ... " << std::endl;
#endif
	// 1b. Extraction of the descriptors
	cv::Mat descriptors1, descriptors2;
	extractor->compute(image1,keypoints1,descriptors1);
#ifdef DEBUG
	std::cout << "FD syn done ... " << std::endl;
#endif
	extractor->compute(image2,keypoints2,descriptors2);
#ifdef DEBUG
	std::cout << "FD real done ... " << std::endl;
#endif
#ifdef DEBUG
	std::cout << "vector sizes: img1 - " << descriptors1.rows << "x" <<descriptors1.cols << ", img2 - " << descriptors2.rows << "x" << descriptors2.cols << ", type: " << type2str(descriptors1.type()) << " ... " << std::endl;
#endif
	if( (descriptors1.rows == 0) || (descriptors1.cols == 0) || (descriptors2.rows == 0) || (descriptors2.cols == 0) )
		return cv::Mat();
	if( (descriptors1.rows < 2) || (descriptors2.rows < 2) )
		return cv::Mat();



	// 2. Match the two image descriptors
	// Construction of the matcher
	//cv::BruteForceMatcher<cv::L2<float>> matcher;
#ifdef DEBUG
	std::cout << "Matching features img1->img2 ..." << std::endl;
#endif
	// from image 1 to image 2
	// based on k nearest neighbours (with k=2)
	std::vector<cv::DMatch> matches1;
	matcher->match(descriptors1, descriptors2, matches1);
#ifdef DEBUG
	std::cout << "Matches img1->img2:" << matches1.size() << std::endl;
#endif
	if(matches1.empty())
		return cv::Mat();

#ifdef DEBUG
	std::cout << "Matching features img2->img1 ..." << std::endl;
#endif
	// from image 2 to image 1
	// based on k nearest neighbours (with k=2)
	std::vector<cv::DMatch> matches2;
	matcher->match(descriptors2, descriptors1, matches2);
#ifdef DEBUG
	std::cout << "Matches img2->img1:" << matches2.size() << std::endl;
#endif
	if(matches2.empty())
		return cv::Mat();

#ifdef DEBUG
	std::cout << "Symmetry-test ... " << std::endl;
#endif
	// 4. Remove non-symmetrical matches
	std::vector<cv::DMatch> symMatches;
	symmetryTest(matches1,matches2,symMatches);
	if(symMatches.empty())
		return cv::Mat();
	matches1.clear();
	matches2.clear();
#ifdef DEBUG
	std::cout << "Matches:" << symMatches.size() << std::endl;
#endif

#ifdef DEBUG
	std::cout << "Region test ..." << std::endl;
#endif
	//Matrix rows - regions1; cols - regions2; shows how many pts in region1 match to region2 (per entry)
	cv::Mat correspondence(regions1.size(), regions2.size(), CV_16U);
	uint row, col;
	for(uint i = 0; i < symMatches.size(); i++)
	{
		row = PtToReg1.at(symMatches.at(i).queryIdx);
		col = PtToReg2.at(symMatches.at(i).trainIdx);
		correspondence.at<ushort>(row,col) +=1;
	}

	std::vector< std::pair<uint, ushort> > _support_vec;
	ushort max_support = 0; uint max_idx = 0;
	for(uint i = 0; i < regions1.size(); i++)
	{
		max_idx = 0; max_support = 0;
		for(uint j = 0; j < regions2.size(); j++)
		{
			if(correspondence.at<ushort>(i,j) > max_support)
			{
				max_idx = j; max_support = correspondence.at<ushort>(i,j);
			}
		}
		_support_vec.push_back(std::pair<uint, ushort>(max_idx, max_support));
	}

	std::vector<cv::DMatch> regionMatches;
	for(uint i=0; i < symMatches.size(); i++)
	{
		row = PtToReg1.at(symMatches.at(i).queryIdx);
		col = PtToReg2.at(symMatches.at(i).trainIdx);
		if((_support_vec.at(row).first == col) && (_support_vec.at(row).second >= nearbyint(0.7*regionSize1.at(row))))
		{
			regionMatches.push_back(symMatches.at(i));
		}
	}
	symMatches.clear();
#ifdef DEBUG
	std::cout << "Matches:" << symMatches.size() << std::endl;
#endif

#ifdef DEBUG
	std::cout << "Homography-test ... " << std::endl;
#endif
	// 5. Validate matches using RANSAC
	cv::Mat fundemental= ransacTest(regionMatches,keypoints1, keypoints2, matches);
#ifdef DEBUG
	std::cout << "Matches:" << matches.size() << std::endl;
#endif
	// return the found fundemental matrix
	return fundemental;
}


