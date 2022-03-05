#pragma once
#include "Rect.h"

class Asteroid {
public:
	Asteroid(int w, int h, int x, int y, const std::string& img_path);
	~Asteroid();

	void draw();

	int* getPos();
	bool setPos(int x, int y);
	static int minMax[2];
	float speed = rand() % Asteroid::minMax[1] + Asteroid::minMax[0];  //rand() % 3 +2; //1-4 inclusive
	Rect* m_Rect = nullptr; //add more properties to asteroid
private:
};