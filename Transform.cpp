/**
 * Transform.cpp
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#pragma region Prerequisites

#include "Transform.h"

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Definitions

/* Ctor, Dtor */

Transform::Transform(const Vec3& position, const Vec3& direction, const Vec3& up, const std::string& tag) :
	m_position(position), m_direction(direction), m_up(up),
	m_yaw(.0f), m_pitch(.0f), m_roll(.0f), m_orientation(Quatn()) { m_tag = tag; }

Transform::Transform(const Vec3& position, const std::string& tag) : 
	m_position(position), m_direction(Vec3(.0f, .0f, -1.0f)), m_up(Vec3(.0f, 1.0f, .0f)),
	m_yaw(.0f), m_pitch(.0f), m_roll(.0f), m_orientation(Quatn()) { m_tag = tag; }

Transform::Transform() :
	m_position(Vec3()), m_direction(Vec3(.0f, .0f, -1.0f)), m_up(Vec3(.0f, 1.0f, .0f)),
	m_yaw(.0f), m_pitch(.0f), m_roll(.0f), m_orientation(Quatn()) { ; }

Transform::~Transform() { ; }

ModelTransform::ModelTransform(const Vec3& position, const Vec3& direction,
	const Vec3& up, const std::string& tag) {
	m_tag = tag;
	m_position = position;
	m_direction = direction;
	m_up = up;
	m_orientation = Quatn();
	m_yaw = m_pitch = m_roll = .0f;
	m_modelMatrix = Matrix4(1.0f);
}

ModelTransform::ModelTransform(const Vec3& position, const std::string& tag) {
	m_tag = tag;
	m_position = position;
	m_direction = Vec3(.0f, .0f, -1.0f);
	m_up = Vec3(.0f, 1.0f, .0f);
	m_orientation = Quatn();
	m_yaw = m_pitch = m_roll = .0f;
	m_modelMatrix = Matrix4(1.0f);
}

ModelTransform::ModelTransform() {
	m_position = Vec3();
	m_direction = Vec3(.0f, .0f, -1.0f);
	m_up = Vec3(.0f, 1.0f, .0f);
	m_orientation = Quatn();
	m_yaw = m_pitch = m_roll = .0f;
	m_modelMatrix = Matrix4(1.0f);
}

ModelTransform::~ModelTransform() { ; }

/* Functions */

void ModelTransform::updateModelMatrix() { ; }

/* Implementations */

void Transform::clean() { ; }

#pragma endregion

// END OF FILE