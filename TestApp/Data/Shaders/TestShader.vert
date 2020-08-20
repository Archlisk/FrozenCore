#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 2) in vec3 vertex_normal;

uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

out vec4 fragment_position;
out vec2 fragment_uv;

out float light_intensity;

vec3 light_position = normalize(vec3(5, 10, 10));

void main() {
	mat4 mvp = projection_mat * view_mat * model_mat;
	gl_Position = mvp * vec4(vertex_position, 1.0f);

	fragment_position = gl_Position;
	fragment_uv = vertex_uv;

	light_intensity = clamp(dot(light_position, vertex_normal) * 0.8, 0.0f, 0.7f) + 0.3f;
}
