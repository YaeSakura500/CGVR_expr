//#pragma once
//#include"MouseInput.h"
//#include"Motivation.h"
//#ifndef __APPLE__
//#include<gl/glut.h>
//#endif // !__APPLE__
//
//#include<iostream>
//#define GLUT_WHEEL_UP 3 //定义滚轮操作
//#define GLUT_WHEEL_DOWN 4
//#define ZOOM_IN 1
//#define ZOOM_OUT -1
//static float x = 0.0f, y = 0.0f, z = 5.0f;//相机位置
//static float lx = 0.0f, ly = 0.0f, lz = -1.0f;//视线方向，初始设为沿着Z轴负方向
//static float fov = 45;
//static float zoom_vol = 1;
//static float ratio = 1.33;
//void inputMouse(int button, int state, int x, int y)
//{
//	if (state == GLUT_UP && button == GLUT_WHEEL_UP)
//	{
//		zoom(ZOOM_IN);
//		//scale = pow(zoom_vol,ZOOM_IN);
//	}
//	else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN)
//	{
//		zoom(ZOOM_OUT);
//		//scale = pow(zoom_vol, ZOOM_OUT);;
//	}
//	std::cout << "fov:" << fov << std::endl;
//	glLoadIdentity();
//	gluPerspective(fov, ratio, 1, 1000);
//	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
//
//	glutPostRedisplay();
//}