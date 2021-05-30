#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

struct ShaderSource {
	std::string VertexShaderSource;
	std::string FragmentShaderSource;
};

class ShaderProgram
{
private:
	ShaderSource m_ShaderSource;
	unsigned int m_RenderID;
	std::unordered_map<std::string, int> m_LocationCache;

public:
	ShaderProgram(const std::string& filepath);
	~ShaderProgram();
	void Bind();
	void UnBind();
	void SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4);
	void SetUniform1i(const std::string& name, int integer);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	ShaderSource ParseShaderSource(const std::string& shaderFilePath);
	unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSource);
	unsigned int CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
	int GetUniformLocation(const std::string& uniformName);
};

