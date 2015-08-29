#version 330

/**
 * Noob Vertex Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

void main() {
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

// END OF FILE