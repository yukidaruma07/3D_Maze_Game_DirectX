#pragma once
#include <Windows.h>
#include <string>

namespace LoggerManager {

	inline void InfoDebug(std::string message) {
		message = "[InfoDebug] " + message + (std::string) "\n";
		OutputDebugString(message.c_str());
	}

	inline void ErrorDebug(std::string message) {
		message = "[ErrorDebug] " + message + (std::string)"\n";
		OutputDebugString(message.c_str());
	}
}