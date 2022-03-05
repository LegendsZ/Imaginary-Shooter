#include "Window.h"

SDL_Renderer* Window::renderer = nullptr;

Window::Window(const std::string& title, int width, int height):
m_Title(title), m_Width(width), m_Height(height)
{
	m_isClosed = !init();
}

Window::~Window() {
	Mix_FreeMusic(menuSound);
	Mix_FreeMusic(gameSound);
	Mix_FreeChunk(laser_effect);
	Mix_FreeChunk(burning_effect);
	Mix_FreeChunk(explosion_effect);
	Mix_FreeChunk(click_effect);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(m_Window);
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Window::pollEvents(const SDL_Event &event)
{
	switch (event.type) {
	case SDL_QUIT:
		m_isClosed = true;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_w:
			break;
		case SDLK_a:
			break;
		case SDLK_s:
			break;
		case SDLK_d:
			break;
		case SDLK_ESCAPE:
			//escape menu?
			m_isClosed = true; //pause here
			break;
		}
	case SDL_MOUSEMOTION:
		//std::cout << "Mouse Location: [" << event.motion.x << ", " << event.motion.y << "]!\n";
		break;
	case SDL_MOUSEBUTTONDOWN:
		break;
	default:
		break;
	}
}

void Window::clear() const
{
	SDL_RenderPresent(renderer);
	SDL_SetRenderDrawColor(renderer, m_R, m_G, m_B, m_A);
	SDL_RenderClear(renderer);
}

bool Window::isClosed() const
{
	return m_isClosed;
}

bool Window::close()
{
	m_isClosed = true;
	return true;
}

bool Window::init() {
	std::cout << "Initializing...";
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cerr << "\nFailed to initailize video!\n";
		return false;
	}

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	menuSound = Mix_LoadMUS(menuSound_path.c_str());
	//gameSound = Mix_LoadMUS(gameSound_path.c_str());
	//laser_effect = Mix_LoadWAV(laser_effect_path.c_str());
	//burning_effect = Mix_LoadWAV(burning_effect_path.c_str());
	explosion_effect = Mix_LoadWAV(explosion_effect_path.c_str());
	//click_effect = Mix_LoadWAV(click_effect_path.c_str());


	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG)) {
		std::cerr << "\nFailed to initailize sdl_image!\n";
		return false;
	}

	if (TTF_Init() == -1) {
		std::cerr << "\nFailed to initailize sdl_ttf!\n";
		return false;
	}

	m_Window = SDL_CreateWindow(m_Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Width, m_Height, SDL_WINDOW_HIDDEN);

	if (m_Window == nullptr) {
		std::cerr << "\nFailed to create window!\n";
		return false;
	}

	renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if (renderer == nullptr) {
		std::cerr << "\nFailed to create renderer!\n";
		return false;
	}
	std::cout << "OK!\n";

	return true;
}