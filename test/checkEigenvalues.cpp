#define BOOST_TEST_MODULE corner_detector
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <opencv2/opencv.hpp>
#include "cornerDetector.h"

namespace tt = boost::unit_test;

struct ComputeEigenvaluesFixture
{
	ComputeEigenvaluesFixture() :
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

	void testEigenvalues(std::pair<float,float> testVal, std::pair<float,float> truthVal)
	{
		float tolerance = 0.001;
		testWithinTolerance(testVal.first, truthVal.first, tolerance);
		testWithinTolerance(testVal.second, truthVal.second, tolerance);
  }
};

BOOST_FIXTURE_TEST_CASE( blank_image, ComputeEigenvaluesFixture )
{
  std::pair<float,float> eigenvalues = getEigenvaluesOfGradientCovariance(blankImg.clone());
  std::pair<float,float> truth_eigenvalues(0,0);
	testEigenvalues(eigenvalues, truth_eigenvalues);
}  

BOOST_FIXTURE_TEST_CASE( solid_image, ComputeEigenvaluesFixture )
{
  std::pair<float,float> eigenvalues = getEigenvaluesOfGradientCovariance(solidImg);
  std::pair<float,float> truth_eigenvalues(0,0);
	testEigenvalues(eigenvalues, truth_eigenvalues);
}  

BOOST_FIXTURE_TEST_CASE( vertical_split_image, ComputeEigenvaluesFixture )
{
  cv::Mat verticalSplitImg = blankImg.clone();
  cv::Mat rightSide = verticalSplitImg.colRange(5,10);
  rightSide = cv::Mat::ones(cv::Size(5,10),imgDepth);
  std::pair<float,float> eigenvalues = getEigenvaluesOfGradientCovariance(verticalSplitImg);
  std::pair<float,float> truth_eigenvalues(0,320);
  testEigenvalues(eigenvalues, truth_eigenvalues);
}  

BOOST_FIXTURE_TEST_CASE( horizontal_split_image, ComputeEigenvaluesFixture )
{
  cv::Mat horizontalSplitImg = blankImg.clone();
  cv::Mat bottomSide = horizontalSplitImg.rowRange(5,10);
  bottomSide = cv::Mat::ones(cv::Size(10,5),imgDepth);
  std::pair<float,float> eigenvalues = getEigenvaluesOfGradientCovariance(horizontalSplitImg);
  std::pair<float,float> truth_eigenvalues(0,320);
  testEigenvalues(eigenvalues, truth_eigenvalues);
}

BOOST_FIXTURE_TEST_CASE( corner_image, ComputeEigenvaluesFixture )
{
	cv::Mat cornerImg = blankImg.clone();
	cv::Mat corner = cornerImg.colRange(5,10).rowRange(5,10);
	corner = cv::Mat::ones(cv::Size(5,5),imgDepth);
	std::pair<float,float> eigenvalues = getEigenvaluesOfGradientCovariance(cornerImg);
	std::pair<float,float> truth_eigenvalues(132,164);
	testEigenvalues(eigenvalues, truth_eigenvalues);
}
