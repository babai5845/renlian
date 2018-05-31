#include "opencv2/objdetect/objdetect.hpp"  
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  

#include <cctype>  
#include <iostream>  
#include <iterator>  
#include <stdio.h>  
#include <string>
#include "CBrowseDir.h"



using namespace std;





CBrowseDir::CBrowseDir()

{

	//�õ�ǰĿ¼��ʼ��m_szInitDir 

	_getcwd(m_szInitDir, _MAX_PATH);



	//���Ŀ¼�����һ����ĸ����'\',����������һ��'\'

	int len = strlen(m_szInitDir);

	if (m_szInitDir[len - 1] != '\\')

		strcat_s(m_szInitDir, "\\");

}



bool CBrowseDir::setInitDir(const char* dir)

{

	//�Ȱ�dirת��Ϊ����·��

	if (_fullpath(m_szInitDir, dir, _MAX_PATH) == NULL)

		return false;



	//�ж�Ŀ¼�Ƿ����  

	if (_chdir(m_szInitDir) != 0)

		return false;



	//���Ŀ¼�����һ����ĸ����'\',����������һ��'\'

	int len = strlen(m_szInitDir);

	if (m_szInitDir[len - 1] != '\\')

		strcat_s(m_szInitDir, "\\");



	return true;

}



vector<char*> CBrowseDir::BeginBrowseFilenames(const char *filespec)

{

	ProcessDir(m_szInitDir, NULL);

	return GetDirFilenames(m_szInitDir, filespec);

}



bool CBrowseDir::BeginBrowse(const char *filespec)

{

	ProcessDir(m_szInitDir, NULL);

	return BrowseDir(m_szInitDir, filespec);

}



bool CBrowseDir::BrowseDir(const char *dir, const char *filespec)

{

	_chdir(dir);



	//���Ȳ���dir�з���Ҫ����ļ� 

	long hFile;

	_finddata_t fileinfo;

	if ((hFile = _findfirst(filespec, &fileinfo)) != -1)

	{

		do

		{

			//����ǲ���Ŀ¼  

			//�������,����д���  

			if (!(fileinfo.attrib & _A_SUBDIR))

			{

				char fileName[_MAX_PATH];

				strcpy_s(fileName, dir);

				strcat_s(fileName, fileinfo.name);

				cout << fileName << endl;

				if (!ProcessFile(fileName))

					return false;

			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);

	}



	//����dir�е���Ŀ¼  

	//��Ϊ�ڴ���dir�е��ļ�ʱ���������ProcessFile�п��ܸı���  

	//��ǰĿ¼����˻�Ҫ�������õ�ǰĿ¼Ϊdir��  

	//ִ�й�_findfirst�󣬿���ϵͳ��¼���������Ϣ����˸ı�Ŀ¼  

	//��_findnextû��Ӱ�졣

	_chdir(dir);

	if ((hFile = _findfirst(filespec, &fileinfo)) != -1)

	{

		do

		{

			//����ǲ���Ŀ¼ (���ļ���)

			//�����,�ټ���ǲ��� . �� ..   

			//�������,���е���  

			if (fileinfo.attrib & _A_SUBDIR)

			{

				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)

				{

					char subdir[_MAX_PATH];

					strcpy_s(subdir, dir);

					strcat_s(subdir, fileinfo.name);

					strcat_s(subdir, "\\");

					ProcessDir(subdir, dir);

					if (!BrowseDir(subdir, filespec))

						return false;

				}

			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);

	}

	return true;

}







vector<char*> CBrowseDir::GetDirFilenames(const char *dir, const char *filespec)

{

	_chdir(dir);

	vector<char*> filesName;

	filesName.clear();



	//���Ȳ���dir�з���Ҫ����ļ� 

	long hFile;

	_finddata_t fileinfo;

	if ((hFile = _findfirst(filespec, &fileinfo)) != -1)

	{

		do

		{

			//����ǲ���Ŀ¼  

			//�������,����д���  

			if (!(fileinfo.attrib & _A_SUBDIR))

			{

				char fileName[_MAX_PATH];

				strcpy_s(fileName, dir);

				strcat_s(fileName, fileinfo.name);

				filesName.push_back(fileName);

			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);

	}



	//����dir�е���Ŀ¼  

	//��Ϊ�ڴ���dir�е��ļ�ʱ���������ProcessFile�п��ܸı���  

	//��ǰĿ¼����˻�Ҫ�������õ�ǰĿ¼Ϊdir��  

	//ִ�й�_findfirst�󣬿���ϵͳ��¼���������Ϣ����˸ı�Ŀ¼  

	//��_findnextû��Ӱ�졣

	_chdir(dir);

	if ((hFile = _findfirst(filespec, &fileinfo)) != -1)

	{

		do

		{

			//����ǲ���Ŀ¼ (���ļ���)

			//�����,�ټ���ǲ��� . �� ..   

			//�������,���е���  

			if (fileinfo.attrib & _A_SUBDIR)

			{

				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)

				{

					char subdir[_MAX_PATH];

					strcpy_s(subdir, dir);

					strcat_s(subdir, fileinfo.name);

					strcat_s(subdir, "\\");

					ProcessDir(subdir, dir);

					vector<char*> subdirFileNames = GetDirFilenames(subdir, filespec);

					for (vector<char*>::iterator it = subdirFileNames.begin(); it != subdirFileNames.end(); it++)

						filesName.push_back(*it);

				}

			}

		} while (_findnext(hFile, &fileinfo) == 0);

		_findclose(hFile);

	}

	return filesName;

}



void CBrowseDir::ProcessDir(const char *currentdir, const char *parentdir)

{

}





bool CBrowseDir::ProcessFile(const char *filename)

{

	return true;

}