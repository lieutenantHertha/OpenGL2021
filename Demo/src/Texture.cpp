#include "Texture.h"
#include "Renderer.h"

Texture::Texture(const std::string& filepath)
	: m_RenderID(0), m_Width(0), m_Height(0), m_nrChannels(0), m_DataSource(nullptr), m_Filepath(filepath)
{
	stbi_set_flip_vertically_on_load(true);
	m_DataSource = stbi_load(m_Filepath.c_str(), &m_Width, &m_Height, &m_nrChannels, 4);
	if (!m_DataSource)
	{
		printf("Failed to load the texture!\n");
		__debugbreak();
	}
	else
		std::cout << "Width: " << m_Width 
		          << ", Height: " << m_Height 
		          << ", Color Channels: " << m_nrChannels << std::endl;

	GLCall(glGenTextures(1, &m_RenderID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_DataSource));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	
	if (m_DataSource)
		stbi_image_free(m_DataSource);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RenderID));
	std::cout << "Current texture has been deleted!" << std::endl;
}

void Texture::Bind(unsigned int slot = 0)
{
	//tie the manufactured texture to some specific texture unit.
	//we bind texture to the slot currently. Still need to fetch the sampler uniform location to pass it to shader.
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderID));
}

void Texture::UnBind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
