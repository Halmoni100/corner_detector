#pragma once

#include <opencv2/opencv.hpp>

std::pair<float, float> compute_eigenvalues_of_gradient_covariance(const cv::Mat& image);
