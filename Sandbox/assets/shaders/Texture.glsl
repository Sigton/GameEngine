// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoords;

out vec2 v_TextureCoords;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	v_TextureCoords = a_TextureCoords;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TextureCoords;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TextureCoords);
}