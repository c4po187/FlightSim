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
	m_eye(eye),
	m_up(up),
	m_target(target),
	m_fov(fov),
	m_aspect(aspect),
	m_zNear(zNear),
	m_zFar(zFar) { 
	this->setTag(tag);
	initialize(); 
}

Camera::Camera() :
	m_eye(Vec3()),
	m_up(Vec3(.0f, 1.0f, .0f)),
	m_target(Vec3(.0f, .0f, -1.0f)),
	m_fov(45.0f),
	m_aspect(4.0f / 3.0f),
	m_zNear(.1f),
	m_zFar(100.0f) { initialize(); }

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
	/**
	 * Set up the orientation. 
	 * First, set the orientation to the identity quaternion.
	 * Secondly, set the orientation helpers.
	 */
	m_orientation = Quatn();
	m_yaw = m_pitch = m_roll = .0f;

	// Set projection matrix
	m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);

	// Normalize target and up vectors
	m_up = glm::normalize(m_up);
	m_target = glm::normalize(m_target);

	// Set the view matrix
	m_viewMatrix = glm::lookAt(m_eye, m_target, m_up);
}

void Camera::updateViewMatrix(bool includeOrientation) {
	if (includeOrientation) {
		// Get a temporary matrix from the orientation
		Matrix4 change = glm::mat4_cast(m_orientation);

		// Grab the target vector from the matrix (we may be looking somewhere else...)
		m_target.x = change[2][0];
		m_target.y = change[2][1];
		m_target.z = change[2][2];

		// Get the right vector from the matrix 
		Vec3 right;
		right.x = change[0][0];
		right.y = change[0][1];
		right.z = change[0][2];

		// Recalculate the up and target vectors using the right vector in the cross products 
		m_up = glm::normalize(glm::cross(m_target, right));
		m_target = glm::normalize(glm::cross(right, m_up));
	}

	// Recalculate the view matrix from our vectors
	m_viewMatrix = glm::lookAt(m_eye, m_eye + m_target, m_up);
}

void Camera::updateProjectionMatrix() {
	m_projectionMatrix = glm::perspective(m_fov, m_aspect, m_zNear, m_zFar);
}

void Camera::orient() {
	m_orientation *= glm::quat_cast(glm::yawPitchRoll(m_yaw, m_pitch, m_roll));
}

#pragma endregion

// END OF FILE