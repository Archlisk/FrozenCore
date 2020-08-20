#version 440

in vec2 fragment_position;
in vec2 fragment_uv;

out vec4 out_color;

uniform sampler2D diffuse_texture;

uniform vec3 text_color;

void main() {
	float diffuse_val = texture(diffuse_texture, fragment_uv).r;
	out_color = vec4(text_color, diffuse_val);
}

