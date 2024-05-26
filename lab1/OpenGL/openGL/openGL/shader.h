#pragma once
#ifndef SHADER_H
 #define SHADER_H
 class Shader
 {
 public:
 // OpenGL ID
 unsigned int ID;
 // 构造器读取并构建着色器
 Shader(const char* vertexPath, const char*
fragmentPath);
// 使用着色器
 void use();
 };
 #endif
 