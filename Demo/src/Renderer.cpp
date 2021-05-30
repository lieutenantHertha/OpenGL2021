#include "Renderer.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR)
		//Checking every single OpenGL function in graphics card RAM alongside the stack
		//And take no execution for fixing error, just clear all OpenGL error until hitting
		//the last current line of code.
		;
}

bool GLCheckError(const char* funcSignature, const char* filePath, int currentLine)
{
	while (int error = glGetError())
	{
		std::cout << "[ERROR](" << error << "): " << funcSignature
			<< ", FROM " << filePath << ", LINE " << currentLine << '\n';
		return false;
	}

	return true;
}