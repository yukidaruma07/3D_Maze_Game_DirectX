#include "Ground.h"
#include "Block.h"
#include <vector>
#include <cmath>
#include "Engine/LoggerManager.h"
#include <algorithm>

#undef min
#undef max

namespace {

}

Ground::Ground()
	: BaseObject("Ground") {
}

Ground::~Ground()
{
}

void Ground::Init() {
	block_ = new Block();
	block_->Init();

	localMapData_.clear();
	localMapData_ = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
}

void Ground::Update() {
	if (block_ != nullptr) {
		block_->Update();
	}
}

void Ground::Draw() {
	for (int x = 0; x < localMapData_[0].size(); x++) {
		for (int z = 0; z < localMapData_.size(); z++) {
			if (localMapData_[z][x] == 1) {
				block_->SetPosition({GROUND_MINX + BLOCK_SIZE * x, 0, GROUND_MAXZ + BLOCK_SIZE * z});
				block_->Update();
				block_->Draw();
			}
		}
	}
}

void Ground::Release() {
}