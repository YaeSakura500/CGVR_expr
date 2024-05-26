#include "Control.h"
#include"Camera.h"
#define GLUT_WHEEL_UP 3 //定义滚轮操作
#define GLUT_WHEEL_DOWN 4
#define ZOOM_IN -1
#define ZOOM_OUT 1
extern Camera myCamera;
//键盘特殊输入
void Control::inputSpecialKey(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		myCamera.rotation.angle_yaw -= 0.03f;
		//myCamera.Yaw(myCamera.rotation.angle_yaw);
		break;
	case GLUT_KEY_RIGHT:
		myCamera.rotation.angle_yaw += 0.03f;
		//myCamera.Yaw(myCamera.rotation.angle_yaw);
		break;
	case GLUT_KEY_UP:										//方向键调用相机旋转
		myCamera.rotation.angle_pitch += 0.03f;
		//myCamera.Pitch(myCamera.rotation.angle_pitch);
		break;
	case GLUT_KEY_DOWN:
		myCamera.rotation.angle_pitch -= 0.03f;
		//myCamera.Pitch(myCamera.rotation.angle_pitch);
		break;
	default:
		break;
	}
	myCamera.rotate();
}
//键盘常规输入
void Control::inputNormalKey(unsigned char key, int x, int y) 
{
	switch (key)
	{
	case 'w':
		myCamera.move_Front_Back(1);
		break;
	case 's':
		myCamera.move_Front_Back(-1);
		break;
	case 'a':
		myCamera.move_Left_Right(1);
		break;
	case 'd':
		myCamera.move_Left_Right(-1);
		break;              //wasd调整相机前后左右移动
	case '1':
		myCamera.move_High_Low(1);
		break;
	case '2':
		myCamera.move_High_Low(-1);
		break;              //1,2键上下移动相机
	default:
		break;
	}
}

//鼠标输入
void Control::inputMouse(int button, int state, int x, int y)
{
	if (state == GLUT_UP && button == GLUT_WHEEL_UP)
	{
		myCamera.zoom(ZOOM_IN);
		//scale = pow(zoom_vol,ZOOM_IN);
	}
	else if (state == GLUT_UP && button == GLUT_WHEEL_DOWN)
	{
		myCamera.zoom(ZOOM_OUT);
	}
}
