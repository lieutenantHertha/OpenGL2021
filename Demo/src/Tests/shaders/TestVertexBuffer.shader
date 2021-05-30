#vertex shader
#version 330 core
layout(location = 0) in vec4 vertexPosition;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vertexPosition;
}

#fragment shader
#version 330 core
out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}
