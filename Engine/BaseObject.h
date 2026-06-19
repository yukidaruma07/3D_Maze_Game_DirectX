#pragma once
#include <string>
#include <DirectXMath.h>

class BaseObject {
private:
protected:
    std::string name_;
    bool isDead_;

    DirectX::XMFLOAT3 postion_;
    DirectX::XMFLOAT3 velocity_;
    DirectX::XMFLOAT3 rotation_;
    DirectX::XMFLOAT3 scale_;
public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Release() = 0;

    virtual void OnCollide(BaseObject* obj) {}

    BaseObject(const std::string& name, const bool isDead = false) {
        name_ = name;
        isDead_ = isDead;
    };
    virtual ~BaseObject() {}

    std::string GetName() { return name_; };
    bool IsDead() { return isDead_; };
    void KillMe() { this->isDead_ = true; }

    DirectX::XMFLOAT3 GetPosition() const { return postion_; }
    void SetPosition(const DirectX::XMFLOAT3 position) { this->postion_ = position; }
    DirectX::XMFLOAT3 GetVelocity() const { return velocity_; }
    void SetVelocity(const DirectX::XMFLOAT3 velocity) { this->velocity_ = velocity; }
    DirectX::XMFLOAT3 GetRotation() const { return rotation_; }
    void SetRotation(const DirectX::XMFLOAT3 rotation) { this->rotation_ = rotation; }
    DirectX::XMFLOAT3 GetScale() const { return scale_; }
    void SetScale(const DirectX::XMFLOAT3 scale) { this->scale_ = scale; }
};