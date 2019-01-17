/*
 * OneWayRobustMatcher.cpp
 *
 *  Created on: Feb 12, 2016
 *      Author: christian
 */

#include "OneWayRobustMatcher.h"

OneWayRobustMatcher::OneWayRobustMatcher() : ratio(0.65f), refineF(false), confidence(0.99), distance(1.0)
{
	// ORB is the default feature
	detector= new cv::OrbFeatureDetector();
	extractor= new cv::OrbDescriptorExtractor();
	matcher= new cv::BFMatcher(cv::NORM_HAMMING2, true);
	inliers_ref = std::vector<int>();
	inliers_syn = std::vector<int>();
}

OneWayRobustMatcher::~OneWayRobustMatcher() {
	// TODO Auto-generated destructor stub
}

int OneWayRobustMatcher::ratioTest(std::vector<std::vector<cv::DMatch> > &matches)
{
	int removed=0;
	// for all matches
	for (std::vector<std::vector<cv::DMatch> >::iterator matchIterator= matches.begin(); matchIterator!= matches.end(); ++matchIterator)
	{
		// if 2 NN has been identified
		if (matchIterator->size() > 1) {
			// check distance ratio
			if( ((*matchIterator)[0].distance <= FLT_MIN) || ((*matchIterator)[1].distance <= FLT_MIN) )
				continue;
			float d = std::min(((*matchIterator)[0].distance / (*matchIterator)[1].distance), ((*matchIterator)[1].distance / (*matchIterator)[0].distance));
			if (d > ratio) {
				matchIterator->clear(); // remove match
				removed++;
			}
		} else { // does not have 2 neighbours
			matchIterator->clear(); // remove match
			removed++;
		}
	}
	return removed;
}

