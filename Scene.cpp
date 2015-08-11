/**
 * Scene.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Scene.h"

using namespace EUMD_FlightSimulator::Resources;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Scene::Scene(const std::string& tag, bool active) {
	m_tag = tag;
	mb_active = active;
}

Scene::Scene() { 
	mb_active = false;
}

Scene::~Scene() { ; }

/* Functions */

void Scene::update() { ; }

void Scene::render() { ; }

#pragma endregion

// END OF FILE