// AbstractFigure.cpp: ���������� ����� ����� ��� ����������.
//

#include "stdafx.h"
#include "AbstractFigure.h"
#include "Figure.h"

#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif
#define MAX_LOADSTRING 100

// ���������� ����������:
HINSTANCE hInst;                                // ������� ���������
WCHAR szTitle[MAX_LOADSTRING];                  // ����� ������ ���������
WCHAR szWindowClass[MAX_LOADSTRING];            // ��� ������ �������� ����
LONG screenHeight, screenWidth;

// ��������� ���������� �������, ���������� � ���� ������ ����:
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

    // TODO: ���������� ��� �����.
	

    // ������������� ���������� �����
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ABSTRACTFIGURE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // ��������� ������������� ����������:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ABSTRACTFIGURE));

    MSG msg;

    // ���� ��������� ���������:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  �������: MyRegisterClass()
//
//  ����������: ������������ ����� ����.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = 0;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ABSTRACTFIGURE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   �������: InitInstance(HINSTANCE, int)
//
//   ����������: ��������� ��������� ���������� � ������� ������� ����.
//
//   �����������:
//
//        � ������ ������� ���������� ���������� ����������� � ���������� ����������, � �����
//        ��������� � ��������� �� ����� ������� ���� ���������.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��������� ���������� ���������� � ���������� ����������

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
   SetTimer(hWnd, 1, 1, NULL);
   return TRUE;
}

//
//  �������: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����������:  ������������ ��������� � ������� ����.
//
//  WM_COMMAND � ���������� ���� ����������
//  WM_PAINT � ���������� ������� ����
//  WM_DESTROY � ��������� ��������� � ������ � ���������
//
//
POINT point = { 100, 100 };
double Vx = 4, Vy = 8;
PAINTSTRUCT ps;
HDC hdc, hCompDC;
HBITMAP hBitMap;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            
			hdc = BeginPaint(hWnd, &ps);
			//hCompDC = CreateCompatibleDC(hdc);
            // TODO: �������� ���� ����� ��� ����������, ������������ HDC...
			//hBitMap = CreateCompatibleBitmap(hCompDC, screenWidth, screenHeight);
			//SelectObject(hCompDC, hBitMap);
			//PatBlt(hCompDC, point.x, point.y, 30, 30, PATCOPY);
			//SelectObject(hCompDC, (HBRUSH)GetStockObject(BLACK_BRUSH));
			Rectangle(hdc/*hCompDC*/, point.x, point.y, point.x + 30, point.y + 30);
			
			//BitBlt(hdc, point.x, point.y, 30, 30, hCompDC, 0, 0, SRCCOPY);
			//DeleteDC(hCompDC);
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
		point.x += Vx;
		if (point.x > screenWidth || point.x < 0)
		{
			Vx = -Vx;
			point.x += Vx;
		}
		point.y += Vy;
		if (point.y > screenHeight || point.y < 0)
		{
			Vy = -Vy;
			point.y += Vy;
		}
		
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if (wParam == 27)
		{
			PostQuitMessage(0);
			KillTimer(hWnd, 1);
		}
		break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


