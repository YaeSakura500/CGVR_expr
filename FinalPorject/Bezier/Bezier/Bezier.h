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
	void PushCtrlPoint(double x, double y);//加入一个点
	void PopCtrlPoint();//删除最后的点
	void SetCtrlPoint(double x, double y, int No);//设置第No个点的坐标
	point GetPoint(int No);//获取第No个点的坐标
	void DrawCurve(double R, double G, double B,int Resoluton);//绘制Bezier曲线
	void DrawCurveWithCtrl(double R, double G, double B, int Resoluton, double Ctrl_R, double Ctrl_G, double Ctrl_B);//绘制曲线+控制点
	void DrawCtrl(double R, double G, double B);//绘制控制点及连线
	int Size();//当前控制点的个数
protected:
	std::vector<point> Bpoints{
	};//控制点
	YangTri Tri;//杨辉三角
};

