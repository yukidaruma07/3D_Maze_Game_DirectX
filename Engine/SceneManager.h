#pragma once
#include "BaseScene.h"

namespace SceneManager {

	void InitManager();
	BaseScene* GetCurrentScene();
	void ChangeScene(const std::string& name);
	void DrawScene();
	void InitScene();
	void UpdateScene();
	void ReleaseScene();

}