#pragma once

#include "Window.h"

class Text {
public:

	Text(SDL_Renderer* renderer,const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color);
	~Text();

	void display() const;

	SDL_Texture* loadFont(SDL_Renderer *renderer, const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color);

	int* getPos();
	bool setPos(int x, int y);
	SDL_Renderer* getRenderer();
	bool setRenderer(SDL_Renderer* renderer);

	bool setText(std::string& message);

	mutable SDL_Rect m_TextRect;

	const std::string& m_FontPath;
	int m_FontSize = 25;
	const SDL_Color& m_Color;
private:

	SDL_Texture* m_Texture = nullptr;
	TTF_Font* m_Font = nullptr;
	int m_Pos[2] = {0,0};
	SDL_Renderer* m_Renderer;
};