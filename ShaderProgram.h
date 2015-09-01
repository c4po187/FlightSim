/**
 * ShaderProgram.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

#pragma once

#pragma region Prerequisites

#include "Component.h"
#include "Shader.h"
#include <algorithm>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		class ShaderProgram;

		typedef std::tr1::shared_ptr<ShaderProgram> ShaderProgram_sptr;
		typedef unsigned int HPROGRAM;

		class ShaderProgram final : public Component {

			public:

				/* Ctor, Dtor */

				ShaderProgram(const std::string& tag);
				ShaderProgram();
				~ShaderProgram();

				/* Accessors */

				inline const HPROGRAM& getHandle() const { return m_handle; }
				inline const bool isLinked() { return (mb_linked == GL_TRUE) ? true : false; }
				inline const bool isValid() { return (mb_valid == GL_TRUE) ? true : false; }
				
				/* Implementations */

				inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) override {
					return (tInfo_ex) ? (Component::getType() + ".ShaderProgram") : "ShaderProgram"; }

				/* Functions */

				int attachmentFrequency();
				void attachShader(Shader_sptr pshader);
				void detachShader(const HSHADER& handle);
				void detachShader(const std::string& tag);
				bool detachShaders();
				bool link();
				bool activate();
				void cacheProgram(const std::string& filename, GLenum& binFormat);
				static ShaderProgram_sptr restoreCache(const std::string& filename, const GLenum& binFormat);
				int getUniformLocation(const std::string& uniform);
				int getAttributeLocation(const std::string& attrib);
				void sendUniform(const int& location, const float& f);
				void sendUniform(const int& location, const float& f0, const float& f1);
				void sendUniform(const int& location, const float& f0, const float& f1, const float& f2);
				void sendUniform(
					const int& location, const float& f0, const float& f1, const float& f2, const float& f3);
				void sendUniform(const int& location, const int& i);
				void sendUniform(const int& location, const int& i0, const int& i1);
				void sendUniform(const int& location, const int& i0, const int& i1, const int& i2);
				void sendUniform(
					const int& location, const int& i0, const int& i1, const int& i2, const int& i3);
				void sendUniform(const int& location, GLsizei count, const Vec2& v);
				void sendUniform(const int& location, GLsizei count, const Vec3& v);
				void sendUniform(const int& location, GLsizei count, const Vec4& v);
				void sendUniform(const int& location, GLsizei count, const iVec2& v);
				void sendUniform(const int& location, GLsizei count, const iVec3& v);
				void sendUniform(const int& location, GLsizei count, const iVec4& v);
				void sendUniform(const int& location, GLsizei count, bool transpose, const Matrix2& m);
				void sendUniform(const int& location, GLsizei count, bool transpose, const Matrix3& m);
				void sendUniform(const int& location, GLsizei count, bool transpose, const Matrix4& m);
				float* getUniformf(const int& location);
				int* getUniformi(const int& location);

			private:

				/* Members */

				HPROGRAM m_handle;
				GLint mb_linked, mb_valid;

				/* Functions */

				void details();
				void detachShader(PComponents::iterator& pit);
		};
	}
}

#pragma endregion

#endif /* !__SHADER_PROGRAM_H__ */

// END OF FILE