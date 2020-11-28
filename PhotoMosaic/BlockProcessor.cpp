//  Created by Arthur Cheung on 2020/09/12.
//  Copyright © 2020年 Arthur Cheung. All rights reserved.

#include "BlockProcessor.hpp"

int BlockProcessor(string readDir, string defaultDir)
{
    struct dirent *ptr;
    DIR *dir;
    string path = readDir + "Resource/";
    dir = opendir(path.c_str());
    vector<string> blocks;
    vector<Vec3b> averages;
    vector<int> hue;
    int rgbArray[SIZE][RGB];
    if ((ptr = readdir(dir)) == NULL)
    {
        printf("Nothing in this directory!\n");
        return -1;
    } // if
    
    Mat tempImg;
    dir = opendir(path.c_str());
    while ((ptr = readdir(dir)) != NULL)
    {
        if (ptr -> d_name[0] == '.')
            continue;
        blocks.push_back(ptr -> d_name); //add the d_name to the end of the vector

        tempImg = imread(path + ptr -> d_name);
        tempImg = resizer(tempImg, BREAK, BREAK);
        imwrite(readDir + "Resizer/" + ptr -> d_name, tempImg);
        
        readPixel(SIZE, rgbArray, tempImg, 0, 0, BREAK);

        averages.push_back(averageValue(SIZE, rgbArray));
        hue.push_back((int)transformRGB2HSV(averageValue(SIZE, rgbArray))[0] * 2);

    } // while
    
    // 写入文件
    writter(ptr, dir, blocks, averages, hue, readDir, defaultDir);
    return 0;
} // ImageAnalysis

Mat resizer(Mat targetImg, int col, int row)
{
    Mat tempImg;
    
    resize(targetImg, tempImg, Size(row, col));
    return tempImg;
} // resizer

Vec3b transformRGB2HSV(Vec3b avgRGB)
{
    Mat3b hsvAverage;
    Mat3b rgb(avgRGB);
    
    cvtColor(rgb, hsvAverage, COLOR_BGR2HSV);     // transform rgb value to hsv value
    return hsvAverage.at<Vec3b>();
} // transformRGB2HSV

int writter(struct dirent *ptr, DIR *dir, vector<string> blocks, vector<Vec3b> averages, vector<int> hue, string path, string defaultDir)
{
    ofstream outfile;
    outfile.open(defaultDir + "data.csv", ios::out | ios::trunc);          // If the file exist, then set the length to 0 then open
    outfile << "Name,B,G,R,H"  << endl; // 4 columns represent: name, B, G and R value

    for (int i = 1; i < blocks.size(); i++)
    {
        if (outfile.is_open())
        {
            outfile << blocks[i] << "," << (int)averages[i][0]  << "," << (int)averages[i][1]  << "," << (int)averages[i][2] << "," << hue[i] << endl;
        } //if
        else
        {
            cout << "Cannot write to the file" << endl;
        } // else
    } //for
    outfile.close();
    closedir(dir);
    cout << "Data.csv file has been created." << endl;
    return 0;
} // writter