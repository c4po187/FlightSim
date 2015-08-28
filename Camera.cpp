/**
 * Camera.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Camera.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Camera::Camera(Vec3 eye, Vec3 up, Vec3 target, 
	float fov, float aspect, float zNear, float zFar, std::string tag) :
	m_fov(fov),
	m_aspect(aspect),
	m_zNear(zNear),
	m_zFar(zFar) { 
	this->setTag(tag);
	mp_transform = Transform_sptr(new Transform(eye, target, up, tag + "_Transform"));
	initialize(); 
}

Camera::Camera() :
	m_fov(45.0f),
	m_aspect(4.0f / 3.0f),
	m_zNear(.1f),
	m_zFar(100.0f) { 
	mp_transform = Transform_sptr(new Transform());
	initialize(); 
}

Camera::~Camera() { ; }

/* Modifiers */

void Camera::setProjectionMatrix(const float& fov, const float& aspect, const float& zNear, const float& zFar) {
	m_fov = fov;
	m_aspect = aspect;
	m_zNear = zNear;
	m_zFar = zFar;

	m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}

/* Functions */

void Camera::initialize() {
	// Set projection matrix
	m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);

	// Set the view matrix
	m_viewMatrix = glm::lookAt(
		mp_transform->getPosition(), mp_transform->getDirection(), mp_transform->getUp());
}

void Camera::updateViewMatrix(bool includeOrientation) {
	if (includeOrientation) {
		// Get a temporary matrix from the orientation
		Matrix4 change = glm::mat4_cast(mp_transform->getOrientation());

		// Grab the target vector from the matrix (we may be looking somewhere else...)
		mp_transform->setDirection(change[2][0], change[2][1], change[2][2]);

		// Get the right vector from the matrix 
		Vec3 right;
		right.x = change[0][0];
		right.y = change[0][1];
		right.z = change[0][2];

		// Recalculate the up and target vectors using the right vector in the cross products
		mp_transform->setUp(glm::normalize(glm::cross(mp_transform->getDirection(), right)));
		mp_transform->setDirection(glm::normalize(glm::cross(right, mp_transform->getUp())));
	}

	// Recalculate the view matrix from our vectors
	m_viewMatrix = glm::lookAt(
		mp_transform->getPosition(), mp_transform->getPosition() + 
		mp_transform->getDirection(), mp_transform->getUp());
}

void Camera::updateProjectionMatrix() {
	m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}

void Camera::orient() {
	mp_transform->setOrientation(mp_transform->getOrientation() *
		glm::quat_cast(glm::yawPitchRoll(
		mp_transform->getYaw(), mp_transform->getPitch(), mp_transform->getRoll())));
}

#pragma endregion

// END OF FILE