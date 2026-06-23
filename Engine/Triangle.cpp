#include "Triangle.h"
#include <DirectXMath.h>
#include "DirectX3DManager.h"
#include "CameraManager.h"
#include "../ImGUI/imgui.h"

using namespace DirectX3DManager;
using namespace DirectX;

Triangle::Triangle(const Color& color, XMFLOAT3 verticePos[3])
	: BaseObject("Triangle") {
	Color colors[3] = { color, color, color };
	Triangle::Triangle(colors, verticePos);
}

Triangle::Triangle(Color color[3], DirectX::XMFLOAT3 verticePos[3])
	: BaseObject("Triangle") {
	postion_ = verticePos[0];
	verticePos_[0] = verticePos[0];
	verticePos_[1] = verticePos[1];
	verticePos_[2] = verticePos[2];

	vertices_[0] = { verticePos[0], color[0], {0, 0}}; // 左上 
	vertices_[1] = { verticePos[1], color[1], {0, 1}}; // 左下
	vertices_[2] = { verticePos[2], color[2], {1, 0}}; // 右上
}

void Triangle::Init() {
	HRESULT result = S_OK;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(vertices_);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	// 参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_desc
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	result = GetDevice()->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer_);

	D3D11_SUBRESOURCE_DATA verticeData = {};
	verticeData.pSysMem = vertices_;

	result = GetDevice()->CreateBuffer(&bufferDesc, &verticeData, &vertexBuffer_);
}

void Triangle::Update() {
	Camera* camera = CameraManager::getCurentCamera();
	if (camera == nullptr) return;

	XMMATRIX scaleMat = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	XMMATRIX rotMat = XMMatrixRotationZ(rotation_.z) * XMMatrixRotationX(rotation_.x) * XMMatrixRotationY(rotation_.y);
	XMMATRIX transMat = XMMatrixTranslation(postion_.x, postion_.y, postion_.z);
	XMMATRIX world = scaleMat * rotMat * transMat;
	XMMATRIX view = camera->getMatrix();
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH(
		0.0f, 1280.0f,
		720.0f, 0.0f,
		0.0f, 100.0f
	);

	ConstantBuffer cb = {};
	cb.worldMat = XMMatrixTranspose(world);
	cb.viewMat = XMMatrixTranspose(view);
	cb.projMat = XMMatrixTranspose(projection);
	GetContext()->UpdateSubresource(constantBuffer_, 0, nullptr, &cb, 0, 0);
}

void Triangle::Draw() {
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	ID3D11DeviceContext* context = GetContext();

	context->IASetInputLayout(ShaderManager::inputLayout_);
	context->VSSetConstantBuffers(0, 1, &constantBuffer_);
	context->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->VSSetShader(ShaderManager::vertexShader_, nullptr, 0);
	context->PSSetShader(ShaderManager::pixelShader_, nullptr, 0);

	context->Draw(3, 0);

#ifdef _DEBUG
	ImGui::Begin("Traiangle");
	ImGui::SliderFloat("PosX", &postion_.x, -1280, 1280);
	ImGui::SliderFloat("PosY", &postion_.y, -1280, 1280);
	ImGui::SliderFloat("PosZ", &postion_.z, -1280, 1280);
	ImGui::SliderFloat("RotationX", &rotation_.x, 0, 90);
	ImGui::SliderFloat("RotationY", &rotation_.y, 0, 90);
	ImGui::SliderFloat("RotationZ", &rotation_.z, 0, 90);
	ImGui::SliderFloat("ScaleX", &scale_.x, 0, 10);
	ImGui::SliderFloat("ScaleY", &scale_.y, 0, 10);
	ImGui::SliderFloat("ScaleZ", &scale_.z, 0, 10);
	ImGui::End();
#endif 

}

void Triangle::Release()
{
}
