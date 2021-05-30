#include "ShaderProgram.h"
#include "Renderer.h"


ShaderProgram::ShaderProgram(const std::string& filepath)
{
	m_ShaderSource = ParseShaderSource(filepath);
	m_RenderID = CreateShader(m_ShaderSource.VertexShaderSource, m_ShaderSource.FragmentShaderSource);
}

ShaderProgram::~ShaderProgram()
{
	GLCall(glDeleteProgram(m_RenderID));
}

void ShaderProgram::Bind()
{
	GLCall(glUseProgram(m_RenderID));
}

void ShaderProgram::UnBind()
{
	GLCall(glUseProgram(0));
}

void ShaderProgram::SetUniform4f(const std::string& name, float v1, float v2, float v3, float v4)
{
	int location = GetUniformLocation(name);
	if(location != -1)
		GLCall(glUniform4f(location, v1, v2, v3, v4));
}

void ShaderProgram::SetUniform1i(const std::string& name, int integer)
{
	int location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniform1i(location, integer));
}

void ShaderProgram::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	int location = GetUniformLocation(name);
	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

ShaderSource ShaderProgram::ParseShaderSource(const std::string& shaderFilePath)
{
	enum class ShaderType {
		NONE = -1,
		VERTEX_SHADER = 0,
		FRAGMENT_SHADER = 1
	};
	std::ifstream shaderSourceReader(shaderFilePath);
	if (!shaderSourceReader)
		std::cout << "Failed to open shader source file!\n";

	std::string singleLine;
	std::stringstream shaderStream[2];
	ShaderType type = ShaderType::NONE;

	while (std::getline(shaderSourceReader, singleLine))
	{
		if (singleLine.find("shader") != std::string::npos)
		{
			if (singleLine.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX_SHADER;
			else if (singleLine.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT_SHADER;
		}
		else
		{
			if (type != ShaderType::NONE)
				shaderStream[(int)type] << singleLine << '\n';
			else
				std::cout << "Unidentified shader source!\n";
		}
	}

	return { shaderStream[0].str(), shaderStream[1].str() };
}

unsigned int ShaderProgram::CompileShader(unsigned int shaderType, const std::string& shaderSource)
{
	GLCall(unsigned int shader = glCreateShader(shaderType));
	const char* source = shaderSource.c_str();
	GLCall(glShaderSource(shader, 1, &source, NULL));
	GLCall(glCompileShader(shader));

	// ERROR HANDLING: whether shader compiled correctly, log the error information if compilation failed.
	int compileResult;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult));
	if (compileResult == GL_FALSE)
	{
		int infoLength;
		GLCall(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength));
		char* infoMessage = new char[infoLength];
		GLCall(glGetShaderInfoLog(shader, infoLength, &infoLength, infoMessage));
		std::cout << "Failed to compile " << (shaderType == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader.\n";
		std::cout << infoMessage << std::endl;
		GLCall(glDeleteShader(shader));

		return 0;
	}

	else
		std::cout << (shaderType == GL_VERTEX_SHADER ? "Vertex " : "Fragment ") << "shader has compiled successfully!" << std::endl;

	return shader;
}

unsigned int ShaderProgram::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
	GLCall(unsigned int shaderProgram = glCreateProgram());
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	GLCall(glAttachShader(shaderProgram, vertexShader));
	GLCall(glAttachShader(shaderProgram, fragmentShader));
	GLCall(glLinkProgram(shaderProgram));

	//ERROR HANDLING: whether shader program linked successfully, log error information if linkage failed.
	int linkResult;
	GLCall(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkResult));
	if (linkResult == GL_FALSE)
	{
		int infoLength;
		GLCall(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLength));
		char* infoMessage = new char[infoLength];
		GLCall(glGetProgramInfoLog(shaderProgram, infoLength, &infoLength, infoMessage));
		std::cout << "Failed to link the shader program.\n";
		std::cout << infoMessage << std::endl;
		GLCall(glDeleteProgram(shaderProgram));
		return 0;
	}
	else
		std::cout << "Shader program linked successfully!\n";

	GLCall(glValidateProgram(shaderProgram));

	return shaderProgram;
}

int ShaderProgram::GetUniformLocation(const std::string& uniformName)
{
	if (m_LocationCache.find(uniformName) != m_LocationCache.end())
		return m_LocationCache[uniformName];

	GLCall(int location = glGetUniformLocation(m_RenderID, uniformName.c_str()));
	if (location == -1)
		std::cout << "The Uniform doesn't exist in the current shader program, please check." << std::endl;
	m_LocationCache[uniformName] = location;
	return location;	
}
