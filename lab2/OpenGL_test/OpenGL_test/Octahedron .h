#pragma once
#include<gl/glut.h>
#include<iostream>
class Octahedron
{
public:
	Octahedron(float l,float w,float h);//初始化八面体尺寸
	void setPos(float x, float y, float z);//设置八面体中心位置
	int setTexture(GLuint);//设置纹理
	void showFaceWithSingleTex();//使用最后一个纹理渲染
	void showFaceWithDuoTex();//用两个纹理渲染上下面
	void showEdge(float R, float G, float B,float LineWidth);//显示棱
	void getver();//计算顶点位置

private:
	//八面体大小
	float length;
	float width;
	float height;
	//中心位置
	float x;
	float y;
	float z;
	//纹理
	struct textureChain
	{
		int No;
		GLuint texture;
		textureChain* next = NULL;
	};
	textureChain* Texture;
	//顶点位置
	float n, f, r, l, t, b;
};
