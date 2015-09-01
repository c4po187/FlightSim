#version 330

in vec3 vertex_position;
in vec3 vertex_color;
uniform mat4 mvp;
out vec3 rgb;

void main() {
	gl_Position = mvp * vec4(vertex_position, 1.0);
	rgb = vertex_color;
}