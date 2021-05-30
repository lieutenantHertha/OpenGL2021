#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(unsigned int singleVertexStride, unsigned int vertexNumber, const void* dataSource)
{
	GLCall(glGenBuffers(1, &m_RenderID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, singleVertexStride * vertexNumber, dataSource, GL_STATIC_DRAW));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

VertexBuffer::~VertexBuffer()
{
	GLCall((GL_ARRAY_BUFFER, 0));
	GLCall(glDeleteBuffers(1, &m_RenderID));
}

void VertexBuffer::Bind()
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RenderID));
}

void VertexBuffer::UnBind()
{
	GLCall((GL_ARRAY_BUFFER, 0));
}

