//
//  main.cpp
//  blend
//
//  Created by z55250825 on 2018/12/16.
//  Copyright © 2018 z55250825. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
using std::cin;
using std::cout;
using std::endl;

const int alpha_slider_max = 100;
int alpha_slider;
double alpha;
double beta;
double input;

Mat src1, src2, dst;

static void on_trackbar(int, void *) {
    alpha = (double) alpha_slider / alpha_slider_max ;
    beta = 1 - alpha;
    addWeighted(src1, alpha, src2, beta, 0.0, dst);
    imshow("blend", dst);
}

int main(int argc, const char * argv[]) {
    /* input alpha by user
     *
    cin >> input;
    if (input <= 1.0 && input >= 0.0)
        alpha = input;
    */
    
    src1 = imread("/Users/z55250825/desktop/LinuxLogo.jpg");
    if (src1.empty()){cout<<"Error loading src1 \n"; return -1;}
    
    src2 = imread("/Users/z55250825/desktop/WindowsLogo.jpg");
    if (src2.empty()){cout<<"Error loading src2 \n"; return -1;}
    
    // use track bar
    alpha_slider = 0;
    
    namedWindow("blend",WINDOW_AUTOSIZE);
    
    char trackBar[50];
    sprintf(trackBar, "Alpha x %d", alpha_slider_max);
    createTrackbar(trackBar, "blend", &alpha_slider, alpha_slider_max, on_trackbar);
    
    on_trackbar(alpha_slider, 0);
    // beta = 1 - alpha; //used for user input
    
    addWeighted(src1, alpha, src2, beta, 0.0, dst);
    
    imshow("blend", dst);
    waitKey();
    return 0;
}
