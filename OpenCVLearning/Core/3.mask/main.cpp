//
//  main.cpp
//  mask
//
//  Created by z55250825 on 2018/12/16.
//  Copyright © 2018 z55250825. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// we usually need to recaculate each pixels according to a mask matrix(kernel)
// this mask adjust influence neighboring pixels have on the new pixel value.
// i.e. weighted function

int main(int argc, const char * argv[]) {
    
    Mat src = imread("/Users/z55250825/desktop/1.png");
    Mat dst;
    // you can achieve this by yourself, but fileter2D is useful
    //
    // for this kernel, the formula is :
    // 5 * f[i][j] - (f[i-1][j] + f[i][j-1] + f[i+1][j] + f[i][j+1])
    Mat kernel = (Mat_<char>(3,3) << 0,-1,0,-1,5,-1,0,-1,0);
    filter2D(src, dst, src.depth(), kernel);
    
    imshow("src", src);
    imshow("dst", dst);
    waitKey();
    
    return 0;
}
