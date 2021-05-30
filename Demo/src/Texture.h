#pragma once
#include <GL/glew.h>
#include <stb_image/stb_image.h>

#include <iostream>
#include <string>

class Texture
{
private:
	unsigned int m_RenderID;
	int m_Width;
	int m_Height;
	int m_nrChannels;
	unsigned char* m_DataSource;
	std::string m_Filepath;

public:
	Texture() = default;
	Texture(const std::string& filepath);
	~Texture();
	void Bind(unsigned int slot);
	void UnBind();
};

