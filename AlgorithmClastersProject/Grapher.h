#pragma once
#include <Windows.h>

enum class PenStyle
{
	Solid = PS_SOLID,
	Dotted = PS_DOT,
	Dashed = PS_DASH
};

struct PointClaster
{
	int x;
	int y;
	COLORREF color;
};

class Grapher
{
	HWND hwnd;
	HDC hdc;
	HANDLE handle;
	HPEN pen;
public:
	Grapher();

	void SetWindowSize(int width, int height);
	void SetPen(COLORREF color = RGB(255, 255, 255), int width = 2, PenStyle style = PenStyle::Solid);
	void MoveTo(int x, int y);
	void LineToPoint(int x, int y);
	void Line(int xstart, int ystart, int xfinish, int yfinish);
	void Rect(int x, int y, int width, int height);
	void Circle(int x, int y, int radius);

	~Grapher();	
};

