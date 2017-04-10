#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;



// Declare a class for a pixel location
class APoint{
    int x; int y;
    
    public:
        void set(int,int);
        int getx();
        int gety();
};

void APoint::set(int a, int b){
    this->x=a;
    this->y=b;
}

int APoint::getx(){
    return this->x;
}
    
int APoint::gety(){
    return this->y;
}


// Function to calculate the initial seed values
std::vector<APoint> get_seeds(Mat gray_image, int filter_size){

    std::vector<APoint> seeds;
    std::vector<APoint>::iterator it;
    it = seeds.begin();
    
    int rows = gray_image.rows;
    int cols = gray_image.cols;
    
    for(int i=(filter_size/2);i<(rows-(filter_size/2));i++){
        for(int j=(filter_size/2);j<(cols-(filter_size/2));j++){
        
            unsigned char max = 0;
            int x = 0;
            int y = 0;
            
            for(int r=-(filter_size)/2; r<=(filter_size)/2; r++){
                for(int c=-(filter_size)/2; c<=(filter_size)/2; c++){
                    if(gray_image.at<uchar>(i+r,j+c) >= max){
                        max = gray_image.at<uchar>(i+r,j+c);
                        x = i+r;
                        y = j+c;
                    }
                }
            }
            
            APoint apoint;
            apoint.set(x,y);
            it = seeds.insert ( it , apoint );
            cout<<"Inserted x="<<x<<" y="<<y<<endl;
        }
    }
    return seeds;
}
    
int regionGrowing(int argc, char** argv )
{

    if ( argc != 2 )
    {
        printf("usage: LocalMaxima.out <Image_Path>\n");
        return -1;
    }

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }

    Mat gray_image;
    cvtColor( image, gray_image, CV_BGR2GRAY );
    
    // Mapping of a pixel to a region
    unsigned char** region_map = new unsigned char*[gray_image.cols];
    for(int i = 0; i < gray_image.cols; ++i) {
        region_map[i] = new unsigned char[gray_image.rows];
    }
    
    // Initially all pixels have no region
    for(int i = 0; i < gray_image.rows; ++i){
        for(int j = 0; j < gray_image.cols; ++j){
            region_map[i][j] = 0;
        }
    }
    
    // Get the initial seed locations
    std::vector<APoint> seeds = get_seeds(gray_image,9);
    
    /*
    for(std::vector<APoint>::iterator it=seeds.begin();it!=seeds.end();++it){
        APoint seed = *it;
        cout<<seed.getx()<<" "<<seed.gety()<<endl;
    }
    */
    
    
    return 0;
    
}
