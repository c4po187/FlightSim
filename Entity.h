/**
 * Entity.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __ENTITY_H__
#define __ENTITY_H__

#pragma once

#pragma region Prerequisites

#include "Resource.h"
#include "Transform.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Resources {

		class Entity;

		typedef std::tr1::shared_ptr<Entity> Entity_sptr;
		typedef std::vector<Entity_sptr> PEntities;

		class Entity : public Resource {

			public:

				/* Ctor, Dtor */

				Entity();
				~Entity();

				/* Implementations */

				inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) override {
					return (tInfo_ex) ? (Resource::getType() + ".Entity") : "Entity";
				}

				/* Accessors */

				inline Transform_sptr getTransform() { return mp_transform; }

				/* Modifiers */

				inline void setTransform(Transform_sptr ptransform) { mp_transform = ptransform; }

				/* Functions */

				void update();
				void render();

			protected:

				/* Members */

				Transform_sptr mp_transform;	// Mandatory component
		};
	}
}

#pragma endregion

#endif /* !__ENTITY_H__ */

// END OF FILE