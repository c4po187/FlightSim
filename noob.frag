#version 330

/**
 * Noob Fragment Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

 uniform vec3 color;

 void main() {
	gl_FragColor = vec4(color, 1.0);
 }

 // END OF FILE