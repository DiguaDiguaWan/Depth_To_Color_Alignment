//copyright 996261413@qq.com

#pragma once
#include "opencv2/calib3d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include <ctime>



class D2C {
public:
	D2C(std::string extrinsics_path, std::string intrinsics_path);

    void D2C_remap(cv::Mat &inputImage, cv::Mat &outputImage,int type);

private:

	cv::FileStorage extrinsics, intrinsics;

	cv::Mat R, T;

	cv::Mat cameraMatrix[2], distCoeffs[2];

};

