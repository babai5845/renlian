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



//ͼ��ߴ�ͳһ��

void normlizeone(const char* dir, string savePath, Size dsize)

{

	CStatDir statDir;

	if (!statDir.setInitDir(dir))

	{
		cout << "Do not exist~!" << endl;

		return;

	}



	//��ȡ·��������png��ͼ��

	vector<char*> FfileNames = statDir.BeginBrowseFilenames("*.jpg");
	std::vector<std::string> fileNames(FfileNames.begin(), FfileNames.end());


	//��ȡÿ��ͼ�񲢱����standard ͼ��

	for (int i = 0; i < fileNames.size(); i++)

	{

		//��ȡͼ��

		Mat cur_img = imread(fileNames[i]);

		//�����ɱ�׼ͼ���С

		Mat standard; //��ű�׼ͼ��

		resize(cur_img, standard, dsize, 0, 0, INTER_AREA);

		//����ͼ��

		imwrite(savePath + to_string(i) + ".jpg", standard);

	}

}



//��src���и��һ��Ϊrect��ͼ���浽res��

void cutImg(Mat& src, Rect rect, Mat& res)

{

	res = src(rect);

}



//��ȡͼ�񣬲�����·����ͼ�����Ŀ

int readImg(const char* dir, vector<Mat>& imgs)

{

	//���ó�ʼ·����·���������ʱ������0

	CStatDir statdir;

	if (!statdir.setInitDir(dir))

	{

		cout << "Dir:" << dir << "donnot exist!" << endl;

		return 0;

	}



	//��ȡ·��������ͼ�������

	vector<char*> FfileNames = statdir.BeginBrowseFilenames("*.jpg");
	std::vector<std::string> fileNames(FfileNames.begin(), FfileNames.end());
	//��ȡͼ�����Ŀ

	int numberOfImgs = fileNames.size();

	//��ȡͼ�񱣴浽imgs��

	for (int i = 0; i < numberOfImgs; i++)

	{

		Mat cur_img = imread(fileNames[i]);

		imgs.push_back(cur_img);

	}

	return numberOfImgs;

}



//��ȡͼ�񣬷���ͼ������ƺ�ͼ������

vector<pair<string, Mat >> read_Img(const char*  dir)

{

	//���ó�ʼ·����·���������ʱ������0

	CStatDir statdir;

	vector<pair<string, Mat >> Vp;

	if (!statdir.setInitDir(dir))

	{

		cout << "Dir:" << dir << "donnot exist!" << endl;

		return Vp;

	}



	//��ȡ·��������ͼ�������

	vector<char*> FfileNames = statdir.BeginBrowseFilenames("*.jpg");
	std::vector<std::string> fileNames(FfileNames.begin(), FfileNames.end());
	//��ȡͼ�����Ŀ

	int numberOfImgs = fileNames.size();

	//��ȡͼ�񱣴浽imgs��

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

	Mat gray;//�洢img�ĻҶ�ͼ��

	cvtColor(img, gray, CV_BGR2GRAY);

	//�洢��scale�仯��ĻҶ�ͼ��

	Mat smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_AREA);

	equalizeHist(smallImg, smallImg);//ֱ��ͼ���⻯



									 //�������

	vector<Rect> faces, faces2;

	double t = (double)cvGetTickCount();//��ʼ��ʱ

									   //������⣬��߶ȼ��

	cascade.detectMultiScale(smallImg, faces, 1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));



	//���轫ͼ���񣬾�����ٽ����������

	if (trpflip)

	{

		flip(smallImg, smallImg, 1);//���ҷ�ת

		cascade.detectMultiScale(smallImg, faces2, 1.1, 2, CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));



		//��������������֮���ٴ�ŵ�faces��

		for (vector<Rect>::iterator it = faces2.begin(); it < faces2.end(); it++)

		{

			faces.push_back(Rect(smallImg.cols - it->x - it->width, it->y, it->width, it->height));

		}

	}



	//��ֹ��ʱ

	t = (double)cvGetTickCount() - t;

	cout << "Detection time:" << t / (cvGetTickFrequency() * 1000) << "ms" << endl;



	//���軭����⵽���������۾���������

	if (draw)

	{

		flip(smallImg, smallImg, 1);//�ָ���ԭ����Сͼ��

		for (vector<Rect>::iterator r = faces.begin(); r != faces.end(); r++)

		{

			//���û�����������ɫ�����

			Scalar color(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255));

			rectangle(img, Point(cvRound((r->x)*scale), cvRound((r->y)*scale)),

				Point(cvRound((r->x + r->width + 1)*scale), cvRound((r->y + r->height + 1)*scale)),

				color, 1, 8, 0);



			//���ۼ����Ϊ��ʱ�������������

			if (nestedCascade.empty())

				continue;



			//����۾�

			Mat smallImgROI = smallImg(*r);  //ȡ������������

			vector<Rect> eyes;

			nestedCascade.detectMultiScale(smallImgROI, eyes, 1.1, 2,

				CV_HAAR_MAGIC_VAL, Size(30, 30));



			//���۾�

			for (vector<Rect>::iterator nr = eyes.begin(); nr != eyes.end(); nr++)

			{

				Scalar color(theRNG().uniform(0, 255), theRNG().uniform(0, 255), theRNG().uniform(0, 255));

				Point center(cvRound((r->x + nr->x + nr->width*0.5)*scale),

					cvRound((r->y + nr->y + nr->height*0.5))*scale); //�������ĵ�

				int radius = (nr->width + nr->height)*0.25*scale;

				circle(img, center, radius, color, 1, 8, 0);

			}

		}

		imshow("��ⴰ��", img);

		//imwrite("���2.jpg", img );

		waitKey();

	}

	return faces;

}



//��Ⲣ�и�ͼ��

Mat detectAndExtract(Mat& img, CascadeClassifier& cascade, CascadeClassifier& nestedCascade,

	double scale, bool trpflip, bool draw)

{

	//�������

	vector<Rect> faces = detectAndDraw(img, cascade, nestedCascade, scale, trpflip, false);

	int maxArea = 0;//�洢������������

	int id = -1; //faces�е�id



				 //Ѱ��faces����������face

	for (int i = 0; i < faces.size(); i++)

	{

		int area = faces[i].width*faces[i].height;//��ǰ������������

												  //Ѱ��������������id

		if (maxArea < area)

		{

			id = i;

			maxArea = area;

		}

	}



	//�и������

	Mat res;//����и����������

	if (id != -1)

	{

		res = img(faces[id]);

	}

	return res;

}