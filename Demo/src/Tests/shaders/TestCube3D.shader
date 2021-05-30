#vertex shader
#version 330 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec2 textureCoord;
out vec2 TextureCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vertexPosition;
	TextureCoord = textureCoord;
}

#fragment shader
#version 330 core
in vec2 TextureCoord;
out vec4 fragmentColor;

uniform sampler2D u_Texture0;
uniform sampler2D u_Texture1;
uniform vec4 u_Color;

void main()
{
	fragmentColor = mix(texture(u_Texture0, TextureCoord), texture(u_Texture1, TextureCoord), 0.3f) * u_Color;
}
