#pragma once
#ifndef CSTATDIR_H

#define CSTATDIR_H

#include "CBrowseDir.h"



class CStatDir :public CBrowseDir

{

protected:

	int m_nFileCount; //�����ļ�����  

	int m_nSubdirCount; //������Ŀ¼���� 



public:

	CStatDir();

	//�����ļ�����  

	int GetFileCount();

	//������Ŀ¼����  

	int GetSubdirCount();

protected:

	//��д�麯��ProcessFile��ÿ����һ�Σ��ļ�������1  

	virtual bool ProcessFile(const char *filename);

	//��д�麯��ProcessDir��ÿ����һ�Σ���Ŀ¼������1  

	virtual void ProcessDir(const char *currentdir, const char *parentdir);

};

#endif