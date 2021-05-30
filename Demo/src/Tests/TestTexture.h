#pragma once
#include "Tests/Test.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <memory>

class TestTexture : public Test
{
private:
	VertexBuffer m_VBO;
	VertexArray m_VAO;
	IndexBuffer m_IBO;
	ShaderProgram m_ShaderProgram;

	glm::vec3 m_viewVector;
	glm::vec4 m_Color;
	int m_SequenceNum; // The index number of texture to be chosen through imGui interface

	std::array<std::unique_ptr<Texture>, 35> m_Textures;

public:
	TestTexture();
	~TestTexture();

	void OnRender() override;
	void OnImguiRender() override;

};

