#pragma once
#include "Engine/FBX.h"
#include "Engine/BaseObject.h"

class Block :public BaseObject {
private:
	FBX* fbx_;
public:

	Block();
	~Block();

	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

};

