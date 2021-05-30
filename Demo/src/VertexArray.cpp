#include "VertexArray.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RenderID));
	GLCall(glBindVertexArray(m_RenderID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RenderID));
}

void VertexArray::Bind()
{
	GLCall(glBindVertexArray(m_RenderID));
}

void VertexArray::UnBind()
{
	GLCall(glBindVertexArray(0));
}

void VertexArray::AddVertexBuffer(VertexBuffer& vertexBufferObj, VertexBufferLayout& layout)
{
	GLCall(glBindVertexArray(m_RenderID));
	vertexBufferObj.Bind();
	const std::vector<VertexBufferElement> attribElements = layout.GetVertexBufferElements();
	unsigned int offset = 0;
	for (unsigned int index = 0; index < attribElements.size(); index++)
	{
		const auto& element = attribElements[index];
		GLCall(glEnableVertexAttribArray(index));
		GLCall(glVertexAttribPointer(index, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}