void OneWayRobustMatcher::symmetryTest(const std::vector<std::vector<cv::DMatch> >& matches1, const std::vector<std::vector<cv::DMatch> >& matches2, std::vector<cv::DMatch>& symMatches)
{
    // for all matches image 1 -> image 2
    for (std::vector<std::vector<cv::DMatch> >::const_iterator matchIterator1= matches1.begin();matchIterator1!= matches1.end(); ++matchIterator1) {
    	// ignore deleted matches
    	if (matchIterator1->size() < 2)
    		continue;
    	// for all matches image 2 -> image 1
    	for (std::vector<std::vector<cv::DMatch> >::const_iterator matchIterator2= matches2.begin(); matchIterator2!= matches2.end(); ++matchIterator2) {
    		// ignore deleted matches
    		if (matchIterator2->size() < 2)
    			continue;
    		// Match symmetry test
    		if ( (*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx && (*matchIterator2)[0].queryIdx ==(*matchIterator1)[0].trainIdx) {
    			// add symmetrical match
    			symMatches.push_back(cv::DMatch((*matchIterator1)[0].queryIdx, (*matchIterator1)[0].trainIdx, (*matchIterator1)[0].distance));
    			break; // next match in image 1 -> image 2
    		}
    	}
    }
}

bool OneWayRobustMatcher::trim(std::vector<cv::DMatch>& matches_inPlace)
{
	if(matches_inPlace.empty())
		return false;
	std::sort(matches_inPlace.begin(), matches_inPlace.end(), CompareQueryID);
	uint _iterator = 1;
	int _currentId = matches_inPlace.at(0).queryIdx;
	int found = false;
	while(_iterator < matches_inPlace.size())
	{
		if(matches_inPlace.at(_iterator).queryIdx != _currentId)
		{
			_currentId = matches_inPlace.at(_iterator).queryIdx;
			_iterator++;
		}
		else
		{
			std::vector<cv::DMatch>::iterator rmIterator = matches_inPlace.begin()+size_t(_iterator);
			matches_inPlace.erase(rmIterator);
		}
	}
	return true;
}

bool OneWayRobustMatcher::trim(const std::vector<cv::DMatch>& matches_in, std::vector<cv::DMatch>& matches_out)
{
	if(matches_in.empty())
		return false;
	std::vector<cv::DMatch>& nconst_matches_in = const_cast<std::vector<cv::DMatch>&>(matches_in);
	std::sort(nconst_matches_in.begin(), nconst_matches_in.end(), CompareQueryID);
	uint _iterator = 1;
	int _currentId = nconst_matches_in.at(0).queryIdx;
	int found = false;
	while(_iterator < nconst_matches_in.size())
	{
		if(nconst_matches_in.at(_iterator).queryIdx != _currentId)
		{
			matches_out.push_back(nconst_matches_in.at(_iterator-1));
			_currentId = nconst_matches_in.at(_iterator).queryIdx;
			found = false;
		}
		else
		{
			found = true;
		}
		_iterator++;
	}
	return true;
}

/*
 * Copies only matches with a unique match in keypoints2 field
 */
bool OneWayRobustMatcher::RemoveDistractors(const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches)
{
	if(matches.empty())
		return false;

	std::vector<cv::DMatch>& nconst_matches = const_cast<std::vector<cv::DMatch>&>(matches);
	std::sort(nconst_matches.begin(), nconst_matches.end(), CompareTrainID);
	uint _iterator = 1;
	int _currentId = nconst_matches.at(0).trainIdx;
	int found = false;
	while(_iterator < nconst_matches.size())
	{
		if(nconst_matches.at(_iterator).trainIdx != _currentId)
		{
			if(!found)
				outMatches.push_back(nconst_matches.at(_iterator-1));
			_currentId = nconst_matches.at(_iterator).trainIdx;
			found = false;
		}
		else
		{
			found = true;
		}
		_iterator++;
	}
	return true;
}

cv::Mat OneWayRobustMatcher::ransacTest(const std::vector< std::vector<cv::DMatch> >& matches, const std::vector<cv::KeyPoint>& keypoints1, const std::vector<cv::KeyPoint>& keypoints2, std::vector<cv::DMatch>& outMatches)
{
	// Convert keypoints into Point2f
	uint subitemsize = 1;
	std::vector<cv::Point2f> points1, points2;
	cv::Mat fundemental;
	for (std::vector< std::vector<cv::DMatch>>:: const_iterator it= matches.begin(); it!= matches.end(); ++it) {
		//subitemsize = it->size();
		//for(uint subiterator = 0; subiterator < (it->size()); subiterator++)
		for (std::vector<cv::DMatch>::const_iterator sub_it= (*it).begin(); sub_it!= (*it).end(); ++sub_it) {
			//cv::DMatch* subitem = &(it->at(subiterator));
			const cv::DMatch* subitem = &(*sub_it);

			// Get the position of left keypoints
			float x= keypoints1[subitem->queryIdx].pt.x;
			float y= keypoints1[subitem->queryIdx].pt.y;
			points1.push_back(cv::Point2f(x,y));
			// Get the position of right keypoints
			x= keypoints2[subitem->trainIdx].pt.x;
			y= keypoints2[subitem->trainIdx].pt.y;
			points2.push_back(cv::Point2f(x,y));
		}
	}
	// Compute F matrix using RANSAC
	std::vector<uchar> inliers(points1.size(),0);
	if (points1.size()>0&&points2.size()>0){
		cv::Mat fundemental= cv::findFundamentalMat(cv::Mat(points1),cv::Mat(points2), // matching points
				inliers,       // match status (inlier or outlier)
				CV_FM_RANSAC, // RANSAC method
				distance,      // distance to epipolar line
				confidence); // confidence probability

		for(uint inlier_iterator = 0; inlier_iterator < inliers.size(); inlier_iterator++)
		{
			uint head_index = uint(inlier_iterator/subitemsize);
			uint sub_index  = uint(inlier_iterator%subitemsize);
			if(inliers.at(inlier_iterator))
			{
				outMatches.push_back(matches.at(head_index).at(sub_index));
	            inliers_syn.push_back(outMatches[outMatches.size()-1].queryIdx);
	            inliers_ref.push_back(outMatches[outMatches.size()-1].trainIdx);
			}
		}
	}
	return fundemental;
}

cv::Mat OneWayRobustMatcher::match(cv::Mat& image1, cv::Mat& image2, std::vector<cv::DMatch>& matches, std::vector<cv::KeyPoint>& keypoints1, std::vector<cv::KeyPoint>& keypoints2)
{
	// 1a. Detection of the SURF features
#ifdef DEBUG
	std::cout << "Feature Detection ... " << std::endl;
#endif
	detector->detect(image1,keypoints1);
	detector->detect(image2,keypoints2);
	if( keypoints1.empty() || keypoints2.empty() )
		return cv::Mat();

#ifdef DEBUG
	std::cout << "Feature Description ... " << std::endl;
#endif
	// 1b. Extraction of the SURF descriptors
	cv::Mat descriptors1, descriptors2;
	extractor->compute(image1,keypoints1,descriptors1);
	extractor->compute(image2,keypoints2,descriptors2);
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
	std::vector<std::vector<cv::DMatch> > matches1;
	matcher->knnMatch(descriptors1, descriptors2, matches1, 2);
	if(matches1.empty())
		return cv::Mat();

#ifdef DEBUG
	std::cout << "Ratio-test ... " << std::endl;
#endif
	// 3. Remove matches for which NN ratio is
	// > than threshold
	// clean image 1 -> image 2 matches
	// int removed= ratioTest(matches1);
#ifdef DEBUG
	//std::cout << "Ratio-Test removed " << removed << " matches ..." << std::endl;
#endif

#ifdef DEBUG
	std::cout << "Homography-test ... " << std::endl;
#endif
	// 5. Validate matches using RANSAC
	std::vector<cv::DMatch> homographicMatches;
	cv::Mat fundemental= ransacTest(matches1,keypoints1, keypoints2, homographicMatches);
	// return the found fundemental matrix



	bool uniqueSuccess = RemoveDistractors(homographicMatches,keypoints1,keypoints2,matches);
	if((uniqueSuccess==false) || (homographicMatches.empty()))
	{
		std::cout << "No points left." << std::endl;
		return cv::Mat();
	}
	trim(matches);

	return fundemental;
}





