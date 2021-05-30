#include <IndexBuffer.h>

IndexBuffer::IndexBuffer(unsigned int elementNumber, const void* dataSource)
{
	glGenBuffers(1, &m_RenderID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementNumber * sizeof(unsigned int), dataSource, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RenderID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderID);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

