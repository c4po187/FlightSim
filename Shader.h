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

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		class Shader : public Component {

			public:

				/* Ctor, Dtor */

				Shader();
				~Shader();

				/* Accessors */

				inline const unsigned int& getHandle() const { return m_handle; }

				/* Implementations */

				inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) override {
					return (tInfo_ex) ? (Component::getType() + "." + "Shader") : "Shader"; }

			private:

				/* Members */

				unsigned int m_handle;
		};
	}
}

#pragma endregion

#endif /* !__SHADER_H__ */

// END OF FILE