#include"MYIO.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"


GLuint MYIO::loadTextureFromBmp(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// ���ļ������ʧ�ܣ�����
	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
	{
		printf("Wrong!!!!\n");
		return 0;
	}

	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	GLint line_bytes = width * 3;
	/*while (line_bytes % 4 != 0)
		++line_bytes;*/
		// bmpͼ����4BΪ��λ���ж������ݣ���Ҫ���¼����д�С��
	line_bytes = ((line_bytes + 3) >> 2) << 2;
	total_bytes = line_bytes * height;

	// �����������ֽ��������ڴ�
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// ��ȡ��������
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}


	// ����һ���µ�������
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// ���µ������������������������
	// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);

	glBindTexture(GL_TEXTURE_2D, texture_ID);   //������

	//����4�����õ��������������ΰ���������ӳ�������
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //ָ��������ͼ����ʵĻ��ģʽ

	//������ Ŀ����������ϸ�ڲ�Σ������Ƕ�������Ϊ0����RGB���ݴ洢��ʽ����ά�������ؿ�ߣ�����߿��С
	//       �����������ݵĸ�ʽ�����ݱ�����ʽ�������������ͣ��ֽڣ����ڴ���ָ������ͼ���ָ�루����ͼ����ڲο��ַ��
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels); //Ϊ�������ָ��һ������

	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //�ָ�֮ǰ�������

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
