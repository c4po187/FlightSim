/**
 * Resource.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#pragma once

#pragma region Prerequisites

#include "IApplicationObject.h"
#include <memory>
#include <vector>
#include "Component.h"
#include "LUT.h"
#include <typeinfo>

using namespace EUMD_FlightSimulator::Components;

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Resources {

		class Resource;

		typedef std::tr1::shared_ptr<Resource> Resource_sptr;
		typedef std::vector<Resource_sptr> PResources;

		class Resource : public IApplicationObject {

			public:

				/* Dtor */

				virtual ~Resource();

				/* Operators */

				bool operator == (const Resource& resource);

				/* Accessors */

				inline const unsigned int&					getID() const { return m_id; }
				inline const std::string&					getTag() const { return m_tag; }
				inline const bool&							isActive() const { return mb_active; }
				inline const PResources&					getChildren() const { return mv_pChildResources; }
				inline const PComponents&					getComponents() const { return mv_pComponents; }

				/* Modifiers */

				inline void									setID(const int& id) { m_id = id; }
				inline void									setTag(const std::string& tag) { m_tag = tag; }
				inline void									setActive(const bool& active) { mb_active = active; }

				/* Functions */

				void										addResource(Resource_sptr presource);
				void										addComponent(Component_sptr pcomponent);
				template <class _TyComponent>
				std::tr1::shared_ptr<_TyComponent>			getComponent();

				/* Implementations */

				inline virtual const std::string			getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { 
					return "Resource"; 
				}
				virtual void								clean();

			protected:

				/* Members */

				unsigned int								m_id;		// To be set by the Factory only
				std::string									m_tag;
				bool										mb_active;
				PResources									mv_pChildResources;
				PComponents									mv_pComponents;
		};
	}
}

#pragma endregion

#endif /* !__RESOURCE_H__ */

// END OF FILE