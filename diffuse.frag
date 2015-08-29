#version 440

/**
 * Diffuse Fragment Shader
 *
 * Rici Underwood © 2015
 * c4po198@gmail.com
 */

in vec4 vertex_position_world, rgba;
in vec3 light_direction, normal;

struct Light {
	vec4 position;
	vec4 color;
	float intensity;
};

uniform Light light;

void main() {
	vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);

	float light_distance = length(light.position - vertex_position_world);
	vec3 _light_direction = normalize(light_direction);

	float coefficient = max(0.0, clamp(dot(normal, _light_direction), 0, 1));

	vec4 lighting = light.color * light.intensity * coefficient / light_distance;
	vec4 illumination = ambient * lighting;

	gl_FragColor = illumination * rgba; 
}

// END OF FILE