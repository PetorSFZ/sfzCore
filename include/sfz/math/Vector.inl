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

// Vector struct declaration: Vector<T,N>
// ------------------------------------------------------------------------------------------------

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N>::Vector(const T* arrayPtr) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		elements[i] = arrayPtr[i];
	}
}

template<typename T, uint32_t N>
template<typename T2>
SFZ_CUDA_CALL Vector<T,N>::Vector(const Vector<T2,N>& other) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		elements[i] = static_cast<T>(other[i]);
	}
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL T& Vector<T,N>::operator[] (uint32_t index) noexcept
{
	sfz_assert_debug(index < N);
	return elements[index];
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL T Vector<T,N>::operator[] (uint32_t index) const noexcept
{
	sfz_assert_debug(index < N);
	return elements[index];
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL T* Vector<T,N>::elementsPtr() noexcept
{
	return elements;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL const T* Vector<T,N>::elementsPtr() const noexcept
{
	return elements;
}

// Vector struct declaration: Vector<T,2>
// ------------------------------------------------------------------------------------------------

template<typename T>
SFZ_CUDA_CALL Vector<T,2>::Vector(const T* arrayPtr) noexcept
:
	x(arrayPtr[0]),
	y(arrayPtr[1])
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,2>::Vector(T value) noexcept
:
	x(value),
	y(value)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,2>::Vector(T x, T y) noexcept
:
	x(x),
	y(y)
{ }

template<typename T>
template<typename T2>
SFZ_CUDA_CALL Vector<T,2>::Vector(const Vector<T2,2>& other) noexcept
:
	x(static_cast<T>(other.x)),
	y(static_cast<T>(other.y))
{ }

template<typename T>
SFZ_CUDA_CALL T& Vector<T,2>::operator[] (uint32_t index) noexcept
{
	sfz_assert_debug(index < 2);
	return elementsPtr()[index];
}

template<typename T>
SFZ_CUDA_CALL T Vector<T,2>::operator[] (uint32_t index) const noexcept
{
	sfz_assert_debug(index < 2);
	return elementsPtr()[index];
}

template<typename T>
SFZ_CUDA_CALL T* Vector<T,2>::elementsPtr() noexcept
{
	return &x;
}

template<typename T>
SFZ_CUDA_CALL const T* Vector<T,2>::elementsPtr() const noexcept
{
	return &x;
}

// Vector struct declaration: Vector<T,3>
// ------------------------------------------------------------------------------------------------

template<typename T>
SFZ_CUDA_CALL Vector<T,3>::Vector(const T* arrayPtr) noexcept
:
	x(arrayPtr[0]),
	y(arrayPtr[1]),
	z(arrayPtr[2])
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,3>::Vector(T value) noexcept
:
	x(value),
	y(value),
	z(value)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,3>::Vector(T x, T y, T z) noexcept
:
	x(x),
	y(y),
	z(z)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,3>::Vector(Vector<T,2> xy, T z) noexcept
:
	x(xy.x),
	y(xy.y),
	z(z)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,3>::Vector(T x, Vector<T,2> yz) noexcept
:
	x(x),
	y(yz.x),
	z(yz.y)
{ }

template<typename T>
template<typename T2>
SFZ_CUDA_CALL Vector<T,3>::Vector(const Vector<T2,3>& other) noexcept
:
	x(static_cast<T>(other.x)),
	y(static_cast<T>(other.y)),
	z(static_cast<T>(other.z))
{ }

template<typename T>
SFZ_CUDA_CALL T& Vector<T,3>::operator[] (uint32_t index) noexcept
{
	sfz_assert_debug(index < 3);
	return elementsPtr()[index];
}

template<typename T>
SFZ_CUDA_CALL T Vector<T,3>::operator[] (uint32_t index) const noexcept
{
	sfz_assert_debug(index < 3);
	return elementsPtr()[index];
}

template<typename T>
SFZ_CUDA_CALL T* Vector<T,3>::elementsPtr() noexcept
{
	return &x;
}

template<typename T>
SFZ_CUDA_CALL const T* Vector<T,3>::elementsPtr() const noexcept
{
	return &x;
}

// Vector struct declaration: Vector<T,4>
// ------------------------------------------------------------------------------------------------

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(const T* arrayPtr) noexcept
:
	x(arrayPtr[0]),
	y(arrayPtr[1]),
	z(arrayPtr[2]),
	w(arrayPtr[3])
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(T value) noexcept
:
	x(value),
	y(value),
	z(value),
	w(value)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(T x, T y, T z, T w) noexcept
:
	x(x),
	y(y),
	z(z),
	w(w)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(Vector<T,3> xyz, T w) noexcept
:
	x(xyz.x),
	y(xyz.y),
	z(xyz.z),
	w(w)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(T x, Vector<T,3> yzw) noexcept
:
	x(x),
	y(yzw.x),
	z(yzw.y),
	w(yzw.z)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(Vector<T,2> xy, Vector<T,2> zw) noexcept
:
	x(xy.x),
	y(xy.y),
	z(zw.x),
	w(zw.y)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(Vector<T,2> xy, T z, T w) noexcept
:
	x(xy.x),
	y(xy.y),
	z(z),
	w(w)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(T x, Vector<T,2> yz, T w) noexcept
:
	x(x),
	y(yz.x),
	z(yz.y),
	w(w)
{ }

template<typename T>
SFZ_CUDA_CALL Vector<T,4>::Vector(T x, T y, Vector<T,2> zw) noexcept
:
	x(x),
	y(y),
	z(zw.x),
	w(zw.y)
{ }

template<typename T>
template<typename T2>
SFZ_CUDA_CALL Vector<T,4>::Vector(const Vector<T2,4>& other) noexcept
:
	x(static_cast<T>(other.x)),
	y(static_cast<T>(other.y)),
	z(static_cast<T>(other.z)),
	w(static_cast<T>(other.w))
{ }

template<typename T>
SFZ_CUDA_CALL T& Vector<T,4>::operator[] (uint32_t index) noexcept
{
	sfz_assert_debug(index < 4);
	return elementsPtr()[index];
}

template<typename T>
SFZ_CUDA_CALL T Vector<T,4>::operator[] (uint32_t index) const noexcept
{
	sfz_assert_debug(index < 4);
	return elementsPtr()[index];
}

template<typename T>
SFZ_CUDA_CALL T* Vector<T,4>::elementsPtr() noexcept
{
	return &x;
}

template<typename T>
SFZ_CUDA_CALL const T* Vector<T,4>::elementsPtr() const noexcept
{
	return &x;
}

// Vector functions
// ------------------------------------------------------------------------------------------------

template<typename T, uint32_t N>
SFZ_CUDA_CALL T length(const Vector<T,N>& vector) noexcept
{
	using std::sqrt;
	return T(sqrt(dot(vector, vector)));
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL T squaredLength(const Vector<T,N>& vector) noexcept
{
	return dot(vector, vector);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> normalize(const Vector<T,N>& vector) noexcept
{
	T lengthTmp = length(vector);
	sfz_assert_debug(lengthTmp != 0);
	return vector / lengthTmp;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> safeNormalize(const Vector<T,N>& vector) noexcept
{
	T lengthTmp = length(vector);
	if (lengthTmp == T(0)) return Vector<T,N>(T(0));
	return vector / lengthTmp;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL T dot(const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	T product = T(0);
	for (uint32_t i = 0; i < N; ++i) {
		product += (left.elements[i]*right.elements[i]);
	}
	return product;
}

template<typename T>
SFZ_CUDA_CALL T dot(const Vector<T,2>& left, const Vector<T,2>& right) noexcept
{
	return left.x * right.x
	     + left.y * right.y;
}

template<typename T>
SFZ_CUDA_CALL T dot(const Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	return left.x * right.x
	     + left.y * right.y
	     + left.z * right.z;
}

template<typename T>
SFZ_CUDA_CALL T dot(const Vector<T,4>& left, const Vector<T,4>& right) noexcept
{
	return left.x * right.x
	     + left.y * right.y
	     + left.z * right.z
	     + left.w * right.w;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,3> cross(const Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	return sfz::Vector<T,3>(left.y*right.z - left.z*right.y,
	                        left.z*right.x - left.x*right.z,
	                        left.x*right.y - left.y*right.x);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL T elementSum(const Vector<T,N>& vector) noexcept
{
	T result = T(0);
	for (uint32_t i = 0; i < N; ++i) {
		result += vector[i];
	}
	return result;
}

template<typename T>
SFZ_CUDA_CALL T elementSum(const Vector<T,2>& vector) noexcept
{
	return vector.x + vector.y;
}

template<typename T>
SFZ_CUDA_CALL T elementSum(const Vector<T,3>& vector) noexcept
{
	return vector.x + vector.y + vector.z;
}

template<typename T>
SFZ_CUDA_CALL T elementSum(const Vector<T,4>& vector) noexcept
{
	return vector.x + vector.y + vector.z + vector.w;
}

// Operators (arithmetic & assignment)
// ------------------------------------------------------------------------------------------------

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N>& operator+= (Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		left.elements[i] += right.elements[i];
	}
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,2>& operator+= (Vector<T,2>& left, const Vector<T,2>& right) noexcept
{
	left.x += right.x;
	left.y += right.y;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,3>& operator+= (Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,4>& operator+= (Vector<T,4>& left, const Vector<T,4>& right) noexcept
{
	left.x += right.x;
	left.y += right.y;
	left.z += right.z;
	left.w += right.w;
	return left;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N>& operator-= (Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		left.elements[i] -= right.elements[i];
	}
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,2>& operator-= (Vector<T,2>& left, const Vector<T,2>& right) noexcept
{
	left.x -= right.x;
	left.y -= right.y;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,3>& operator-= (Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,4>& operator-= (Vector<T,4>& left, const Vector<T,4>& right) noexcept
{
	left.x -= right.x;
	left.y -= right.y;
	left.z -= right.z;
	left.w -= right.w;
	return left;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N>& operator*= (Vector<T,N>& left, T right) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		left.elements[i] *= right;
	}
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,2>& operator*= (Vector<T,2>& left, T right) noexcept
{
	left.x *= right;
	left.y *= right;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,3>& operator*= (Vector<T,3>& left, T right) noexcept
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,4>& operator*= (Vector<T,4>& left, T right) noexcept
{
	left.x *= right;
	left.y *= right;
	left.z *= right;
	left.w *= right;
	return left;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N>& operator*= (Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		left.elements[i] *= right.elements[i];
	}
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,2>& operator*= (Vector<T,2>& left, const Vector<T,2>& right) noexcept
{
	left.x *= right.x;
	left.y *= right.y;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,3>& operator*= (Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,4>& operator*= (Vector<T,4>& left, const Vector<T,4>& right) noexcept
{
	left.x *= right.x;
	left.y *= right.y;
	left.z *= right.z;
	left.w *= right.w;
	return left;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N>& operator/= (Vector<T,N>& left, T right) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		left.elements[i] /= right;
	}
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,2>& operator/= (Vector<T,2>& left, T right) noexcept
{
	left.x /= right;
	left.y /= right;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,3>& operator/= (Vector<T,3>& left, T right) noexcept
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,4>& operator/= (Vector<T,4>& left, T right) noexcept
{
	left.x /= right;
	left.y /= right;
	left.z /= right;
	left.w /= right;
	return left;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N>& operator/= (Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		left.elements[i] /= right.elements[i];
	}
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,2>& operator/= (Vector<T,2>& left, const Vector<T,2>& right) noexcept
{
	left.x /= right.x;
	left.y /= right.y;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,3>& operator/= (Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	return left;
}

template<typename T>
SFZ_CUDA_CALL Vector<T,4>& operator/= (Vector<T,4>& left, const Vector<T,4>& right) noexcept
{
	left.x /= right.x;
	left.y /= right.y;
	left.z /= right.z;
	left.w /= right.w;
	return left;
}

// Operators (arithmetic)
// ------------------------------------------------------------------------------------------------

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator+ (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp += right);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator- (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp -= right);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator- (const Vector<T,N>& vector) noexcept
{
	Vector<T,N> temp = vector;
	return (temp *= T(-1));
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator* (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T, N> temp = left;
	return (temp *= right);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator* (const Vector<T,N>& left, T right) noexcept
{
	Vector<T,N> temp = left;
	return (temp *= right);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator* (T left, const Vector<T,N>& right) noexcept
{
	return right * left;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator/ (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> temp = left;
	return (temp /= right);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator/ (const Vector<T,N>& left, T right) noexcept
{
	Vector<T,N> temp = left;
	return (temp /= right);
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL Vector<T,N> operator/ (T left, const Vector<T,N>& right) noexcept
{
	Vector<T,N> temp(left);
	return (temp /= right);
}

// Operators (comparison)
// ------------------------------------------------------------------------------------------------

template<typename T, uint32_t N>
SFZ_CUDA_CALL bool operator== (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	for (uint32_t i = 0; i < N; ++i) {
		if (left.elements[i] != right.elements[i]) return false;
	}
	return true;
}

template<typename T>
SFZ_CUDA_CALL bool operator== (const Vector<T,2>& left, const Vector<T,2>& right) noexcept
{
	return left.x == right.x
	    && left.y == right.y;
}

template<typename T>
SFZ_CUDA_CALL bool operator== (const Vector<T,3>& left, const Vector<T,3>& right) noexcept
{
	return left.x == right.x
	    && left.y == right.y
	    && left.z == right.z;
}

template<typename T>
SFZ_CUDA_CALL bool operator== (const Vector<T,4>& left, const Vector<T,4>& right) noexcept
{
	return left.x == right.x
	    && left.y == right.y
	    && left.z == right.z
	    && left.w == right.w;
}

template<typename T, uint32_t N>
SFZ_CUDA_CALL bool operator!= (const Vector<T,N>& left, const Vector<T,N>& right) noexcept
{
	return !(left == right);
}

} // namespace sfz
