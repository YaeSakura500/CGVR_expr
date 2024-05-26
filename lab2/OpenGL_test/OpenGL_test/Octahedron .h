#pragma once
#include<gl/glut.h>
#include<iostream>
class Octahedron
{
public:
	Octahedron(float l,float w,float h);//��ʼ��������ߴ�
	void setPos(float x, float y, float z);//���ð���������λ��
	int setTexture(GLuint);//��������
	void showFaceWithSingleTex();//ʹ�����һ��������Ⱦ
	void showFaceWithDuoTex();//������������Ⱦ������
	void showEdge(float R, float G, float B,float LineWidth);//��ʾ��
	void getver();//���㶥��λ��

private:
	//�������С
	float length;
	float width;
	float height;
	//����λ��
	float x;
	float y;
	float z;
	//����
	struct textureChain
	{
		int No;
		GLuint texture;
		textureChain* next = NULL;
	};
	textureChain* Texture;
	//����λ��
	float n, f, r, l, t, b;
};
