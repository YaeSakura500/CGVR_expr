#pragma once
#include"Camera.h"
#include<cmath>
#include<gl/glut.h>
#include<glm/glm.hpp>
#include<vector>

Camera::Camera()
{
	this->pos.x = 0.0f;
	this->pos.y = 0.0f;
	this->pos.z = 5.0f;
	this->view.lx = 0.0f;
	this->view.ly = 0.0f;
	this->view.lz = -1.0f;
	this->right.lx = 1.0f;
	this->right.ly = 0.0f;
	this->right.lz = 0.0f;
	this->up.lx = 0.0f;
	this->up.ly = 1.0f;
	this->up.lz = 0.0f;
	this->innerParm.fov = 45;
	this->innerParm.zoom_vol = 1;
	this->rotation.angle_yaw = 0.0;//��y�����ת��
	this->rotation.angle_pitch = 0.0;//��x�����ת��
}
//��ת�������y����ת
void Camera::Yaw(float ang)
{
	float* temp = new(float);
	*temp = powf(powf(this->view.lx, 2) + powf(this->view.lz, 2), 0.5);
	this->view.lx = *temp * sin(ang);
	this->view.lz = *temp * -cos(ang);
	//�������ĵ㣨�����߷����ϵĵ㣩���Ϊ��һ��Բ����ת�������õĵ������Ӧ������ת�ģ�ͨ��Բ�뾶��������
	delete(temp);
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);

}
//��ת�������x����ת
void Camera::Pitch(float ang)
{
	float* temp = new(float);
	*temp = powf(powf(this->view.ly, 2) + powf(this->view.lz, 2), 0.5);
	this->view.ly = *temp * sin(ang);
	this->view.lz = *temp * -cos(ang);
	//�������ĵ㣨�����߷����ϵĵ㣩���Ϊ��һ��Բ����ת�������õĵ������Ӧ������ת�ģ�ͨ��Բ�뾶��������
	delete(temp);
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);

}

void Camera::rotate()
{
	rotation.angle_pitch = rotation.angle_pitch > 1.57 ? 1.57 : rotation.angle_pitch;
	rotation.angle_pitch = rotation.angle_pitch < -1.57 ? -1.57 : rotation.angle_pitch;
	view.lz = -cos(rotation.angle_pitch) * cos(rotation.angle_yaw);
	view.lx = cos(rotation.angle_pitch) * sin(rotation.angle_yaw);
	view.ly = sin(rotation.angle_pitch);
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);

}


//����ӳ�����
void Camera::zoom(int dir)
{
	this->innerParm.fov = this->innerParm.fov + dir * this->innerParm.zoom_vol;
	if (this->innerParm.fov < 1)
	{
		this->innerParm.fov = 1;
	}
	else if (this->innerParm.fov > 90)
	{
		this->innerParm.fov = 90;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(innerParm.fov, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);     //ģ�ͱ任
	glLoadIdentity();
	//��������ۣ�λ�ã� �۾����ĵ㣨���λ��+���߷��򣩣� �۲��߱����򣨽Ƕȣ�����������
	gluLookAt(pos.x, pos.y,pos.z,pos.x + view.lx, pos.y + view.ly, pos.z + view.lz, 0.0f, 1.0f, 0.0f);

}

//��ת������
void Camera::rotateVec(float angle, VIEW* axie, VIEW* aim)
{
	/** ���� sin ��cosֵ */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
	VIEW* nV = new(VIEW);
	/** ������ת������xֵ */
	nV->lx = (cosTheta + (1 - cosTheta) * axie->lx * axie->lx) * aim->lx;
	nV->lx += ((1 - cosTheta) * axie->lx * axie->ly - axie->lz * sinTheta) * aim->ly;
	nV->lx += ((1 - cosTheta) * axie->lx * axie->lz + axie->ly * sinTheta) * aim->lz;

	/** ������ת������yֵ */
	nV->ly = ((1 - cosTheta) * axie->lx * axie->ly + axie->lz * sinTheta) * aim->lx;
	nV->ly += (cosTheta + (1 - cosTheta) * axie->ly * axie->ly) * aim->ly;
	nV->ly += ((1 - cosTheta) * axie->ly * axie->lz - axie->lx * sinTheta) * aim->lz;

	/** ������ת������zֵ */
	nV->lz = ((1 - cosTheta) * axie->lx * axie->lz - axie->ly * sinTheta) * aim->lx;
	nV->lz += ((1 - cosTheta) * axie->ly * axie->lz + axie->lx * sinTheta) * aim->ly;
	nV->lz += (cosTheta + (1 - cosTheta) * axie->lz * axie->lz) * aim->lz;

	//������������� 
	aim->lx = nV->lx;
	aim->ly = nV->ly;
	aim->lz = nV->lz;
	delete(nV);
}

//ǰ���ƶ����
void Camera::move_Front_Back(int direction)
{
	this->pos.x = this->pos.x + direction * (this->view.lx) * 0.1;
	this->pos.z = this->pos.z + direction * (this->view.lz) * 0.1;
	this->pos.y = this->pos.y + direction * (this->view.ly) * 0.1;
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);
	
	//ͬʱ�ƶ�����������ĵ�����,���߲��������޸ģ�
}

//�����ƶ����
void Camera::move_Left_Right(int direction)
{
	this->pos.x = this->pos.x + direction * (this->view.lz) * 0.1;
	this->pos.z = this->pos.z - direction * (this->view.lx) * 0.1;
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);
}
//�����ƶ����
void Camera::move_High_Low(int direction)
{
	this->pos.y = this->pos.y + direction * 0.1;
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);
}

