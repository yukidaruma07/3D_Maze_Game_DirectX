#include "Player.h"
#include "Engine/ObjectManager.h"
#include "Ground.h"
#include "Engine/LoggerManager.h"
#include "Engine/InputManager.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace DirectX;

namespace {
	XMVECTOR forward = { 0.0f, 0.0f, 1.0f };
}

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

	const float SPPED = 0.1f;
	XMVECTOR moveVec = {};
	XMVECTOR nextPos = XMLoadFloat3(&postion_);
	XMVECTOR pVec = XMLoadFloat3(&postion_);
	XMVECTOR mat = XMVector3TransformCoord(forward, XMMatrixRotationY(rotation_.y));
	if (InputManager::IsPushKey(DIK_W)) {
		//nextPos = pVec + mat * SPPED;
		nextPos = pVec + XMVectorSet(0, 0, SPPED, 1.0f);
	}
	if (InputManager::IsPushKey(DIK_S)) {
		//nextPos = pVec - mat * SPPED;
		nextPos = pVec + XMVectorSet(0, 0, -SPPED, 1.0f);
	}
	if (InputManager::IsPushKey(DIK_A)) {
		//rotation_.y -= XMConvertToRadians(1.0f);
		nextPos = pVec + XMVectorSet(-SPPED, 0, 0.0, 1.0f);
	}
	if (InputManager::IsPushKey(DIK_D)) {
		//rotation_.y += XMConvertToRadians(1.0f);
		nextPos = pVec + XMVectorSet(SPPED, 0, 0, 1.0f);
	}

	Ground* ground = ObjectManager::GetDrawObject<Ground>();

	int pLeftX = static_cast<int>(
		std::floor((XMVectorGetX(nextPos) - GROUND_MINX) / BLOCK_SIZE));
	int pLeftZ = static_cast<int>(
		std::floor((XMVectorGetZ(nextPos) - GROUND_MAXZ) / BLOCK_SIZE));
	int pRightX = static_cast<int>(
		std::floor((XMVectorGetX(nextPos) - GROUND_MINX + BLOCK_SIZE) / BLOCK_SIZE));
	int pRightZ = static_cast<int>(
		std::floor((XMVectorGetZ(nextPos) - GROUND_MAXZ + BLOCK_SIZE) / BLOCK_SIZE));


	auto& mapData = ground->GetLocalMapData();

	LoggerManager::InfoDebug(
		"x=" + std::to_string(postion_.x) + "," +
		"x=" + std::to_string(XMVectorGetX(nextPos)) + "[" + std::to_string((int)pLeftX) + "]" +
		"x=" + std::to_string(postion_.z) + "," +
		"z=" + std::to_string(XMVectorGetZ(nextPos)) + "[" + std::to_string((int)pLeftZ) + "]" + "="
		" map=" + std::to_string(mapData[pLeftZ][pLeftX]));

	if (mapData[pLeftZ][pLeftX] == 0 && mapData[pRightZ][pRightX] == 0) {
		XMStoreFloat3(&postion_, nextPos);
	}


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
