#version 330

in vec3 rgb;

void main() {
	gl_FragColor = vec4(rgb, 1.0);
}