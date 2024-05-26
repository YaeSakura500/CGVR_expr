#pragma once
#ifndef __MYCAMERA__
#include<gl/glut.h>
extern GLdouble ratio;
	class Camera
	{
	public:
		struct POS//���λ��,��ʼΪ��0��0��5��
		{
			float x, y, z;
		};
		POS pos;
		struct VIEW//���߷��򣬳�ʼ��Ϊ����Z�Ḻ����
		{
			float lx, ly, lz;
		};
		VIEW view, right, up;
		struct INNER_PARM//����ڲ�
		{
			float fov;//�ӳ���
			float zoom_vol;//���ű���
		};
		INNER_PARM innerParm;
		struct ROTATION//��ת�Ƕ�
		{
			float angle_yaw;//yaw
			float angle_pitch;//pitch
		};
		ROTATION rotation;
		Camera();
		//��ת�������y����ת
		void Yaw(float ang);
		//��ת�������x����ת
		void Pitch(float ang);
		//��������ת
		void rotate();
		//�ӳ�������
		void zoom(int dir);
		//������������������ת
		void rotateVec(float angle, VIEW* axie, VIEW* aim);

		//ǰ���ƶ����
		void move_Front_Back(int direction);
		//�����ƶ����
		void move_Left_Right(int direction);
		//�����ƶ����
		void move_High_Low(int direction);
	};
#define __MYCAMERA__
#endif