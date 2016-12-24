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

#include "sfz/PushWarnings.hpp"
#include "catch.hpp"
#include "sfz/PopWarnings.hpp"

#include "sfz/math/Quaternion.hpp"

using namespace sfz;

TEST_CASE("Quaternion Constructors", "[sfz::Quaternion]")
{
	SECTION("(a,b,c,d) constructor") {
		Quaternion q(1.0f, 2.0f, 3.0f, 4.0f);
		REQUIRE(q.a == 1.0f);
		REQUIRE(q.b == 2.0f);
		REQUIRE(q.c == 3.0f);
		REQUIRE(q.d == 4.0f);
	}
}

TEST_CASE("Quaternion Operators", "[sfz::Quaternion]")
{
	Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f), q2(-1.0f, 3.0f, 1.0f, 6.0f);

	SECTION("Equality operators") {
		REQUIRE(q1 == Quaternion(1.0f, 2.0f, 3.0f, 4.0f));
		REQUIRE(q2 == Quaternion(-1.0f, 3.0f, 1.0f, 6.0f));
		REQUIRE(q1 != q2);
	}
	SECTION("+ operator") {
		Quaternion r1 = q1 + q2;
		REQUIRE(r1 == Quaternion(0.0f, 5.0f, 4.0f, 10.0f));
	}
	SECTION("- operator") {
		Quaternion r1 = q1 - q2;
		REQUIRE(r1 == Quaternion(2.0f, -1.0f, 2.0f, -2.0f));
	}
}
