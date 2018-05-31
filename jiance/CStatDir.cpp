#include "CStatDir.h"



CStatDir::CStatDir()

{

	//初始化数据成员m_nFileCount和m_nSubdirCount

	m_nFileCount = m_nSubdirCount = 0;

}



//返回文件个数

int CStatDir::GetFileCount()

{

	return m_nFileCount;

}



//返回子目录个数

int CStatDir::GetSubdirCount()

{

	return m_nSubdirCount;

}



//覆写虚函数ProcessFile，每调用一次，文件个数加1  

bool CStatDir::ProcessFile(const char *filename)

{

	m_nFileCount++;

	return CBrowseDir::ProcessFile(filename);

}



//覆写虚函数ProcessDir，每调用一次，子目录个数加1

void CStatDir::ProcessDir(const char *currentdir, const char *parentdir)

{

	m_nSubdirCount++;

	CBrowseDir::ProcessDir(currentdir, parentdir);

}