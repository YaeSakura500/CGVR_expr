#pragma once
#ifndef __MYIO__

#pragma warning(disable: 4996)
#include<gl/glut.h>
#include<cstdio>

#define BMP_Header_Length 54
namespace MYIO
{
	GLuint loadTextureFromBmp(const char* file_name);//��bmpͼ���������
	GLuint loadTexture(const char* file_name);//��jpg/png�ȼ�������
};
#define __MYIO__
#endif // !__MYIO__
