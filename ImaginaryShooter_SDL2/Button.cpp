#include "Button.h"

Button::Button(int w, int h, int x, int y, int r, int g, int b, int a, SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color, void(*handler)(SDL_Event&) ) :
	m_Handler(handler)
{
	m_Rect = new Rect(w, h, x, y, r, g, b, a);
	m_Text = new Text(renderer, font_path, font_size, message, color);
	m_Text->setRenderer(renderer);
	m_Text->setPos(x + w / 2 - m_Text->m_TextRect.w / 2, y + h / 2 - m_Text->m_TextRect.h/2);
}

Button::Button(int w, int h, int x, int y, const std::string& img_path, SDL_Renderer* renderer, const std::string& font_path, int font_size, const std::string& message, const SDL_Color& color, void(*handler)(SDL_Event&)):
	m_Handler(handler)
{
	m_Rect = new Rect(w, h, x, y, img_path);
	m_Text = new Text(renderer, font_path, font_size, message, color);
	m_Text->setRenderer(renderer);
	m_Text->setPos(x + w / 2 - m_Text->m_TextRect.w / 2, y + h / 2 - m_Text->m_TextRect.h / 2);
}

Button::Button(Rect *rect, Text *text, void(*handler)(SDL_Event&)): m_Rect(rect), m_Text(text), m_Handler(handler)
{
}

bool Button::pollEvents()
{
	SDL_Event event; //may add more components to button class so keeping it scalable.
	if (SDL_PollEvent(&event)) {
		//m_Rect->pollEvents(event);
		m_Handler(event);
	}
	return true;
}

bool Button::pollEvents(SDL_Event event)
{
	m_Handler(event);
	return true;
}

bool Button::setPos(int x, int y)
{
	m_Rect->setPos(x, y);
	m_Text->setPos(x +m_Rect->m_Width / 2 - m_Text->m_TextRect.w / 2, y + m_Rect->m_Height / 2 - m_Text->m_TextRect.h / 2);
	return true;
}

int* Button::getPos()
{
	return m_Rect->getPos();
}

bool Button::draw()
{
	m_Rect->draw();
	m_Text->display();
	return true;
}
