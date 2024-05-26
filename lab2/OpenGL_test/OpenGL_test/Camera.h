#pragma once
#ifndef __MYCAMERA__
#include<gl/glut.h>
extern GLdouble ratio;
	class Camera
	{
	public:
		struct POS//相机位置,初始为（0，0，5）
		{
			float x, y, z;
		};
		POS pos;
		struct VIEW//视线方向，初始设为沿着Z轴负方向
		{
			float lx, ly, lz;
		};
		VIEW view, right, up;
		struct INNER_PARM//相机内参
		{
			float fov;//视场角
			float zoom_vol;//缩放倍率
		};
		INNER_PARM innerParm;
		struct ROTATION//旋转角度
		{
			float angle_yaw;//yaw
			float angle_pitch;//pitch
		};
		ROTATION rotation;
		Camera();
		//旋转相机，绕y轴旋转
		void Yaw(float ang);
		//旋转相机，绕x轴旋转
		void Pitch(float ang);
		//球坐标旋转
		void rotate();
		//视场角缩放
		void zoom(int dir);
		//计算向量绕任意轴旋转
		void rotateVec(float angle, VIEW* axie, VIEW* aim);

		//前后移动相机
		void move_Front_Back(int direction);
		//左右移动相机
		void move_Left_Right(int direction);
		//上下移动相机
		void move_High_Low(int direction);
	};
#define __MYCAMERA__
#endif