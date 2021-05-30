#include "TestTexture.h"

std::array<float, 4 * 4> vertexData = {
	-0.5f, -0.5f, 0.0f, 0.0f,
	 0.5f, -0.5f, 1.0f, 0.0f,
	 0.5f,  0.5f, 1.0f, 1.0f,
	-0.5f,  0.5f, 0.0f, 1.0f
};

std::array<unsigned int, 6> indicesData = {
	0, 1, 2,
	2, 3, 0
};

TestTexture::TestTexture()
	: m_VBO(sizeof(float)*4, 4, &vertexData), m_VAO(), m_IBO(indicesData.size(), &indicesData),
	  m_ShaderProgram("src/Tests/shaders/TestTexture.shader"), m_viewVector(0.0f, 0.0f, 0.0f), 
	  m_Color(1.0f, 1.0f, 1.0f, 1.0f), m_SequenceNum(1), m_Textures()
{			   
	m_VBO.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VAO.AddVertexBuffer(m_VBO, layout);
	m_IBO.Bind();
	m_ShaderProgram.Bind();

	std::ifstream fileStream("src/Tests/texturePaths.txt");
	std::string singleLine;
	std::vector<std::string> pathArray;
	pathArray.reserve(m_Textures.size());
	if (fileStream)
	{
		unsigned int index = 0;
		while (std::getline(fileStream, singleLine))
		{
			pathArray.emplace_back(singleLine);
			if(pathArray.size() == pathArray.max_size())
				break;
		}
	}
	else
	{
		std::cout << "The Texture Paths File has been failed to open!" << std::endl;
		__debugbreak();
	}

	for (unsigned int index = 0; index < pathArray.size(); index++)
		m_Textures[index] = std::make_unique<Texture>(pathArray[index]);

	for (unsigned int index = 0; index < m_Textures.size(); index++)
		m_Textures[index]->Bind(index);
}

TestTexture::~TestTexture()
{
	for (unsigned int index = 0; index < m_Textures.size(); index++)
		m_Textures[index]->UnBind();

	m_ShaderProgram.UnBind();
	m_IBO.UnBind();
	m_VAO.UnBind();
	m_VBO.UnBind();
}

void TestTexture::OnRender()
{
	glm::mat4 transitionMatrix = glm::translate(glm::mat4(1.0f), m_viewVector);
	m_ShaderProgram.SetUniformMat4f("u_MVP", transitionMatrix);
	m_ShaderProgram.SetUniform1i("u_Texture", m_SequenceNum - 1);
	m_ShaderProgram.SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
	GLCall(glDrawElements(GL_TRIANGLES, indicesData.size(), GL_UNSIGNED_INT, nullptr));
}

void TestTexture::OnImguiRender()
{
	ImGui::SliderInt("Serial Number", &m_SequenceNum, 1, 35);
	ImGui::SliderFloat("Horizon", &m_viewVector[0], -0.5f, 0.5f);
	ImGui::SliderFloat("Vertical", &m_viewVector[1], -0.5f, 0.5f);
	ImGui::ColorPicker4("Color", &m_Color[0]);
}
