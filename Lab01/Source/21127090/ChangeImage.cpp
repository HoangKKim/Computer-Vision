#include "function.h"

void convertRGBToGray(Mat inputImg, Mat& resImg) {

	resImg.create(inputImg.size(), CV_8UC1);

	// get width and heigt of image
	int width = inputImg.cols, height = inputImg.rows;

	// number of Image's channels
	int nChannels = inputImg.channels();
	int resChannels = resImg.channels();

	for (int i = 0; i < height; i++) {
		// get the pointer to the first element of y-th row: dua con tro den ptu dau tien cua dong thu y
		uchar* pRow = inputImg.ptr<uchar>(i);
		uchar* res_pRow = resImg.ptr<uchar>(i);

		// traverse each element in the row
		for (int j = 0; j < width; j++, pRow += nChannels, res_pRow += resChannels) {
			uchar gray = pRow[2] * 0.299 + pRow[1] * 0.587 + pRow[0] * 0.114;

			// assign gray value for the output image
			res_pRow[0] = gray;
		}
	}
}

void changeBrightness(Mat inputImg, Mat& resImg, float brightnessFactor) {

	resImg.create(inputImg.size(), CV_8UC3);

	int width = inputImg.cols, height = inputImg.rows;
	int nChannels = inputImg.channels();

	for (int i = 0; i < height; i++) {
		uchar* pRow = inputImg.ptr<uchar>(i);
		uchar* res_pRow = resImg.ptr<uchar>(i);

		for (int j = 0; j < width; j++, pRow += nChannels, res_pRow += nChannels) {
			for (int k = 0; k < 3; k++) {
				if (pRow[k] + brightnessFactor > 255) {
					res_pRow[k] = 255;
				}
				else if (pRow[k] + brightnessFactor < 0) {
					res_pRow[k] = 0;
				}
				else res_pRow[k] = pRow[k] + brightnessFactor;
			}
		}

	}
}

void changeContrast(Mat inputImg, Mat& resImg, float contrastFactor) {

	resImg.create(inputImg.size(), CV_8UC3);

	int width = inputImg.cols, height = inputImg.rows;
	int nChannels = inputImg.channels();

	for (int i = 0; i < height; i++) {
		uchar* pRow = inputImg.ptr<uchar>(i);
		uchar* res_pRow = resImg.ptr<uchar>(i);

		for (int j = 0; j < width; j++, pRow += nChannels, res_pRow += nChannels) {
			for (int k = 0; k < 3; k++) {
				if (pRow[k] * contrastFactor > 255) {
					res_pRow[k] = 255;
				}
				else if (pRow[k] * contrastFactor < 0) {
					res_pRow[k] = 0;
				}
				else res_pRow[k] = pRow[k] * contrastFactor;
			}
		}
	}
}

