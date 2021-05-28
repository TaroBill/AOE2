#include "Button.h"
#include "../../stdafx.h"
#include "../../Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../../audio.h"
#include "../../gamelib.h"
#include "../GUI.h"
using namespace game_framework;

Button::Button(int X, int Y, int h = 50, int w = 50, bool en = true) {
	init(X, Y, h, w, en);
}

Button::~Button() {

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

void Button::OnShow() {
	texture.SetTopLeft(LocX, LocY);
	texture.ShowBitmap();
}

void Button::setEnable(bool b) {
	enable = b;
}

bool Button::isEnable() {
	return enable;
}

bool Button::isInButton(CPoint p) {
	if (p.x >= LocX && p.x <= (LocX + Width) && p.y >= (LocY) && p.y <= (LocY + Height)) {
		return true;
	}
	return false;
}

CPoint Button::getLocation() {
	return CPoint(LocX, LocY);
}
