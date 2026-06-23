#include "DirectX3DManager.h"
#include "../GameEngine.hpp"
#include <Windows.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace DirectX3DManager {
	inline ID3D11Device* d3d11Device_ = nullptr;
	inline ID3D11DeviceContext* d3d11Context_ = nullptr;
	inline IDXGISwapChain* swapChain_ = nullptr;
	inline ID3D11RenderTargetView* renderTargetView_ = nullptr;
	inline ID3D11Texture2D* texture2D_ = nullptr;
	inline ID3D11RasterizerState* rasterizerState_ = nullptr;

	void DirectX3DManager::InitDirectX3D() {

		//参考：https://learn.microsoft.com/ja-jp/windows/win32/api/dxgi/ns-dxgi-dxgi_swap_chain_desc
		DXGI_SWAP_CHAIN_DESC desc = {};
		desc.BufferDesc.Width = GameEngine::DEFAULT_WIDTH;
		desc.BufferDesc.Height = GameEngine::DEFAULT_HEIGHT;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.Windowed = TRUE;
		desc.OutputWindow = GameEngine::GetWindowHandle();
		desc.BufferCount = 1;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		//参考：https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/nf-d3d11-d3d11createdeviceandswapchain
		D3D_FEATURE_LEVEL level = {};
		D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			D3D11_CREATE_DEVICE_BGRA_SUPPORT,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&desc,
			&swapChain_,
			&d3d11Device_,
			&level,
			&d3d11Context_
		);

		swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&texture2D_);
		d3d11Device_->CreateRenderTargetView(texture2D_, NULL, &renderTargetView_);

		//参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_viewport
		D3D11_VIEWPORT viewport = {};
		viewport.Width = GameEngine::DEFAULT_WIDTH;
		viewport.Height = GameEngine::DEFAULT_HEIGHT;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;

		//参考： https://learn.microsoft.com/ja-jp/windows/win32/api/d3d11/ns-d3d11-d3d11_rasterizer_desc
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_SOLID; // レンダリング時に使用する塗りつぶしモード
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FrontCounterClockwise = FALSE;

		GetDevice()->CreateRasterizerState(&rasterizerDesc, &rasterizerState_);
		d3d11Context_->RSSetState(rasterizerState_);

		d3d11Context_->RSSetViewports(1, &viewport);
	}

	void DirectX3DManager::Release() {
	}

	ID3D11Device* DirectX3DManager::GetDevice() { return d3d11Device_; }

	ID3D11DeviceContext* DirectX3DManager::GetContext() { return d3d11Context_; }

	IDXGISwapChain* DirectX3DManager::GetSwapChain() { return swapChain_;}

	ID3D11RenderTargetView* DirectX3DManager::GetRenderTargetView() { return renderTargetView_; }

	ID3D11Texture2D* DirectX3DManager::GetTexture2D() { return texture2D_; }

}

namespace ShaderManager {

	void InitShader() {
		ID3DBlob* vsBlob = nullptr; 
		ID3DBlob* psBlobDebug = nullptr;
		ID3DBlob* psBlob = nullptr; 

		D3DCompileFromFile(
			L"Engine//TexturePixelShader.hlsl", //シェーダーのファイル
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", //シェーダーのメイン関数
			"ps_5_0", //シェーダーの種類
			D3DCOMPILE_ENABLE_STRICTNESS, //シェーダーコンパイルオプション
			0, //オプション
			&psBlob, //コンパイルしたデータを指定する
			NULL //コンパイル失敗時のデータを保存する
		);

		D3DCompileFromFile(
			L"Engine//DebugPixelShader.hlsl", //シェーダーのファイル
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main", //シェーダーのメイン関数
			"ps_5_0", //シェーダーの種類
			D3DCOMPILE_ENABLE_STRICTNESS, //シェーダーコンパイルオプション
			0, //オプション
			&psBlobDebug, //コンパイルしたデータを指定する
			NULL //コンパイル失敗時のデータを保存する
		);

		D3DCompileFromFile(
			L"Engine//DebugVertexShader.hlsl",
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"main",
			"vs_5_0",
			D3DCOMPILE_ENABLE_STRICTNESS,
			0,
			&vsBlob,
			NULL
		);

		DirectX3DManager::GetDevice()->CreateVertexShader(
			vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
			NULL,
			&vertexShader_);

		DirectX3DManager::GetDevice()->CreatePixelShader(
			psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
			NULL,
			&pixelShader_);

		DirectX3DManager::GetDevice()->CreatePixelShader(
			psBlobDebug->GetBufferPointer(), psBlobDebug->GetBufferSize(),
			NULL,
			&pixelDebugShader_);

		D3D11_INPUT_ELEMENT_DESC layout[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, offsetof(Vertex, postion), D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color),    D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{"TEXCOORD",       0, DXGI_FORMAT_R32G32_FLOAT,  0, offsetof(Vertex, uv),    D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		DirectX3DManager::GetDevice()->CreateInputLayout(
			layout,
			ARRAYSIZE(layout),
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&inputLayout_
		);

	}
}