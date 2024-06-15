#include "Bezier.h"

void Bezier::PushCtrlPoint(double x, double y)
{
	Bpoints.push_back(point{ x,y });
}

void Bezier::PopCtrlPoint()
{
	Bpoints.pop_back();
}

void Bezier::SetCtrlPoint(double x, double y, int No)
{
	Bpoints[No] = point{ x,y };
}

point Bezier::GetPoint(int No)
{
	return Bpoints[No];
}

void Bezier::DrawCurve(double R, double G, double B, int Resoluton)
{
	int times = Bpoints.size();
	if (times == 0)
	{
		return;
	}
	else if (times == 1)//点数过少，直接计算返回即可
	{
		glPointSize(1);
		glBegin(GL_POINT);
		glVertex2f(Bpoints[0].x, Bpoints[0].y);
	}
	else
	{
		glPointSize(0.5);
		glBegin(GL_POINTS);
		for (size_t i = 0; i < Resoluton; i++)
		{
			double y_n = 0, x_n = 0;
			for (int j = 0; j < times; j++)
			{
				y_n += pow(i / (double)Resoluton, (double)j) * pow(1.0 - (i / (double)Resoluton), (double)(times - j - 1)) * Tri.GetElem(times - 1, j) * Bpoints[j].y;
				x_n += pow(i / (double)Resoluton, (double)j) * pow(1.0 - (i / (double)Resoluton), (double)(times - j - 1)) * Tri.GetElem(times - 1, j) * Bpoints[j].x;
			}
			glVertex2d(x_n, y_n);
		}
		glEnd();
		if (Bpoints.size()>34)//超过34个点时，坐标溢出，无法正常计算
		{
			glColor3f(1, 0, 0);
			glRasterPos2i(Bpoints.back().x, Bpoints.back().y);
			std::string Mesg = "Too Many Points!";
			for (const char& c : Mesg) {
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
			}
		}
	}
}

void Bezier::DrawCurveWithCtrl(double R, double G, double B, int Resoluton, double Ctrl_R, double Ctrl_G, double Ctrl_B)
{
	DrawCurve(R, G, B, Resoluton);
	DrawCtrl(Ctrl_R, Ctrl_G, Ctrl_B);
}

void Bezier::DrawCtrl(double R, double G, double B)
{
	if (Bpoints.size())
	{
		glColor3f(R, G, B);
		glBegin(GL_LINE_STRIP);
		for (size_t i = 0; i < Bpoints.size(); i++)
		{
			glVertex2f(Bpoints[i].x, Bpoints[i].y);
		}
		glEnd();
		glPointSize(5);
		glBegin(GL_POINTS);
		for (size_t i = 0; i < Bpoints.size(); i++)
		{
			glVertex2f(Bpoints[i].x, Bpoints[i].y);
		}
		glEnd();
	}
}

int Bezier::Size()
{
	return Bpoints.size();
}
