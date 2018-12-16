//
//  main.cpp
//  image
//
//  Created by z55250825 on 2018/12/16.
//  Copyright © 2018 z55250825. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    //gray image
    
    /*
    Mat a = imread("/Users/z55250825/desktop/1.png", IMREAD_GRAYSCALE);
    imshow("a", a);
    waitKey();
    
    uchar intensity = a.at<uchar>(1,1);
    cout << intensity << endl;
    */
    
    //Scalar is define as double val[4]
    
    /*
    Mat a = imread("/Users/z55250825/desktop/1.png");
    Vec3b intensity = a.at<Vec3b>(10,10);
    uchar blue = intensity.val[0];
    uchar green = intensity.val[1];
    uchar red = intensity.val[2];
    cout<<(int)blue<<" "<<(int)green<<" "<<(int)red<<endl;
     */
    
    Mat b = imread("/Users/z55250825/desktop/1.png");
    // b = Scalar(0); // make the image black
    Rect r(10, 10, 500, 500);
    Mat c = b(r);
    imshow("c", c);
    waitKey();
    
    return 0;
}
