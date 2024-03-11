#include "function.h"

int main(int argc, char* argv[])
{
	// run the code without any parameter
	if (argc == 1) {
		std::cout << "Invalid manipulation! \nPlease read User Guide to run the code properly.";
		return 0;
	}

	// get strings from argv
	String inputPathFile = argv[2];
	String outputPathFile = argv[3];
	String requirement = argv[1];

	// read the input image from file
	Mat colorImg = imread(inputPathFile, IMREAD_COLOR);
	Mat grayImg = imread(inputPathFile, IMREAD_GRAYSCALE);

	// create a Mat that contains the result image
	Mat resImg;

	// check the requirement to call the corresponding function
	if (requirement == "-rgb2gray") {			// convert color image to gray image
		
		convertRGBToGray(colorImg, resImg);
	}
	else if (requirement == "-brightness") {	// change the brightness in color image
		
		double brightFactor = std::stod(argv[4]);
		changeBrightness(colorImg, resImg, brightFactor);
	}
	else if (requirement == "-contrast") {		// change the contrast in color image
		
		double contrastFactor = std::stod(argv[4]);
		changeContrast(colorImg, resImg, contrastFactor);
	}
	else if (requirement == "-avg") {			// filter the grayscale image with average method

		int kernelSize = std::stod(argv[4]);
		avgFilter(grayImg, resImg, kernelSize);
	}
	else if (requirement == "-med") {			// filter the grayscale image with median method
		
		int kernelSize = std::stod(argv[4]);
		medianFilter(grayImg, resImg, kernelSize);
	}
	else if (requirement == "-gau") {			// filter the grayscale image with gaussian kernel

		int kernelSize = std::stod(argv[4]);
		gaussianFilter(grayImg, resImg, kernelSize);
	}
	else if (requirement == "-sobel") {			// detect edge with the grayscale image with sobel

		detectBySobel(grayImg, resImg);
	}
	else if (requirement == "-laplace") {		// detect edge with the grayscale image with laplace

		detectByLaplace(grayImg, resImg);
	}
	else {
		std::cout << "Invalid requirement";
		return 0;
	}


	imshow("Result Image", resImg);
	String fileName = outputPathFile;
	imwrite(fileName, resImg);

	waitKey(0);

	return 0;

}