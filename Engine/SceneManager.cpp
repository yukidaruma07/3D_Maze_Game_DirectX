#include "SceneManager.h"
#include <vector>
#include "BootScene.h"
#include "ObjectManager.h"

namespace {
	std::vector<BaseScene*> sceneList;
	BaseScene* currentScene = nullptr;
}

namespace SceneManager {

	void InitManager() {
		sceneList.clear();
		auto bootScene = new BootScene();
		sceneList.push_back(bootScene);
		ChangeScene("BootScene");
	}

	BaseScene* GetCurrentScene() {
		return currentScene;
	}

	void ChangeScene(const std::string& name) {
		for (auto& scene : sceneList) {
			if (scene->GetName() == name) {
				currentScene = scene;
				ObjectManager::ClearObject();
				currentScene->Init();
				ObjectManager::InitManager();
				break;
			}
		}
	}

	void DrawScene() {
		if (currentScene == nullptr) return;
		currentScene->Draw();
	}

	void InitScene() {
		if (currentScene == nullptr) return;
		currentScene->Init();
	}

	void UpdateScene() {
		if (currentScene == nullptr) return;
		currentScene->Update();
	}

	void ReleaseScene() {
		if (currentScene == nullptr) return;
		currentScene->Release();
	}

}
