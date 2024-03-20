#include "function.h"

int main(int argc, char* argv[]) {
    // Load color images
    if (argc !=5) {
		cout << "Invalid manipulation! \nPlease read User Guide to run the code properly.\n";
		return 0;
	}

	String requirement = argv[1];
	String templateImagePath = argv[2];
	String sceneImagePath = argv[3];
	String outputFilePath = argv[4];


	Mat sceneImg = imread(sceneImagePath, IMREAD_COLOR);
	Mat templateImg = imread(templateImagePath, IMREAD_COLOR);
	Mat result, combinedImg;
	

	if (requirement == "-sift") {
		result= objectDetection(templateImg, sceneImg);
	}
	else {
		cout << "Invalid requirement!";
		return 0;
	}
	imshow("Object Detection Image", result);
	imshow("Template Image", templateImg);

	imwrite(outputFilePath, result);

    waitKey(0);
    return 0;
}
