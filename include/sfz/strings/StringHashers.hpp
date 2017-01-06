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

#pragma once

#include <cstdint>
#include <functional> // std::hash

#include "sfz/strings/DynString.hpp"
#include "sfz/strings/StackString.hpp"

namespace sfz {

using std::size_t;
using std::uint64_t;

static_assert(sizeof(uint64_t) == sizeof(size_t), "size_t is not 64 bit");

// Common hashing function for all sfz strings (and raw C strings)
// ------------------------------------------------------------------------------------------------

/// Hashes a null-terminated C string. The exact hashing function used is currently FNV-1A, this
/// might however change in the future.
inline size_t hash(const char* str) noexcept;

// DynString hash function
// ------------------------------------------------------------------------------------------------

template<typename Allocator = sfz::StandardAllocator>
size_t hash(const DynStringTempl<Allocator>& str) noexcept;

// StackString hash function
// ------------------------------------------------------------------------------------------------

template<size_t N>
size_t hash(const StackStringTempl<N>& str) noexcept;

// Raw C string hash struct (not std::hash specialization, but same interface)
// ------------------------------------------------------------------------------------------------

struct RawStringHash {
	inline size_t operator() (const char* str) const noexcept;
};

} // namespace sfz

namespace std {

// DynString hash struct
// ------------------------------------------------------------------------------------------------

template<typename Allocator>
struct hash<sfz::DynStringTempl<Allocator>> {
	size_t operator() (const sfz::DynStringTempl<Allocator>& str) const noexcept;
};

// StackString hash struct
// ------------------------------------------------------------------------------------------------

template<size_t N>
struct hash<sfz::StackStringTempl<N>> {
	size_t operator() (const sfz::StackStringTempl<N>& str) const noexcept;
};

} // namespace std

#include "sfz/strings/StringHashers.inl"
