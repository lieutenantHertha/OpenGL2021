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

#include <chrono>
#include <cmath>

class TestCube3D : public Test
{
private:
	VertexBuffer m_VBO;
	VertexArray m_VAO;
	IndexBuffer m_IBO;
	ShaderProgram m_ShaderProgram;
	Texture m_Texture[2];

	float m_PositionX, m_PositionY, m_PositionZ;
	float m_Angle;
	float m_Color[4];
public:
	TestCube3D();
	~TestCube3D();

	void OnRender() override;
	void OnImguiRender() override;
};

