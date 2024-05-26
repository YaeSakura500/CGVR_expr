#include <gl/glut.h>
#include"Camera.h"
#include"Octahedron .h"
#include"Control.h"
#include"MYIO.h"
#include<vector>

//全局变量
Camera myCamera;
Octahedron myOct(1, 1, 1);
GLdouble ratio = 1.778;
int width, height;

//枚举纹理名称
enum Tex
{
	cristal, sky
};

//定义纹理容器
std::vector<GLuint> texture;

void reDraw(void);
void changeSize(int w, int h);
void renderScene(void);
void init(void);

int main(int argc, char** argv)
{
	//初始化，建立窗口
	glutInit(&argc, argv);
	//深度缓冲，双缓冲，颜色缓冲
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
	glEnable(GL_DEPTH_TEST);        //开启深度缓冲区
	glutKeyboardFunc(Control::inputNormalKey);     //键盘响应事件
	glutSpecialFunc(Control::inputSpecialKey);
	glutMouseFunc(Control::inputMouse);		//鼠标响应事件
	glutDisplayFunc(renderScene);   //绘制回调函数
	glutIdleFunc(renderScene);      //闲置时回调函数
	glutReshapeFunc(changeSize);    //调整窗口大小回调函数
	glutMainLoop();
	return 0;
}

//窗口重绘
void reDraw(void)
{
	glMatrixMode(GL_PROJECTION);    //投影变换
	glLoadIdentity();
	//设置视口为整个窗口大小
	glViewport(0, 0, width, height);
	//设置可视空间
	gluPerspective(myCamera.innerParm.fov, ratio, 1, 1000); //角度， 窗口纵横比， 眼睛所及距离（近和远）
	glMatrixMode(GL_MODELVIEW);     //模型变换
	glLoadIdentity();
	//相机（人眼）位置， 眼睛看的点（相机位置+视线方向）， 观察者本身方向（角度，比如正立）
	gluLookAt(myCamera.pos.x, myCamera.pos.y, myCamera.pos.z, myCamera.pos.x + myCamera.view.lx, myCamera.pos.y + myCamera.view.ly, myCamera.pos.z + myCamera.view.lz, 0.0f, 1.0f, 0.0f);
}

//定义观察方式
void changeSize(int w, int h)
{
	width = w;
	height = h;
	ratio = 1.0f * width / height;
	reDraw();
}

//渲染场景
void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清空颜色和深度缓冲
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
	glutSwapBuffers();  //交换缓冲区
}

//gl初始化
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_TEXTURE_2D);
	glClearDepth(1.0f);    // 设置深度缓存
	glDepthFunc(GL_LEQUAL);  // 选择深度测试方式
	glEnable(GL_DEPTH_TEST);  // 开启深度测试
	glShadeModel(GL_SMOOTH);  // 阴暗处理采用平滑方式
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // 最精细的透视计算
}
