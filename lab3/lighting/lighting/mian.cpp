//���Ʋ��
//#include "stdafx.h"
#include <GL/glut.h>
#include <stdlib.h>
#include<cmath>
#include<iostream>

#define SPEED 1e-2

//������������
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //���淴�����
GLfloat mat_shininess[] = { 400.0 };               //�߹�ָ��
//������������
GLfloat light_position[] = { 2.0, 0.0, 0.0, 1.0 };   //��λ��(1,1,1), ���1-����
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat Light_Model_Ambient[] = { 0.4, 0.4, 0.4, 1.0 }; //���������
float angel = 1.57,rot =0;
float env = 0.2;
float on = 1;
//�Զ����ʼ��opengl����
void init(void)
{



    glClearColor(0.0, 0.0, 0.0, 0.0);  //����ɫ
    glShadeModel(GL_SMOOTH);           //��������ģʽ

    //��������
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);



    glEnable(GL_LIGHTING);   //����:ʹ�ù�
    glEnable(GL_LIGHT0);     //��0#��
    glEnable(GL_DEPTH_TEST); //����Ȳ���
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidTeapot(1);
    //�ƹ�����
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ�������
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //���淴���
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //���������
    
    //angel += 1e-4;
    //light_position[0] = cos(angel);
    //light_position[2] = sin(angel);

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    //����ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //����ͶӰ
    if (w <= h)
        glOrtho(-1.5, 1.5, -1.5 * (GLfloat)h / (GLfloat)w, 1.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-1.5 * (GLfloat)w / (GLfloat)h, 1.5 * (GLfloat)w / (GLfloat)h, -1.5, 1.5, -10.0, 10.0);

    //����ģ�Ͳ���--���������
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void normalinput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        env += 0.01;
        break;
    case '2':
        env -= 0.01;
        break;
    default:
        break;
    }
    env = env < 0 ? 0: env;
    env = env > 1 ? 1 : env;
    //std::cout << env << std::endl;
    Light_Model_Ambient[0] = env;
    Light_Model_Ambient[1] = env;
    Light_Model_Ambient[2] = env;
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

    //�ƹ�����
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ�������
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //���淴���
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //���������
    glutPostRedisplay();
    //std::cout << "angle" << angel << "rot" << rot << std::endl;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("lighting");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(keyinput);
    glutKeyboardFunc(normalinput);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}