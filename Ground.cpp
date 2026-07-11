#include "Ground.h"
#include "Block.h"
#include <vector>

namespace {
	Block* block = nullptr;

	const float minX = -5.8f;
	const float minZ = -4.5f;
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
		for (int z = 0; z < localMapData.size(); z++) {
			if (localMapData.at(z).at(x) == 1) {
				block->SetPosition({minX + blockSize * x, 0, minZ + blockSize * z});
				block->Update();
				block->Draw();
			}
		}
	}
}

void Ground::Release() {
}
