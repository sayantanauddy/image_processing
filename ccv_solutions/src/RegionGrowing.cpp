#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void find_8_neighbors(std::list<Point>& neighbor_list, int i, int j, const Mat& image){

    int max_rows = image.rows;
    int max_cols = image.cols;
    uchar intensity = image.at<uchar>(i,j);

    // Find 8 connected neighbors with the same intensity
    for(int r=-1; r<=1; r++) {
        for (int c = -1; c <= 1; c++) {

            // Check if the calculate location of the neighbor is within bounds
            if ((i + r) < 0 || (i + r) >= max_rows || (j + c) < 0 || (j + c) >= max_cols)
                continue;

            // Do not consider the center point itself
            if (r == 0 && c == 0)
                continue;

            // Check if the neighbor's intensity is the same
            if (intensity == image.at<uchar>(i + r, j + c)) {
                neighbor_list.push_front(Point(j + c, i + r));
            }
        }
    }
}

int regionGrowing(std::list<Point>& maxima, const Mat& image){

    // An array of bools to tell if a pixel has been visited or not
    bool pixel_visited[image.rows][image.cols];
    for(int i=0; i<image.rows; ++i){
        for(int j=0; j<image.cols; ++j){
            pixel_visited[i][j] = false;
        }
    }

    // List of segments
    // Each element is a list of pixels
    std::list<std::list<Point> > segments;

    // Iterate through the list of maxima and process each element
    for(std::list<Point>::iterator it=maxima.begin(); it!=maxima.end(); ++it){

        // List of pixels for current region
        std::list<Point> current_segment_list;

        // List of neighbors to process
        std::list<Point> neighbor_list;

        Point p = *it;

        // Check if p has been visited
        // i is row -> y-axis
        // j is col -> x-axis
        if(pixel_visited[p.y][p.x])
            continue;
        else{
            pixel_visited[p.y][p.x] = true;

            // Add p to the segment being processed
            current_segment_list.push_back(p);

            // Find neighbors of p
            find_8_neighbors(neighbor_list, p.y, p.x, image);

            while(neighbor_list.size() > 0){

                int size=neighbor_list.size();
                // Get a neighbor of p
                Point n = neighbor_list.front();
                neighbor_list.pop_front();

                // Check if the neighbor has been visited
                if(pixel_visited[n.y][n.x]){
                    continue;
                }
                else{
                    pixel_visited[n.y][n.x] = true;

                    // Add the neighbor to the segment
                    current_segment_list.push_back(n);

                    // Find the neighbors of the neighbor
                    std::list<Point> next_neighbor_list;
                    find_8_neighbors(next_neighbor_list, n.y, n.x, image);

                    // Store these in the list of neighbors
                    for(std::list<Point>::iterator next_it = next_neighbor_list.begin(); next_it!=next_neighbor_list.end(); ++next_it){
                        neighbor_list.push_front(*(next_it));
                    }
                }
            }
            // Add the segment to the list of segments
            segments.push_back(current_segment_list);
        }
    }

    // Return the number of segments
    return segments.size();

}