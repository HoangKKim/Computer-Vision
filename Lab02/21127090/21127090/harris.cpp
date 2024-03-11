#include "function.h"

Mat harrisDetector(Mat img) {
	int width = img.cols, height = img.rows;
	double threshold, k = 0.04;
	Mat dstImg = img.clone();

	// convert img to grayscale
	Mat grayImg(img.size(), CV_8UC1);
	cvtColor(img, grayImg, COLOR_BGR2GRAY);

	// reduce noise by Gaussian 
	GaussianBlur(grayImg, grayImg, Size(5, 5), 0, 0);

	Mat Ix, Iy;
	// Compute the image gradient along the x and y direction using Sobel
	gradientBySobel(grayImg, Ix, 1, 0);
	gradientBySobel(grayImg, Iy, 0, 1);

	Mat A, B, C;
	// Compute the correlation between the derivatives 
	A = multiplyMat(Ix, Ix);
	B = multiplyMat(Ix, Iy);
	C = multiplyMat(Iy, Iy);

	// Construct matrix M 
	GaussianBlur(A, A, Size(5, 5), 0, 0);
	GaussianBlur(B, B, Size(5, 5), 0, 0);
	GaussianBlur(C, C, Size(5, 5), 0, 0);

	// Compute matrix R
	Mat mulAC = multiplyMat(A,C);
	Mat squaredB = multiplyMat(B, B);
	Mat detM = subtractMat(mulAC, squaredB);

	Mat traceM = sumMat(A,C);
	Mat squaredTraceM = multiplyMat(traceM, traceM);
	squaredTraceM *= k;

	Mat R = subtractMat(detM, squaredTraceM);

	// Set the threshold depend on R
	double maxValue;
	minMaxLoc(R, NULL, &maxValue);
	threshold = maxValue * 0.01;	

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (R.at<float>(i, j) > threshold && isLocalMaxima(R, i, j, R.at<float>(i,j))) {
				circle(dstImg, Point(j, i), 2, Scalar(0, 0, 255), -1);
			}
		} 
	} 

	return dstImg;
}

bool isLocalMaxima(Mat matrix, int rowIndex, int colIndex, float checkingValue) {

	// check the local maxima with the windown of 3x3 size 
	int padding = 1;

	if (rowIndex < padding ) {
		rowIndex += padding;
	}
	else if (rowIndex == matrix.rows - padding) {
		rowIndex -= padding;
	}

	if (colIndex < padding) {
		colIndex += padding;
	}
	else if (colIndex == matrix.cols - padding) {
		colIndex -= padding;
	}

	// create mask to check the local maxima
	for (int i = rowIndex - padding; i <= rowIndex + padding; i++) {
		for (int j = colIndex - padding; j <= colIndex + padding; j++) {
			if (checkingValue < matrix.at<float>(i, j)) {
				return false;
			}
		}
	}
	return true;
}