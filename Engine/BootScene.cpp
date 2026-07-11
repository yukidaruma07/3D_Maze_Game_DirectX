#include "BootScene.h"
#include "ObjectManager.h"
#include "Triangle.h"
#include "Image.h"
#include "LoggerManager.h"
#include "FBX.h"
#include "Box.h"
#include "SceneManager.h"
#include "../Ground.h"
#include "../Player.h"
#include "CSVRender.h"
#include "../Block.h"

BootScene::BootScene()
	: BaseScene("BootScene") {
	csv_ = nullptr;
}

BootScene::~BootScene() {
}

void BootScene::Init() {
	DirectX::XMFLOAT3 vertexPos[3] = {
		{0.0f, 0.0f, 0.0f},
		{0.0f, 128.0f, 0.0f},
		{64.0f, 0.0f, 0.0f}
	};
	Color color[3] = {
		Color::GetRed(),
		Color::GetGreen(),
		Color::GetBlue()
	};
	//ObjectManager::AddObject(new Triangle(color, vertexPos));
	//ObjectManager::AddObject(new Image("test.PNG", 64, 64));
	//ObjectManager::AddObject(new FBX("Oden.fbx"));
	//ObjectManager::AddObject(new Box(Color::GetRed(), 64, 64));
	ObjectManager::AddObject(new Ground());
	ObjectManager::AddObject(new Player({0, 0, 0}));
	//ObjectManager::AddObject(new Block());

	csv_ = (new CSVRender("asset/map.csv"));
	csv_->Init();
}

void BootScene::Update() {
	//SceneManager::ChangeScene("TitleScene");
}

void BootScene::Draw() {
}

void BootScene::Release() {
}
