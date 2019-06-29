#pragma once

#include <opencv2/opencv.hpp>

std::pair<float, float> getEigenvaluesOfGradientCovariance(const cv::Mat& image_gray);
float getHarrisResponse(const cv::Mat& image_gray, float k=0.04);
