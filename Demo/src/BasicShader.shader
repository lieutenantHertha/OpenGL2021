#vertex shader
#version 330 core
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 aTextureCoord;
                     out vec3 color;
					 out vec2 textureCoord;

					 uniform mat4 u_MVP;
void main()
{
	gl_Position = u_MVP * vertexPosition;
	color = vertexColor;
	textureCoord = aTextureCoord;
}


#fragment shader
#version 330 core
out vec4 fragmentColor;

in vec3 color;
in vec2 textureCoord;

uniform sampler2D ourTexture;
uniform sampler2D anotherTexture;

uniform vec4 u_Color;

void main()
{
	fragmentColor = mix(texture(ourTexture, textureCoord), texture(anotherTexture, textureCoord), 0.2f);
}

