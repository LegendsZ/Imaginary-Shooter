#pragma once

#include "fileLocations.h"
#include "SDL.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream> //for debug

class Window {
public:
	Window(const std::string& title, int width, int height);
	~Window();

	void pollEvents(const SDL_Event& event);
	void clear() const;

	bool isClosed() const;

	static SDL_Renderer* renderer;

	bool close();


	Mix_Music* menuSound = nullptr;
	Mix_Music* gameSound = nullptr;
	Mix_Chunk* laser_effect = nullptr;
	Mix_Chunk* burning_effect = nullptr;
	Mix_Chunk* explosion_effect = nullptr;
	Mix_Chunk* click_effect = nullptr;

	SDL_Window* m_Window = nullptr;
private:
	bool init();


	std::string m_Title;
	int m_Width = 800;
	int m_Height = 600;
	bool m_isClosed = false;

	int m_R = 0;
	int m_G = 0;
	int m_B = 0;
	int m_A = 0;
};