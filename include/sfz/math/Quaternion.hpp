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

#pragma once

#include "sfz/math/Vector.hpp"

#include "sfz/CudaCompatibility.hpp"

namespace sfz {

// Quaternion struct
// ------------------------------------------------------------------------------------------------

struct alignas(16) Quaternion final {

	// Members
	// --------------------------------------------------------------------------------------------

	/// i*x + j*y + k*z + w
	/// or
	/// [v, w], v = [x, y, z] in the imaginary space, w is scalar real part
	/// where
	/// i� = j� = k� = -1
	/// j*k = -k*j = i
	/// k*i = -i*k = j
	/// i*j = -j*i = k
	union {
		struct { float x, y, z, w; };
		struct { vec3 v; };
		vec4 vector;
	};

	// Constructors & destructors
	// --------------------------------------------------------------------------------------------

	Quaternion() noexcept = default;
	Quaternion(const Quaternion&) noexcept = default;
	Quaternion& operator= (const Quaternion&) noexcept = default;
	~Quaternion() noexcept = default;

	SFZ_CUDA_CALL Quaternion(float x, float y, float z, float w) noexcept;
	SFZ_CUDA_CALL Quaternion(vec3 v, float w) noexcept;

	/// Creates an identity quaternion representing a non-rotation, i.e. [0, 0, 0, 1]
	static SFZ_CUDA_CALL Quaternion identity() noexcept;
};

static_assert(sizeof(Quaternion) == sizeof(float) * 4, "Quaternion is padded");

// Quaternion functions
// ------------------------------------------------------------------------------------------------

/// Calculates the length (norm) of the Quaternion. A unit Quaternion has length 1. If the
/// Quaternions are used for rotations they should always be unit.
SFZ_CUDA_CALL float length(const Quaternion& q) noexcept;

/// Calculates the conjugate quaternion, i.e. [-v, w]. If the quaternion is unit length this is
/// the same as the inverse.
SFZ_CUDA_CALL Quaternion conjugate(const Quaternion& q) noexcept;

/// Calculates the inverse for any Quaternion, i.e. (1 / length(q)�) * conjugate(q). For unit
/// Quaternions (which should be the most common case) the conjugate() function should be used
/// instead as it is way faster.
SFZ_CUDA_CALL Quaternion inverse(const Quaternion& q) noexcept;

// Operators (comparison)
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL bool operator== (const Quaternion& lhs, const Quaternion& rhs) noexcept;
SFZ_CUDA_CALL bool operator!= (const Quaternion& lhs, const Quaternion& rhs) noexcept;

// Operators (arithmetic & assignment)
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL Quaternion& operator+= (Quaternion& left, const Quaternion& right) noexcept;
SFZ_CUDA_CALL Quaternion& operator-= (Quaternion& left, const Quaternion& right) noexcept;
SFZ_CUDA_CALL Quaternion& operator*= (Quaternion& left, const Quaternion& right) noexcept;
SFZ_CUDA_CALL Quaternion& operator*= (Quaternion& q, float scalar) noexcept;

// Operators (arithmetic)
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL Quaternion operator+ (const Quaternion& left, const Quaternion& right) noexcept;
SFZ_CUDA_CALL Quaternion operator- (const Quaternion& left, const Quaternion& right) noexcept;
SFZ_CUDA_CALL Quaternion operator* (const Quaternion& left, const Quaternion& right) noexcept;
SFZ_CUDA_CALL Quaternion operator* (const Quaternion& q, float scalar) noexcept;
SFZ_CUDA_CALL Quaternion operator* (float scalar, const Quaternion& q) noexcept;

} // namespace sfz

#include "sfz/math/Quaternion.inl"
