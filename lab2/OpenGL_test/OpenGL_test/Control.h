#pragma once
#ifndef __MYCONTROL__

#include<gl/glut.h>
namespace Control
{
	void inputSpecialKey(int key, int x, int y);//�������������ӽ�
	void inputNormalKey(unsigned char key, int x, int y);//wasd12ǰ����������
	void inputMouse(int button, int state, int x, int y);//��������
};
#define __MYCONTROL__
#endif // !__MYCONTROL__
