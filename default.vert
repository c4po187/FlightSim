#version 440

/** 
 * Default Vertex Shader
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

layout (location = 0) in vec4 vertex_position;
layout (location = 1) in vec4 vertex_normal;
layout (location = 2) in vec4 vertex_tangent;
layout (location = 3) in vec4 vertex_color;
layout (location = 4) in vec2 vertex_uv;

uniform mat4 model_matrix, view_matrix, projection_matrix, modelview_matrix, mvp_matrix;

struct Light {
	vec4 position;
	vec4 color;
	float intensity;
};

uniform Light light;

out vec2 uv;
out vec4 vertex_position_world, rgba;
out vec3 light_direction, eye_direction, normal;

void main() {
	gl_Position = mvp_matrix * vertex_position;

	rgba = vertex_color;
	uv = vertex_uv;
	vertex_position_world = model_matrix * vertex_position;

	vec4 eye_pos = view_matrix * model_matrix * vertex_position;
	vec4 eye_dir = normalize(vec4(0.0, 0.0, 0.0, 0.0) - eye_pos);
	vec4 eye_light_pos = view_matrix * light.position;
	vec4 eye_light_dir = normalize(eye_light_pos - eye_pos);
	
	normal = normalize((view_matrix * model_matrix * vertex_normal).xyz);
	vec3 tangent = normalize((view_matrix * model_matrix * vertex_tangent).xyz);
	vec3 bitangent = normalize(cross(normal, tangent));
	
	mat3 tbn = transpose(mat3(tangent, bitangent, normal));
	
	light_direction = tbn * eye_light_dir.xyz;
	eye_direction = tbn * eye_dir.xyz; 
}