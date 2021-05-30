#include "Test3DScene.h"

extern std::string Texture0Path;
extern std::string Texture1Path;

float vertexPositions[] = {
	-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,   //0
	 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,   //1
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,   //2
	-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,   //3
									   
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,   //4
	 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   //5
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,   //6
	 0.5f,  0.5f,  0.5f, 0.0f, 1.0f,   //7
									   
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   //8
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f,   //9
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f,   //10
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,   //11
									   
	-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,   //12
	 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,   //13
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f,   //14
	-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,   //15
									   
	 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   //16
	-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   //17
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,   //18
	 0.5f,  0.5f, -0.5f, 0.0f, 1.0f,   //19
									   
	 0.5f, -0.5f,  0.5f, 0.0f, 0.0f,   //20
	-0.5f, -0.5f,  0.5f, 1.0f, 0.0f,   //21
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,   //22
	 0.5f, -0.5f, -0.5f, 0.0f, 1.0f	   //23
};

unsigned int vertexIndices[] = {
	 0,   1,   2,   0,   2,   3,        //Plane0
	 4,   5,   6,   4,   6,   7,	    //Plane1
	 8,   9,  10,   8,  10,  11,	    //Plane2
	12,  13,  14,  12,  14,  15,	    //Plane3
	16,  17,  18,  16,  18,  19,	    //Plane4
	20,  21,  22,  20,  22,  23	        //Plane5
};

glm::vec3 positionVectors[] = {
	glm::vec3( 0.0f,  0.0f,  0.0f),
	glm::vec3( 2.0f,  5.0f, -3.6f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f,  6.3f),
	glm::vec3( 2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -1.7f),
	glm::vec3( 1.3f, -2.0f,  2.5f),
	glm::vec3( 1.5f,  2.0f, -2.5f),
	glm::vec3( 1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f,  1.5f)
};

glm::vec3 axisCollection[] = {
	glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(2.3f, 1.2f, 0.5f),
	glm::vec3(0.9f, 0.8f, 1.5f),
	glm::vec3(0.2f, 0.3f, 0.8f),
	glm::vec3(0.5f, 1.0f, 2.2f),
	glm::vec3(1.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, 0.0f, 1.0f),
	glm::vec3(0.6f, 0.2f, 0.9f),
	glm::vec3(1.3f, 0.7f, 1.0f),
	glm::vec3(0.3f, 0.8f, 0.3f)
};

float TestCube::RADIUS = 10.0f;
float TestCube::MULTIPLE = 1.0f;

TestCube::TestCube()
	: m_VBO(sizeof(float) * 5, 24, &vertexPositions), m_VAO(), m_IBO(36, &vertexIndices),
	  m_ShaderProgram("src/Tests/shaders/TestTextureSplicing.shader"),
	  m_Texture{ Texture0Path, Texture1Path },
	  m_PositionX(3.0f), m_PositionY(3.0f), m_PositionZ(3.0f)
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

TestCube::~TestCube()
{
	m_Texture[0].UnBind();
	m_Texture[1].UnBind();
	m_ShaderProgram.UnBind();
	m_IBO.UnBind();
	m_VAO.UnBind();
	m_VBO.UnBind();
}

void TestCube::OnRender()
{
	glm::mat4 projMatrix = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 40.0f);

	for (unsigned int index = 0; index < 10; index++)
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), positionVectors[index]);
		modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime() * TestCube::MULTIPLE, axisCollection[index]);

		m_PositionX = TestCube::RADIUS * cos((float)glfwGetTime());
		m_PositionZ = TestCube::RADIUS * sin((float)glfwGetTime());
		glm::mat4 viewMatrix = glm::lookAt(glm::vec3(m_PositionX, m_PositionY, m_PositionZ),
			                   glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_ShaderProgram.SetUniformMat4f("u_MVP", projMatrix * viewMatrix * modelMatrix);
		GLCall(glDrawElements(GL_TRIANGLES, sizeof(vertexIndices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr));
	}
}

void TestCube::OnImguiRender()
{
	ImGui::SliderFloat("PositionX", &m_PositionX, -10.0f, 10.0f);
	ImGui::SliderFloat("PositionY", &m_PositionY, -10.0f, 10.0f);
	ImGui::SliderFloat("PositionZ", &m_PositionZ, -10.0f, 10.0f);
	ImGui::SliderFloat("RADIUS", &RADIUS, 1.0f, 30.0f);
	ImGui::SliderFloat("Spin Speed", &MULTIPLE, 0.1f, 10.0f);
}
