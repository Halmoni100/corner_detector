#define BOOST_TEST_MODULE corner_detector
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <opencv2/opencv.hpp>
#include "cornerDetector.h"

struct HarrisResponseFixture
{
	HarrisResponseFixture() :
		initSize(10,10),
		imgDepth(CV_8U)
	{
	  blankImg = cv::Mat::zeros(initSize, imgDepth);
		solidImg = cv::Mat::ones(initSize, imgDepth);
	}
	cv::Size initSize; 
	int imgDepth;
  cv::Mat blankImg;
  cv::Mat solidImg;

	void testWithinTolerance(float testVal, float truthVal, float tolerance)
	{
		bool withinTolerance = abs(testVal - truthVal) < tolerance;
		BOOST_TEST(withinTolerance);
	}

};

BOOST_FIXTURE_TEST_CASE( blank_image, HarrisResponseFixture )
{
  float harrisResponse = getHarrisResponse(blankImg);
  //float truth_harrisResponse(0,0);
	std::cout << "Harris response for blank image: " << harrisResponse << std::endl;
}  

BOOST_FIXTURE_TEST_CASE( solid_image, HarrisResponseFixture )
{
  float harrisResponse = getHarrisResponse(solidImg);
  //float truth_harrisResponse(0,0);
	std::cout << "Harris response for solid image: " << harrisResponse << std::endl;
}  

BOOST_FIXTURE_TEST_CASE( vertical_split_image, HarrisResponseFixture )
{
  cv::Mat verticalSplitImg = blankImg.clone();
  cv::Mat rightSide = verticalSplitImg.colRange(5,10);
  rightSide = cv::Mat::ones(cv::Size(5,10),imgDepth);
  float harrisResponse = getHarrisResponse(verticalSplitImg);
  //float truth_harrisResponse(0,320);
	std::cout << "Harris response for vertical split image: " << harrisResponse << std::endl;
}  

BOOST_FIXTURE_TEST_CASE( horizontal_split_image, HarrisResponseFixture )
{
  cv::Mat horizontalSplitImg = blankImg.clone();
  cv::Mat bottomSide = horizontalSplitImg.rowRange(5,10);
  bottomSide = cv::Mat::ones(cv::Size(10,5),imgDepth);
  float harrisResponse = getHarrisResponse(horizontalSplitImg);
  //float truth_harrisResponse(0,320);
	std::cout << "Harris response for horizontal split image: " << harrisResponse << std::endl;
}

BOOST_FIXTURE_TEST_CASE( corner_image, HarrisResponseFixture )
{
	cv::Mat cornerImg = blankImg.clone();
	cv::Mat corner = cornerImg.colRange(5,10).rowRange(5,10);
	corner = cv::Mat::ones(cv::Size(5,5),imgDepth);
	float harrisResponse = getHarrisResponse(cornerImg);
  //float truth_harrisResponse(132,164);
	std::cout << "Harris response for corner image: " << harrisResponse << std::endl;
}
