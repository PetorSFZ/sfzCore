// Copyright (c) Peter Hillerström (skipifzero.com, peter@hstroem.se)
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

// Quaternion: Constructors & destructors
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL Quaternion::Quaternion(float x, float y, float z, float w) noexcept
:
	x(x),
	y(y),
	z(z),
	w(w)
{ }

SFZ_CUDA_CALL Quaternion::Quaternion(vec3 v, float w) noexcept
:
	v(v), wAlias(w)
{ }

// Quaternion:Operators (comparison)
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL bool operator== (const Quaternion& lhs, const Quaternion& rhs) noexcept
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

SFZ_CUDA_CALL bool operator!= (const Quaternion& lhs, const Quaternion& rhs) noexcept
{
	return !(lhs == rhs);
}

// Quaternion:Operators (arithmetic & assignment)
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL Quaternion& operator+= (Quaternion& left, const Quaternion& right) noexcept
{
	left.vector += right.vector;
	return left;
}

SFZ_CUDA_CALL Quaternion& operator-= (Quaternion& left, const Quaternion& right) noexcept
{
	left.vector -= right.vector;
	return left;
}

// Quaternion:Operators (arithmetic)
// ------------------------------------------------------------------------------------------------

SFZ_CUDA_CALL Quaternion operator+ (const Quaternion& left, const Quaternion& right) noexcept
{
	Quaternion tmp = left;
	return tmp += right;
}

SFZ_CUDA_CALL Quaternion operator- (const Quaternion& left, const Quaternion& right) noexcept
{
	Quaternion tmp = left;
	return tmp -= right;
}

} // namespace sfz
