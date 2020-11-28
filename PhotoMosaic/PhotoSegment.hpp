//  Created by Arthur Cheung on 2020/09/12.
//  Copyright © 2020年 Arthur Cheung. All rights reserved.

#ifndef PhotoSegment_hpp
#define PhotoSegment_hpp

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

#define SIZE 625
#define BREAK 25
#define RGB 3

using namespace cv;
using namespace std;

int PhotoSegment(Mat referenceImage);
Mat edgeBorder(Mat targetImg);
Mat mosaicFilter(Mat targetImg, int height, int width);
void readPixel(int size, int array[][RGB], Mat targetImg, int pixelY, int pixelX, int breakpoint);
void writePixel(int size, Vec3b average, Mat targetImg, int pixelY, int pixelX, int breakpoint);
Vec3b averageValue(int size, int array[][RGB]);

#endif /* PhotoSegment_hpp */