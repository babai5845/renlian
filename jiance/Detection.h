#pragma once
#ifndef DETECTION_H

#define DETECTION_H



#include "opencv2/highgui/highgui.hpp"
#include <opencv.hpp>
#include "opencv2/core/core.hpp"
#include <vector>
#include <cv.h>
#include <utility>
using namespace std;

using namespace cv;



//图像尺寸统一化

void normlizeone(const char* dir, string savePath, Size dsize);



//从src总切割出一块大小为rect的图保存到res中

void cutImg(Mat& src, Rect rect, Mat& res);



//读取图像，并返回路径中图像的数目

int readImg(const char*  dir, vector<Mat>& imgs);



//读取图像，返回图像的名称和图像数据

vector<pair<string, Mat >> read_Img(const char*  dir);



//检测并标记出人脸

vector<Rect> detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale, bool trpflip, bool draw);



//检测并提取出人脸

Mat detectAndExtract(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade,

	double scale, bool trpflip, bool draw);



#endif