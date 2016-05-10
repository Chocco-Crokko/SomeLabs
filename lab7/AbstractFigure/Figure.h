#pragma once
#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif

const double PI = 3.14159265358979323846;

enum direction {
	vertical, horizontal
};


class Figure {
	POINT center_;
	DWORD size_;
	LONG angle_;
	LONG angleSpeed_;
	direction dir_;
	LONG speed_;
	COLORREF color_;
	HWND hwnd_;
	Figure(POINT center, DWORD size, LONG angle, LONG angleSpeed, direction dir, LONG speed, COLORREF color, HWND hwnd)
		: center_(center), size_(size), angle_(angle), angleSpeed_(angleSpeed), dir_(dir), speed_(speed), color_(color), hwnd_(hwnd)
	{
	}
	void spin() {
		angle_ += angleSpeed_;
	}
	void move() {

	}
};