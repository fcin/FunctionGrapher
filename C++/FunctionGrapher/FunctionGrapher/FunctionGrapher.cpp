#include "stdafx.h"
#include <Windows.h>
#include <time.h>
#include <string>
#include "src\Parser.h"
#include "src\Calculator.h"
#include "src\CalculateResult.h"

const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;

void Draw(HWND& hwnd);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);

	std::string input = "(8954.523 + 214) * 7547";
	Parser parser;
	Calculator calculator(parser);
	CalculateResult result = calculator.CalculateForX(input, 1);

	switch (msg)
	{
		case WM_PAINT:
			Draw(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void Draw(HWND& hwnd)
{
	PAINTSTRUCT ps;
	HGDIOBJ hBlackPen = GetStockObject(BLACK_PEN);

	HDC hdc = BeginPaint(hwnd, &ps);

	MoveToEx(hdc, 50, 50, NULL);
	LineTo(hdc, 150, 200);

	SelectObject(hdc, hBlackPen);


	EndPaint(hwnd, &ps);
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

