#include <glad/glad.h>
 #include <iostream>
 #include <GLFW/glfw3.h>
#include"shader.h"

 const unsigned int SCR_WIDTH = 800;
 const unsigned int SCR_HEIGHT = 600;
 void processInput(GLFWwindow* window);

 float vertices[] = {
 -0.5f, -0.5f, 0.0f, // 左下角
 0.5f, -0.5f, 0.0f, // 右下角
 0.0f, 0.5f, 0.0f // 顶部
 };



 int main()
 {
	 //glEnableVertexAttribArray(0);
	glfwInit();

	// 设置OpenGL版本为3.3
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	 // 设置OpenGL为核心模式 (只能使用OpenGL功能的一个子集)
	 glfwWindowHint(GLFW_OPENGL_PROFILE,
		 GLFW_OPENGL_CORE_PROFILE);

	 // 或者可以使用向后兼容的OpenGL功能
	 //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	 // 创建窗口对象
	 // 参数：宽度，高度，窗口标题，不使用全屏，不共享资源
	 GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,
		 SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	 if (window == NULL)
	 {
		 std::cout << "Failed to create GLFW window" << std
			 ::endl;
		 glfwTerminate();
		 return -1;
	 }
	 glfwMakeContextCurrent(window);
	 // GLAD初始化
	 if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress
	 ))
	 {
		 std::cout << "Failed to initialize GLAD" << std::
			 endl;
		 return -1;
	 }
	 unsigned int VAO, VBO;
	 glGenVertexArrays(1, &VAO);
	 glGenBuffers(1, &VBO);
	 glBindVertexArray(VAO);
	 // 在OpenGL上下文中绑定缓冲对象到GL_ARRAY_BUFFER目标上
	 // 此后，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)
	 glBindBuffer(GL_ARRAY_BUFFER, VBO);
	 // 这里我们就不用VBO了，直接对GL_ARRAY_BUFFER操作就行，因为已经绑定
	 // glBufferData函数会把之前定义的顶点数据复制到缓冲的内存中
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
		 vertices, GL_STATIC_DRAW);
	 //glBindBuffer(GL_ARRAY_BUFFER, 0); //解绑
	 //
	 // 2. 解释传入的缓冲数据
	 //
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 *
		 sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);
	 Shader shader_triangle("./exprl.vs", "./exprl.fs");

	 // 视口：渲染窗口大小
	 glViewport(0, 0, 800, 600);



	 while (!glfwWindowShouldClose(window))
	 {
		 // 输入
		 processInput(window);
		 // 清理颜色缓冲和深度缓冲
		 glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		 //
		 // 渲染指令
		  // 渲染指令
		 shader_triangle.use();
		 // 绑定VAO
		 glBindVertexArray(VAO);
		 // 绘制三角形
		 glDrawArrays(GL_TRIANGLES, 0, 3);

		 glBegin(GL_POLYGON);
		 glColor3f(0.5, 0.5, 0.5);
		 glVertex3f(-1, -1, -0);
		 glVertex3f(-1, -1, -0);
		 glVertex3f(-1, -1, -0);
		 glEnd();
		 // 检查并调用事件，交换缓冲
		 glfwSwapBuffers(window);
		 glfwPollEvents();
	 }
	 return 0;
 }


 void processInput(GLFWwindow* window)
 {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		 glfwSetWindowShouldClose(window, true);
 }

