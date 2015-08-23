/**
 * Camera.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __CAMERA_H__
#define __CAMERA_H__

#pragma once

#pragma region Prerequisites

#include "Component.h"
#include <glm\gtx\euler_angles.hpp>

using namespace EUMD_FlightSimulator;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {
		
		class Camera;

		typedef std::tr1::shared_ptr<Camera> Camera_sptr;

		class Camera : public Component {

			public:

				/* Ctor, Dtor */

				Camera(Vec3 eye, Vec3 up, Vec3 target, 
					float fov, float aspect, float zNear, float zFar, std::string tag);
				Camera();
				~Camera();

				/* Accessors */

				inline const Matrix4& getViewMatrix() const { return m_viewMatrix; }
				inline const Matrix4& getProjectionMatrix() const { return m_projectionMatrix; }
				inline const Quatn& getOrientation() const { return m_orientation; }
				inline const Vec3& getPosition() const { return m_eye; }
				inline const Vec3& getUp() const { return m_up; }
				inline const Vec3& getTarget() const { return m_target; }
				inline const float& getFieldofView() const { return m_fov; }
				inline const float& getAspectRatio() const { return m_aspect; }
				inline const float& getMaxDepth() const { return m_zFar; }
				inline const float& getMinDepth() const { return m_zNear; }
				inline const float& getYaw() const { return m_yaw; }
				inline const float& getPitch() const { return m_pitch; }
				inline const float& getRoll() const { return m_roll; }

				/* Modifiers */

				inline void setViewMatrix(const Matrix4& m) { m_viewMatrix = m; }
				inline void setProjectionMatrix(const Matrix4& m) { m_projectionMatrix = m; }
				void setProjectionMatrix(const float& fov, const float& aspect, 
					const float& zNear, const float& zFar);
				inline void setOrientation(const Quatn& q) { m_orientation = q; }
				inline void setPosition(const Vec3& v) { m_eye = v; }
				inline void setPosition(const float& x, const float& y, const float& z) {
					this->setPosition(Vec3(x, y, z)); }
				inline void setUp(const Vec3& v) { m_up = v; }
				inline void setUp(const float& x, const float& y, const float& z) {
					this->setUp(Vec3(x, y, z)); }
				inline void setTarget(const Vec3& v) { m_target = v; }
				inline void setTarget(const float& x, const float& y, const float& z) {
					this->setTarget(Vec3(x, y, z)); }
				inline void setFieldofView(const float& f) { m_fov = f; }
				inline void setAspectRatio(const float& f) { m_aspect = f; }
				inline void setAspectRatio(const float& w, const float& h) { m_aspect = (w / h); }
				inline void setMaxDepth(const float& f) { m_zFar = f; }
				inline void setMinDepth(const float& f) { m_zNear = f; }
				inline void setYaw(const float& f) { m_yaw = f; }
				inline void setPitch(const float& f) { m_pitch = f; }
				inline void setRoll(const float& f) { m_roll = f; }

				/* Implementations */

				inline const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) override {
					return (tInfo_ex) ? (Component::getType() + "." + "Camera") : "Camera";
				}

				/* Functions */

				void updateProjectionMatrix();
				void updateViewMatrix(bool includeOrientation = false);
				void orient();

			private:

				/* Members */

				Matrix4 m_viewMatrix, m_projectionMatrix;
				Quatn m_orientation;
				Vec3 m_eye, m_up, m_target;
				float m_fov, m_aspect, m_zNear, m_zFar, m_yaw, m_pitch, m_roll;

				/* Functions */

				void initialize();
		};
	}
}

#pragma endregion

#endif /* !__CAMERA_H__ */

// END OF FILE