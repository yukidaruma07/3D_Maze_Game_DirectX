#pragma once
#include "Engine//BaseObject.h"
#include "Engine//FBX.h"
#include "Block.h"
#include <DirectXMath.h>

namespace {
	const float BLOCK_SIZE = 1.0f;
	const float GROUND_MINX = 0.0f;
	const float GROUND_MAXZ = 0.0f;
}

class Ground : public BaseObject {
private:
	Block* block_ = nullptr;
	std::vector<std::vector<std::vector<int>>> localMapData_;
public:
	Ground();
	~Ground();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	std::vector<std::vector<std::vector<int>>>& GetLocalMapData() { return localMapData_; };


};

