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
#define RESOLUTION 10000//Bezier�������ܹ��ĵ���
#define RANGE 50//�Ҽ�ʱ��Ѱ�㷶Χ

Bezier B;

int Win_w = 400, Win_h = 400;//��ʼ���ڴ�С
int Mouse_x, Mouse_y;//���λ��
bool isDragging = false; // �����Ƿ������϶�
int selectedPoint = -1;//��ѡ�еĿ��Ƶ�


void display();//�����ڻ��ƺ���
void resize(int w, int h);//�������ſ���
void mouse(int button, int state, int x, int y);//��굥����Ӧ����
void move(int x, int y);//��ȡ��굱ǰ����
void motion(int x, int y);//����϶�����
void key(unsigned char Button, int x, int y);//��������


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);//����Ĭ��λ��
	glutInitWindowSize(Win_w, Win_h);//����Ĭ�ϴ�С
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//RGBģʽ��˫����
	glutCreateWindow("Bezier");//������Bezier
	glutReshapeFunc(resize);//ע�����ź���
	glutDisplayFunc(display);//ע������ʾ����
	glutMouseFunc(mouse);//ע����굥������
	glutPassiveMotionFunc(move);//ע������ƶ�����
	glutMotionFunc(motion);//ע������϶�����
	glutKeyboardFunc(key);//ע�������Ӧ����
	glClearColor(1, 1, 1, 1);//���ñ���ɫ
	glutMainLoop();//glut��ѭ������
	return (0);


}

void key(unsigned char Button, int x, int y)
{
	if (Button == 'z')//��zɾ�����һ����
	{
		B.PopCtrlPoint();
	}
	glutPostRedisplay();
}

void motion(int x, int y) 
{
	Mouse_x = x;
	Mouse_y = Win_h - y;
	if (isDragging && selectedPoint != -1) // ���±�ѡ�п��Ƶ��λ��
	{
		B.SetCtrlPoint(Mouse_x, Mouse_y, selectedPoint);
		glutPostRedisplay();
	}
}

void move(int x, int y)
{
	//ʵʱ��ȡ���λ��
	Mouse_x = x;
	Mouse_y = Win_h - y;
	glutPostRedisplay();
}

void mouse(int button,int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		B.PushCtrlPoint((double)x,Win_h-(double)y );
	}
	if (button == GLUT_RIGHT_BUTTON )
	{
		if (state == GLUT_DOWN)// ���������£��ҵ���Χ������Ŀ��Ƶ�
		{

			double minDist = RANGE;
			int closestPointIndex = -1;
			point clickPoint = { (double)x,Win_h - (double)y };
			for (int i = 0; i < B.Size(); ++i) {
				double dist = std::sqrt(std::pow(B.GetPoint(i).x - clickPoint.x, 2) + std::pow(B.GetPoint(i).y - clickPoint.y, 2));
				if (dist < minDist) {
					minDist = dist;
					closestPointIndex = i;
				}
			}
			selectedPoint = closestPointIndex;//���±�ѡ�еĵ�
			isDragging = true;
		}
		else if (state == GLUT_UP) {
			// �������ͷţ�ֹͣ�϶�
			isDragging = false;
		}
	}
	glutPostRedisplay();
}

void resize(int w, int h) 
{
	if (h == 0)//���ⴰ�ڹ�С 
	{
		h = 1;
	}
	Win_w = w;//���´��ڴ�С
	Win_h = h;
	glViewport(0, 0, w, h);//�����ӿڴ�СΪ���ڴ�С
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, w, 0.0f, h, 1.0f, -1.0f);//����ͶӰ��������Ϊ���ڴ�С
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(1);
	B.DrawCurveWithCtrl(0, 0, 0, RESOLUTION, 1, 0, 0);//����
	{//���½����֣���굱ǰλ��
		glColor3f(0, 0, 0);
		glRasterPos2i(10, 10);
		std::string mousePos = "X:" + std::to_string(Mouse_x) + "Y:" + std::to_string(Mouse_y);
		for (const char& c : mousePos)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
		}
	}
	{//���½����֣���ǰ��ĸ���/��󲻳��������34��
		glColor3f(0, 0, 0);
		glRasterPos2i(Win_w - 30, 5);
		std::string Count = "[" + std::to_string(B.Size()) + "/34]";
		for (const char& c : Count)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, c);
		}	
	}
	glutSwapBuffers();
}
