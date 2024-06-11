
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<stdio.h>
#include<vector>
#include<iostream>
int DrawPixel(int x, int y);
int BrCircle(int x0, int y0, int R);
void display();
void resize(int w, int h);
int main(int argc,char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(400, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	glutCreateWindow("Circle");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glClearColor(1, 1, 1, 1);
	glutMainLoop();
	return (0);


}



void resize(int w, int h) {
	if (h == 0) {
		h = 1;
	}

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(0.0f, 400.0f, 200-200.f * h / w, 200+200.f * h / w, 1.0f, -1.0f);
	}
	else {
		glOrtho(200 - 200.0f * w / h, 200+200.0f * w / h, 0.0f, 400.0f, 1.0f, -1.0f);
	}
	std::cout << "w:" << w << "  h:" << h << std::endl;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1, 0, 0);
	glLineWidth(1);
	glColor3f(0, 0, 0);
	BrCircle(200, 200, 150);
	glFlush();
}

int DrawPixel(int x, int y)//���Ƶ�һ����
{
	//glColor3d(0, 0, 0);
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
	return(0);
}

int BrCircle(int x0, int y0, int R)//Բ��λ�á��뾶
{
	double x = 0, y = R,delta=0;
	while (y >= x)//������ڶ��˷�Բ������ͨ���Գ��Եõ�
	{
		DrawPixel(x + x0, y + y0);//�ڶ��˷�Բ
		DrawPixel(-x + x0, y + y0);//�����˷�Բ
		DrawPixel(x + x0, -y + y0);//���߰˷�Բ
		DrawPixel(-x + x0, -y + y0);//�����˷�Բ
		DrawPixel(y + x0, x + y0);//��һ�˷�Բ
		DrawPixel(-y + x0, x + y0);//�ڰ˰˷�Բ
		DrawPixel(y + x0, -x + y0);//���İ˷�Բ
		DrawPixel(-y + x0, -x + y0);//����˷�Բ
		if (delta > 0)//bressenham��Բ��
		{
			if (2 * (delta - x) + 1>=0)
			{
				y -= 1;
				delta = delta - 2 * y + 3;
			}
			else
			{
				x++;
				y--;
				delta = delta + 2 * x - 2 * y + 2;
			}
		}
		else if (delta < 0)
		{
			if (2 * (delta + y) - 1 <= 0)
			{
				x++;
				delta = delta + 2 * x + 3;
			}
			else
			{
				x++;
				y--;
				delta = delta + 2 * x - 2 * y + 2;
				
			}
		}
		else
		{
			x++;
			y--;
			delta = delta + 2 * x - 2 * y + 2;
		}

	}
	return(0);
}