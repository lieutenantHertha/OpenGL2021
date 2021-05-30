#include "TestCube3D.h"

extern float vertexPositions[];
extern unsigned int vertexIndices[];

std::string Texture0Path = "resource/texture/container0.jpg";
std::string Texture1Path = "resource/texture/awesomeface.png";

TestCube3D::TestCube3D()
	: m_VBO(sizeof(float) * 5, 24, &vertexPositions), m_VAO(), m_IBO(36, &vertexIndices),
	  m_ShaderProgram("src/Tests/shaders/TestCube3D.shader"),
	  m_Texture{ Texture0Path, Texture1Path },
	  m_PositionX(3.0f), m_PositionY(3.0f), m_PositionZ(3.0f), m_Angle(0.0f),
	  m_Color{1.0f, 1.0f, 1.0f, 1.0f}
{
	m_VBO.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	m_VAO.AddVertexBuffer(m_VBO, layout);
	m_IBO.Bind();
	m_ShaderProgram.Bind();
	for (unsigned int index = 0; index < 2; index++)
	{
		m_Texture[index].Bind(index);
		m_ShaderProgram.SetUniform1i(std::string("u_Texture") + std::to_string(index), index);
	}
}

TestCube3D::~TestCube3D()
{
	m_Texture[0].UnBind();
	m_Texture[1].UnBind();
	m_ShaderProgram.UnBind();
	m_IBO.UnBind();
	m_VAO.UnBind();
	m_VBO.UnBind();
}

void TestCube3D::OnRender()
{
	glm::mat4 projMatrix = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 50.0f);
	glm::mat4 modelMatrix = glm::rotate(glm::mat4(1.0f), m_Angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(m_PositionX, m_PositionY, m_PositionZ), 
		                               glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	m_ShaderProgram.SetUniformMat4f("u_MVP", projMatrix * viewMatrix * modelMatrix);
	m_ShaderProgram.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	GLCall(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));
}

void TestCube3D::OnImguiRender()
{
	ImGui::SliderFloat("PositionX", &m_PositionX, -10.0f, 10.0f);
	ImGui::SliderFloat("PositionY", &m_PositionY, -10.0f, 10.0f);
	ImGui::SliderFloat("PositionZ", &m_PositionZ, -10.0f, 10.0f);
	ImGui::SliderAngle("Angle", &m_Angle, -180.0f, 180.0f);
	ImGui::ColorEdit4("Color", m_Color);
}
