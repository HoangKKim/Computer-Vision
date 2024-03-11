#include "function.h"

int main(int argc, char* argv[]) {
	if (argc == 1) {

		cout << "Invalid manipulation! \nPlease read User Guide to run the code properly.\n";
		return 0;
	}
	else if (argc < 4) {
		cout << "Invalid manipulation! \nPlease read User Guide to run the code properly.\n";
		return 0;
	}

	String requirement = argv[1];
	String inputPathFile = argv[2];
	String outputPathFile = argv[3];


	Mat colorImg = imread(inputPathFile, IMREAD_COLOR);
	Mat cornersByHarris;
	if (requirement == "-harris") {
		cornersByHarris = harrisDetector(colorImg);
	}
	else {
		cout << "Invalid requirement!";
		return 0;
	}

	imshow("Result", cornersByHarris);
	imwrite(outputPathFile, cornersByHarris);


	waitKey(0);
}
