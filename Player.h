#pragma once
#include "Engine//BaseObject.h"
#include "Engine//FBX.h"
#include <DirectXMath.h>

class Player : public BaseObject {
private:
	FBX* fbx_;
public:

	Player(DirectX::XMFLOAT3 postion);
	~Player();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

