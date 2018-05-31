#include "CStatDir.h"

#include "Detection.h"



using namespace std;

using namespace cv;



//人脸检测的haar分类器的位置

string cascadeName = "E:\\OPENCV3.3\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml";

//眼睛检测的haar分类器的位置

string nesstedCascadeName = "E:\\OPeNCV3.3\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";



int main()

{

	CascadeClassifier cascade, nestedCascade;



	//加载分类器，如任意一个加载失败，则报错

	if (!cascade.load(cascadeName) || !nestedCascade.load(nesstedCascadeName))

	{

		cerr << "ERROR: cannot load classifier cascadeName or nestedCascade";
		
		return false;

	}



	//读取图像

	const char* dir = "F:\\finally\\pic\\color\\1\\";

	vector<pair<string, Mat >> Vp;//存放读取出来的图像信息

	Vp = read_Img(dir);

	double scale = 1.1;

	bool trpflip = false;

	bool draw = false;

	for (int i = 0; i < Vp.size(); i++)

	{

		Mat face = detectAndExtract(Vp[i].second, cascade, nestedCascade, scale, trpflip, draw);

		imwrite(Vp[i].first, face);

	}

	return true;



}