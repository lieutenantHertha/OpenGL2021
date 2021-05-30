#pragma once
#include <GL/glew.h>

class IndexBuffer {
private:
	unsigned int m_RenderID;
public:
	IndexBuffer(unsigned int elementNumber, const void* dataSource);
	~IndexBuffer();
	void Bind();
	void UnBind();
};
