#include "stdafx.h"
#include <Windows.h>
#include <time.h>

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HGDIOBJ hBlackPen = GetStockObject(BLACK_PEN);

	RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);

	switch (msg)
	{
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);

			MoveToEx(hdc, 50, 50, NULL);
			LineTo(hdc, 150, 200);

			SelectObject(hdc, hBlackPen);


			EndPaint(hwnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSW wndClass = { 0 };

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = L"Function Grapher";
	
	RegisterClassW(&wndClass);
	CreateWindowW(wndClass.lpszClassName, L"Function Grapher", 
					WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
					100, 100, windowWidth, windowHeight, NULL, NULL, hInstance, NULL);
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

