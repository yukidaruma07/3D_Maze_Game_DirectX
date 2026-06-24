#pragma once
#include "BaseObject.h"
#include <d3d11.h>
#include "DirectX3DManager.h"

class Box : public BaseObject {
private:
    float width = 0.0f, height = 0.0f;
    Color color_ = {};
    ID3D11Buffer* vertexBuffer_ = nullptr;
    ID3D11Buffer* constantBuffer_ = nullptr;
    ID3D11RasterizerState* rasterizerState = nullptr;
    Vertex vertices_[6] = {};
public:
    Box(const Color& color, float width, float height);
    ~Box() {}

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};