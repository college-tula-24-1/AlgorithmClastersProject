#include "Grapher.h"

Grapher::Grapher()
{
	hwnd = GetConsoleWindow();
	hdc = GetDC(hwnd);
	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	pen = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	SelectObject(hdc, pen);
}

void Grapher::SetWindowSize(int width, int height)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT window = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(handle, true, &window);
	COORD buffer = { width, height };
	SetConsoleScreenBufferSize(handle, buffer);
}

void Grapher::SetPen(COLORREF color, int width, PenStyle style)
{
	pen = CreatePen((int)style, width, color);
	SelectObject(hdc, pen);
}

void Grapher::MoveTo(int x, int y)
{
	MoveToEx(hdc, x, y, nullptr);
}

void Grapher::LineToPoint(int x, int y)
{
	LineTo(hdc, x, y);
}

void Grapher::Line(int xstart, int ystart, int xfinish, int yfinish)
{
	MoveTo(xstart, ystart);
	LineToPoint(xfinish, yfinish);
}

void Grapher::Rect(int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

void Grapher::Circle(int x, int y, int radius)
{
	Arc(hdc, x - radius, y - radius, x + radius, y + radius, 0, 0, 0, 0);
}


Grapher::~Grapher()
{
	DeleteObject(pen);
	ReleaseDC(hwnd, hdc);
}
