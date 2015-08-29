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

Shader::Shader() : m_handle(0) { ; }

Shader::~Shader() {
	if (glIsShader(m_handle))
		glDeleteShader(m_handle);
}

/* Functions */

Shader_sptr Shader::createShaderFromSource(const std::string& filename, SHADER_TYPE type, const std::string& tag) {
	std::ifstream src(filename);
	if (!src) return nullptr;

	std::ostringstream srcStream;
	for (std::string line; std::getline(src, line);) {
		// We need to add newline escape sequences at the end of every directive
		size_t found = line.find('#');
		if (found != std::string::npos) 
			line.push_back('\n');

		srcStream << line;
	}
	
	std::string srcstr = srcStream.str();

	return createShaderFromText(srcstr, type, tag);
}

Shader_sptr Shader::createShaderFromText(const std::string& text, SHADER_TYPE type, const std::string& tag) {
	if (text.empty()) return nullptr;
	const GLchar* glsrc = text.c_str();
	
	Shader_sptr pshader = Shader_sptr(new Shader());
	pshader->m_type = type;
	if (!tag.empty())
		pshader->setTag(tag);

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
	glShaderSource(pshader->getHandle(), 1, &glsrc, NULL);
	glCompileShader(pshader->getHandle());
	glGetShaderiv(pshader->getHandle(), GL_COMPILE_STATUS, &err);

#if _DEBUG
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
#endif
	if (err == GL_FALSE) {
#if _DEBUG
		GLint maxLength = 0;
		glGetShaderiv(pshader->getHandle(), GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(pshader->getHandle(), maxLength, &maxLength, &errorLog[0]);

		// Print out the error & delete the shader object to prevent leaks
		std::cout << &errorLog[0] << std::flush;
#endif
		glDeleteShader(pshader->getHandle());

		return nullptr;
	}
	else {
#if _DEBUG
		std::cout << "SUCCESS: ";
		if (!pshader->getTag().empty())
			std::cout << pshader->getTag() << ", ";
		std::cout << '(' << pshader->getType(EXTENDED_TYPE_INFO) << ")\n" << std::endl;
#endif
	}

	return pshader;
}

#pragma endregion

// END OF FILE 