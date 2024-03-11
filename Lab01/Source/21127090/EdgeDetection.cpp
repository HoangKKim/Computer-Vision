#include "function.h"

void detectBySobel(Mat grayImg, Mat& resImg) {
    grayImg.copyTo(resImg);

    std::vector<std::vector<double>> sobelMaskX = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} };
    std::vector<std::vector<double>> sobelMaskY = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };
    int nChannels = grayImg.channels();
    int width = grayImg.cols, height = grayImg.rows;

    Mat sobelByX = myConvolution(grayImg, 3, sobelMaskX);
    Mat sobelByY = myConvolution(grayImg, 3, sobelMaskY);

    for (int i = 0; i < height; i++) {
        uchar* pRow = resImg.ptr<uchar>(i);
        uchar* pRow_X = sobelByX.ptr<uchar>(i);
        uchar* pRow_Y = sobelByY.ptr<uchar>(i);
        for (int j = 0; j < width; j++, pRow += nChannels, pRow_X += nChannels, pRow_Y += nChannels) {
            pRow[0] = abs(pRow_X[0]) + abs(pRow_Y[0]);
        }
    }
}

void detectByLaplace(Mat grayImg, Mat& resImg) {
    grayImg.copyTo(resImg);

    std::vector<std::vector<double>> laplacianMask = { {1, 1, 1}, {1, -8, 1}, {1, 1, 1} };

    resImg = myConvolution(grayImg, 3, laplacianMask);

}