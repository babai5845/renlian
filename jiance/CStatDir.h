#pragma once
#ifndef CSTATDIR_H

#define CSTATDIR_H

#include "CBrowseDir.h"



class CStatDir :public CBrowseDir

{

protected:

	int m_nFileCount; //保存文件个数  

	int m_nSubdirCount; //保存子目录个数 



public:

	CStatDir();

	//返回文件个数  

	int GetFileCount();

	//返回子目录个数  

	int GetSubdirCount();

protected:

	//覆写虚函数ProcessFile，每调用一次，文件个数加1  

	virtual bool ProcessFile(const char *filename);

	//覆写虚函数ProcessDir，每调用一次，子目录个数加1  

	virtual void ProcessDir(const char *currentdir, const char *parentdir);

};

#endif