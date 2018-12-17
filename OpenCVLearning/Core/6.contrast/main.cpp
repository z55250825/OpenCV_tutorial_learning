//
//  main.cpp
//  contrast
//
//  Created by z55250825 on 2018/12/16.
//  Copyright © 2018 z55250825. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
using namespace cv;
using std::cin;
using std::cout;
using std::endl;

double alpha = 0.5;
double beta = 70.0;
const int max_alpha = 100;
const int max_beta = 100;
int slider_alpha = 0, slider_beta = 0;
Mat img,new_img;

static void on_tracker_alpha(int, void*){
    alpha = 1.0*(double)slider_alpha/(double)max_alpha;
    img.convertTo(new_img, -1, alpha, beta);
    imshow("new_img", new_img);
}

static void on_tracker_beta(int, void*){
    beta = (double)slider_beta;
    img.convertTo(new_img, -1, alpha, beta);
    imshow("new_img", new_img);
}

int main(int argc, const char * argv[]) {
    img = imread("/Users/z55250825/desktop/4.jpg");
    new_img = Mat::zeros(img.size(), img.type());
    
    char track_alpha[50],track_beta[50];
    sprintf(track_alpha, "alpha");
    sprintf(track_beta, "beta");
    namedWindow("img",WINDOW_AUTOSIZE);
    namedWindow("new_img",WINDOW_AUTOSIZE);
    createTrackbar(track_alpha, "new_img", &slider_alpha, max_alpha, on_tracker_alpha);
    createTrackbar(track_beta, "new_img", &slider_beta, max_beta, on_tracker_beta);
    imshow("img", img);
    imshow("new_img", new_img);
    waitKey();
    imwrite("/Users/z55250825/desktop/5.jpg", new_img);
    
    // used for user input
    /*
    for (int x = 0; x < img.rows; ++x)
        for (int y = 0; y < img.cols; ++y)
            for (int c = 0; c < img.channels(); ++c) {
                new_img.at<Vec3b>(x,y)[c] =
                saturate_cast<uchar>(alpha * img.at<Vec3b>(x,y)[c] + beta);
            }
    
    imshow("img", img);
    imshow("new_img", new_img);
    
    waitKey();
     */
    return 0;
}
