#version 440

in vec4 fragment_position;
in vec2 fragment_uv;

in float light_intensity;

out vec4 out_color;

uniform sampler2D diffuse_texture;

void main() {
	vec4 diffuse_color = texture(diffuse_texture, fragment_uv);

	out_color = vec4(diffuse_color.rgb * light_intensity, diffuse_color.a);
}
