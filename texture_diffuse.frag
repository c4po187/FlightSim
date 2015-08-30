#version 440

/**
 * Texture Diffuse Fragment Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

in vec2 uv;
in vec4 vertex_position_world;
in vec3 light_direction;

uniform sampler2D diffuse_texture, normalmap_texture;

struct Light {
	vec4 position;
	vec4 color;
	float intensity;
};

uniform Light light;

void main() {
	vec4 ambient = vec4(1.0, 1.0, 1.0, 1.0);

	float light_distance = length(light.position - vertex_position_world);
	vec4 normal = normalize(texture2D(normalmap_texture, uv) * 2.0 - 1.0);
	vec3 _light_direction = normalize(light_direction);

	float coefficient = max(0.0, clamp(dot(normal.xyz, _light_direction), 0, 1));

	vec4 lighting = light.color * light.intensity * coefficient / light_distance;
	vec4 illumination = ambient * lighting;

	gl_FragColor = illumination * texture2D(diffuse_texture, uv); 
}

// END OF FILE