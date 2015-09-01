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
#include "Vertex.h"
#include "Pair.h"
#include "Camera.h"
#include "ShaderProgram.h"

using namespace EUMD_FlightSimulator::Components;
using namespace EUMD_FlightSimulator::Core::Graphics;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Resources {

		#define GRID_COLOR Vec3(.0f, .85f, .25f)

		class Scene;

		typedef std::tr1::shared_ptr<Scene> Scene_sptr;

		class Scene : public Resource {

			public:

				/* Ctor, Dtor */

				Scene(const std::string& tag, Camera_sptr pcamera, bool showGrid);
				Scene(const std::string& tag, bool active = true);
				Scene();
				~Scene();

				/* Accessors */

				inline const bool& isGridVisible() const { return mb_showGrid; }

				/* Modifiers */

				inline void gridVisibility(const bool& visible) { mb_showGrid = visible; }

				/* Functions */

				void update();
				void render();
				void renderGrid();

				/* Implementations */

				inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) override { 
					return (tInfo_ex) ? (Resource::getType() + "." + "Scene") : "Scene";
				}

			private:

				/* Members */

				bool mb_showGrid;
				unsigned int m_grid_vao, m_grid_vbo;

				/* Functions */

				void initializeGrid();
		};
	}
}

#pragma endregion

#endif /* !__SCENE_H__ */

// END OF FILE