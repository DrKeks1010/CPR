#version 460 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;

out vec3 color;
out vec3 normal;
out vec3 fragPos;

uniform mat4 model;
uniform mat3 inverse_model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(a_pos, 1.0);
	color = vec3(1.0, 0.0, 0.8);
	normal = inverse_model * a_normal;
	fragPos = vec3(model * vec4(a_pos, 1.0));
}
