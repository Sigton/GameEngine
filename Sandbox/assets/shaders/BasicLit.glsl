// Basic Diffuse Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_FragCoords;
out vec3 v_WorldNormal;

void main()
{

	// calculate frag coords
	v_FragCoords = u_Transform * vec4(a_Position, 1.0);

	// calculate the normal in world space
	v_WorldNormal = vec3(transpose(inverse(u_Transform)) * vec4(a_Normal, 0.0));

	gl_Position = u_ViewProjection * v_FragCoords;
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec3 u_LightPos;
uniform vec3 u_LightColor;
uniform vec3 u_ObjectColor;
uniform vec3 u_ViewPos;

in vec4 v_FragCoords;
in vec3 v_WorldNormal;

void main()
{
	// ambient lighting
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * u_ObjectColor;

	// diffuse lighting

	// get direction vector from fragment to light
	vec3 toLight = u_LightPos - vec3(v_FragCoords);
	vec3 lightDir = normalize(toLight);
	float distToLight = length(toLight);

	// then the brightness of the fragment can be represented by the dot product between
	// the surface normal and direction to the light source
	float brightness = max(dot(lightDir, v_WorldNormal), 0.0);

	// things get dimmer as they get further from the light
	brightness *= 2 * exp(-0.1f * distToLight);

	// combine the brightenss with the light color
	vec3 diffuse = u_LightColor * brightness;


	// specular lighting
	float specularStrength = 0.5;
	vec3 viewDir = normalize(u_ViewPos - vec3(v_FragCoords));
	vec3 reflectDir = reflect(-lightDir, v_WorldNormal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * u_LightColor;


	color = vec4((diffuse + ambient + specular) * u_ObjectColor, 1.0);
}