#pragma once
#ifndef __MYCONTROL__

#include<gl/glut.h>
namespace Control
{
	void inputSpecialKey(int key, int x, int y);//键盘上下左右视角
	void inputNormalKey(unsigned char key, int x, int y);//wasd12前后左右上下
	void inputMouse(int button, int state, int x, int y);//滚轮缩放
};
#define __MYCONTROL__
#endif // !__MYCONTROL__
