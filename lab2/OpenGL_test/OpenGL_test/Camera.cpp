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
	this->rotation.angle_yaw = 0.0;//绕y轴的旋转角
	this->rotation.angle_pitch = 0.0;//绕x轴的旋转角
}
//旋转相机，绕y轴旋转
void Camera::Yaw(float ang)
{
	float* temp = new(float);
	*temp = powf(powf(this->view.lx, 2) + powf(this->view.lz, 2), 0.5);
	this->view.lx = *temp * sin(ang);
	this->view.lz = *temp * -cos(ang);
	//把所看的点（即视线方向上的点）理解为在一个圆上旋转，那设置的点的坐标应该是旋转的，通过圆半径计算坐标
	delete(temp);
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);

}
//旋转相机，绕x轴旋转
void Camera::Pitch(float ang)
{
	float* temp = new(float);
	*temp = powf(powf(this->view.ly, 2) + powf(this->view.lz, 2), 0.5);
	this->view.ly = *temp * sin(ang);
	this->view.lz = *temp * -cos(ang);
	//把所看的点（即视线方向上的点）理解为在一个圆上旋转，那设置的点的坐标应该是旋转的，通过圆半径计算坐标
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


//相机视场缩放
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
	glMatrixMode(GL_MODELVIEW);     //模型变换
	glLoadIdentity();
	//相机（人眼）位置， 眼睛看的点（相机位置+视线方向）， 观察者本身方向（角度，比如正立）
	gluLookAt(pos.x, pos.y,pos.z,pos.x + view.lx, pos.y + view.ly, pos.z + view.lz, 0.0f, 1.0f, 0.0f);

}

//旋转坐标轴
void Camera::rotateVec(float angle, VIEW* axie, VIEW* aim)
{
	/** 计算 sin 和cos值 */
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
	VIEW* nV = new(VIEW);
	/** 计算旋转向量的x值 */
	nV->lx = (cosTheta + (1 - cosTheta) * axie->lx * axie->lx) * aim->lx;
	nV->lx += ((1 - cosTheta) * axie->lx * axie->ly - axie->lz * sinTheta) * aim->ly;
	nV->lx += ((1 - cosTheta) * axie->lx * axie->lz + axie->ly * sinTheta) * aim->lz;

	/** 计算旋转向量的y值 */
	nV->ly = ((1 - cosTheta) * axie->lx * axie->ly + axie->lz * sinTheta) * aim->lx;
	nV->ly += (cosTheta + (1 - cosTheta) * axie->ly * axie->ly) * aim->ly;
	nV->ly += ((1 - cosTheta) * axie->ly * axie->lz - axie->lx * sinTheta) * aim->lz;

	/** 计算旋转向量的z值 */
	nV->lz = ((1 - cosTheta) * axie->lx * axie->lz - axie->ly * sinTheta) * aim->lx;
	nV->lz += ((1 - cosTheta) * axie->ly * axie->lz + axie->lx * sinTheta) * aim->ly;
	nV->lz += (cosTheta + (1 - cosTheta) * axie->lz * axie->lz) * aim->lz;

	//更新摄像机方向 
	aim->lx = nV->lx;
	aim->ly = nV->ly;
	aim->lz = nV->lz;
	delete(nV);
}

//前后移动相机
void Camera::move_Front_Back(int direction)
{
	this->pos.x = this->pos.x + direction * (this->view.lx) * 0.1;
	this->pos.z = this->pos.z + direction * (this->view.lz) * 0.1;
	this->pos.y = this->pos.y + direction * (this->view.ly) * 0.1;
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);
	
	//同时移动相机和所看的点坐标,视线参数不用修改，
}

//左右移动相机
void Camera::move_Left_Right(int direction)
{
	this->pos.x = this->pos.x + direction * (this->view.lz) * 0.1;
	this->pos.z = this->pos.z - direction * (this->view.lx) * 0.1;
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);
}
//上下移动相机
void Camera::move_High_Low(int direction)
{
	this->pos.y = this->pos.y + direction * 0.1;
	glLoadIdentity();
	gluLookAt(this->pos.x, this->pos.y, this->pos.z, this->pos.x + this->view.lx, this->pos.y + this->view.ly, this->pos.z + this->view.lz, 0.0f, 1.0f, 0.0f);
}

