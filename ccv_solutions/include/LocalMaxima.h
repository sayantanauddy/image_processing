//
// Created by sayantan on 5/4/17.
//
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "iostream"

using namespace cv;
using namespace std;

#ifndef CCV_SOLUTIONS_LOCALMAXIMA_H
#define CCV_SOLUTIONS_LOCALMAXIMA_H

int localMaxima(std::list<Point>& maxima, const string imagefile);
void drawCircle(cv::Mat& src, int y, int x, int radius);

#endif //CCV_SOLUTIONS_LOCALMAXIMA_H

