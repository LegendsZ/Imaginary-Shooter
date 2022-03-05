#pragma once
#include "Window.h"

class Rect{
public:
	Rect(int w, int h, int x, int y, int r, int g, int b, int a);
	Rect(int w, int h, int x, int y, const std::string &img_path);
	~Rect();

	void draw()const;

	bool pollEvents();
	bool pollEvents(SDL_Event event);

	int* getPos();
	bool setPos(int x, int y);

	bool setDisplacement(int x, int y);

	bool changeImage(std::string &img_path);

	std::string current_img_path = "";

	int m_Width, m_Height;
	int m_R, m_G, m_B, m_A;

	void (*m_Handler)(SDL_Event&) = nullptr;
private:
	int m_Pos[2] = { 0,0 };
	SDL_Texture* m_Texture = nullptr;
};