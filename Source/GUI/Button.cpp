#include "Button.h"


Button::Button(int X=0, int Y=0, int h=50, int w=50, bool en=true) {
	init(X, Y, h, w, en);
}

void Button::init(int X, int Y, int h, int w, bool en) {
	LocX = X;
	LocY = Y;
	Height = h;
	Width = w;
	enable = en;
}

int Button::getX() {
	return LocX;
}

int Button::getY() {
	return LocY;
}

void Button::setRange(int h, int w) {
	Height = h;
	Width = w;
}

void Button::setLocation(int X, int Y) {
	LocX = X;
	LocY = Y;
}
void Button::LoadBitmap() {
	texture.LoadBitmap(IDB_7);
}
void Button::OnShow() {
	texture.ShowBitmap();
}
bool Button::isEnable() {
	return enable;
}
