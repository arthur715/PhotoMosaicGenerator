//  Created by Arthur Cheung on 2020/09/12.
//  Copyright © 2020年 Arthur Cheung. All rights reserved.

#ifndef BlockMatcher_hpp
#define BlockMatcher_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace cv;
using namespace std;

#define transparency 0.6

int BlockMatcher(Mat mosaicImg, string readDir, string defaultDir, string saveDir);
void reader(string fileDir, vector<string> &blocks, vector<Vec3b> &averages, vector<int> &hue);
int compareHue(Vec3b averageRGB, vector<int> hue);
Mat findBestMatchBlock(string readDir, int bestFitIndex, vector<string> blocks);
void replaceBlock(int size, Mat mosaicImg, Mat targetImg, Mat block, int pixelY, int pixelX, int breakpoint);

#endif /* BlockMatcher_hpp */