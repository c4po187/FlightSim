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

			private:

				/* Members */

				HPROGRAM m_handle;

				/* Functions */

				void detachShader(PComponents::iterator& pit);
		};
	}
}

#pragma endregion

#endif /* !__SHADER_PROGRAM_H__ */

// END OF FILE