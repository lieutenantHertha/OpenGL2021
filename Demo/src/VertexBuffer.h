#pragma once
#include <GL/glew.h>
#include "Renderer.h"

class VertexBuffer {
private:
	unsigned int m_RenderID;
public:
	VertexBuffer(unsigned int singleVertexStride, unsigned int vertexNumber, const void* dataSource);
	~VertexBuffer();
	void Bind();
	void UnBind();
};
