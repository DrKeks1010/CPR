#version 460 core
in vec3 color;
in vec3 normal;
in vec3 fragPos;

out vec4 FragColor;

void main()
{
	vec3 lightPos = vec3(0, 10, 0);
	vec3 diffuseColor = vec3(1, 1, 1);

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(vec3(0, 10, 0) - fragPos);
	float diffuse = max(dot(norm, lightDir), 0.0f);

	vec3 result = (diffuseColor * diffuse) * color;
	FragColor = vec4(result, 1.0f);
}
