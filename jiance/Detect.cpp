////Detect.cpp  
////Preprocessing - Detect, Cut and Save  
////@Author : Rachel-Zhang  
//
//#include "opencv2/objdetect/objdetect.hpp"  
//#include "opencv2/highgui/highgui.hpp"  
//#include "opencv2/imgproc/imgproc.hpp"  
//
//#include <cctype>  
//#include <iostream>  
//#include <iterator>  
//#include <stdio.h>  
//#include "BrowseDir.h"  
////#include "StatDir.h"  
//#include "Prehelper.h"  
//
//using namespace std;
//using namespace cv;
//#define CAM 2  
//#define PHO 1  
//#define K 5  
//
//string cascadeName = "E:/OPENCV3.3/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
//string nestedCascadeName = "E:/OPENCV3.3/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
//
//int main()
//{
//	CvCapture* capture = 0;
//	Mat frame, frameCopy, image;
//	string inputName;
//	bool tryflip = false;
//	int mode;
//	CascadeClassifier cascade, nestedCascade;
//	double scale = 1.0;
//	if (!cascade.load(cascadeName) || !nestedCascade.load(nestedCascadeName))
//	{
//		cerr << "ERROR: Could not load classifier cascade or nestedCascade" << endl;//若出现该问题请去检查cascadeName，可能是opencv版本路径问题  
//		return -1;
//	}
//
//	//  printf("select the mode of detection: \n1: from picture\t 2: from camera\n");  
//	//  scanf("%d",&mode);  
//	char** pics = (char**)malloc(sizeof*pics);
//
//	/************************************************************************/
//	/*                                  detect face and save                                    */
//	/************************************************************************/
//	int i, j;
//	cout << "detect and save..." << endl;
//	const char dir[256] = "F:\\finally\\pic\\";
//	string cur_dir;
//	char id[5];
//	for (i = 1; i <= K; i++)
//	{
//		cur_dir = dir;
//		_itoa_s(i, id, 10);
//		cur_dir.append("color\\");
//		cur_dir.append(id);
//		vector<pair<char*, Mat>> imgs = read_img(cur_dir);
//		for (j = 0; j<imgs.size(); j++)
//		{
//			IplImage* res = DetectandExtract(imgs[j].second, cascade, nestedCascade, scale, tryflip);
//			if (res)
//				cvSaveImage(imgs[j].first, res);
//		}
//	}
//	return 0;
//}