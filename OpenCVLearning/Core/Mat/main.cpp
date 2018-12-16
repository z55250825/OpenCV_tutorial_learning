//
//  main.cpp
//  Mat
//
//  Created by z55250825 on 2018/12/16.
//  Copyright © 2018 z55250825. All rights reserved.
//

// 1. Mat is that you no longer need to manually allocate its memory and release it as
// soon as you do not need it
//
// 2. Mat : the matrix header and a pointer to the matrix containing the pixel values
//
// 3. each Mat object has its own header, however the matrix may be shared between two
// instance of them by having their matrix pointers point to the same address
//
// 4. the copy operators will only copy the headers and the pointer to the large
// matrix, not the data itself.

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    Mat A,C;
    A = imread("/Users/z55250825/desktop/1.png");
    Mat B(A);
    C = A;
    
    // all above objects point to the same data matrix.
    // header are different.
    
    Mat D (A, Rect(10, 10, 100, 100));
    // D will show the region of 10,10,100,100 left up right bottom
    
    Mat E = A(Range::all(), Range(1,100));
    // E just like D
    
    /*
    imshow("A", A);
    imshow("B", B);
    imshow("C", C);
    // they are the same
     */
    
    /*
    imshow("D", D);
    imshow("E", E);
    // ROI of A
     */
    
    //multiple matrix -> same data, the last used it clean(reference counting)
    //use cv::Mat::clone() or cv::Mat::copyTo() to copy matrix data
    
    Mat F = A.clone();
    Mat G;
    A.copyTo(G);
    
    /*
    imshow("F", F);
    imshow("G", G);
    waitKey();
    */
    
    //1)do not need to think about memory management with OpenCVs C++ interface.
    //
    //2)The assignment operator and the copy constructor only copies the header.
    //
    //3)The underlying matrix of an image may be copied using the cv::Mat::clone() and
    //  cv::Mat::copyTo() functions.
    
    Mat H;
    cvtColor(A, H, COLOR_RGB2GRAY);
    imwrite("/Users/z55250825/desktop/2.png", H);
    
    /*
     *  now it's time to see the actual value of Matrix
     *  for two dimension Mat use << for Mat to print out
     *  Mat is also a general matrix class.
     */
    
    //1. cv::Mat::Mat constructor
    
    // note :
    // 1) CV_[the number of bits per item][signed or unsigned][Type prefix][the channel number]
    // eg : CV_8UC3, 8 bits char type unsigned, 3 channels
    //
    // 2) cv::Scalar() -> four element short vector
    Mat M(2,2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << M << endl;
    
    //2. use C/C++ arrays and initialize via constructor
    int sz[3] = {2,2,2};
    Mat L(3,sz, CV_8UC(1), Scalar::all(0));
    
    //3. CV::Mat::create function:
    M.create(2, 2, CV_8UC(2));
    cout << "M = " << endl << M << endl;
    
    //4. MATLAB style : cv::Mat::zeros, cv::Mat::ones, cv::Mat::eye
    Mat I = Mat::eye(4, 4, CV_64F);
    Mat J = Mat::ones(2, 2, CV_32F);
    Mat K = Mat::zeros(3, 3, CV_8UC1);
    cout << "I = " << endl << I << endl;
    cout << "J = " << endl << J << endl;
    cout << "K = " << endl << K << endl;
    
    Mat O = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
    cout << "O = " << endl << O << endl;

    O = (Mat_<double>({0,-1,0,-1,5,-1,0,-1,0})).reshape(3);
    cout << "O = " << endl << O << endl;
    
    // OpenCV format output
    cout << "O (python) = " << endl << format(O, Formatter::FMT_PYTHON) << endl;
    cout << "O (CSV) = " << endl << format(O, Formatter::FMT_CSV) << endl;
    cout << "O (numpy) = " << endl << format(O, Formatter::FMT_NUMPY) << endl;
    
    // OpenCV format for other data type
    Point2f P(5, 1);
    cout << "Point (2D) = " << P << endl;
    Point3f P3f(2, 6, 7);
    cout << "Point (3D) = " << P3f << endl;
    vector<float> v;
    v.push_back((float) CV_PI);
    v.push_back(2);
    v.push_back(3.01f);
    cout << "Vector via Mat "<< Mat(v) << endl;
    vector<Point2f> vPoints(20);
    for (size_t i = 0; i < vPoints.size(); ++i )
        vPoints[i] = Point2f((float)(i * 5), (float)(i % 7));
    cout << "Vector of 2D points " << vPoints << endl;
    return 0;
}
