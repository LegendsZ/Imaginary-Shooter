#include "Text.h"

Text::Text(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color) :
	m_FontPath(font_path), m_FontSize(font_size), m_Color(color)
{
	m_Texture = loadFont(renderer, font_path, font_size, message, color);
	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_TextRect.w, &m_TextRect.h);
}

Text::~Text()
{
	SDL_DestroyTexture(m_Texture);
	TTF_CloseFont(m_Font);
}

void Text::display() const
{
	m_TextRect.x = m_Pos[0];
	m_TextRect.y = m_Pos[1];
	SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &m_TextRect);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	m_Font = font;
	if (!font) {
		std::cerr << "Failed to load font!\n";
		return nullptr;
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), color);
	if (!textSurface) {
		std::cerr << "Failed to create text surface!\n";
		return nullptr;
	}
	SDL_Texture* textTextire = SDL_CreateTextureFromSurface(renderer, textSurface);
	if (!textTextire) {
		std::cerr << "Failed to create text texture!\n";
		return nullptr;
	}
	SDL_FreeSurface(textSurface);
	return textTextire;
}

int* Text::getPos()
{
	return m_Pos;
}

bool Text::setPos(int x, int y)
{
	m_Pos[0] = x;
	m_Pos[1] = y;
	return true;
}

SDL_Renderer* Text::getRenderer()
{
	return m_Renderer;
}

bool Text::setRenderer(SDL_Renderer* renderer)
{
	m_Renderer = renderer;
	return true;
}

bool Text::setText(std::string& message)
{
	TTF_CloseFont(m_Font);
	SDL_DestroyTexture(m_Texture);
	m_Texture = loadFont(m_Renderer, m_FontPath, m_FontSize, message, m_Color);
	return true;
}
