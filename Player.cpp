#include "Player.h"

Player::Player(DirectX::XMFLOAT3 postion)
	: BaseObject("Player") {
	fbx_ = nullptr;
	postion_ = postion;
}

Player::~Player()
{
}

void Player::Init() {
	fbx_ = new FBX("Asset/Player.fbx");
	fbx_->Init();
}

void Player::Update() {
	if (fbx_ != nullptr) {
		fbx_->SetPosition(postion_);
		fbx_->SetRotation(rotation_);
		fbx_->SetScale(scale_);
		fbx_->Update();
	}
}

void Player::Draw() {
	if (fbx_ != nullptr) {
		fbx_->Draw();
	}
}

void Player::Release() {
}
