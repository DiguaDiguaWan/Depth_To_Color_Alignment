/*  create by digua   */

#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include "opencv2/opencv.hpp"
#include "DepthToColorAlignment/DepthToColorAlignment.h"

std::string depfile = "./data/image/depth/1673666759409_depth.png";
std::string rgbfile = "./data/image/rgb/1673666759391_color.png";

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

    //归一化
    cv::Mat dep_64f(dep.size(),CV_64FC1);
    dep_64f = dep_d2c.clone();
    double dep_max, dep_min;
    minMaxIdx(dep_64f, &dep_min, &dep_max);
    dep_64f = ((dep_64f - dep_min) / (dep_max - dep_min)) * 255;
    cv::Mat dep_verify(dep.size(), CV_8UC1);
    //转灰度
    dep_64f.convertTo(dep_verify, CV_8UC1);
    //rgb
    cv::Mat rgb_verify;
    cv::cvtColor(rgb, rgb_verify, cv::COLOR_BGR2GRAY);
    cv::Mat Mix;
    cv::addWeighted(rgb_verify, 0.5, dep_verify, 0.5, 0, Mix);


    cv::imshow("dep",dep*34);
    cv::imshow("dep_d2c",dep_d2c*34);
    cv::imshow("rgb",rgb);
    cv::imshow("mix",Mix);
    cv::waitKey(0);



    return 0;
}