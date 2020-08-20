#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

out vec2 fragment_position;
out vec2 fragment_uv;

void main() {
	mat4 mvp = projection_mat * view_mat * model_mat;
	gl_Position = mvp * vec4(vertex_position, 1.0f);

	fragment_position = gl_Position.xy;
	fragment_uv = vertex_uv;
}

