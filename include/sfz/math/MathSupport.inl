// Copyright (c) Peter Hillerstr�m (skipifzero.com, peter@hstroem.se)
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.

namespace sfz {

// Approximate equal functions
// ------------------------------------------------------------------------------------------------

template<typename T, typename EpsT>
SFZ_CUDA_CALL bool approxEqual(T lhs, T rhs, EpsT epsilon) noexcept
{
	return (lhs <= (rhs + epsilon)) && (lhs >= (rhs - epsilon));
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL bool approxEqual(const Vector<T,N>& lhs, const Vector<T,N>& rhs, T epsilon) noexcept
{
	for (uint32_t i = 0; i < N; i++) {
		if (!approxEqual<T,T>(lhs[i], rhs[i], epsilon)) return false;
	}
	return true;
}

template<typename T, uint32_t M, uint32_t N>
SFZ_CUDA_CALL bool approxEqual(const Matrix<T,M,N>& lhs, const Matrix<T,M,N>& rhs, T epsilon) noexcept
{
	for (uint32_t i = 0; i < M; i++) {
		for (uint32_t j = 0; j < N; j++) {
			if (!approxEqual<T,T>(lhs.at(i, j), rhs.at(i, j), epsilon)) return false;
		}
	}
	return true;
}

// abs()
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL float abs(float val) noexcept
{
#ifdef SFZ_CUDA_DEVICE_CODE
	return fabsf(val);
#else
	return std::abs(val);
#endif
}

SFZ_CUDA_CALL int32_t abs(int32_t val) noexcept
{
#ifdef SFZ_CUDA_DEVICE_CODE
	return abs(val);
#else
	return std::abs(val);
#endif
}

SFZ_CUDA_CALL vec2 abs(vec2 val) noexcept
{
	val.x = sfz::abs(val.x);
	val.y = sfz::abs(val.y);
	return val;
}

SFZ_CUDA_CALL vec3 abs(vec3 val) noexcept
{
	val.x = sfz::abs(val.x);
	val.y = sfz::abs(val.y);
	val.z = sfz::abs(val.z);
	return val;
}

SFZ_CUDA_CALL vec4 abs(vec4 val) noexcept
{
#ifdef SFZ_CUDA_DEVICE_CODE
	val.x = sfz::abs(val.x);
	val.y = sfz::abs(val.y);
	val.z = sfz::abs(val.z);
	val.w = sfz::abs(val.w);
	return val;
#else
	// Floating points has a dedicated sign bit, simply mask it out
	const __m128 SIGN_BIT_MASK = _mm_set1_ps(-0.0f);
	__m128 tmpReg = _mm_load_ps(val.elementsPtr());
	tmpReg = _mm_andnot_ps(SIGN_BIT_MASK, tmpReg); // (~(-0.0f)) & value
	_mm_store_ps(val.elementsPtr(), tmpReg);
	return val;
#endif
}

SFZ_CUDA_CALL vec2i abs(vec2i val) noexcept
{
	val.x = sfz::abs(val.x);
	val.y = sfz::abs(val.y);
	return val;
}

SFZ_CUDA_CALL vec3i abs(vec3i val) noexcept
{
	val.x = sfz::abs(val.x);
	val.y = sfz::abs(val.y);
	val.z = sfz::abs(val.z);
	return val;
}

SFZ_CUDA_CALL vec4i abs(vec4i val) noexcept
{
#ifdef SFZ_CUDA_DEVICE_CODE
	val.x = sfz::abs(val.x);
	val.y = sfz::abs(val.y);
	val.z = sfz::abs(val.z);
	val.w = sfz::abs(val.w);
	return val;
#else
	__m128i tmpReg = _mm_load_si128((const __m128i*)val.elementsPtr());
	tmpReg = _mm_abs_epi32(tmpReg);
	_mm_store_si128((__m128i*)val.elementsPtr(), tmpReg);
	return val;
#endif
}

// sgn()
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL float sgn(float val) noexcept
{
	// Union for accessing raw bits of float
	union FloatBitsUnion {
		float value;
		uint32_t bits;
	};
	static_assert(sizeof(FloatBitsUnion) == sizeof(float), "Ensure no padding");
	static_assert(sizeof(FloatBitsUnion) == sizeof(uint32_t), "Ensure no padding");

	// Constants
	const FloatBitsUnion SIGN_BIT_MASK = {-0.0f};
	const FloatBitsUnion FLOAT_ONE = {1.0f};

	// Use bitwise magic to get the sign
	FloatBitsUnion tmp;
	tmp.value = val;

	tmp.bits &= SIGN_BIT_MASK.bits; // Mask out sign bit
	tmp.bits |= FLOAT_ONE.bits; // Add the sign bit to "1.0f"

	return tmp.value;
}

SFZ_CUDA_CALL int32_t sgn(int32_t val) noexcept
{
	return (0 < val) - (val < 0);
}

SFZ_CUDA_CALL vec2 sgn(vec2 val) noexcept
{
	val.x = sfz::sgn(val.x);
	val.y = sfz::sgn(val.y);
	return val;
}

SFZ_CUDA_CALL vec3 sgn(vec3 val) noexcept
{
	val.x = sfz::sgn(val.x);
	val.y = sfz::sgn(val.y);
	val.z = sfz::sgn(val.z);
	return val;
}

SFZ_CUDA_CALL vec4 sgn(vec4 val) noexcept
{
#ifdef SFZ_CUDA_DEVICE_CODE
	val.x = sfz::sgn(val.x);
	val.y = sfz::sgn(val.y);
	val.z = sfz::sgn(val.z);
	val.w = sfz::sgn(val.w);
	return val;
#else
	// Mask out sign bit using bitwise magic and return -1.0f or 1.0f for each element
	const __m128 SIGN_BIT_MASK = _mm_set1_ps(-0.0f);
	const __m128 FLOAT_ONE = _mm_set1_ps(1.0f);
	__m128 tmpReg = _mm_load_ps(val.elementsPtr());
	tmpReg = _mm_or_ps(FLOAT_ONE, _mm_and_ps(SIGN_BIT_MASK, tmpReg));
	_mm_store_ps(val.elementsPtr(), tmpReg);
	return val;
#endif
}

SFZ_CUDA_CALL vec2i sgn(vec2i val) noexcept
{
	val.x = sfz::sgn(val.x);
	val.y = sfz::sgn(val.y);
	return val;
}

SFZ_CUDA_CALL vec3i sgn(vec3i val) noexcept
{
	val.x = sfz::sgn(val.x);
	val.y = sfz::sgn(val.y);
	val.z = sfz::sgn(val.z);
	return val;
}

SFZ_CUDA_CALL vec4i sgn(vec4i val) noexcept
{
	val.x = sfz::sgn(val.x);
	val.y = sfz::sgn(val.y);
	val.z = sfz::sgn(val.z);
	val.w = sfz::sgn(val.w);
	return val;

	// TODO: Implement SSE variant
}

// old
// ------------------------------------------------------------------------------------------------

template<typename ArgT, typename FloatT>
SFZ_CUDA_CALL ArgT lerp(ArgT v0, ArgT v1, FloatT t) noexcept
{
	return (FloatT(1)-t)*v0 + t*v1;
}

template<typename T>
SFZ_CUDA_CALL T clamp(T value, T minValue, T maxValue)
{
	using std::min;
	using std::max;
	return max(minValue, min(value, maxValue));
}

} // namespace sfz