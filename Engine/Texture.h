#pragma once
#include "DirectX3DManager.h"
#include <string>
#include <wincodec.h>
#include <vector>
#include "BaseObject.h"

/// <summary>
/// 画像を表示するクラス
/// </summary>
class Texture : public BaseObject {
protected:
	UINT width_, height_;
	std::string path_;

	ID3D11SamplerState* samplerState_ = nullptr;
	ID3D11ShaderResourceView* shaderResourceView_ = nullptr;
	ID3D11Buffer* constantBuffer_ = nullptr;
	ID3D11Buffer* vertexBuffer_ = nullptr;
	IWICImagingFactory* pFactory = nullptr;
	IWICBitmapDecoder* pDecoder = nullptr;
	IWICBitmapFrameDecode* pFrame = nullptr;
	IWICFormatConverter* pConverter = nullptr;
	Vertex vertices_[6];
public:
	Texture(const std::string& path, const float leftX, const float leftY);
	~Texture() {};
	void Init() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	ID3D11SamplerState* GetSampleState() { return samplerState_; }
	ID3D11ShaderResourceView* GetShaderReasourceView() { return shaderResourceView_; }
};
