//
//  main.cpp
//  VideoInput
//
//  Created by z55250825 on 2019/1/17.
//  Copyright © 2019 z55250825. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    stringstream conv;
    
    const string sourceReference = "/Users/z55250825/Downloads/百度网盘/[Yumeki][Ressha Sentai TOQGER][02][BDRip][1080P][MKV].mkv";
    VideoCapture captRefrnc(sourceReference);
    if (!captRefrnc.isOpened()) {
        cout << "couldn't open reference " << sourceReference << endl;
        return -1;
    }
    
    Mat frameReference;
    captRefrnc >> frameReference;
    
    namedWindow("Reference", WINDOW_AUTOSIZE);
    
    cout<<"start"<<endl;
    
    while ( !frameReference.empty()) {
        imshow("Reference", frameReference);
        captRefrnc >> frameReference;
        
        char c = (char)waitKey(200);
        if (c==27)break;
    }
    return 0;
}
