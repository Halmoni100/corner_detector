#include <assert.h>
#include <opencv2/imgproc.hpp>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include "corner_detector.h"

std::pair<float, float> getEigenvaluesOfGradientCovariance(const cv::Mat& image_gray)
{
  Eigen::Matrix2f grad_covariance = getGradientCovariance(image_gray);
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix2f> eigensolver;
  eigensolver.compute(grad_covariance);

  std::pair<float, float> eigenvalues(eigensolver.eigenvalues()(0), eigensolver.eigenvalues()(1));

  return eigenvalues;
}

float getHarrisResponse(const cv::Mat& image_gray)
{
  Eigen::Matrix2f grad_covariance = getGradientCovariance(image_gray);
  
  float determinant = grad_covariance.
}
Eigen::Matrix2f getGradientCovariance(const cv::Mat& image_gray)
{
  cv::Mat grad_x, grad_y;
  cv::Sobel(image_gray, grad_x, CV_32F, 1, 0);
  cv::Sobel(image_gray, grad_y, CV_32F, 0, 1);

  cv::Mat grad_x_square = grad_x.mul(grad_x); 
  float E_x_square = cv::sum(grad_x_square)[0];

  cv::Mat grad_y_square = grad_y.mul(grad_y); 
  float E_y_square = cv::sum(grad_y_square)[0];

  cv::Mat grad_x_grad_y = grad_x.mul(grad_y); 
  float E_x_E_y = cv::sum(grad_x_grad_y)[0];

  Eigen::Matrix2f grad_covariance;
  grad_covariance << E_x_square, E_x_E_y, E_x_E_y, E_y_square;
  
  return grad_covariance;
}
