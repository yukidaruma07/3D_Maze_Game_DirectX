#include <Windows.h>

#define WINDOW_CLASS_NAME "GameEngine"
#define WINDOW_TITLE "MyGame"

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "Winmm.lib")

void initializeWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

namespace GameEngine {
	HWND hwnd = {};

	inline HWND GetWindowHandle() {
		return hwnd;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	initializeWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

		}
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE: {
		break;
	}
	case WM_COMMAND: {
		break;
	}
	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void initializeWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//WNDCLASSEXWの参考：https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/ns-winuser-wndclassexw
	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(WNDCLASSEX); //構造体のサイズ
	wndClass.hInstance = hInstance; //インスタンス
	wndClass.lpszClassName = WINDOW_CLASS_NAME; //クラスの名前
	wndClass.lpfnWndProc = WndProc; //ウインドウプロシージャ
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION); //アイコン（参考：https://learn.microsoft.com/ja-jp/windows/win32/menurc/about-icons）
	wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO); //小さいアイコン
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW); //カーソル（参考：https://learn.microsoft.com/ja-jp/windows/win32/menurc/about-cursors）
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景
	RegisterClassEx(&wndClass); //ウインドウクラスを登録する関数

	//CreateWindowの参考：https://learn.microsoft.com/ja-jp/windows/win32/api/winuser/nf-winuser-createwindoww
	GameEngine::hwnd = CreateWindow(
		WINDOW_CLASS_NAME, //クラスの名前（※WNDCLASSEXと同じクラス名を指定する）
		WINDOW_TITLE, //ウインドウの名前
		WS_OVERLAPPEDWINDOW, //ウインドウスタイル（参考：https://learn.microsoft.com/ja-jp/windows/win32/winmsg/window-styles）
		CW_USEDEFAULT, CW_USEDEFAULT, //ウインドウのX座標＆Y座標
		CW_USEDEFAULT, CW_USEDEFAULT, //ウインドウの幅＆高さ
		NULL, //親ウインドウ（※親ウインドウがいない場合はNULLで問題ない）
		NULL, //メニューのハンドル（※メニューがない場合はNULLで問題ない）
		hInstance, //インスタンス
		NULL //パラメータ
	);

	ShowWindow(GameEngine::GetWindowHandle(), nCmdShow);
	UpdateWindow(GameEngine::GetWindowHandle());
}