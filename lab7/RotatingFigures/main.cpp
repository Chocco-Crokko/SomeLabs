// AbstractFigure.cpp: определяет точку входа для приложения.
//

#include "Figure.h"
#include "resource.h"
#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
LONG screenHeight, screenWidth;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: разместите код здесь.


	// Инициализация глобальных строк
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_ROTATINGFIGURES, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = 0;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_WINLOGO);

	return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_POPUP,
		0, 0, screenWidth, screenHeight, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	SetTimer(hWnd, 1, 10, NULL);
	return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
PAINTSTRUCT ps;
HDC hdc, hCompDC;
HBITMAP hBitMap;
int k = 6;
somefigures::Figure **p = nullptr;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		p = new somefigures::Figure*[k];
		p[0] = new somefigures::Line({ 200, 200 }, 200, 0, 20 * PI / 180, somefigures::direction::horizontal, 7, RGB(40, 100, 159), hWnd);
		p[1] = new somefigures::Line({ 450, 650 }, 50, 45 * PI / 180, 10 * PI / 180, somefigures::direction::vertical, 4, RGB(240, 10, 154), hWnd);
		p[2] = new somefigures::Rectangle({ 1000, 300 }, 50, 100, 0, 10 * PI / 180, somefigures::direction::vertical, 5, RGB(0, 140, 0), hWnd);
		p[3] = new somefigures::Rectangle({ 650, 400 }, 100, 150, 45 * PI / 180, 10 * PI / 180, somefigures::direction::horizontal, 6, RGB(41, 65, 15), hWnd);
		p[4] = new somefigures::Triangle({ 500, 800 }, 50, 0, 10 * PI / 180, somefigures::direction::horizontal, 5, RGB(150, 10, 250), hWnd);
		p[5] = new somefigures::Triangle({ 1300, 400 }, 100, 45 * PI / 180, 10 * PI / 180, somefigures::direction::vertical, 6, RGB(0, 0, 240), hWnd);
		break;
	case WM_PAINT:
	{
		
		hdc = BeginPaint(hWnd, &ps);
		hCompDC = CreateCompatibleDC(hdc);
		hBitMap = CreateCompatibleBitmap(hdc, screenWidth, screenHeight);
		SelectObject(hCompDC, hBitMap);
		PatBlt(hCompDC, 0, 0, screenWidth, screenHeight, PATCOPY);
		
		for (int i = 0; i < k; ++i)
			p[i]->paint(hCompDC);
		BitBlt(hdc, 0, 0, screenWidth, screenHeight, hCompDC, 0, 0, SRCCOPY);
		DeleteObject(hBitMap);
		DeleteDC(hCompDC);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
		if (wParam == 27)
		{
			PostQuitMessage(0);
			KillTimer(hWnd, 1);
			for (int i = 0; i < k; ++i)
				delete p[i];
			delete[] p;
		}
		break;
	case WM_DESTROY:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


