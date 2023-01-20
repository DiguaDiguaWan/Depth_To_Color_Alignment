//copyright 996261413@qq.com

#include"DepthToColorAlignment.h"
#include "cmath"

D2C::D2C(std::string extrinsics_path, std::string intrinsics_path) {
    //读取内外参
    extrinsics.open(extrinsics_path, cv::FileStorage::READ);
    if (extrinsics.isOpened())
    {
        extrinsics["R"] >> R;
        extrinsics["T"] >> T;
        //if you using opencv calibrator , The R Matrix need be change.
        //R = R.inv();
        extrinsics.release();
    }

    intrinsics.open(intrinsics_path, cv::FileStorage::READ);
    if (intrinsics.isOpened())
    {
        intrinsics["M1"] >> cameraMatrix[0];
        intrinsics["D1"] >> distCoeffs[0];
        intrinsics["M2"] >> cameraMatrix[1];
        intrinsics["D2"] >> distCoeffs[1];
        intrinsics.release();
    }

}



// qyk's feat

void D2C::D2C_remap(cv::Mat &inputImage, cv::Mat &outputImage,int type) {


    cv::Point2f center = cv::Point2f(cameraMatrix[1].at<double>(0, 2), cameraMatrix[1].at<double>(1, 2));
    cv::Point2f center_rgb = cv::Point2f(cameraMatrix[0].at<double>(0, 2), cameraMatrix[0].at<double>(1, 2));
    cv::Point2f foc = cv::Point2f(cameraMatrix[1].at<double>(0, 0), cameraMatrix[1].at<double>(1, 1));
    cv::Point2f foc_rgb = cv::Point2f(cameraMatrix[0].at<double>(0, 0), cameraMatrix[0].at<double>(1, 1));
    outputImage=cv::Mat::zeros(inputImage.size(),CV_16UC1);


    for (int i = 0; i < inputImage.rows; i++)
    {
        uint16_t* ptr = inputImage.ptr<uint16_t>(i);

        for (int j = 0; j < inputImage.cols; j++) {


            cv::Point3d newPoint;
            //像素转换至点云
            newPoint.x = (j - center.x) * *ptr / foc.x;
            newPoint.y = (i - center.y) * *ptr / foc.y;
            newPoint.z = *ptr;

            double nx, ny, nz;

            nx = *R.ptr<double>(0,0) * newPoint.x - *T.ptr<double>(0);
            nx += *R.ptr<double>(0,1) * newPoint.y;
            nx += *R.ptr<double>(0,2) * newPoint.z;

            //R_ptr = R.ptr<double>(1);
            ny =  *R.ptr<double>(1,0) * newPoint.x - *T.ptr<double>(1);
            ny += *R.ptr<double>(1,1) * newPoint.y;
            ny += *R.ptr<double>(1,2) * newPoint.z;

           //R_ptr = R.ptr<double>(2);
            nz = *R.ptr<double>(2,0) * newPoint.x - *T.ptr<double>(1);
            nz += *R.ptr<double>(2,1) * newPoint.y;
            nz += *R.ptr<double>(2,2) * newPoint.z;


             int x_int = round(nx / nz * foc_rgb.x + center_rgb.x);
             int y_int = round( ny / nz * foc_rgb.y + center_rgb.y);
             int z_int = round( nz);
             if(x_int>0&&x_int<inputImage.cols&&y_int>0&&y_int<inputImage.rows)
             {

                 if (type==0)
                 outputImage.at<uint16_t>(y_int,x_int)= z_int;
                 else
                     outputImage.at<uint16_t>(y_int,x_int)= inputImage.at<uint16_t>(i,j);
             }
            ptr++;

        }

    }

}

