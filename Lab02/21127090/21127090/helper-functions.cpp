#include "function.h"

Mat multiplyMat(Mat matrixA, Mat matrixB) {
	Mat resMatrix(matrixA.size(), CV_32FC1);

	int nChannels = matrixA.channels();
	int width = matrixA.cols, height = matrixA.rows;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			resMatrix.at<float>(i, j) = static_cast<float>(matrixA.at<float>(i, j) * matrixB.at<float>(i, j));
		}
	}
	return resMatrix;
}

Mat sumMat(Mat matrixA, Mat matrixB) {
	Mat resMatrix(matrixA.size(), CV_32FC1);

	int nChannels = matrixA.channels();
	int width = matrixA.cols, height = matrixA.rows;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			resMatrix.at<float>(i, j) = static_cast<float>(matrixA.at<float>(i, j) + matrixB.at<float>(i, j));
		}
	}
	return resMatrix;
}

Mat subtractMat(Mat matrixA, Mat matrixB) {
	Mat resMatrix(matrixA.size(), CV_32FC1);

	int nChannels = matrixA.channels();
	int width = matrixA.cols, height = matrixA.rows;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			resMatrix.at<float>(i, j) = static_cast<float>(matrixA.at<float>(i, j) - matrixB.at<float>(i, j));
		}
	}
	return resMatrix;
}

Mat myConvolution(Mat matrix, int kSize, std::vector<std::vector<double>> kernel) {
	int padding = (kSize - 1) / 2;
	int width = matrix.cols, height = matrix.rows;

	//Mat resImg(img.size(), CV_8UC1, Scalar(0));  // Use the same type as the input image
	Mat resMatrix(matrix.size(), CV_32FC1);



	// Retrieve pixel in img
	for (int i = padding; i < height - padding; i++) {
		for (int j = padding; j < width - padding; j++) {

			// Retrieve element in kernel
			double sum = 0;
			for (int m = 0; m < kSize; m++) {
				for (int n = 0; n < kSize; n++) {
					sum += matrix.at<uchar>(i + m - padding, j + n - padding) * kernel[m][n];
				}
			}

			// clip the value for each pixel from 0 to 255
			resMatrix.at<float>(i, j) = (sum / (kSize * kSize));  // Average the sum
		}
	}
	return resMatrix;
}

void gradientBySobel(Mat inputMatrix, Mat& resMatrix, int axisX, int axisY) {

	std::vector<std::vector<double>> sobelMaskX = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
	std::vector<std::vector<double>> sobelMaskY = { {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };

	if (axisX == 1 && axisY == 0) {
		resMatrix = myConvolution(inputMatrix, 3, sobelMaskX);
	}
	else if (axisX == 0 && axisY == 1) {
		resMatrix = myConvolution(inputMatrix, 3, sobelMaskY);
	}
}
