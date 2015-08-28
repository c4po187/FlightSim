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

#include "Transform.h"
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

				inline Transform_sptr getTransform() { return mp_transform; }
				inline const Matrix4& getViewMatrix() const { return m_viewMatrix; }
				inline const Matrix4& getProjectionMatrix() const { return m_projectionMatrix; }
				inline const float& getFieldofView() const { return m_fov; }
				inline const float& getAspectRatio() const { return m_aspect; }
				inline const float& getMaxDepth() const { return m_zFar; }
				inline const float& getMinDepth() const { return m_zNear; }

				/* Modifiers */

				inline void setTransform(Transform_sptr ptransform) { mp_transform = ptransform; }
				inline void setViewMatrix(const Matrix4& m) { m_viewMatrix = m; }
				inline void setProjectionMatrix(const Matrix4& m) { m_projectionMatrix = m; }
				void setProjectionMatrix(const float& fov, const float& aspect, 
					const float& zNear, const float& zFar);
				inline void setFieldofView(const float& f) { m_fov = f; }
				inline void setAspectRatio(const float& f) { m_aspect = f; }
				inline void setAspectRatio(const float& w, const float& h) { m_aspect = (w / h); }
				inline void setMaxDepth(const float& f) { m_zFar = f; }
				inline void setMinDepth(const float& f) { m_zNear = f; }

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

				Transform_sptr mp_transform;
				Matrix4 m_viewMatrix, m_projectionMatrix;
				float m_fov, m_aspect, m_zNear, m_zFar;

				/* Functions */

				void initialize();
		};
	}
}

#pragma endregion

#endif /* !__CAMERA_H__ */

// END OF FILE