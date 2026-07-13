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
        {
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1}
        },
        {
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1}
        },
        {
            {1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,1,0,0,0,0,1},
            {1,0,1,0,1,0,0,0,0,1},
            {1,0,1,0,1,0,1,0,0,1},
            {1,0,1,0,1,0,1,0,0,1},
            {1,0,1,0,1,0,1,0,0,1},
            {1,0,0,0,1,0,1,0,0,1},
            {1,0,0,0,1,0,1,0,0,1},
            {1,0,0,0,0,0,1,0,0,1},
            {1,1,1,1,1,1,1,1,1,1},
        }
    };
	
}

void Ground::Update() {
}

void Ground::Draw() {
	for (int y = 0; y < localMapData_.size(); y++) {
        for (int z = 0; z < localMapData_[y].size(); z++) {
            for (int x = 0; x < localMapData_[y][z].size(); x++) {
                if (localMapData_[y][z][x] == 1) {
                    block_->SetPosition({ GROUND_MINX + x * BLOCK_SIZE, static_cast<float>(y) * BLOCK_SIZE, GROUND_MAXZ + z * BLOCK_SIZE });
                    block_->Update();
                    block_->Draw();
                }
            }
        }
    }
}

void Ground::Release() {
}