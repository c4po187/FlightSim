/**
 * SceneManager.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "SceneManager.h"

using namespace EUMD_FlightSimulator::Resources;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

SceneManager::SceneManager() : 
	m_index(0), 
	mp_currentScene(NULL), 
	mb_lastScene(false) { ; }

SceneManager::~SceneManager() {
	clean();
#if _DEBUG
	DST_NOTIFY;
#endif
}

/* Operator Overloads */

// Use with caution (No error checking!)
SceneManager& SceneManager::operator -- () {
	this->previousScene();

	return (*this);
}

// Use with caution (No error checking!)
SceneManager& SceneManager::operator ++ () {
	this->nextScene();

	return (*this);
}

SceneManager& SceneManager::operator << (const Scene_sptr pscene) {
	this->addScene(pscene);

	return (*this);
}

/* Functions */

SceneManager_sptr SceneManager::createSceneManager(const PScenes& scenes) {
	SceneManager_sptr sm = SceneManager_sptr(new SceneManager());
	sm->mv_pScenes = scenes;

	return (sm->initialize()) ? sm : nullptr;
}

// Must be called after adding at least one scene, prior to calling update!
bool SceneManager::initialize() {
	if (getSceneQuantity() > 0) {
		invokeScene();
		return true;
	}

	return false;
}

void SceneManager::invokeScene() {
	// Deactivate current scene
	if (mp_currentScene)
		mp_currentScene->setActive(false);

	// Make current scene match index from vector
	mp_currentScene = mv_pScenes[m_index];

	// Activate it
	mp_currentScene->setActive(true);
}

bool SceneManager::exists(const std::string& tag) {
	bool _exists = false;

	for (auto s : mv_pScenes) {
		if (s->getTag() == tag) {
			_exists = true;
			break;
		}
	}

	return _exists;
}

PScenes::iterator SceneManager::getSceneIteratorFromTag(const std::string& tag) {
	if (!exists(tag))
		throw EX_INV_TAG;

	return std::find_if(mv_pScenes.begin(), mv_pScenes.end(),
		[&tag](Scene_sptr s)-> bool { return s->getTag() == tag; });
}

void SceneManager::addScene(Scene_sptr pscene) {
	mv_pScenes.push_back(pscene);
}

bool SceneManager::removeSceneAt(const int& index) {
	if (index < 0 || index >= getSceneQuantity())
		throw EX_IOR;

	if (m_index == index) 
		mp_currentScene = NULL;

	size_t pre = getSceneQuantity();
	mv_pScenes.erase(mv_pScenes.begin() + index);

	return (mv_pScenes.size() < pre);
}

bool SceneManager::removeScene(const std::string& tag) {
	if (!exists(tag))
		throw EX_INV_TAG;

	int index = std::distance(mv_pScenes.begin(), getSceneIteratorFromTag(tag));

	return removeSceneAt(index);
}

Scene_sptr SceneManager::findScene(const unsigned int& id) {
	PScenes::iterator sit = std::find_if(
		mv_pScenes.begin(), mv_pScenes.end(),
		[&id](Scene_sptr s)-> bool { return s->getID() == id; });

	return (sit != mv_pScenes.end()) ? (*sit) : nullptr;
}

Scene_sptr SceneManager::findScene(const std::string& tag) {
	PScenes::iterator sit = std::find_if(
		mv_pScenes.begin(), mv_pScenes.end(),
		[&tag](Scene_sptr s)-> bool { return s->getTag() == tag; });

	return (sit != mv_pScenes.end()) ? (*sit) : nullptr;
}

Scene_sptr SceneManager::getSceneByIndex(const int& index) {
	if (!mv_pScenes.empty() && index >= 0 && index < mv_pScenes.size()) {
		return mv_pScenes[index];
	}

	return nullptr;
}

bool SceneManager::previousScene() {
	--m_index;
	
	if (m_index >= 0) {
		invokeScene();

		return true;
	}

	return false;
}

bool SceneManager::nextScene() {
	++m_index;
	
	if (m_index < getSceneQuantity()) {
		invokeScene();

		return true;
	}

	return false;
}

void SceneManager::activateScene(const std::string& tag) {
	if (!exists(tag))
		throw EX_INV_TAG;

	m_index = std::distance(mv_pScenes.begin(), getSceneIteratorFromTag(tag));
	invokeScene();
}

void SceneManager::activateScene(const int& index) {
	if (index >= 0 || index < mv_pScenes.size()) {
		m_index = index;
		invokeScene();
	}
}

void SceneManager::update() {
	// Set the last scene boolean based on the following condition
	mb_lastScene = (m_index == (getSceneQuantity() - 1));
}

void SceneManager::clean() {
	if (!mv_pScenes.empty())
		mv_pScenes.clear();
}

#pragma endregion

// END OF FILE