#pragma once
#include "BaseObject.h"
#include <d3d11.h>
#include "DirectX3DManager.h"

class Triangle : public BaseObject {
private:
    Color color_[3] = {};
    ID3D11Buffer* vertexBuffer_ = nullptr;
    ID3D11Buffer* constantBuffer_ = nullptr;
    ID3D11RasterizerState* rasterizerState = nullptr;
    Vertex vertices_[3] = {};
public:
    Triangle(const Color& color, DirectX::XMFLOAT3 postion[3]);
    Triangle(Color color[3], DirectX::XMFLOAT3 postion[3]);
    ~Triangle() {}

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};