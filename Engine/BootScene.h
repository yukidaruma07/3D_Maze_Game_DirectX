#pragma once
#include "BaseScene.h"

class BootScene : public BaseScene {
private:
public:
    BootScene();
    ~BootScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
