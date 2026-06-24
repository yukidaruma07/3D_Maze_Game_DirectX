#pragma once

#include <Windows.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>

struct ConstantBuffer {
	DirectX::XMMATRIX wvpMat = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT4 diffUse = {};
	bool isTexture;
};

struct Color {
	float r, g, b, a;

	static Color GetRed() { return {1.0, 0, 0, 1}; }
	static Color GetBlue() { return { 0, 1.0, 0, 1 }; }
	static Color GetGreen() { return { 0, 0, 1.0, 1 }; }
	static Color GetWhite() { return { 1.0, 1.0, 1.0, 1 }; }
	static Color GetBlack() { return { 0, 0, 0, 1 }; }
};

struct Vertex {
	DirectX::XMFLOAT3 postion = {};
	Color color = {};
	DirectX::XMFLOAT2 uv = {};
	bool has_texture = false;
};

namespace DirectX3DManager {

	void InitDirectX3D();
	void Release();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	IDXGISwapChain* GetSwapChain();
	ID3D11RenderTargetView* GetRenderTargetView();
	ID3D11Texture2D* GetTexture2D();

}

namespace ShaderManager {

	inline ID3D11VertexShader* vertexShader_ = nullptr;
	inline ID3D11PixelShader* pixelShader_ = nullptr;
	inline ID3D11PixelShader* pixelDebugShader_ = nullptr;
	inline ID3D11InputLayout* inputLayout_ = nullptr;

	void InitShader();


}