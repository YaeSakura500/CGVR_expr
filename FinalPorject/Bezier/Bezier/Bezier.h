#pragma once
#include<vector>
#include"YangTri.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<string>

struct point
	{
		double x;
		double y;
	};
class Bezier
{
public:
	void PushCtrlPoint(double x, double y);//����һ����
	void PopCtrlPoint();//ɾ�����ĵ�
	void SetCtrlPoint(double x, double y, int No);//���õ�No���������
	point GetPoint(int No);//��ȡ��No���������
	void DrawCurve(double R, double G, double B,int Resoluton);//����Bezier����
	void DrawCurveWithCtrl(double R, double G, double B, int Resoluton, double Ctrl_R, double Ctrl_G, double Ctrl_B);//��������+���Ƶ�
	void DrawCtrl(double R, double G, double B);//���ƿ��Ƶ㼰����
	int Size();//��ǰ���Ƶ�ĸ���
protected:
	std::vector<point> Bpoints{
	};//���Ƶ�
	YangTri Tri;//�������
};

