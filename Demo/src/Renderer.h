#pragma once
#include <GL/glew.h>
#include <iostream>

#define ASSERT(someFunc) if(!someFunc) __debugbreak()
#define GLCall(someOpenGLFunction) GLClearError();\
	someOpenGLFunction;\
	ASSERT(GLCheckError(#someOpenGLFunction, __FILE__, __LINE__))


void GLClearError();
bool GLCheckError(const char* funcSignature, const char* filePath, int currentLine);

