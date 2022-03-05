#pragma once
#include "Rect.h"

class Laser {
public:
	Laser(int w, int h, int x, int y, const std::string& img_path);
	~Laser();

	void draw();

	int* getPos();
	bool setPos(int x, int y);

	float speed = 3;
	Rect* m_Rect = nullptr; //add more properties to asteroid
private:
};