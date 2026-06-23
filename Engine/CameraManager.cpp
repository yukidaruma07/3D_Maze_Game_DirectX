#include "CameraManager.h"
#include <map>
#include <string>

namespace CameraManager {
	inline std::map<std::string, Camera*> cameraMap;
	inline Camera* currentCamera_ = nullptr;

	void addCamera(const std::string& name) {
		cameraMap[name] = new Camera(name);
	}

	void setCurentCamera(const std::string& name) {
		if (cameraMap.find(name) != cameraMap.end()) {
			currentCamera_ = cameraMap[name];
		}
	}

	Camera* getCamera(const std::string& name) {
		return cameraMap[name];
	}

	Camera* getCurentCamera() {
		return currentCamera_;
	}
}