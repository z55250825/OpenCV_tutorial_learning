//
//  main.cpp
//  pixel
//
//  Created by z55250825 on 2018/12/16.
//  Copyright © 2018 z55250825. All rights reserved.
//

// Step 2 : learning pixel control

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

// there are 3 ways to go through pixels

// OpenCV offers 2 simple functions to achieve timing
// CV::getTickCount() and CV::getTickFrequency()
// usually code:
// double t = (double)getTickCount();
// // do something
// t = ((double)getTickCount() - t)/getTickFrequency();

// OpenCV order is BGR instead of RGB
// in many ways store the rows in a successive fashion

uchar tables[256];

void prepare(){
    for (int i = 0; i < 256; ++i)
        tables[i] = (uchar)(10 * (i/10));
}

// Method 1 : C style operator []

Mat& ScanImageAndReduceC(Mat& I, const uchar* const tables){
    //accept only char type element
    CV_Assert(I.depth() == CV_8U);
    
    const int channels = I.channels();
    
    int nRows = I.rows;
    int nCols = I.cols * channels;
    
    if (I.isContinuous()){
        nCols *= nRows;
        nRows = 1;
    }
    
    int i,j;
    uchar *p;
    for (i = 0; i < nRows; ++i){
        p = I.ptr(i);
        for ( j = 0; j < nCols; ++j)
            p[j] = tables[p[j]];
    }
    
    return I;
}

// Method 2 : iterator (safe) method
Mat& ScanImageAndReduceIterator(Mat &I, const uchar* const tables){
    //accept only char type element
    CV_Assert(I.depth() == CV_8U);
    
    const int channels = I.channels();
    switch (channels) {
        case 1:{
            MatIterator_<uchar>it, end;
            for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
                *it = tables[*it];
            break;
        }
        case 3:{
            MatIterator_<Vec3b>it, end;
            for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it){
                (*it)[0] = tables[(*it)[0]];
                (*it)[1] = tables[(*it)[1]];
                (*it)[2] = tables[(*it)[2]];
            }
            break;
        }
    }
    
    return I;
}

Mat& ScanImageAndReduceRandomAccess(Mat &I, const uchar* const tables){
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    
    const int channels = I.channels();
    switch (channels) {
        case 1:
            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j)
                    I.at<uchar>(i, j) = tables[I.at<uchar>(i, j)];
            break;
        case 3:
            Mat_<Vec3b> _I = I;
            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j){
                    _I(i,j)[0] = tables[_I(i,j)[0]];
                    _I(i,j)[1] = tables[_I(i,j)[1]];
                    _I(i,j)[2] = tables[_I(i,j)[2]];
                }
            I = _I;
            break;
    }
    return I;
}

//Method 4: if you want to modify all of a given image values
//OpenCV provides a function for modifying CV::LUT() of the core

int main(int argc, const char * argv[]) {
    // insert code here...
    prepare();
    
    Mat I = imread("/Users/z55250825/desktop/1.png");
    Mat J = I.clone();
    Mat K = I.clone();
    Mat L; I.copyTo(K);
    Mat M;
    Mat LookUpTable(1, 256, CV_8U);
    uchar *ptr = LookUpTable.ptr();
    for (int i = 0; i < 256; ++i)
        ptr[i] = tables[i];
    
    double t = (double)getTickCount();
    I = ScanImageAndReduceC(I, tables);
    t = 10*((double)getTickCount() - t)/getTickFrequency();
    cout << t << endl;
    
    t = (double)getTickCount();
    J = ScanImageAndReduceIterator(J, tables);
    t = 10*((double)getTickCount() - t)/getTickFrequency();
    cout << t << endl;
    
    t = (double)getTickCount();
    K = ScanImageAndReduceRandomAccess(K, tables);
    t = 10*((double)getTickCount() - t)/getTickFrequency();
    cout << t << endl;
    
    //t = (double)getTickCount();
    //LUT(L, LookUpTable, M);
    //t = ((double)getTickCount() - t)/getTickFrequency();
    //cout << t << endl;
    
    imshow("I", I);
    imshow("J", J);
    imshow("K", K);
    //imshow("M", M);
    waitKey();
    return 0;
}
