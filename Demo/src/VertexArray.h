#pragma once
#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
	unsigned int m_RenderID;
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void AddVertexBuffer(VertexBuffer& vertexBufferObj, VertexBufferLayout& layout);
};

