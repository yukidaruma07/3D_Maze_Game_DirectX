#pragma once
#include "BaseScene.h"
#include "CSVRender.h"

class BootScene : public BaseScene {
private:
    CSVRender* csv_;
public:
    BootScene();
    ~BootScene();

    void Init() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};
