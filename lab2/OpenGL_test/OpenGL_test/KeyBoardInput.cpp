//#pragma once
//#include"KeyBoardInput.h"
//#ifndef __APPLE__
//#include<gl/glut.h>
//#endif // !__APPLE__
//#include"Camera.h"
//extern Camera myCamera;
//static float angle_x=0, angle_y=0;
//void inputNormalKey(unsigned char key, int x, int y) {
//	switch (key)
//	{
//	case 'w':
//		myCamera.move_Front_Back(1);
//		break;
//	case 's':
//		myCamera.move_Front_Back(-1);
//		break;
//	case 'a':
//		myCamera.move_Left_Right(1);
//		break;
//	case 'd':
//		myCamera.move_Left_Right(-1);
//		break;              //wasd调整相机前后左右移动
//	case '1':
//		myCamera.move_High_Low(1);
//		break;
//	case '2':
//		myCamera.move_High_Low(-1);
//		break;              //1,2键上下移动相机
//	default:
//		break;
//	}
//}
//
//void inputSpecialKey(int key, int x, int y)
//{
//	switch (key)
//	{
//	case GLUT_KEY_LEFT:
//		angle_y -= 0.03f;
//		Yaw(angle_y);
//		break;
//	case GLUT_KEY_RIGHT:               //q,e键调用相机旋转
//		angle_y += 0.03f;
//		Yaw(angle_y);
//		break;
//	case GLUT_KEY_UP:
//		angle_x += 0.03f;
//		Pitch(angle_x);
//		break;
//	case GLUT_KEY_DOWN:               //q,e键调用相机旋转
//		angle_x -= 0.03f;
//		Pitch(angle_x);
//		break;
//	default:
//		break;
//	}
//}