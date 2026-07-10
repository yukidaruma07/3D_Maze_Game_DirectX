#include "Ground.h"

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
}

void Ground::Update() {
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
}

void Ground::Release() {
}
