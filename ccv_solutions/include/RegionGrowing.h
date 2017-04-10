//
// Created by sayantan on 10/4/17.
//
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#ifndef CCV_SOLUTIONS_REGIONGROWING_H
#define CCV_SOLUTIONS_REGIONGROWING_H

void find_8_neighbors(std::list<Point>& neighbor_list, int i, int j, const Mat& image);
int regionGrowing(std::list<Point>& maxima, const Mat& image);

#endif //CCV_SOLUTIONS_REGIONGROWING_H
