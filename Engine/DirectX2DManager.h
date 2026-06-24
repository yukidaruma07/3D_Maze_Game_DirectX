#pragma once
#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <string>
#include <DirectXMath.h>

#pragma comment(lib, "d2d1.lib") 
#pragma comment(lib, "dwrite.lib")

/// <summary>
/// Direct2Dに関する名前空間
/// </summary>
namespace DirectX2DManager {
	void Init();
	void DrawFontText(int x, int y, std::wstring text);
}