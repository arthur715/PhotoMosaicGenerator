//  Created by Arthur Cheung on 2020/09/12.
//  Copyright © 2020年 Arthur Cheung. All rights reserved.

#include "BlockMatcher.hpp"
#include "BlockProcessor.hpp"
#include "PhotoSegment.hpp"

int BlockMatcher(Mat mosaicImg, string readDir, string defaultDir, string saveDir)
{
    string path = readDir + "Resource/";
    string fileDir = defaultDir + "data.csv";
    Mat targetImg = imread(readDir + "EdgeBorder/25*25Edgeborder.jpg");

    vector<string> blocks;
    vector<Vec3b> averages;
    vector<int> hue;

    reader(fileDir, blocks, averages, hue);

    Mat tempImg = mosaicImg, bestFitTile;
    
    int i = 0, j = 0, pixelX = 0, pixelY = 0, bestFitIndex;
    int height = tempImg.rows;
    int width = tempImg.cols;
    
    Vec3b averageRGB;
    
    for (i = 0; i < width; i+=BREAK)
    {
        for (j = 0; j < height; j+=BREAK)
        {
            pixelX = i;
            pixelY = j;
            averageRGB = tempImg.at<Vec3b>(pixelY,pixelX);
            
            bestFitIndex = compareHue(averageRGB, hue);
            bestFitTile = findBestMatchBlock(readDir, bestFitIndex, blocks);

            pixelX = i;     // the first pixel
            pixelY = j;

            replaceBlock(SIZE, tempImg, targetImg, bestFitTile, pixelY, pixelX, BREAK);
        } // for
    } // for
    
    imshow("Result", tempImg);
    imwrite(saveDir + "result(25*25) with masking.jpg", tempImg);
    printf("The result picture has been created.\n");

    
    return 0;
} // BlockMatcher

void reader(string fileDir, vector<string> &blocks, vector<Vec3b> &averages, vector<int> &hue)
{
    ifstream data(fileDir);
    
    if (!data)
    {
        printf("Can't open the file.");
        exit(EXIT_FAILURE);
    }
    string line;
    string word;
    Vec3b average;
    int count = -1;
    
    if (count == -1)// get rid of the first title line in data.csv
    {
        getline(data, line);
        count++;
    } // if
    while(getline(data, line))
    {
        stringstream parsing(line);
        while (getline(parsing, word, ','))
        {
            if (count == 0)
            {
                blocks.push_back(word);
                count++;
            } // if
            else if (count == 1)
            {
                average[0] = stoi(word);
                count++;
            } // else if
            else if (count == 2)
            {
                average[1] = stoi(word);
                count++;
            } // else if
            else if (count == 3)
            {
                average[2] = stoi(word);
                averages.push_back(average);
                count++;
            } // else if
            else if (count == 4)
            {
                hue.push_back(stoi(word));
                count = 0;
            } // else if
        } // while
    } // while
    
} // reader

int compareHue(Vec3b averageRGB, vector<int> hue)
{
    int averageHue = (int)transformRGB2HSV(averageRGB)[0] * 2;
    
    int temp, currentMin = 360, bestFitIndex = 0;
    
    for (int i = 0; i < hue.size(); i++)
    {
        temp = abs(hue[i] - averageHue);        // stored as an absolute value, need to be none-negative
        if (currentMin > temp)
        {
            currentMin = temp;
            bestFitIndex = i;
        } // if
    } // for
    
    return bestFitIndex;
} // compareHue

Mat findBestMatchBlock(string readDir, int bestFitIndex, vector<string> blocks)
{
    Mat block = imread(readDir + "Resizer/" + blocks[bestFitIndex]);
    return block;
}

void replaceBlock(int size, Mat mosaicImg, Mat targetImg, Mat block, int pixelY, int pixelX, int breakpoint)
{
        int temp = 0, i = 0;
    
        for (int k = 0; k < size; k++)
        {
            mosaicImg.at<Vec3b>(pixelY, pixelX + temp) = (1 - transparency) * block.at<Vec3b>(i, temp) +
                                                         transparency * targetImg.at<Vec3b>(pixelY, pixelX + temp);
            temp++;
            if (temp == breakpoint)
            {
                temp = 0;
                i++;
                pixelY++;
            } // if
        } // for
} // replaceBlock