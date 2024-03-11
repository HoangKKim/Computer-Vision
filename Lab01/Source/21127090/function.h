#pragma once
#include "stdio.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

# define M_PI           3.14159265358979323846

using namespace cv;

// point processing
void convertRGBToGray(Mat inputImg, Mat& resImg);
void changeBrightness(Mat inputImg, Mat& resImg, float brightnessFactor);
void changeContrast(Mat inputImg, Mat& resImg, float contrastFactor);

// pre-filtering
std::vector<std::vector<double>> generateGaussianKernel(int kSize);
Mat myConvolution(Mat img, int kSize, std::vector<std::vector<double>> kernel);

// filtering
void avgFilter(Mat grayImg, Mat& resImg, int kernelSize);
void gaussianFilter(Mat grayImg, Mat& resImg, int kernelSize);
void medianFilter(Mat grayImg, Mat& resImg, int kernelSize);

// edge detection
void detectBySobel(Mat grayImg, Mat& resImg);
void detectByLaplace(Mat grayImg, Mat& resImg);
