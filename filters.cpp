//
// Created by juliuswang on 1/17/17.
//

#include "filters.h"

filters::filters() {

}

filters::~filters() {

}

void filters::hough_transform(Mat &src, Mat &dst, bool is_prob) {
    Mat edge_dst;
    Canny(src, edge_dst, 20, 200, 3);
    cvtColor(edge_dst, dst, CV_GRAY2BGR);

    if (is_prob) {
        vector<Vec4i> lines;
        HoughLinesP( edge_dst, lines, 1, CV_PI/180, 80, 30, 10 );
        for ( size_t i = 0; i < lines.size(); i++ )
        {
            line(dst, Point(lines[i][0], lines[i][1]),
                 Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
        }
    }
    else {
        vector<Vec2f> lines;
        HoughLines( edge_dst, lines, 1, CV_PI/180, 100 );

        for( size_t i = 0; i < lines.size(); i++ )
        {
            float rho = lines[i][0];
            float theta = lines[i][1];
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            Point pt1(cvRound(x0 + 1000*(-b)),
                      cvRound(y0 + 1000*(a)));
            Point pt2(cvRound(x0 - 1000*(-b)),
                      cvRound(y0 - 1000*(a)));
            line( dst, pt1, pt2, Scalar(0,0,255), 3, 8 );
        }
    }
}