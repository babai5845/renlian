#include "CStatDir.h"

#include "Detection.h"



using namespace std;

using namespace cv;



//��������haar��������λ��

string cascadeName = "E:\\OPENCV3.3\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml";

//�۾�����haar��������λ��

string nesstedCascadeName = "E:\\OPeNCV3.3\\opencv\\sources\\data\\haarcascades\\haarcascade_eye_tree_eyeglasses.xml";



int main()

{

	CascadeClassifier cascade, nestedCascade;



	//���ط�������������һ������ʧ�ܣ��򱨴�

	if (!cascade.load(cascadeName) || !nestedCascade.load(nesstedCascadeName))

	{

		cerr << "ERROR: cannot load classifier cascadeName or nestedCascade";
		
		return false;

	}



	//��ȡͼ��

	const char* dir = "F:\\finally\\pic\\color\\1\\";

	vector<pair<string, Mat >> Vp;//��Ŷ�ȡ������ͼ����Ϣ

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