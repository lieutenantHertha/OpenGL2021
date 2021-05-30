#pragma once
#include "Tests/Test.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "TextureSplicing.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <array>
#include <memory>
#include <unordered_map>

class TestTextureSplicing : public Test
{
private:
	VertexBuffer m_VBO;
	VertexArray m_VAO;
	IndexBuffer m_IBO;
	ShaderProgram m_ShaderProgram;
	std::array<std::unique_ptr<Texture>, 2> m_Textures;
	int m_Repitition;
	std::unordered_map<int, std::vector<Vector2>> m_ViewVectorArray;

public:
	TestTextureSplicing();
	~TestTextureSplicing();

	void OnRender() override;
	void OnImguiRender() override;
};


