//  Created by Arthur Cheung on 2020/09/12.
//  Copyright © 2020年 Arthur Cheung. All rights reserved.

#ifndef BlockProcessor_hpp
#define BlockProcessor_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <dirent.h>
#include "PhotoSegment.hpp"

using namespace cv;
using namespace std;

int BlockProcessor(string readDir, string defaultDir);
Mat resizer(Mat targetImg, int col, int row);
Vec3b transformRGB2HSV(Vec3b avgRGB);
int writter(struct dirent *ptr, DIR *dir, vector<string> blocks, vector<Vec3b> averages, vector<int> hue, string path, string defaultDir);
#endif /* BlockProcessor_hpp */