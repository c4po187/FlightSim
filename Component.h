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

				inline const std::string&			getTag() const { return m_tag; }
				inline const PComponents&			getChildren() const { return mv_pChildComponents; }

				/* Modifiers */

				inline void							setTag(const std::string& tag) { m_tag = tag; }

				/* Functions */

				void								addComponent(Component_sptr pComponent);
				bool								removeComponentAt(const int& index);
				virtual void						clean();

				/* Implementations */

				inline virtual const std::string	getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { 
					return "Component"; 
				}

			protected:

				/* Members */

				std::string							m_tag;
				PComponents							mv_pChildComponents;
		};
	}
}

#pragma endregion

#endif /* !__COMPONENT_H__ */

// END OF FILE