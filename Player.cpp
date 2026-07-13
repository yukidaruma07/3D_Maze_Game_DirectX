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
#include "Engine/CameraManager.h"

using namespace DirectX;

namespace {
	XMVECTOR forward = { 0.0f, 0.0f, 1.0f };
}

Player::Player(DirectX::XMFLOAT3 postion)
	: BaseObject("Player") {
	fbx_ = nullptr;
	postion_ = postion;
	cameraType_ = 0;
}

Player::~Player()
{
}

void Player::Init() {
	fbx_ = new FBX("Asset/Player.fbx");
	fbx_->Init();

	Camera* camera = CameraManager::getCamera("PlayerCamera");
	camera->setFoucsPostion({});
	camera->setCameraPostion({ 0, 20, -5 });
	camera->SetProjection(DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 1280.0f / 720.0f, 0.1f, 100.0f));
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

	const float PLAYER_SIZE = 0.9f;
	int pLeftX = static_cast<int>(
		std::floor((XMVectorGetX(nextPos) - GROUND_MINX) / BLOCK_SIZE));
	int pLeftZ = static_cast<int>(
		std::floor((XMVectorGetZ(nextPos) - GROUND_MAXZ) / BLOCK_SIZE));
	int pRightX = static_cast<int>(
		std::floor((XMVectorGetX(nextPos) - GROUND_MINX + PLAYER_SIZE) / BLOCK_SIZE));
	int pRightZ = static_cast<int>(
		std::floor((XMVectorGetZ(nextPos) - GROUND_MAXZ + PLAYER_SIZE) / BLOCK_SIZE));

	auto& mapData = ground->GetLocalMapData();

	int mapHeight = static_cast<int>(mapData.size());
	int mapDepth = mapHeight > 0 ? static_cast<int>(mapData[0].size()) : 0;
	int mapWidth = (mapDepth > 0) ? static_cast<int>(mapData[0][0].size()) : 0;

	int pY = mapHeight - 1 - static_cast<int>(std::floor(XMVectorGetY(nextPos) / BLOCK_SIZE));

	bool canMove = true;

	if (mapData[pY][pLeftZ][pLeftX] != 0) canMove = false;
	if (mapData[pY][pLeftZ][pRightX] != 0) canMove = false;
	if (mapData[pY][pRightZ][pLeftX] != 0) canMove = false;
	if (mapData[pY][pRightZ][pRightX] != 0) canMove = false;

	if (canMove) {
		XMStoreFloat3(&postion_, nextPos);
	}

	if (fbx_ != nullptr) {
		fbx_->SetPosition(postion_);
		fbx_->SetRotation(rotation_);
		fbx_->SetScale(scale_);
		fbx_->Update();
	}

	if (InputManager::IsPushKeyDown(DIK_F5)) {
		cameraType_++;
	}

	if (cameraType_ == 0) {
		CameraManager::setCurentCamera("RootCamera");
	}
	else if (cameraType_ == 1) {
		CameraManager::setCurentCamera("PlayerCamera");
		Camera* currentCamera = CameraManager::getCurentCamera();
		currentCamera->setCameraPostion({postion_.x + 0.5f, postion_.y + 5.0f, postion_.z - 1.0f});
		currentCamera->setFoucsPostion({ postion_.x + 0.5f, postion_.y + 2.0f, postion_.z + 5.0f});
	}
	else {
		cameraType_ = 0;
	}
}

void Player::Draw() {

	if (fbx_ != nullptr) {
		fbx_->Draw();
	}
}

void Player::Release() {
}