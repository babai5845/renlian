#include "CStatDir.h"



CStatDir::CStatDir()

{

	//��ʼ�����ݳ�Աm_nFileCount��m_nSubdirCount

	m_nFileCount = m_nSubdirCount = 0;

}



//�����ļ�����

int CStatDir::GetFileCount()

{

	return m_nFileCount;

}



//������Ŀ¼����

int CStatDir::GetSubdirCount()

{

	return m_nSubdirCount;

}



//��д�麯��ProcessFile��ÿ����һ�Σ��ļ�������1  

bool CStatDir::ProcessFile(const char *filename)

{

	m_nFileCount++;

	return CBrowseDir::ProcessFile(filename);

}



//��д�麯��ProcessDir��ÿ����һ�Σ���Ŀ¼������1

void CStatDir::ProcessDir(const char *currentdir, const char *parentdir)

{

	m_nSubdirCount++;

	CBrowseDir::ProcessDir(currentdir, parentdir);

}