/*
 * Function to iterate over an image and print out the individual pixel values
 */

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "iostream"

using namespace cv;
using namespace std;

int iterateImage(const string imagefile )
{
	printf("CV_MAJOR_VERSION:%d\n",CV_MAJOR_VERSION);
	printf("CV_MINOR_VERSION:%d\n",CV_MINOR_VERSION);

    Mat image;
    image = imread( imagefile, 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    cout<<image.type()<<endl;
    
    for(int i=0;i<image.rows;i++){
        for(int j=0;j<image.cols;j++){
        
            Vec3b pixel = image.at<Vec3b>(i,j);
            
            cout<<pixel<<" ";
            
            }
            
        cout<<endl;
    }
            
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);

    waitKey(0);

    return 0;
}

