#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "iostream"

#include "RegionGrowing.h"

using namespace cv;
using namespace std;

void drawCircle(cv::Mat& src, int x, int y, int radius)
{
    Point center = Point(x,y);
    Scalar color = Scalar(255,0,0);
    int thickness = 1;

    circle(src, center, radius, color, thickness);
}

int localMaxima(std::list<Point>& maxima, const string imagefile)
{
    Mat image;
    image = imread( imagefile, 1 );

    Mat gray_image;

    /*
    uchar data[10][10] = {{ 255, 255, 255, 255, 255, 255, 10, 10, 10, 10 } ,
                          { 255, 255, 255, 255, 255, 255, 10, 10, 10, 10 } ,
                          { 255, 255, 255, 255, 255, 255, 10, 10, 10, 10 } ,
                          { 255, 255, 255, 255, 255, 255, 10, 10, 10, 10 } ,
                          { 255, 255, 255, 255, 255, 255, 10, 10, 10, 10 } ,
                          { 255, 255, 255, 255, 255, 255, 10, 10, 10, 10 } ,
                          { 255, 255, 255, 255, 255, 255, 10, 10, 10, 10 } ,
                          {  10,  10,  10,  10,  10,  10, 10, 10, 10, 10} ,
                          {  10,  10,  10,  10,  10,  10, 10, 10, 10, 10} ,
                          {  10,  10,  10,  10,  10,  10, 10, 50, 50, 50}} ;

    gray_image = Mat(10,10,CV_8UC1, &data);
    */

    cvtColor( image, gray_image, CV_BGR2GRAY );

    // Pad image with 1 pixel border (since 8-neighborhood is considered)
    Mat gray_image_padded = gray_image;

    copyMakeBorder(gray_image, gray_image_padded, 1, 1, 1, 1, BORDER_REPLICATE);

    int filter_size = 3;
    
    int rows = gray_image_padded.rows;
    int cols = gray_image_padded.cols;

    for(int i=(filter_size/2);i<(rows-(filter_size/2));i++){
        for(int j=(filter_size/2);j<(cols-(filter_size/2));j++){

            // Check if all pixels in the window have the same value
            // If yes, then do not mark any pixel as maxima
            // If this remains true at the end, then all pixels
            // have the same value
            bool uniform_flag = true;

            // Check if the center pixel at (i,j) has a greater or equal value
            // than all of its 8-connected neighbors
            uchar center_val = gray_image_padded.at<uchar>(i,j);

            // Flag to indicate if center pixel has higher value
            // than its neighbors
            bool maxFlag = true;

            // Iterate through the neighbors and see if a neighbors
            // value is greater than the center. If yes, then the
            // center is not a local maxima and the windows should
            // be shifted to the next position.
            for(int r=-(filter_size)/2; r<=(filter_size)/2; r++){
                for(int c=-(filter_size)/2; c<=(filter_size)/2; c++){

                    // Do not consider the center point itself
                    if(r==0 && c==0)
                        continue;

                    // Value of neighbor
                    uchar neighbor_val = gray_image_padded.at<uchar>(i+r,j+c);

                    if(neighbor_val > center_val){
                        // If neighbor has higher value do not process
                        // the other neighbors
                        maxFlag = false;
                        uniform_flag = false;
                        break;
                    }
                    else if(neighbor_val < center_val){
                        maxFlag = true;
                        uniform_flag = false;
                    }
                }
                if(maxFlag == false){
                    break;
                }
            }

            if(uniform_flag == true){
                // All neighbors have the same value
                // proceed to the next pixel
                continue;
            }
            else if(maxFlag == true) {
                // The center has the highest value
                // j is the col number -> x axis
                // i ths the row number -> y axis
                // strip 1 from row and col to account
                // for the padding in the padded image
                maxima.push_back(Point(j-1,i-1));
            }
            else{
                continue;
            }
        }
    }

    // Compute number of regions and return
    int num_segments = regionGrowing(maxima, gray_image);
    return num_segments;

}
    
    
    
    
    
    
