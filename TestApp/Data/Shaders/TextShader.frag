#version 440

in vec2 fragment_position;
in vec2 fragment_uv;

out vec4 out_color;

uniform sampler2D diffuse_texture;

uniform vec3 gui_draw_color;

void main() {
	vec4 diffuse_color = texture(diffuse_texture, fragment_uv);
	out_color = vec4(diffuse_color.rgb * gui_draw_color, diffuse_color.a);
}

