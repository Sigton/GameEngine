// Basic Diffuse Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

uniform vec3 u_LightPos;

out vec4 v_FragCoords;
out vec3 v_WorldNormal;
out vec3 v_LightPos;

void main()
{

	// calculate frag coords
	v_FragCoords = u_Transform * vec4(a_Position, 1.0);

	// calculate the normal in world space
	v_WorldNormal = vec3(transpose(inverse(u_Transform)) * vec4(a_Normal, 0.0));

	v_LightPos = u_LightPos;

	gl_Position = u_ViewProjection * v_FragCoords;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_FragCoords;
in vec3 v_WorldNormal;
in vec3 v_LightPos;

void main()
{
	// get direction vector from fragment to light
	vec3 lightDir = normalize(v_LightPos - vec3(v_FragCoords));

	// then the brightness of the fragment can be represented by the dot product between
	// the surface normal and direction to the light source
	// then divide by the square of the distance to the light source
	float brightness = dot(lightDir, v_WorldNormal);

	// brightness is currently in range [-1, 1]
	// convert to [0, 1]
	brightness = (1 + brightness) * 0.5;

	color = vec4(brightness * vec3(1.0), 1.0);
}