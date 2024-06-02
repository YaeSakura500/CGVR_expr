//绘制茶壶
//#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include<cmath>
#include<iostream>

#define SPEED 1e-2

GLfloat light_position[] = { 2.0, 0.0, 0.0, 0.0 };   //灯位置(1,1,1), 最后1-开关
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat Light_Model_Ambient[] = { 0.4, 0.4, 0.4, 1.0 }; //环境光参数
float angel = 1.57,rot =0;
//自定义初始化opengl函数
void init(void)
{
    //材质反光性设置
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
    GLfloat mat_shininess[] = { 50.0 };               //高光指数


    glClearColor(0.0, 0.0, 0.0, 0.0);  //背景色
    glShadeModel(GL_SMOOTH);           //多变性填充模式

    //材质属性
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);



    glEnable(GL_LIGHTING);   //开关:使用光
    glEnable(GL_LIGHT0);     //打开0#灯
    glEnable(GL_DEPTH_TEST); //打开深度测试
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(0.5);
    //灯光设置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数
    
    //angel += 1e-4;
    //light_position[0] = cos(angel);
    //light_position[2] = sin(angel);

    glFlush();   //glSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    //设置投影参数
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //正交投影
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

    //设置模型参数--几何体参数
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyinput(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        angel -= SPEED;
        break;
    case GLUT_KEY_RIGHT:
        angel += SPEED;
        break;
    case GLUT_KEY_UP:
        rot += SPEED;
        break;
    case GLUT_KEY_DOWN:
        rot -= SPEED;
        break;
    default:
        break;
    }

    light_position[0] = 2*cos(rot) * sin(angel);
    light_position[2] = 2*cos(rot) * cos(angel);
    light_position[1] = 2*sin(rot);

    //灯光设置
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数
    glutPostRedisplay();
    std::cout << "angle" << angel << "rot" << rot << std::endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("茶壶");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(keyinput);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}