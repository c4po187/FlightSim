/**
 * EUMD_Math.h
 *
 * Rici Underwood © 2015
 * c4po187@gmail.com
 */

#ifndef __EUMD_MATH_H__
#define __EUMD_MATH_H__

#pragma once

#pragma region Prerequisites

#include <cmath>
#include <random>

#pragma endregion

#pragma region Declarations

namespace EUMD_FlightSimulator {

	namespace Utilities {

		/**
		 * Uses the Mersenne Twister algorithm to generate and return 
		 * a proper random number of the specified type.
		 * The result is within the range specified by the min & max
		 * parameters.
		 */
		template <typename _Ty>
		static _Ty generateRandom32(const _Ty& min, const _Ty& max) {
			std::random_device seed;
			std::mt19937 engine(seed());
			std::uniform_int_distribution<_Ty> dist(min, max);

			return dist(engine);
		}

		/** 
		 * Returns a rounded long (unsigned int -> 32 bits).
		 * If the decimal part of the number is greater or
		 * equal to .5 - we round up, down otherwise.
		 * If the number is negative, the principle is in reverse.
		 */
		static long round32(double n) {
			double i;
			if (modf(n, &i) >= .5)
				return (n >= 0.0) ? static_cast<long>(ceil(n)) : static_cast<long>(floor(n));
			else
				return (n < 0.0) ? static_cast<long>(ceil(n)) : static_cast<long>(floor(n));
		}

		/**
		 * Does exactly the same as the above function.
		 * Only this function returns a 64 bit integer,
		 * rather than it's 32 bit counterpart.
		 */
		static long long round64(double n) {
			double i;
			if (modf(n, &i) >= .5)
				return (n >= 0.0) ? static_cast<long long>(ceil(n)) : static_cast<long long>(floor(n));
			else
				return (n < 0.0) ? static_cast<long long>(ceil(n)) : static_cast<long long>(floor(n));
		}
	}
}

#pragma endregion

#endif /* !__EUMD_MATH_H__ */

// END OF FILE