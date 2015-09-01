/**
 * Pair.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __PAIR_H__
#define __PAIR_H__

#pragma once

#pragma region Prerequisites

#include <ostream>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	template <typename _Ty0, typename _Ty1>
	class Pair final {

		public:

			/* Ctor, Dtor */

			Pair(const _Ty0& rfirst, const _Ty1& rsecond) : m_first(rfirst), m_second(rsecond) { ; }
			Pair() { ; }
			~Pair() { ; }

			/* Accessors */

			inline const _Ty0& getFirst() const { return m_first; }
			inline const _Ty1& getSecond() const { return m_second; }

			/* Modifiers */

			inline void setFirst(const _Ty0& first) { m_first = first; }
			inline void setSecond(const _Ty1& second) { m_second = second; }

			/* Operator Overloads */

			inline bool operator == (const Pair<_Ty0, _Ty1>& other) {
				return (m_first == other.getFirst() && m_second == other.getSecond());
			}

			inline bool operator != (const Pair<_Ty0, _Ty1>& other) {
				return (!((*this) == other));
			}

			inline const Pair<_Ty0, _Ty1>& operator += (const Pair<_Ty0, _Ty1>& other) {
				m_first += other.getFirst();
				m_second += other.getSecond();
				return *this;
			}

			inline const Pair<_Ty0, _Ty1>& operator -= (const Pair<_Ty0, _Ty1>& other) {
				m_first -= other.getFirst();
				m_second -= other.getSecond();
				return *this;
			}

			inline const Pair<_Ty0, _Ty1>& operator *= (const Pair<_Ty0, _Ty1>& other) {
				m_first *= other.getFirst();
				m_second *= other.getSecond();
				return *this;
			}

			inline const Pair<_Ty0, _Ty1>& operator /= (const Pair<_Ty0, _Ty1>& other) {
				m_first /= other.getFirst();
				m_second /= other.getSecond();
				return *this;
			}

			inline const Pair<_Ty0, _Ty1>& operator &= (const Pair<_Ty0, _Ty1>& other) {
				m_first &= other.getFirst();
				m_second &= other.getSecond();
				return *this;
			}

			inline const Pair<_Ty0, _Ty1>& operator |= (const Pair<_Ty0, _Ty1>& other) {
				m_first |= other.getFirst();
				m_second |= other.getSecond();
				return *this;
			}

			inline const Pair<_Ty0, _Ty1>& operator ^= (const Pair<_Ty0, _Ty1>& other) {
				m_first ^= other.getFirst();
				m_second ^= other.getSecond();
				return *this;
			}

			inline friend std::ostream& operator << (std::ostream& os, const Pair<_Ty0, _Ty1>& pair) {
				os << pair.getFirst() << ',' << pair.getSecond();
				return os;
			}

		private:

			/* Members */

			_Ty0 m_first;
			_Ty1 m_second;
	};
}

#pragma endregion

#endif /* !__PAIR_H__ */

// END OF FILE