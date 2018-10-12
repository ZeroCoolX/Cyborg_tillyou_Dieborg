#include "res_path.h"


std::string getResourcePath(const std::string &subDir)
{
	// We need to choose the path seperator properly based on which
	// platform we're running on, since Windows uses a different
	// seperator than most

#ifndef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif

	// This will hold the base resource path
	// We give it static lifetime so that we'll only need to call 
	// SDL_GetBasePAth once to get the exe path
	static std::string baseRes;
	if (baseRes.empty()) {
		// SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		if (basePath) {
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		// We replace the last bin/ with res/ to get the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}

	// If we want a specific subdir path in the resource dir
	// append if to the base path. This would be something like topic/res/topic1
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}
