#include "TestVertexBuffer.h"

float positions[] = {
	-0.5f, -0.5f, 
	 0.5f, -0.5f, 
	 0.5f,  0.5f, 
	-0.5f,  0.5f 
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
};


TestVertexBuffer::TestVertexBuffer()
	: m_VBO(sizeof(float) * 2, 4, positions), m_VAO(), m_IBO(6, indices), 
	  m_Shader("src/Tests/shaders/TestVertexBuffer.shader"), m_ViewVector(0.0f, 0.0f, 0.0f)
{
	m_VBO.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	m_VAO.AddVertexBuffer(m_VBO, layout);
	m_IBO.Bind();
	m_Shader.Bind();
}

TestVertexBuffer::~TestVertexBuffer()
{
	// JUST DO NOTHING
}

void TestVertexBuffer::OnRender()
{
	glm::mat4 transitionMatrix = glm::translate(glm::mat4(1.0f), m_ViewVector);
	m_Shader.SetUniformMat4f("u_MVP", transitionMatrix);
	GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr));
}

void TestVertexBuffer::OnImguiRender()
{
	// Configuration of current test
	ImGui::SliderFloat2("Position", &m_ViewVector[0], -0.5f, 0.5f);
}
