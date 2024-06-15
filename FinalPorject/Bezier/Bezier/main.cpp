#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<vector>
#include<string>
#include<iostream>
#include"YangTri.h"
#include"Bezier.h"
#define RESOLUTION 10000//Bezier曲线上总共的点数


Bezier B;


int Win_x = 400, Win_y = 400;//初始窗口大小
int Mouse_x, Mouse_y;//鼠标位置
bool isDragging = false; // 跟踪是否正在拖动
int selectedPoint = -1;//被选中的控制点


void display();//主窗口绘制函数
void resize(int w, int h);//窗口缩放控制
void mouse(int button, int state, int x, int y);//鼠标单击响应函数
void move(int x, int y);//获取鼠标当前坐标
void motion(int x, int y);//鼠标拖动处理
void key(unsigned char Button, int x, int y);//键盘输入


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutCreateWindow("Bezier");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(move);
	glutMotionFunc(motion);
	glutKeyboardFunc(key);
	glClearColor(1, 1, 1, 1);
	glutMainLoop();
	return (0);


}

void key(unsigned char Button, int x, int y)
{
	if (Button == 'z')//按z删除最后一个点
	{
		B.PopCtrlPoint();
	}
	glutPostRedisplay();
}

void motion(int x, int y) 
{
	Mouse_x = x;
	Mouse_y = Win_y - y;
	if (isDragging && selectedPoint != -1) {
		// 更新被选中控制点的位置
		B.SetCtrlPoint(Mouse_x, Mouse_y, selectedPoint);
		glutPostRedisplay();
	}
}

void move(int x, int y)
{
	//实时获取鼠标位置
	Mouse_x = x;
	Mouse_y = Win_y - y;
	glutPostRedisplay();
}

void mouse(int button,int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		B.PushCtrlPoint((double)x,Win_y-(double)y );
	}
	if (button == GLUT_RIGHT_BUTTON )
	{
		if (state == GLUT_DOWN) {
			// 鼠标左键按下，找到范围内最近的控制点
			double minDist = 50;
			int closestPointIndex = -1;
			point clickPoint = { (double)x,Win_y - (double)y };
			for (int i = 0; i < B.Size(); ++i) {
				double dist = std::sqrt(std::pow(B.GetPoint(i).x - clickPoint.x, 2) + std::pow(B.GetPoint(i).y - clickPoint.y, 2));
				if (dist < minDist) {
					minDist = dist;
					closestPointIndex = i;
				}
			}
			selectedPoint = closestPointIndex;//更新被选中的点
			isDragging = true;
		}
		else if (state == GLUT_UP) {
			// 鼠标左键释放，停止拖动
			isDragging = false;
		}
	}
	glutPostRedisplay();
}

void resize(int w, int h) 
{
	if (h == 0)//避免窗口过小 
	{
		h = 1;
	}
	Win_x = w;//更新窗口大小
	Win_y = h;
	glViewport(0, 0, w, h);//设置视口大小为窗口大小
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, w, 0.0f, h, 1.0f, -1.0f);//设置投影立方体宽高为窗口大小
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(1);
	B.DrawCurveWithCtrl(0, 0, 0, RESOLUTION, 1, 0, 0);//画线
	{//左下角文字：鼠标当前位置
		glColor3f(0, 0, 0);
		glRasterPos2i(10, 10);
		std::string mousePos = "X:" + std::to_string(Mouse_x) + "Y:" + std::to_string(Mouse_y);
		for (const char& c : mousePos)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
		}
	}
	{//右下角文字：当前点的个数
		glColor3f(0, 0, 0);
		glRasterPos2i(Win_x - 30, 5);
		std::string Count = "[" + std::to_string(B.Size()) + "/34]";
		for (const char& c : Count)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
		}
		glutSwapBuffers();
	}
}
