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

				/* Accessors */

				inline const std::string	getTypeExt() { 
					return (Resource::getType() + "." + this->getType()); 
				}

				/* Functions */

				void						update();
				void						render();

				/* Implementations */

				inline const std::string	getType() override { return "Scene"; }

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