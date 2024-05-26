#include"MYIO.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"


GLuint MYIO::loadTextureFromBmp(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// 打开文件，如果失败，返回
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
	{
		printf("Wrong!!!!\n");
		return 0;
	}

	// 读取文件中图象的宽度和高度
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// 计算每行像素所占字节数，并根据此数据计算总像素字节数
	GLint line_bytes = width * 3;
	/*while (line_bytes % 4 != 0)
		++line_bytes;*/
		// bmp图像以4B为单位按行对齐数据，需要重新计算行大小。
	line_bytes = ((line_bytes + 3) >> 2) << 2;
	total_bytes = line_bytes * height;

	// 根据总像素字节数分配内存
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// 读取像素数据
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}


	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);

	glBindTexture(GL_TEXTURE_2D, texture_ID);   //绑定纹理

	//设置4个常用的纹理参数。。如何把纹理像素映射成像素
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //指定纹理贴图与材质的混合模式

	//参数： 目标纹理，多重细节层次（不考虑多重纹理为0），RGB数据存储格式，二维纹理像素宽高，纹理边框大小
	//       纹理像素数据的格式，数据保存形式（像素数据类型，字节），内存中指向纹理图像的指针（纹理图像的内参快地址）
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels); //为纹理对象指定一个纹理

	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定

	free(pixels);
	return texture_ID;
}

GLuint MYIO::loadTexture(const char* file_name)
{
	GLint* lastTextureID = new(GLint);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, lastTextureID);

	int width, height, channels;
	unsigned char* data = stbi_load(file_name, &width, &height, &channels, 0);
	if (data == NULL) {
		fprintf(stderr, "Error loading image file %s\n", file_name);
		exit(1);
	}
	GLenum format;
		if (channels == 1)
			format = GL_RED;
		else if (channels == 3)
			format = GL_RGB;
		else if (channels == 4)
			format = GL_RGBA;
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load the texture into OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	// Generate mipmaps
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Free the loaded data because we now have a copy in the GPU
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, *lastTextureID);
	delete(lastTextureID);
	return textureID;
}
