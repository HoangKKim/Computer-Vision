#include "function.h"

Mat myConvolution(Mat img, int kSize, std::vector<std::vector<double>> kernel) {
    int padding = (kSize - 1) / 2;
    int width = img.cols, height = img.rows;

    //Mat resImg(img.size(), CV_8UC1, Scalar(0));  // Use the same type as the input image
    Mat resImg;
    // copy the content from the input image
    img.copyTo(resImg);

    // Retrieve pixel in img
    for (int i = padding; i < height - padding; i++) {
        for (int j = padding; j < width - padding; j++) {

            // Retrieve element in kernel
            double sum = 0;
            for (int m = 0; m < kSize; m++) {
                for (int n = 0; n < kSize; n++) {
                    sum += img.at<uchar>(i + m - padding, j + n - padding) * kernel[m][n];
                }
            }

            // clip the value for each pixel from 0 to 255
            if (sum < 0) {
                resImg.at<uchar>(i, j) = (uchar)0;
            }
            else if (sum > 255) {
                resImg.at<uchar>(i, j) = (uchar)255;
            }
            else
                resImg.at<uchar>(i, j) = (uchar)sum;
            //resImg.at<uchar>(i, j) = saturate_cast<uchar>(sum / (kSize * kSize));  // Average the sum
        }
    }
    return resImg;
}

std::vector<std::vector<double>> generateGaussianKernel(int kSize) {

    std::vector<std::vector<double>> gaussianKernel;

    // initializing standard deviation to 1.0 
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization 
    double sum = 0.0;

    int index = (kSize - 1) / 2;

    // generating kxk kernel 
    for (int x = -index; x <= index; x++) {
        std::vector<double> row;
        for (int y = -index; y <= index; y++) {
            r = sqrt(x * x + y * y);
            row.push_back((exp(-(r * r) / s)) / (M_PI * s));
            sum += row.back();
        }
        gaussianKernel.push_back(row);
    }

    // normalizing the Kernel 
    for (size_t i = 0; i < gaussianKernel.size(); ++i)
        for (size_t j = 0; j < gaussianKernel[i].size(); ++j)
            gaussianKernel[i][j] /= sum;

    return gaussianKernel;
}

void avgFilter(Mat grayImg, Mat& resImg, int kernelSize) {

    double value = 1.0 / (kernelSize * kernelSize);
    // Create a 2D vector (matrix) with size kernelSize x kernelSize and initialize with the value 1
    std::vector<std::vector<double>> mask(kernelSize, std::vector<double>(kernelSize, value));

    resImg = myConvolution(grayImg, kernelSize, mask);
}

void gaussianFilter(Mat grayImg, Mat& resImg, int kernelSize) {
    std::vector<std::vector<double>> gaussianKernel = generateGaussianKernel(kernelSize);

    resImg = myConvolution(grayImg, kernelSize, gaussianKernel);
}

void medianFilter(Mat grayImg, Mat& resImg, int kernelSize) {
    int width = grayImg.cols, height = grayImg.rows;
    int padding = (kernelSize - 1) / 2;
    int center = ((kernelSize * kernelSize) - 1) / 2;

    grayImg.copyTo(resImg);


    for (int i = padding; i < height - padding; i++) {
        for (int j = padding; j < width - padding; j++) {

            // use kernel kxk 
            std::vector<uchar> flattenImg;
            for (int m = 0; m < kernelSize; m++) {
                for (int n = 0; n < kernelSize; n++) {
                    flattenImg.push_back(grayImg.at<uchar>(i + m - padding, j + n - padding));
                }
            }
            //for (int k = 0; k < flattenImg.size(); k++) {
            //    std::cout << flattenImg[i];
            //}
            //std::cout << std::endl;
            std::sort(flattenImg.begin(), flattenImg.end());

            resImg.at<uchar>(i, j) = flattenImg[center];
        }
    }
}