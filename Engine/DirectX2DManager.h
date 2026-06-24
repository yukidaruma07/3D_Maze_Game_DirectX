#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <DirectXMath.h>

#pragma comment(lib, "d2d1.lib") 
#pragma comment(lib, "dwrite.lib")

namespace DirectX2DManager {
	inline ID2D1Factory* factory = nullptr;
	inline IDWriteFactory* writeFactory = nullptr;
	inline ID2D1RenderTarget* renderTarget = nullptr;

	void Init();
	void DrawFontText(int x, int y, std::wstring text);
}