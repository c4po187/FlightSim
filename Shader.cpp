/**
 * Shader.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Shader.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Shader::Shader() { ; }

Shader::~Shader() { ; }

/* Functions */

Shader_sptr Shader::createShaderFromSource(const std::string& filename, 
	const std::string& tag, SHADER_TYPE type) {
	std::ifstream src(filename);
	if (!src) return nullptr;

	std::vector<const GLchar*> lines;
	for (std::string line; std::getline(src, line);)
		lines.push_back(line.c_str());
	if (lines.empty()) return nullptr;

	Shader_sptr pshader = Shader_sptr(new Shader());
	pshader->setTag(tag);
	pshader->m_type = type;
	
	GLenum typeflag = 0;
	switch (type) {
		case VERT: typeflag = GL_VERTEX_SHADER; break;
		case TESS_CTRL: typeflag = GL_TESS_CONTROL_SHADER; break;
		case TESS_EVAL: typeflag = GL_TESS_EVALUATION_SHADER; break;
		case GEOM: typeflag = GL_GEOMETRY_SHADER; break;
		case FRAG: typeflag = GL_FRAGMENT_SHADER; break;
		case COMP: typeflag = GL_COMPUTE_SHADER; break;
		default: break;
	}
	if (typeflag == 0) return nullptr;

	GLint err = 0;
	pshader->m_handle = glCreateShader(typeflag);
	glShaderSource(pshader->getHandle(), lines.size(), &lines[0], NULL);
	glCompileShader(pshader->getHandle());
	glGetShaderiv(pshader->getHandle(), GL_COMPILE_STATUS, &err);

	return (err != GL_FALSE) ? pshader : nullptr;
}

#pragma endregion

// END OF FILE 