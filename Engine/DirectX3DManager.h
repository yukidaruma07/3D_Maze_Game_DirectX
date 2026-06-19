#pragma once

#include <Windows.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>

struct Color {
	float r, g, b, a;

	static Color GetRed() { return {255, 0, 0, 1}; }
	static Color GetBlue() { return { 0, 255, 0, 1 }; }
	static Color GetGreen() { return { 0, 0, 255, 1 }; }
	static Color GetWhite() { return { 255, 255, 255, 1 }; }
	static Color GetBlack() { return { 0, 0, 0, 1 }; }
};

struct Vertex {
	DirectX::XMFLOAT3 postion = {};
	Color color = {};
	DirectX::XMFLOAT2 uv = {};
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

	void InitShader();
}