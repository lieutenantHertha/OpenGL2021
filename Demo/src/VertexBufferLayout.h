#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexBufferElement {

public:
	unsigned int count;
	unsigned int type;
	unsigned char normalized;
public:
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:            return sizeof(GLfloat);
			case GL_UNSIGNED_INT:     return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:    return sizeof(GLubyte);
		}
		// Under current circumstances, seems like only three type could represent vertexBuffer attribute data.
		printf("Unrecognized Attribute Type\n");
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0)
	{
		// VertexBufferLayout constructor
	}
	
	template <typename AttribType>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_FLOAT, GL_FALSE });
		m_Stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_INT, GL_FALSE });
		m_Stride += count * sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ count, GL_UNSIGNED_BYTE, GL_TRUE });
		m_Stride += count * sizeof(GLubyte);
	}

	inline const std::vector<VertexBufferElement>& GetVertexBufferElements() const
	{
		return m_Elements;
	}

	inline unsigned int GetStride() const
	{
		return m_Stride;
	}

};