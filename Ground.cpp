#include "Ground.h"
#include "Block.h"
#include <vector>

namespace {
	Block* block = nullptr;

	const float minX = 0.0f;
	const float minY = 0.0f;
	const float blockSize = 1.2f;

	std::vector<std::vector<int>> localMapData = {
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};
}

Ground::Ground()
	: BaseObject("Ground") {
	fbx_ = nullptr;
}

Ground::~Ground()
{
}

void Ground::Init() {
	fbx_ = new FBX("Asset/map.fbx");
	fbx_->Init();
	block = new Block();
	block->Init();
}

void Ground::Update() {
	if (block != nullptr) {
		block->Update();
	}

	if (fbx_ != nullptr) {
		fbx_->SetPosition(postion_);
		fbx_->SetRotation(rotation_);
		fbx_->SetScale(scale_);
		fbx_->Update();
	}
}

void Ground::Draw() {
	if (fbx_ != nullptr) {
		fbx_->Draw();
	}

	for (int x = 0; x < localMapData.at(0).size(); x++) {
		for (int y = 0; y < localMapData.size(); y++) {
			if (localMapData.at(y).at(x) == 1) {
				block->SetPosition({minX + blockSize * x, minY + blockSize * y, 0});
				block->Update();
				block->Draw();
			}
		}
	}
}

void Ground::Release() {
}
