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



//ͼ��ߴ�ͳһ��

void normlizeone(const char* dir, string savePath, Size dsize);



//��src���и��һ���СΪrect��ͼ���浽res��

void cutImg(Mat& src, Rect rect, Mat& res);



//��ȡͼ�񣬲�����·����ͼ�����Ŀ

int readImg(const char*  dir, vector<Mat>& imgs);



//��ȡͼ�񣬷���ͼ������ƺ�ͼ������

vector<pair<string, Mat >> read_Img(const char*  dir);



//��Ⲣ��ǳ�����

vector<Rect> detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale, bool trpflip, bool draw);



//��Ⲣ��ȡ������

Mat detectAndExtract(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade,

	double scale, bool trpflip, bool draw);



#endif