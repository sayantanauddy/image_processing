//
// Created by sayantan on 5/4/17.
//
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <printf.h>
#include "iostream"

#include "IterateImage.h"
#include "LocalMaxima.h"
#include "RegionGrowing.h"

using namespace cv;
using namespace std;

int main(){
    //iterateImage("../lena.jpg");
    std::list<Point> maxima;
    int num_regions = localMaxima(maxima, "../black_white_dots2.png");
    cout<<"Number of regions = "<<num_regions<<endl;
}