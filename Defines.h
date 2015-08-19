/**
 * Defines.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__

#pragma once

#pragma region Prerequisites

#include <glm\glm.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#pragma endregion

#pragma region Definitions

namespace EUMD_FlightSimulator {

		/* Type Definitions */

		typedef unsigned short		U16;
		typedef unsigned long		U32;
		typedef unsigned long long	U64;
		typedef const char*			Cstr;
		typedef glm::vec2			Vec2;
		typedef glm::vec3			Vec3;
		typedef glm::vec4			Vec4;
		typedef glm::mat2			Matrix2;
		typedef glm::mat3			Matrix3;
		typedef glm::mat4			Matrix4;
		typedef glm::quat			Quatn;
}

#pragma endregion

#endif /* !__DEFINES_H__ */

// END OF FILE