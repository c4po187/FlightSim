/**
 * Transform.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#pragma once

#pragma region Prerequisites

#include "Component.h"

using namespace EUMD_FlightSimulator;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		class Transform;
		class ModelTransform;

		typedef std::tr1::shared_ptr<Transform> Transform_sptr;
		typedef std::tr1::shared_ptr<ModelTransform> ModelTransform_sptr;

		class Transform : public Component {

			public:

				/* Ctor, Dtor */

				Transform(const Vec3& position, const Vec3& direction, const Vec3& up, const std::string& tag);
				Transform(const Vec3& position, const std::string& tag);
				Transform();
				virtual ~Transform();

				/* Accessors */

				inline const Vec3& getPosition() const { return m_position; }
				inline const Vec3& getDirection() const { return m_direction; }
				inline const Vec3& getUp() const { return m_up; }
				inline const Quatn& getOrientation() const { return m_orientation; }
				inline const float& getYaw() const { return m_yaw; }
				inline const float& getPitch() const { return m_pitch; }
				inline const float& getRoll() const { return m_roll; }

				/* Modifiers */

				inline void setPosition(const Vec3& v) { m_position = v; }
				inline void setPosition(const float& x, const float& y, const float& z) {
					this->setPosition(Vec3(x, y, z)); }
				inline void setDirection(const Vec3& v) { m_direction = v; }
				inline void setDirection(const float& x, const float& y, const float& z) { 
					this->setDirection(Vec3(x, y, z)); }
				inline void setUp(const Vec3& v) { m_up = v; }
				inline void setUp(const float& x, const float& y, const float& z) {
					this->setUp(Vec3(x, y, z)); }
				inline void setOrientation(const Quatn& q) { m_orientation = q; }
				inline void setYaw(const float& f) { m_yaw = f; }
				inline void setPitch(const float& f) { m_pitch = f; }
				inline void setRoll(const float& f) { m_roll = f; }

				/* Implementations */

				inline virtual const std::string getType(TypeInfo typeInfo_ex = DEFAULT_TYPE_INFO) override {
					return (typeInfo_ex) ? (Component::getType() + ".Transform") : "Transform";
				}

				virtual void clean() override;

			protected:

				/* Members */

				Vec3 m_position, m_direction, m_up;
				Quatn m_orientation;
				float m_yaw, m_pitch, m_roll;
		};

		class ModelTransform : public Transform {

			public:

				/* Ctor, Dtor */

				ModelTransform(const Vec3& position, const Vec3& direction, const Vec3& m_up, 
					const std::string& tag);
				ModelTransform(const Vec3& position, const std::string& tag);
				ModelTransform();
				~ModelTransform();

				/* Accessors */

				inline const Matrix4& getModelMatrix() const { return m_modelMatrix; }

				/* Implementations */

				inline const std::string getType(TypeInfo typeInfo_ex = DEFAULT_TYPE_INFO) override {
					return (typeInfo_ex) 
						? (Component::getType() + "." + Transform::getType() + ".ModelTransform") 
						: "ModelTransform";
				}

				/* Functions */

				void updateModelMatrix();

			private:

				/* Members */

				Matrix4 m_modelMatrix;
		};
	}
}

#pragma endregion

#endif /* !__TRANSFORM_H__ */

// END OF FILE