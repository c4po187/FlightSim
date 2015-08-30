#version 330

/**
 * Simple Color Fragment Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

 in vec3 rgb;

 void main() {
	gl_FragColor = vec4(rgb, 1.0);
 }

 // END OF FILE