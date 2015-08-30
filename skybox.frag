#version 440

/**
 * Skybox Fragment Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com 
 */

 in vec3 uv;

 uniform samplerCube cube_texture;

 void main() {
	gl_FragColor = texture(cube_texture, uv);
 }

 // END OF FILE