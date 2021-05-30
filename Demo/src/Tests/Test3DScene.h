#pragma once
#include "Tests/Test.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>

class TestCube : public Test
{
private:
	VertexBuffer m_VBO;
	VertexArray m_VAO;
	IndexBuffer m_IBO;
	ShaderProgram m_ShaderProgram;
	Texture m_Texture[2];

	float m_PositionX, m_PositionY, m_PositionZ;

public:
	static float RADIUS;
	static float MULTIPLE;

public:
	TestCube();
	~TestCube();

	void OnRender() override;
	void OnImguiRender() override;
};
