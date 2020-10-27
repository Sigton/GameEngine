// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

uniform vec3 u_LightPos;

out vec3 v_FragCoords;
out vec3 v_Normal;
out vec3 v_LightPos;

void main()
{

	// calculate frag coords
	v_FragCoords = vec3(u_Transform * vec4(a_Position, 1.0));

	// calculate normal
	v_Normal = 0.5 * (1 + normalize(a_Position));  // light it as if it were a sphere for simplicity

	v_LightPos = u_LightPos;

	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_FragCoords;
in vec3 v_Normal;
in vec3 v_LightPos;

void main()
{
	// get direction vector from fragment to light
	vec3 lightDir = normalize(v_LightPos - v_FragCoords);

	// then the brightness of the fragment can be represented by the dot product between
	// the surface normal and direction to the light source
	float brightness = dot(lightDir, v_Normal);

	// brightness is currently in range [-1, 1]
	// convert to [0, 1]
	brightness = (1 + brightness) * 0.5;

	color = vec4(brightness * vec3(1.0), 1.0);
}