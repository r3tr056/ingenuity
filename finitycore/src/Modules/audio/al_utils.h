#pragma once

#include <cstring>
#include <AL/al.h>
#include <AL/alc.h>

namespace finity {
	namespace audio {

#define al_check(expr)
		do 
		{
			expr;
			al_check_error(__FILE__, __LINE__, #expr);
		} while (false)

		void al_check_error(const char* file, unsigned int line, const char* expr) {
			ALenum err = alGetError();

			if (err != AL_NO_ERROR) {
				std::string file_string = file;
				std::string error = "Unknown Error";
				std::string desc = "No description";

				// Decode the error code
				switch (err)
				{
				case AL_INVALID_NAME:
				{
					error = "AL_INVALID_NAME";
					desc = "A bad name (ID) has been specified.";
					break;
				}

				case AL_INVALID_ENUM:
				{
					error = "AL_INVALID_ENUM";
					desc = "An unacceptable value has been specified for an enumerated argument.";
					break;
				}

				case AL_INVALID_VALUE:
				{
					error = "AL_INVALID_VALUE";
					desc = "A numeric argument"
				}
				default:
					break;
				}
			}
		}
	}
}