/**
 * Component.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#pragma once

#pragma region Prerequisites

#include "IApplicationObject.h"
#include <memory>
#include <vector>
#include "LUT.h"
#include <algorithm>
#include <typeinfo>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Components {

		class Component;

		typedef std::tr1::shared_ptr<Component> Component_sptr;
		typedef std::vector<Component_sptr> PComponents;

		class Component : public IApplicationObject {

			public:

				/* Dtor */

				virtual ~Component();

				/* Accessors */

				inline const std::string& getTag() const { return m_tag; }
				inline const PComponents& getChildren() const { return mv_pChildComponents; }

				/* Modifiers */

				inline void setTag(const std::string& tag) { m_tag = tag; }

				/* Functions */

				void addComponent(Component_sptr pComponent);
				bool removeComponentAt(const int& index);
				virtual void clean();

				template <class _TyComponent>
				inline std::tr1::shared_ptr<_TyComponent> getComponent() {
					if (!checkValidity(typeid(_TyComponent).name())) return nullptr;

					Component_sptr component = NULL;
					std::string tname = getClassNameFromTypeID(typeid(_TyComponent).name());

					for (auto c : mv_pChildComponents) {
						if (c->getType() == tname) {
							component = c;
							break;
						}
					}

					return (component) ? std::dynamic_pointer_cast<_TyComponent>(component) : nullptr;
				}

				template <class _TyComponent>
				inline std::tr1::shared_ptr<_TyComponent> getComponent(const std::string& tag) {
					if (!checkValidity(typeid(_TyComponent).name())) return nullptr;

					PComponents::iterator pcit = std::find_if(
						mv_pChildComponents.begin(), mv_pChildComponents.end(),
						[&tag](Component_sptr c)-> bool { return c->getTag() == tag; });

					return (std::dynamic_pointer_cast<_TyComponent>(*pcit)) ?
						std::dynamic_pointer_cast<_TyComponent>(*pcit) : nullptr;
				}

				/* Implementations */

				inline virtual const std::string getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { 
					return "Component"; 
				}

			protected:

				/* Members */

				std::string m_tag;
				PComponents mv_pChildComponents;

			private:

				/* Functions */

				bool checkValidity(const char* type_id);
				std::string getClassNameFromTypeID(const char* type_id);
		};
	}
}

#pragma endregion

#endif /* !__COMPONENT_H__ */

// END OF FILE