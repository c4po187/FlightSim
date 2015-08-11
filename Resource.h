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

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Resources {

		class Resource;

		typedef std::tr1::shared_ptr<Resource> Resource_sptr;
		typedef std::vector<Resource_sptr> PResources;

		class Resource : public IApplicationObject {

			protected:

				/* Members */

				unsigned int						m_id;
				std::string							m_tag;

			public:

				/* Accessors */

				inline const unsigned int&			getID() const { return m_id; }
				inline const std::string&			getTag() const { return m_tag; }

				/* Modifiers */

				inline void							setID(const int& id) { m_id = id; }
				inline void							setTag(const std::string& tag) { m_tag = tag; }

				/* Implementations */

				inline virtual const std::string	getType(TypeInfo tInfo_ex = DEFAULT_TYPE_INFO) { 
					return "Resource"; 
				}
		};
	}
}

#pragma endregion

#endif /* !__RESOURCE_H__ */

// END OF FILE