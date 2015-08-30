#version 330

/**
 * Simple Color Vertex Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

 layout (location = 0) in vec3 vertex_position;
 layout (location = 1) in vec3 vertex_color;

 uniform mat4 mvp_matrix;

 out vec3 rgb;

 void main() {
	rgb = vertex_color;

	gl_Position = mvp_matrix * vec4(vertex_position, 1.0);
 }

 // END OF FILE