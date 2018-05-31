#include "opencv2/objdetect/objdetect.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  

#include <cctype>  
#include <iostream>  
#include <iterator>  
#include <stdio.h>  
#include <string>
#include "Detection.h"

#include "CStatDir.h"



using namespace std;

using namespace cv;



//图像尺寸统一化

void normlizeone(const char* dir, string savePath, Size dsize)

{

	CStatDir statDir;

	if (!statDir.setInitDir(dir))

	{
		cout << "Do not exist~!" << endl;

		return;

	}



	//获取路径内所有png的图像

	vector<char*> FfileNames = statDir.BeginBrowseFilenames("*.jpg");
	std::vector<std::string> fileNames(FfileNames.begin(), FfileNames.end());


	//读取每幅图像并保存成standard 图像

	for (int i = 0; i < fileNames.size(); i++)

	{

		//读取图像

		Mat cur_img = imread(fileNames[i]);

		//调整成标准图像大小

		Mat standard; //存放标准图像

		resize(cur_img, standard, dsize, 0, 0, INTER_AREA);

		//保存图像

		imwrite(savePath + to_string(i) + ".jpg", standard);

	}

}



//从src总切割出一块为rect的图保存到res中

void cutImg(Mat& src, Rect rect, Mat& res)

{

	res = src(rect);

}



//读取图像，并返回路径中图像的数目

int readImg(const char* dir, vector<Mat>& imgs)

{

	//设置初始路径，路径不错存在时，返回0

	CStatDir statdir;

	if (!statdir.setInitDir(dir))

	{

		cout << "Dir:" << dir << "donnot exist!" << endl;

		return 0;

	}



	//获取路径中所有图像的名字

	vector<char*> FfileNames = statdir.BeginBrowseFilenames("*.jpg");
	std::vector<std::string> fileNames(FfileNames.begin(), FfileNames.end());
	//获取图像的数目

	int numberOfImgs = fileNames.size();

	//读取图像保存到imgs中

	for (int i = 0; i < numberOfImgs; i++)

	{

		Mat cur_img = imread(fileNames[i]);

		imgs.push_back(cur_img);

	}

	return numberOfImgs;

}



//读取图像，返回图像的名称和图像数据

vector<pair<string, Mat >> read_Img(const char*  dir)

{

	//设置初始路径，路径不错存在时，返回0

	CStatDir statdir;

	vector<pair<string, Mat >> Vp;

	if (!statdir.setInitDir(dir))

	{

		cout << "Dir:" << dir << "donnot exist!" << endl;

		return Vp;

	}



	//获取路径中所有图像的名字

	vector<char*> FfileNames = statdir.BeginBrowseFilenames("*.jpg");
	std::vector<std::string> fileNames(FfileNames.begin(), FfileNames.end());
	//获取图像的数目

	int numberOfImgs = fileNames.size();

	//读取图像保存到imgs中

	for (int i = 0; i < numberOfImgs; i++)

	{

		pair<string, Mat> tmp;

		tmp.first = fileNames[i];

		tmp.second = imread(fileNames[i]);

		Vp.push_back(tmp);

	}

	return Vp;

}





vector<Rect> detectAndDraw(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade, double scale, bool trpflip, bool draw)

{

	Mat gray;//存储img的灰度图像

	cvtColor(img, gray, CV_BGR2GRAY);

	//存储按scale变化后的灰度图像

	Mat smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_AREA);

	equalizeHist(smallImg, smallImg);//直方图均衡化



									 //人脸检测

	vector<Rect> faces, faces2;

	double t = (double)cvGetTickCount();//开始计时

									   //人脸检测，多尺度检测

	cascade.detectMultiScale(smallImg, faces, 1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));



	//如需将图像镜像，镜像后再进行人脸检测

	if (trpflip)

	{

		flip(smallImg, smallImg, 1);//左右翻转

		cascade.detectMultiScale(smallImg, faces2, 1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));



		//将检测的人脸镜像之后再存放到faces中

		for (vector<Rect>::iterator it = faces2.begin(); it < faces2.end(); it++)

		{

			faces.push_back(Rect(smallImg.cols - it->x - it->width, it->y, it->width, it->height));

		}

	}



	//终止计时

	t = (double)cvGetTickCount() - t;

	cout << "Detection time:" << t / (cvGetTickFrequency() * 1000) << "ms" << endl;



	//如需画出检测到的人脸和眼睛，画出来

	if (draw)

	{

		flip(smallImg, smallImg, 1);//恢复到原来的小图像

		for (vector<Rect>::iterator r = faces.begin(); r != faces.end(); r++)

		{

			//设置画出人脸的颜色：随机

			Scalar color(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255));

			rectangle(img, Point(cvRound((r->x)*scale), cvRound((r->y)*scale)),

				Point(cvRound((r->x + r->width + 1)*scale), cvRound((r->y + r->height + 1)*scale)),

				color, 1, 8, 0);



			//人眼检测器为空时，则继续画人脸

			if (nestedCascade.empty())

				continue;



			//检测眼睛

			Mat smallImgROI = smallImg(*r);  //取出检测出的人脸

			vector<Rect> eyes;

			nestedCascade.detectMultiScale(smallImgROI, eyes, 1.1, 2,

				CV_HAAR_MAGIC_VAL, Size(30, 30));



			//画眼睛

			for (vector<Rect>::iterator nr = eyes.begin(); nr != eyes.end(); nr++)

			{

				Scalar color(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255));

				Point center(cvRound((r->x + nr->x + nr->width*0.5)*scale),

					cvRound((r->y + nr->y + nr->height*0.5))*scale); //设置中心点

				int radius = (nr->width + nr->height)*0.25*scale;

				circle(img, center, radius, color, 1, 8, 0);

			}

		}

		imshow("检测窗口", img);

		//imwrite("检测2.jpg", img );

		waitKey();

	}

	return faces;

}



//检测并切割图像

Mat detectAndExtract(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade,

	double scale, bool trpflip, bool draw)

{

	//检测人脸

	vector<Rect> faces = detectAndDraw(img, cascade, nestedCascade, scale, trpflip, false);

	int maxArea = 0;//存储最大人脸的面积

	int id = -1; //faces中的id



				 //寻找faces中最大面积的face

	for (int i = 0; i < faces.size(); i++)

	{

		int area = faces[i].width*faces[i].height;//当前检测人脸的面积

												  //寻找最大的人脸及其id

		if (maxArea < area)

		{

			id = i;

			maxArea = area;

		}

	}



	//切割出人脸

	Mat res;//存放切割出来的人脸

	if (id != -1)

	{

		res = img(faces[id]);

	}

	return res;

}