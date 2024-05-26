#pragma once
#ifndef __MYIO__

#pragma warning(disable: 4996)
#include<gl/glut.h>
#include<cstdio>

#define BMP_Header_Length 54
namespace MYIO
{
	GLuint loadTextureFromBmp(const char* file_name);//从bmp图像加载纹理
	GLuint loadTexture(const char* file_name);//从jpg/png等加载纹理
};
#define __MYIO__
#endif // !__MYIO__
