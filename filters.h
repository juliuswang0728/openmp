//
// Created by juliuswang on 1/17/17.
//

#ifndef OPENMP_FILTER_H
#define OPENMP_FILTER_H
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

class filters {

public:

    filters();
    ~filters();

    // hough transform (is_prob == false)
    // probabilistic hough transform (is_prob == true)
    void hough_transform(Mat& src, Mat &dst, bool is_prob);

};

#endif //OPENMP_FILTER_H
