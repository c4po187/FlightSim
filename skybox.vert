#version 440

/**
 * Skybox Vertex Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

 in vec4 vertex_position;

 uniform mat4 projection_matrix, view_matrix;

 out vec3 uv;

 void main() {
	uv = vertex_position.xyz;

	gl_Position = projection_matrix * view_matrix * vertex_position;
 }

 // END OF FILE