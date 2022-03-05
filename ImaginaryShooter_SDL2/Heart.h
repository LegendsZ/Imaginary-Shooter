#pragma once
#include "Rect.h"
#include "fileLocations.h"

class Heart {
public:
	Heart(int x, int y);
	~Heart();
	void draw();
	Rect* m_Rect = nullptr;
private:
	int m_X = NULL;
	int m_Y = NULL;
};