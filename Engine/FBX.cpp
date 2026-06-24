#include "FBX.h"
#include "fbxsdk.h"
#include "DirectX3DManager.h"
#include "BootScene.h"
#include "Texture.h"
#include <vector>
#include "../ImGUI/imgui.h"
#include "CameraManager.h"
#include "../GameEngine.hpp"
using namespace DirectX3DManager;

using namespace fbxsdk;
using namespace DirectX;

FBX::FBX(const std::string fName)
	: BaseObject("FBX") {
	this->path_ = fName;
	isShowTexture_ = true;
	indexCount_ = -1;
	materialCount_ = -1;
	polygonCount_ = -1;
	vertexCount_ = -1;
	materials_ = nullptr;
	pConstantBuffer_ = nullptr;
	pIndexBuffer_ = nullptr;
	pVertexBuffer_ = nullptr;
	vertices_ = nullptr;
}

FBX::~FBX() {
}

void FBX::Init() {
	fbxManager_ = FbxManager::Create();
	fbxImporter_ = FbxImporter::Create(fbxManager_, "imp");
	fbxImporter_->Initialize(path_.c_str(), -1, fbxManager_->GetIOSettings());
	FbxScene* fbxScene = FbxScene::Create(fbxManager_, "fbxscene");
	fbxImporter_->Import(fbxScene);
	fbxImporter_->Destroy();

	FbxNode* rootNode = fbxScene->GetRootNode();
	FbxNode* node = rootNode->GetChild(0); //結合済み前提
	FbxMesh* mesh = node->GetMesh();

	vertexCount_ = mesh->GetControlPointsCount();
	polygonCount_ = mesh->GetPolygonCount();
	materialCount_ = node->GetMaterialCount();

	InitVertex(mesh);
	InitIndex(mesh);
	InitConstantBuffer();
	InitMaterial(node);
}

void FBX::InitVertex(FbxMesh* mesh) {
	vertices_ = new Vertex[vertexCount_](); //頂点

	for (DWORD poly = 0; poly < polygonCount_; poly++) {
		for (int vertex = 0; vertex < 3; vertex++) {
			int index = mesh->GetPolygonVertex(poly, vertex);
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices_[index].postion.x = (float)pos[0];
			vertices_[index].postion.y = (float)pos[1];
			vertices_[index].postion.z = (float)pos[2];

			FbxLayerElementUV* uvLayer = mesh->GetLayer(0)->GetUVs();
			int uvIndex = mesh->GetTextureUVIndex(poly, vertex);
			FbxVector2 uv = uvLayer->GetDirectArray().GetAt(uvIndex);

			vertices_[index].uv.x = (float)uv.mData[0];
			vertices_[index].uv.y = (float)(1.0f - uv.mData[1]);
		}
	}

	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertexCount_;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = vertices_;

	HRESULT hr = GetDevice()->CreateBuffer(&bd, &data, &pVertexBuffer_);
}

void FBX::InitIndex(FbxMesh* mesh) {
	pIndexBuffer_ = new ID3D11Buffer*[materialCount_];
	index_ = new int[polygonCount_ * 3];

	for (int i = 0; i < materialCount_; i++) {
		int count = 0;

		for (DWORD poly = 0; poly < polygonCount_; poly++) {
			FbxLayerElementMaterial* materialLayer = mesh->GetLayer(0)->GetMaterials();
			int materialId = materialLayer->GetIndexArray().GetAt(poly);

			if (materialId == i) {
				for (DWORD vertex = 0; vertex < 3; vertex++) {
					index_[count] = mesh->GetPolygonVertex(poly, vertex);
					count++;
				}
			}

		}

		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = sizeof(int) * polygonCount_ * 3;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = {};
		data.pSysMem = index_;

		HRESULT hr = GetDevice()->CreateBuffer(&bd, &data, &pIndexBuffer_[i]);
	}
}

void FBX::InitConstantBuffer() {
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	HRESULT hr = GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, &pConstantBuffer_);
}

void FBX::InitMaterial(fbxsdk::FbxNode* node) {
	materials_ = new MATERIAL[materialCount_];
	for (int i = 0; i < materialCount_; i++) {
		FbxSurfaceMaterial* material = node->GetMaterial(i);
		FbxProperty property = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		int fileTextureCount = property.GetSrcObjectCount <FbxFileTexture>();
		FbxSurfaceLambert* pMaterial = (FbxSurfaceLambert*)node->GetMaterial(i);
		FbxDouble3  diffuse = pMaterial->Diffuse;
		materials_[i].diffuse = XMFLOAT4((float)diffuse[0], (float)diffuse[1], (float)diffuse[2], 1.0f);

		if (fileTextureCount > 0) {
			FbxFileTexture* textureInfo = property.GetSrcObject<FbxFileTexture>();
			const char* texturePath = textureInfo->GetFileName();
			materials_[i].texture = new Texture(texturePath, -0.5f, 0.5f);
			materials_[i].texture->Init();
		}
		else {
			materials_[i].texture = nullptr;
		}
	}
}

void FBX::Update() {
	XMMATRIX scaleMat = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	XMMATRIX rotMat = XMMatrixRotationZ(rotation_.z) * XMMatrixRotationX(rotation_.x) * XMMatrixRotationY(rotation_.y);
	XMMATRIX transMat = XMMatrixTranslation(postion_.x, postion_.y, postion_.z);
	XMMATRIX world = scaleMat * rotMat * transMat;
	XMMATRIX view = CameraManager::getCurentCamera()->getMatrix();
	XMMATRIX projection = DirectX::XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

	ConstantBuffer cb = {};
	for (int i = 0; i < materialCount_; i++) {
		auto material = materials_[i];
		cb.wvpMat = XMMatrixTranspose(world * view * projection);
		cb.diffUse = material.diffuse;
		cb.isTexture = material.texture != nullptr ? TRUE : FALSE;
		GetContext()->UpdateSubresource(pConstantBuffer_, 0, nullptr, &cb, 0, 0);
	}

}

void FBX::Draw() {
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };

	GetContext()->VSSetShader(ShaderManager::vertexShader_, nullptr, 0);
	GetContext()->PSSetShader(ShaderManager::pixelShader_, nullptr, 0);
	GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	GetContext()->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);
	for (int i = 0; i < materialCount_; i++) {
		if (!isShowTexture_) {
			GetContext()->PSSetShaderResources(0, 1, nullSRV);
			GetContext()->PSSetShader(ShaderManager::pixelDebugShader_, nullptr, 0);
		}
		else {
			if (materials_[i].texture != nullptr) {
				GetContext()->IASetIndexBuffer(pIndexBuffer_[i], DXGI_FORMAT_R32_UINT, 0);
				auto srv = (materials_[i].texture->GetShaderReasourceView());
				auto samplerState = materials_[i].texture->GetSampleState();
				GetContext()->PSSetShaderResources(0, 1, &srv);
				GetContext()->PSSetSamplers(0, 1, &samplerState);
			}
			else {
				GetContext()->PSSetShaderResources(0, 1, nullSRV);
			}
		}

		GetContext()->VSSetConstantBuffers(0, 1, &pConstantBuffer_);
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FrontCounterClockwise = FALSE;
		ID3D11RasterizerState* rasterizerState = nullptr;
		GetDevice()->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
		GetContext()->RSSetState(rasterizerState);
		GetContext()->DrawIndexed(polygonCount_ * 3, 0, 0);
		GetContext()->RSSetState(nullptr);
	}
}

void FBX::Release() {

}
