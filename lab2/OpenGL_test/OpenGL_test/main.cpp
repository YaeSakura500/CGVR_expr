#include <gl/glut.h>
#include"Camera.h"
#include"Octahedron .h"
#include"Control.h"
#include"MYIO.h"
#include<vector>

//ȫ�ֱ���
Camera myCamera;
Octahedron myOct(1, 1, 1);
GLdouble ratio = 1.778;
int width, height;

//ö����������
enum Tex
{
	cristal, sky
};

//������������
std::vector<GLuint> texture;

void reDraw(void);
void changeSize(int w, int h);
void renderScene(void);
void init(void);

int main(int argc, char** argv)
{
	//��ʼ������������
	glutInit(&argc, argv);
	//��Ȼ��壬˫���壬��ɫ����
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glEnable(GL_TEXTURE_2D);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 360);
	glutCreateWindow("test");
	init();
	//texture.push_back(MYIO::loadTextureFromBmp("test1.bmp"));
	texture.push_back(MYIO::loadTexture("diamond.jpg"));
	myOct.setTexture(texture[cristal]);
	myOct.setTexture(texture[cristal]);
	//myOct.setTexture(texture[sky]);
	glEnable(GL_DEPTH_TEST);        //������Ȼ�����
	glutKeyboardFunc(Control::inputNormalKey);     //������Ӧ�¼�
	glutSpecialFunc(Control::inputSpecialKey);
	glutMouseFunc(Control::inputMouse);		//�����Ӧ�¼�
	glutDisplayFunc(renderScene);   //���ƻص�����
	glutIdleFunc(renderScene);      //����ʱ�ص�����
	glutReshapeFunc(changeSize);    //�������ڴ�С�ص�����
	glutMainLoop();
	return 0;
}

//�����ػ�
void reDraw(void)
{
	glMatrixMode(GL_PROJECTION);    //ͶӰ�任
	glLoadIdentity();
	//�����ӿ�Ϊ�������ڴ�С
	glViewport(0, 0, width, height);
	//���ÿ��ӿռ�
	gluPerspective(myCamera.innerParm.fov, ratio, 1, 1000); //�Ƕȣ� �����ݺ�ȣ� �۾��������루����Զ��
	glMatrixMode(GL_MODELVIEW);     //ģ�ͱ任
	glLoadIdentity();
	//��������ۣ�λ�ã� �۾����ĵ㣨���λ��+���߷��򣩣� �۲��߱����򣨽Ƕȣ�����������
	gluLookAt(myCamera.pos.x, myCamera.pos.y, myCamera.pos.z, myCamera.pos.x + myCamera.view.lx, myCamera.pos.y + myCamera.view.ly, myCamera.pos.z + myCamera.view.lz, 0.0f, 1.0f, 0.0f);
}

//����۲췽ʽ
void changeSize(int w, int h)
{
	width = w;
	height = h;
	ratio = 1.0f * width / height;
	reDraw();
}

//��Ⱦ����
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ɫ����Ȼ���
	glClearColor(1, 1, 1, 0);
	myOct.showFaceWithSingleTex();
	myOct.showEdge(0, 0, 0, 0.1);
	glBegin(GL_POLYGON);
	glColor3f(0.3, 0.3, 0.5);
	glVertex3f(1000, -10, 1000);
	glVertex3f(-1000, -10, 1000);
	glVertex3f(-1000, -10, -1000);
	glVertex3f(1000, -10, -1000);
	glEnd();
	glutSwapBuffers();  //����������
}

//gl��ʼ��
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0f);    // ������Ȼ���
	glDepthFunc(GL_LEQUAL);  // ѡ����Ȳ��Է�ʽ
	glEnable(GL_DEPTH_TEST);  // ������Ȳ���
	glShadeModel(GL_SMOOTH);  // �����������ƽ����ʽ
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // �ϸ��͸�Ӽ���
}
