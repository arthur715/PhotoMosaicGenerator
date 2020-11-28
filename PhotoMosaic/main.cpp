//  Created by Arthur Cheung on 2020/09/12.
//  Copyright © 2020年 Arthur Cheung. All rights reserved.
 
#include <iostream>
#include <stdio.h>
#include <string>
#include <opencv2/opencv.hpp>
#include "PhotoSegment.hpp"
#include "BlockProcessor.hpp"
#include "BlockMatcher.hpp"

using namespace cv;  
using namespace std;

string defaultDir = "/Users/arthurcheung/Desktop/opencv/Image_Mosaic/IMG/";
string readDir = defaultDir + "Input/";
string saveDir = defaultDir + "Output/";

int main()
{
    //read the reference image
    Mat referenceImage = imread(readDir + "testing_image.jpg");

    if (!referenceImage.data)
    {
        printf("Can't read the file, please check the path and try again.\n");
        exit(0);
    }
    else{
        printf("Read image sucess!\n");
    }
    
    //split the reference photo
    PhotoSegment(referenceImage);
    
    //read the image name and output the index file
    BlockProcessor(readDir, defaultDir);
    
    Mat mosaicImage = imread(readDir + "Cutter/25*25Cutter(masking).jpg");
    
    //match the source images to the reference photo's block
    BlockMatcher(mosaicImage, readDir, defaultDir, saveDir);
    
    
    if(waitKey(0))
    {
        printf("The program is successfully exited by keyboard interruption :) \n");
    }
    return 0;
}