#pragma once
#ifndef SHADER_H
 #define SHADER_H
 class Shader
 {
 public:
 // OpenGL ID
 unsigned int ID;
 // ��������ȡ��������ɫ��
 Shader(const char* vertexPath, const char*
fragmentPath);
// ʹ����ɫ��
 void use();
 };
 #endif
 