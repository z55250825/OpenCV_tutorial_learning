//
//  main.cpp
//  imageStitch
//
//  Created by z55250825 on 2018/12/17.
//  Copyright © 2018 z55250825. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

Stitcher::Mode mode = Stitcher::PANORAMA;
vector<Mat> imgs;

int main(int argc, const char * argv[]) {
    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(mode, false);
    Stitcher::Status status = stitcher -> stitch(imgs, pano);
    
    if (status != Stitcher::OK){
        cout << "can not stitch image, error code = " << (int)status << endl;
        return EXIT_FAILURE;
    }
    
    imwrite("/Users/z55250825/desktop/result.jpg", pano);
    cout << "stitching successful!\n"<<endl;
    return EXIT_SUCCESS;
}
