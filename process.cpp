//
// Created by juliuswang on 1/17/17.
//

#include "process.h"

process::process(string filename) {
    ifile = filename;
}

process::~process() {

}

void process::run() {
    Mat src, dst;
    cout << "read " << ifile << endl;
    VideoCapture capture(ifile.c_str());
    if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    namedWindow("w", 1);
    int frame_count = 0;
    for(;;) {
        capture >> src;
        if (src.empty())
            break;

        filter.hough_transform(src, dst, true);
        imshow("processed", dst);
        imshow("source", src);
        waitKey(0); // waits to display frame
        frame_count++;
    }
}
