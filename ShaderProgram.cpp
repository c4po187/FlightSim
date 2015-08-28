/**
 * ShaderProgram.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "ShaderProgram.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

ShaderProgram::ShaderProgram(const std::string& tag) {
	m_tag = tag;
	m_handle = glCreateProgram();
}

ShaderProgram::ShaderProgram() {
	m_handle = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
	/**
	 * @TODO:
	 *		Detach all shaders and delete them
	 *		before deleting the program.
	 */
	if (glIsProgram(m_handle))
		glDeleteProgram(m_handle);
}

/* Functions */

int ShaderProgram::attachmentFrequency() {
	GLint nShaders = 0;
	glGetProgramiv(m_handle, GL_ATTACHED_SHADERS, &nShaders);

	return nShaders;
}

void ShaderProgram::attachShader(Shader_sptr pshader) {
	// Add as a child component, for later comparisons
	mv_pChildComponents.push_back(pshader);

	// Now attach to the program, and set the delete flag to the shader ready for detachment.
	glAttachShader(m_handle, pshader->getHandle());
	glDeleteShader(pshader->getHandle());
}

void ShaderProgram::detachShader(PComponents::iterator& pit) {
	int index = std::distance(mv_pChildComponents.begin(), pit);

	// Detach from program
	glDetachShader(m_handle, std::dynamic_pointer_cast<Shader>(*pit)->getHandle());

	// Now remove the child
	mv_pChildComponents.erase(mv_pChildComponents.begin() + index);
}

void ShaderProgram::detachShader(const HSHADER& handle) {
	static HSHADER _handle = handle;

	if (!mv_pChildComponents.empty()) {
		PComponents::iterator pit = std::find_if(
			mv_pChildComponents.begin(), mv_pChildComponents.end(),
			[](Component_sptr c)-> bool { 
			return std::dynamic_pointer_cast<Shader>(c)->getHandle() == _handle; });

		if (pit != mv_pChildComponents.end())
			detachShader(pit);
	}
}

void ShaderProgram::detachShader(const std::string& tag) {
	static std::string _tag = tag;

	if (!mv_pChildComponents.empty()) {
		PComponents::iterator pit = std::find_if(
			mv_pChildComponents.begin(), mv_pChildComponents.end(),
			[](Component_sptr c)-> bool { return c->getTag() == _tag; });

		if (pit != mv_pChildComponents.end())
			detachShader(pit);
	}
}

bool ShaderProgram::detachShaders() {
	GLint nShaders = 0;

	for (auto c : mv_pChildComponents) 
		glDetachShader(m_handle, std::dynamic_pointer_cast<Shader>(c)->getHandle());

	if (attachmentFrequency() == 0) {
		// The shaders were detached, so clear children and return true
		mv_pChildComponents.clear();

		return true;
	}

	return false;
}

bool ShaderProgram::link() {
	glLinkProgram(m_handle);

	GLint linked = 0;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &linked);

#if _DEBUG
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << '\n';
#endif
	if (linked == GL_FALSE) {
#if _DEBUG
		GLint maxLength = 0;
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorlog(maxLength);
		glGetProgramInfoLog(m_handle, maxLength, &maxLength, &errorlog[0]);

		glDeleteProgram(m_handle);
		std::cout << "LINK ERROR: ";
		if (!getTag().empty())
			std::cout << getTag() << ", ";
		std::cout << "(" << getType(EXTENDED_TYPE_INFO) << ")...\n";
		std::cout << &errorlog[0] << "\n" << std::endl;
#endif
		return false;
	}
	else {
#if _DEBUG
		std::cout << "LINK SUCCESS: ";
		if (!getTag().empty())
			std::cout << getTag() << ", ";
		std::cout << "(" << getType(EXTENDED_TYPE_INFO) << ")\n" << std::endl;
#endif
		return true;
	}
}

bool ShaderProgram::activate() {
	// First validate the program, to guarantee its execution
	GLint valid = 0;
	glValidateProgram(m_handle);
	glGetProgramiv(m_handle, GL_VALIDATE_STATUS, &valid);

	if (valid == GL_TRUE) {
		glUseProgram(m_handle);
#if _DEBUG
		std::cout << "ACTIVATED: ";
		if (!getTag().empty())
			std::cout << getTag() << ", ";
		std::cout << "(" << getType(EXTENDED_TYPE_INFO) << ")\n" << std::endl;
#endif
		return true;
	}
#if _DEBUG
	std::cout << "ACTIVATION FAILURE: ";
	if (!getTag().empty())
		std::cout << getTag() << ", ";
	std::cout << "(" << getType(EXTENDED_TYPE_INFO) << ")\n" << std::endl;
#endif
	return false;
}

void ShaderProgram::cacheProgram(const std::string& filename, GLenum& binFormat) {
	GLint len = 0;

	glGetProgramiv(m_handle, GL_PROGRAM_BINARY_LENGTH, &len);

	if (len > 0) {
		char* cache = new char[len];
		glGetProgramBinary(m_handle, len, NULL, &binFormat, cache);

		// Write to file
		std::ofstream bin(filename, std::ios::out | std::ios::binary);
		bin.write(cache, sizeof(cache));
		bin.close();

		delete[] cache;
	}
}

ShaderProgram_sptr ShaderProgram::restoreCache(const std::string& filename, const GLenum& binFormat) {
	// Create a program first up...
	ShaderProgram_sptr pshaderProg = ShaderProgram_sptr(new ShaderProgram("_RESTORED"));

	std::streampos szFile;
	char* cache;

	// Open the file (positioned at the end (ate))
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open()) {
		// Allocate size for the cache
		szFile = file.tellg();
		cache = new char[szFile];

		// Rewind to start of file, now we have allocated size for the cache
		file.seekg(0, std::ios::beg);

		// Read into cache and close file
		file.read(cache, szFile);
		file.close();

		// Load binary to handle & delete the cache
		glProgramBinary(pshaderProg->getHandle(), binFormat, cache, szFile);
		delete[] cache;

		return pshaderProg;
	}

	return nullptr;
}

#pragma endregion

// END OF FILE