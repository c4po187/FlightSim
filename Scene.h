/**
 * Scene.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __SCENE_H__
#define __SCENE_H__

#pragma once

#pragma region Prerequisites

#include "Resource.h"

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Resources {

		class Scene;

		typedef std::tr1::shared_ptr<Scene> Scene_sptr;

		class Scene : public Resource {

			public:

				/* Ctor, Dtor */

				Scene(const std::string& tag);
				Scene();
				~Scene();

				/* Functions */

				void						update();
				void						render();

				/* Implementations */

				inline const std::string	getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) override { 
					return (tInfo_ex) ? (Resource::getType() + "." + "Scene") : "Scene";
				}

			private:

				/* Members */

				/** 
				 * @TODO:
				 *
				 * We will need a vector of GameObject pointers here 
				 * linking to ones previously provided by the ResourceFactory.
				 */
		};
	}
}

#pragma endregion

#endif /* !__SCENE_H__ */

// END OF FILE