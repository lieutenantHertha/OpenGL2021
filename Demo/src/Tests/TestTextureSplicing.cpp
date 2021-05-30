#include "TestTextureSplicing.h"

extern std::array<float, 4*4> vertexData;
extern std::array<unsigned int, 6> indicesData;

TestTextureSplicing::TestTextureSplicing()
	: m_VBO(sizeof(float)*4, 4, &vertexData), m_VAO(), m_IBO(6, &indicesData),
	  m_ShaderProgram("src/Tests/shaders/TestTextureSplicing.shader"), 
	  m_Textures{std::make_unique<Texture>("resource/texture/whiteBrick.jpg"), 
	             std::make_unique<Texture>("resource/texture/burgerKing1.png")},
	  m_Repitition(3), m_ViewVectorArray{}
{
	m_VBO.Bind();
	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	m_VAO.AddVertexBuffer(m_VBO, layout);
	m_IBO.Bind();
	m_ShaderProgram.Bind();
	m_Textures[0]->Bind(0);
	m_Textures[1]->Bind(1);
	m_ShaderProgram.SetUniform1i("u_Texture0", 0);
	m_ShaderProgram.SetUniform1i("u_Texture1", 1);
}

TestTextureSplicing::~TestTextureSplicing()
{
	m_Textures[0]->UnBind();
	m_Textures[1]->UnBind();
	m_ShaderProgram.UnBind();
	m_IBO.UnBind();
	m_VAO.UnBind();
	m_VBO.UnBind();
}

void TestTextureSplicing::OnRender()
{
	if (m_ViewVectorArray.find(m_Repitition) != m_ViewVectorArray.end())
		std::vector<Vector2> currentVectorArray = m_ViewVectorArray[m_Repitition];
	else
	{
		std::vector<Vector2> currentVectorArray = GenerateViewVectors(m_Repitition);
		m_ViewVectorArray[m_Repitition] = currentVectorArray;
	}

	for (const auto& singleVector : m_ViewVectorArray[m_Repitition])
	{
		glm::mat4 projMatrix = glm::ortho(vertexData[0] * m_Repitition, vertexData[4] * m_Repitition, 
			vertexData[5] * m_Repitition, vertexData[9] * m_Repitition);
		
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), 
			glm::vec3(singleVector.DimensionX, singleVector.DimensionY, 0.0f));

		m_ShaderProgram.SetUniformMat4f("u_MVP", projMatrix * viewMatrix);
		GLCall(glDrawElements(GL_TRIANGLES, indicesData.size(), GL_UNSIGNED_INT, nullptr));
	}
}

void TestTextureSplicing::OnImguiRender()
{
	ImGui::SliderInt("Repetition", &m_Repitition, 1, 12);
}
