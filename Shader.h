/**
 * Shader.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __SHADER_H__
#define __SHADER_H__

#pragma once

#pragma region Prerequisites

#include "Component.h"
#include <iostream>
#include <fstream>
#include <GL\glew.h>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		enum SHADER_TYPE {
			VERT,
			TESS_CTRL,
			TESS_EVAL,
			GEOM,
			FRAG,
			COMP 
		};

		class Shader;

		typedef std::tr1::shared_ptr<Shader> Shader_sptr;

		class Shader : public Component {

			public:

				/* Ctor, Dtor */

				Shader();
				~Shader();

				/* Accessors */

				inline const unsigned int& getHandle() const { return m_handle; }
				inline const SHADER_TYPE& getShaderType() const { return m_type; }

				/* Implementations */

				inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) override {
					return (tInfo_ex) ? (Component::getType() + "." + "Shader") : "Shader"; }

				/* Functions */

				static Shader_sptr createShaderFromSource(const std::string& filename, const std::string& tag, 
					SHADER_TYPE type);

			private:

				/* Members */

				unsigned int m_handle;
				SHADER_TYPE m_type;
		};
	}
}

#pragma endregion

#endif /* !__SHADER_H__ */

// END OF FILE