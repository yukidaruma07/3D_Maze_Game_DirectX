#include "Block.h"

Block::Block()
	: BaseObject("Block") {
	fbx_ = nullptr;
}

Block::~Block()
{
}

void Block::Init() {
	fbx_ = new FBX("asset/block.fbx");
	fbx_->Init();
}

void Block::Update() {
	if (fbx_ != nullptr) {
		fbx_->SetPosition(postion_);
		fbx_->SetRotation(rotation_);
		fbx_->SetScale(scale_);
		fbx_->Update();
	}
}

void Block::Draw() {
	if (fbx_ != nullptr) {
		fbx_->Draw();
	}
}

void Block::Release() {
}
