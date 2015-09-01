/**
 * SceneManager.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#pragma once

#pragma region Prerequisites

#include "Scene.h"
#include <vector>
#include <algorithm>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Resources {

		class SceneManager;

		typedef std::tr1::shared_ptr<SceneManager> SceneManager_sptr;
		typedef std::vector<Scene_sptr> PScenes;

		class SceneManager final : public IApplicationObject {

			public:

				/* Ctor, Dtor */

				SceneManager();
				~SceneManager();

				/* Operators */

				SceneManager& operator -- ();
				SceneManager& operator ++ ();
				SceneManager& operator << (const Scene_sptr pscene);

				/* Accessors */

				inline const bool& isLastScene() const { return mb_lastScene; }
				inline const size_t getSceneQuantity() const { return mv_pScenes.size(); }
				inline Scene_sptr getCurrentScene() { return mp_currentScene; }
				inline const U32& getIndex() const { return m_index; }

				/* Modifiers */

				inline void setIndex(const unsigned int& index) { m_index = index; }

				/* Implementations */

				inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { return "SceneManager"; }
				void clean();

				/* Functions */

				static SceneManager_sptr createSceneManager(const PScenes& scenes);
				bool initialize();
				void addScene(Scene_sptr pscene);
				bool removeSceneAt(const int& index);
				bool removeScene(const std::string& tag);
				Scene_sptr findScene(const unsigned int& id);
				Scene_sptr findScene(const std::string& tag);
				Scene_sptr getSceneByIndex(const int& index);
				bool previousScene();
				bool nextScene();
				void activateScene(const std::string& tag);
				void activateScene(const int& index);
				void update();

			private:

				/* Members */

				PScenes mv_pScenes;
				Scene_sptr mp_currentScene;
				U32 m_index;
				bool mb_lastScene;

				/* Functions */

				bool exists(const std::string& tag);
				PScenes::iterator getSceneIteratorFromTag(const std::string& tag);
				void invokeScene();
		};
	}
}

#pragma endregion

#endif /* !__SCENE_MANAGER_H__ */

// END OF FILE