#pragma once
#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif
#include <cmath>
const double PI = 3.14159265358979323846;

namespace somefigures {

	enum direction {
		vertical, horizontal
	};

	class Figure {
	protected:
		POINT center_;
		DWORD size_;
		double angle_;
		double angleSpeed_;
		direction dir_;
		double speed_;
		COLORREF color_;
		HWND hwnd_;
		POINT *vertexs = nullptr;
		int n_ = 0;

		void spin() {
			angle_ += angleSpeed_;
			if (angle_ >= 2 * PI) {
				int k = angle_ / (2 * PI);
				angle_ -= k * (2 * PI);
			}
		}
		void move() {
			if (dir_ == direction::horizontal) {
				center_.x += speed_;
			}
			else {
				center_.y += speed_;
			}
		}
		virtual void calculate_vertexs() = 0;
		bool check_borders(size_t arr_size) {
			RECT rect = { 0 };
			GetWindowRect(hwnd_, &rect);
			for (int i = 0; i < arr_size; ++i) {
				if (dir_ == direction::horizontal) {
					if (vertexs[i].x >= rect.right || vertexs[i].x <= rect.left)
						return true;
				}
				else {
					if (vertexs[i].y >= rect.bottom || vertexs[i].y <= rect.top)
						return true;
				}
			}
			return false;
		}
		void facticalPaint(HDC &hdc, int n) {
			HPEN hp = CreatePen(PS_SOLID, 1, color_);
			SelectObject(hdc, hp);
			calculate_vertexs();
			Polyline(hdc, vertexs, n);
			DeleteObject(hp);
			if (check_borders(n)) {
				angleSpeed_ = -angleSpeed_;
				speed_ = -speed_;
			}
			spin();
			move();
		}
	public:
		Figure(POINT center, DWORD size, double angle, double angleSpeed, direction dir, double speed, COLORREF color, HWND hwnd)
			: center_(center), size_(size), angle_(angle), angleSpeed_(angleSpeed), dir_(dir), speed_(speed), color_(color), hwnd_(hwnd)
		{
		}
		virtual void paint(HDC &hdc) = 0;
		virtual ~Figure()
		{
		}
	};

	class Line : public Figure {
	public:
		// size - длина линии
		Line(POINT center, DWORD size, double angle, double angleSpeed, direction dir, double speed, COLORREF color, HWND hwnd)
			: Figure::Figure(center, size, angle, angleSpeed, dir, speed, color, hwnd)
		{
			n_ = 2;
			vertexs = new POINT[n_];
			calculate_vertexs();
		}
		void calculate_vertexs() override {
			for (int i = 0; i < n_; ++i) {
				vertexs[i].x = center_.x + (size_ / 2) * cos(angle_);
				vertexs[i].y = center_.y + (size_ / 2) * sin(angle_);
				angle_ += PI;
			}
		}
		void paint(HDC &hdc) override {
			facticalPaint(hdc, n_);
		}
		~Line()
		{
			delete[] vertexs;
		}
	};

	class Rectangle : public Figure {
		DWORD width_;
	public:
		// size выступает как height
		Rectangle(POINT center, DWORD height, DWORD width, double angle, double angleSpeed, direction dir, double speed, COLORREF color, HWND hwnd)
			: Figure::Figure(center, height, angle, angleSpeed, dir, speed, color, hwnd), width_(width)
		{
			n_ = 5;
			vertexs = new POINT[n_];
			calculate_vertexs();
		}
		void calculate_vertexs() override {
			double certainAngle = atan((size_ / 2.0) / (width_ / 2.0)); // половина угла между диагоналями (меньший)
			double sizeBetweenCenterAndVertex = sqrt(size_ * size_ + width_ * width_) / 2.0; // расстояние от центра до вершины прямоугольника
			for (int i = 0; i < n_ - 1; ++i) {
				vertexs[i].x = center_.x + sizeBetweenCenterAndVertex * cos(certainAngle + angle_);
				vertexs[i].y = center_.y + sizeBetweenCenterAndVertex * sin(certainAngle + angle_);
				angle_ += i & 1 ? (2 * certainAngle) : (PI - 2 * certainAngle);
			}
			vertexs[4].x = vertexs[0].x;
			vertexs[4].y = vertexs[0].y;
		}
		void paint(HDC &hdc) override {
			facticalPaint(hdc, n_);
		}
		~Rectangle()
		{
			delete[] vertexs;
		}
	};

	class Triangle : public Figure {
	public:
		// size - катет
		Triangle(POINT center, DWORD size, double angle, double angleSpeed, direction dir, double speed, COLORREF color, HWND hwnd)
			: Figure::Figure(center, size, angle, angleSpeed, dir, speed, color, hwnd)
		{
			n_ = 4;
			vertexs = new POINT[n_];
			calculate_vertexs();
		}
		void calculate_vertexs() override {
			double certainSize = size_ * tan(22.5 * PI / 180);// длина перпендикуляра от центра треугольника 
															//(точка пересечения биссектрис) до вершины прямого угла
			
			vertexs[0].x = center_.x - certainSize * cos(PI / 4 + angle_);
			vertexs[0].y = center_.y - certainSize * sin(PI / 4 + angle_);
			vertexs[1].x = vertexs[0].x - size_ * sin(angle_);
			vertexs[1].y = vertexs[0].y + size_ * cos(angle_);
			vertexs[2].x = vertexs[0].x + size_ * cos(angle_);
			vertexs[2].y = vertexs[0].y + size_ * sin(angle_);
			vertexs[3].x = vertexs[0].x;
			vertexs[3].y = vertexs[0].y;
		}
		void paint(HDC &hdc) override {
			facticalPaint(hdc, n_);
		}
		~Triangle()
		{
			delete[] vertexs;
		}
	};
}