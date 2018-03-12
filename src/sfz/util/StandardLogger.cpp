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

#include "sfz/util/StandardLogger.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstring>

namespace sfz {

// Static functions
// ------------------------------------------------------------------------------------------------

constexpr const char* LOG_LEVEL_STRINGS[] = {
	"INFO_NOISY",
	"INFO",
	"WARNING",
	"ERROR"
};

static const char* toString(LogLevel level) noexcept
{
	return LOG_LEVEL_STRINGS[uint32_t(level)];
}

// StandardLogger implementation
// ------------------------------------------------------------------------------------------------

class StandardLogger final : public LoggingInterface {
public:
	void log(const char* file, int line, LogLevel level, const char* tag,
		const char* format, ...) override final
	{
		// Strip path from file
#ifdef _WIN32
		const char* strippedFile = std::strrchr(file, '\\') + 1;
#else
		const char* strippedFile = std::strrchr(file, '/') + 1;
#endif
		if (strippedFile == nullptr) strippedFile = file;

		// Print log level, tag, file and line number.
		printf("[%s] -- [%s] -- [%s:%i]: ", toString(level), tag, strippedFile, line);

		// Print message
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);

		// Print newline
		printf("\n");

		// Flush stdout
		fflush(stdout);
	}
};

// StandardLogger retrieval function
// ------------------------------------------------------------------------------------------------

LoggingInterface* getStandardLogger() noexcept
{
	static StandardLogger logger;
	return &logger;
}

} // namespace sfz