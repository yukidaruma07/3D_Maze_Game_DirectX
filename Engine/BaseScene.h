#pragma once
#include <string>

class BaseScene {
private:
    std::string name_;
public:
    BaseScene(const std::string& name) {
        name_ = name;
    };
    virtual ~BaseScene() {}

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Release() = 0;

    std::string GetName() { return name_; };
};