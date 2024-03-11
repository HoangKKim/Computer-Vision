#pragma once

#include "stdio.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>

using namespace cv;
using namespace std;

Mat harrisDetector(Mat img);
Mat multiplyMat(Mat matrixA, Mat matrixB);
Mat sumMat(Mat matrixA, Mat matrixB);
Mat subtractMat(Mat matrixA, Mat matrixB);
Mat myConvolution(Mat matrix, int kSize, std::vector<std::vector<double>> kernel);
void gradientBySobel(Mat inputMatrix, Mat& restMatrix, int axisX, int axisY);
bool isLocalMaxima(Mat matrix, int rowIndex, int colIndex, float checkingValue);

