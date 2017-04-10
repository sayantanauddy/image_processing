#include <vector>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

bool lesser (float i,float j) { return (i<j); }

float median_filter(int filtersize, int pixel_i, int pixel_j, Mat &img_mat){
	
	int distance_from_center = (filtersize-1)/2;
	int center_element_linear_order = (filtersize*filtersize-1)/2;
	
	vector<float> filter_members;
	
	for(int i=pixel_i-distance_from_center;i<=pixel_i+distance_from_center;i++){
		for(int j=pixel_j-distance_from_center;j<=pixel_j+distance_from_center;j++){
			filter_members.push_back(img_mat.at<float>(i,j));
		}
	}
	
	sort(filter_members.begin(),filter_members.end(),lesser);
	return filter_members[center_element_linear_order];
}

int floatImage(){
	int filter_size = 5;	
	cv::Mat img_mat_all = cv::imread("/home/sayantan/programs/cpp/opencv_test/lena.jpg",CV_LOAD_IMAGE_ANYDEPTH);
	vector<Mat> channels;
	cv::split(img_mat_all,channels);
	Mat img_mat = channels[0];
	int rows = img_mat.rows;
	int cols = img_mat.cols;
		
	cv::Mat filtered_img_mat =  cv::Mat(rows,cols,16);

	for(int i=0+((filter_size-1)/2 + 1);i<rows-((filter_size-1)/2);i++){
		for(int j=0+((filter_size-1)/2 + 1);j<cols-((filter_size-1)/2);j++){
			filtered_img_mat.at<float>(i,j)=(float)median_filter(filter_size, i, j,img_mat);
		}
	}
	
	cv::imshow("Median Filter",filtered_img_mat);
	cv::waitKey(0);
	cv::destroyAllWindows();
	//cout<<filtered_img_mat<<endl;
			
	return 0;
}
