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

Mat objectDetection(Mat templateImg, Mat sceneImg);