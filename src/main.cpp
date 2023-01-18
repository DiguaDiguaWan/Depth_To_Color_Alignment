/*  create by digua   */

#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include "opencv2/opencv.hpp"
#include "DepthToColorAlignment/DepthToColorAlignment.h"

std::string depfile = "./data/image/depth/1673668318870_depth.png";
std::string rgbfile = "./data/image/rgb/1673668318854_color.png";

std::string intrinsicsfile = "./data/camera/intrinsics.yml";
std::string extrinsicsfile = "./data/camera/extrinsics.yml";



int main()
{

    cv::Mat rgb = cv::imread(rgbfile);
    cv::Mat dep = cv::imread(depfile, -1);
    cv::Mat dep_d2c;

//    cv::FileStorage intrinsics;
//    cv::Mat cameraMatrix[2], distCoeffs[2];
//    intrinsics.open(intrinsicsfile, cv::FileStorage::READ);
//    if (intrinsics.isOpened())
//    {
//        intrinsics["M1"] >> cameraMatrix[0];
//        intrinsics["D1"] >> distCoeffs[0];
//        intrinsics["M2"] >> cameraMatrix[1];
//        intrinsics["D2"] >> distCoeffs[1];
//        intrinsics.release();
//    }
//    cv::Mat rgb_un,dep_un;
//    cv::undistort(rgb, rgb_un, cameraMatrix[0], distCoeffs[0]);
//    cv::undistort(dep, dep_un, cameraMatrix[1], distCoeffs[1]);

    D2C D2C(extrinsicsfile,intrinsicsfile);
    D2C.D2C_remap(dep,dep_d2c,0);
    cv::imshow("dep",dep*34);
    cv::imshow("dep_d2c",dep_d2c*34);
    cv::imshow("rgb",rgb);
    cv::waitKey(0);



    return 0;
}