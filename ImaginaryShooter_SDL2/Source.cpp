#include "SDL.h"
#undef main
#include <filesystem>
#include <conio.h>
#include "gameMethods.h"



std::string getRandomBackgroundImagePath() {
	int randBack = rand() % 3;
	std::string randImgPath = "res/background" + std::to_string(randBack) + "PNG.png";
	return randImgPath;
}

void pollEvents(Window& window, Rect& background1, Rect& background2, Button& btnPlay, Button& btnExit) {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {

		if (event.type == SDL_MOUSEMOTION) {
			windowValues::mousePos[0] = event.motion.x <= windowValues::windowWidth ? event.motion.x : windowValues::mousePos[0];
			windowValues::mousePos[1] = event.motion.y <= windowValues::windowHeight ? event.motion.y : windowValues::mousePos[1];
		}

		if (!gameValues::gameActive && windowValues::mousePos[0] >= btnPlay.getPos()[0] && windowValues::mousePos[0] <= btnPlay.getPos()[0] + btnPlay.m_Rect->m_Width && windowValues::mousePos[1] >= btnPlay.getPos()[1] && windowValues::mousePos[1] <= btnPlay.getPos()[1] + btnPlay.m_Rect->m_Height) {
			btnPlay.pollEvents(event);
		}
		else if (!gameValues::gameActive && windowValues::mousePos[0] >= btnExit.getPos()[0] && windowValues::mousePos[0] <= btnExit.getPos()[0] + btnExit.m_Rect->m_Width && windowValues::mousePos[1] >= btnExit.getPos()[1] && windowValues::mousePos[1] <= btnExit.getPos()[1] + btnExit.m_Rect->m_Height) {
			btnExit.pollEvents(event);
		}
		else if (windowValues::mousePos[0] >= background1.getPos()[0] && windowValues::mousePos[0] <= background1.getPos()[0] + background1.m_Width && windowValues::mousePos[1] >= background1.getPos()[1] && windowValues::mousePos[1] <= background1.getPos()[1] + background1.m_Height) {
			background1.pollEvents(event);
		}
		else if (windowValues::mousePos[0] >= background2.getPos()[0] && windowValues::mousePos[0] <= background2.getPos()[0] + background2.m_Width && windowValues::mousePos[1] >= background2.getPos()[1] && windowValues::mousePos[1] <= background2.getPos()[1] + background2.m_Height) {
			background2.pollEvents(event);
		}

		//window.pollEvents(event);

	}
}
void backgroundEvent(SDL_Event& event) {
	if (gameValues::gameActive && event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			gameValues::paused = true;
		}
		else if (event.key.keysym.sym == SDLK_SPACE) {
			if (gameValues::laserList.size() >= gameValues::laserMax) {
				return;
			}
			int* tempPos = windowComponentPTRContainer::playerPTR->getPos();
			gameValues::laserList.push_back(spawnLaser(gameValues::laserSize[0], gameValues::laserSize[1], tempPos[0] + windowComponentPTRContainer::playerPTR->m_Width / 2 - gameValues::laserSize[0] / 2, tempPos[1] - ADJUSTMENT_FACTOR));
		}
	}
}
void btnPlayEvent(SDL_Event& event) {
	if (!windowValues::showMenu) {
		return;
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		gameValues::gameActive = true;
		SDL_SetWindowTitle(windowComponentPTRContainer::windowPTR->m_Window, "Imaginary Shooter | Game");
		//give 3 hearts
		gameValues::lives = 3;
		for (int i = 0; i < gameValues::lives; i++) {
			int x = i == 0 ? 0 : gameValues::heartList[i - 1]->m_Rect->getPos()[0] + gameValues::heartList[i - 1]->m_Rect->m_Width;
			gameValues::heartList.push_back(spawnHeart(x, 0));
		}
		gameValues::score = 0;
		gameValues::startMS = SDL_GetTicks();
		std::string levelString = "LEVEL: " + std::to_string(gameValues::level);
		windowComponentPTRContainer::lblLevelPTR->setText(levelString);
	}
}
void btnExitEvent(SDL_Event& event) {
	if (!windowValues::showMenu) {
		return;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		windowComponentPTRContainer::windowPTR->close();
	}
}


bool checkIfFilesExist() {
	bool retTrue = true;
	for (int i = 0; i < arrayFiles.size(); i++) {
		if (!std::filesystem::exists(arrayFiles[i])) { //change check
			std::cout << "\nCould not find [" << arrayFiles[i] << "]!";
			retTrue = false;
		}
	}
	return retTrue;
}

int main() {
	system("title Imaginary Shooter");

	std::cout << "                                              Welcome to\n\n";
	std::cout << "  _____                       _                           _____ _                 _            \n";
	std::cout << " |_   _|                     (_)                         / ____| |               | |           \n";
	std::cout << "   | |  _ __ ___   __ _  __ _ _ _ __   __ _ _ __ _   _  | (___ | |__   ___   ___ | |_ ___ _ __ \n";
	std::cout << "   | | | '_ ` _ \\ / _` |/ _` | | '_ \\ / _` | '__| | | |  \\___ \\| '_ \\ / _ \\ / _ \\| __/ _ \\ '__|\n";
	std::cout << "  _| |_| | | | | | (_| | (_| | | | | | (_| | |  | |_| |  ____) | | | | (_) | (_) | ||  __/ |   \n";
	std::cout << " |_____|_| |_| |_|\\__,_|\\__, |_|_| |_|\\__,_|_|   \\__, | |_____/|_| |_|\\___/ \\___/ \\__\\___|_|   \n";
	std::cout << "                         __/ |                    __/ |                                        \n";
	std::cout << "                        |___/                    |___/                                     BETA\n";
	std::cout << "\n\n                                     ";

	std::cout << "\nSearching for files...";
	if (!checkIfFilesExist()) {
		std::cout << "\n\n";
		system("pause");
		return 0;
	}
	std::cout << "OK!\n";


	std::cout << "Loading values...";
	srand(time(NULL));
	//windowValues::resetValues();
	std::cout << "OK!\n\n";

	std::cout << "Do you wish to change settings first before launching? (Y/y)/(N/n): ";
	std::string input;
	std::getline(std::cin, input);
	if (input == "Y" || input == "y") {
		int key = 0;
		int selected = 0;
		int max = 3;
		while (true) {
			system("cls");

			std::cout << "  __  __                  \n";
			std::cout << " |  \\/  |                 \n";
			std::cout << " | \\  / | ___ _ __  _   _ \n";
			std::cout << " | |\\/| |/ _ \\ '_ \\| | | |\n";
			std::cout << " | |  | |  __/ | | | |_| |\n";
			std::cout << " |_|  |_|\\___|_| |_|\\__,_|\n\n\n";

			if (selected == 0) 
				std::cout << "--> ";
			std::cout << "1. Change FPS\n";
			if (selected == 1)
				std::cout << "--> ";
			std::cout << "2.Exit settings\n";

			key = _getch();
			if (key == 72) {
				selected = --selected % max;
			}
			else if (key == 80) {
				selected = ++selected % max;
			}
			else if (key == 13) {
				if (selected == 1) {
					std::cout << "\n";
					break;
				}
				else if (selected == 0) {
					while (true) {
						std::cout << "FPS cap allowed range is 1-1000 inclusive.\n";
						std::cout << "\nChange FPS cap from " << windowValues::framesCap << " to: ";
						std::getline(std::cin, input);
						bool number = true;
						for (int i = 0; i < input.length(); i++) {
							if (!std::isdigit(input[i])) {
								number = false;
							}
						}
						if (!number || input == "0") {
							std::cout << "Error: input is not a acceptable number.\n";
						}
						else {
							if (std::stoi(input) > 1000) {
								std::cout << "Error: input is not a acceptable number.\n";
							}
							else {
								windowValues::framesCap = std::stoi(input);
								std::cout << "Changed FPS cap to " << windowValues::framesCap << "\n";
								system("pause");
								break;
							}
						}
					}

				}
			}
		}
	}

	gameValues::img_path = getRandomBackgroundImagePath();
	windowComponentPTRContainer::windowPTR = new Window("Imaginary Shooter | Menu", windowValues::windowWidth, windowValues::windowHeight);
	windowComponentPTRContainer::backgroundPTR = new Rect(windowValues::windowWidth, windowValues::windowHeight, 0, 0, mainMenuPNG_path);
	windowComponentPTRContainer::background1PTR = new Rect(windowValues::windowWidth, windowValues::windowHeight, 0, -windowValues::windowHeight, gameValues::img_path);
	windowComponentPTRContainer::backgroundPTR->m_Handler = backgroundEvent;
	windowComponentPTRContainer::background1PTR->m_Handler = backgroundEvent;

	Mix_VolumeMusic(windowValues::volumeLevel); //vol settings
	Mix_VolumeChunk(windowComponentPTRContainer::windowPTR->explosion_effect, 7);

	float colorDisplacement = 0;
	bool inc = true;

	int smallestSizeBtn = 150;
	bool btnSizeinc = false;

	windowComponentPTRContainer::btnPlayPTR = new Button(
		windowValues::btnPlayWidth, windowValues::btnPlayHeight,
		(windowValues::windowWidth / 2) - (windowValues::btnPlayWidth / 2),
		(windowValues::windowHeight / 2) - (windowValues::btnPlayWidth - ADJUSTMENT_FACTOR),
		132, 0, 255, 255,
		Window::renderer, comicFont_path, 40, "PLAY", { 255,255,255,255 }, btnPlayEvent);

	windowComponentPTRContainer::btnExitPTR = new Button(
		windowValues::btnPlayWidth, windowValues::btnPlayHeight,
		(windowValues::windowWidth / 2) - (windowValues::btnPlayWidth / 2),
		(windowValues::windowHeight / 2) + (ADJUSTMENT_FACTOR),
		132, 0, 255, 255,
		Window::renderer, comicFont_path, 40, "EXIT", { 255,255,255,255 }, btnExitEvent);


	windowComponentPTRContainer::lblFPSPTR = new Text(
		Window::renderer, comicFont_path, 25, "FPS: ", { 255,255,255,255 }
	);
	int lblFPSX = windowComponentPTRContainer::btnPlayPTR->getPos()[0];
	int lblFPSY = windowValues::windowHeight - windowComponentPTRContainer::lblFPSPTR->m_TextRect.h - ADJUSTMENT_FACTOR;
	windowComponentPTRContainer::lblFPSPTR->setPos(lblFPSX,lblFPSY);
	windowComponentPTRContainer::lblFPSPTR->setRenderer(Window::renderer);

	windowComponentPTRContainer::lblScorePTR = new Text(
		Window::renderer, comicFont_path, 25, "SCORE: ", { 255,255,255,255 }
	);
	int lblSCOREX = windowComponentPTRContainer::btnPlayPTR->getPos()[0] + windowComponentPTRContainer::btnPlayPTR->m_Rect->m_Width - windowComponentPTRContainer::lblScorePTR->m_TextRect.w;
	int lblSCOREY = windowValues::windowHeight - windowComponentPTRContainer::lblScorePTR->m_TextRect.h - ADJUSTMENT_FACTOR;
	windowComponentPTRContainer::lblScorePTR->setPos(lblSCOREX, lblSCOREY);
	windowComponentPTRContainer::lblScorePTR->setRenderer(Window::renderer);


	windowComponentPTRContainer::lblTimePTR = new Text(
		Window::renderer, comicFont_path, 25, "TIME: ", { 255,255,255,255 }
	);
	int lblTIMEX = lblSCOREX + windowComponentPTRContainer::lblTimePTR->m_TextRect.w + ADJUSTMENT_FACTOR*4;
	int lblTIMEY = windowValues::windowHeight - windowComponentPTRContainer::lblTimePTR->m_TextRect.h - ADJUSTMENT_FACTOR;
	windowComponentPTRContainer::lblTimePTR->setPos(lblTIMEX, lblTIMEY);
	windowComponentPTRContainer::lblTimePTR->setRenderer(Window::renderer);



	windowComponentPTRContainer::lblLevelPTR = new Text(
		Window::renderer, comicFont_path, 25, "LEVEL: ", { 255,255,255,255 }
	);
	int lblLEVELX = lblFPSX - windowComponentPTRContainer::lblLevelPTR->m_TextRect.w - ADJUSTMENT_FACTOR * 4;
	int lblLEVELY = windowValues::windowHeight - windowComponentPTRContainer::lblLevelPTR->m_TextRect.h - ADJUSTMENT_FACTOR;
	windowComponentPTRContainer::lblLevelPTR->setPos(lblLEVELX, lblLEVELY);
	windowComponentPTRContainer::lblLevelPTR->setRenderer(Window::renderer);
	std::string levelString = "LEVEL: " + std::to_string(gameValues::level);
	windowComponentPTRContainer::lblLevelPTR->setText(levelString);

	windowComponentPTRContainer::playerPTR = new Rect(windowValues::playerWidth, windowValues::playerHeight, windowValues::windowWidth/2 - windowValues::playerWidth/2, windowValues::windowHeight, playerPNG_path);

	std::cout << "\n";
	system("pause");
	system("cls");

	SDL_ShowWindow(windowComponentPTRContainer::windowPTR->m_Window);

	Mix_PlayMusic(windowComponentPTRContainer::windowPTR->menuSound, -1); //WORK HERE
	gameValues::startMS = SDL_GetTicks();
	Uint32 iStart;
	gameValues::lastMoveMS = SDL_GetTicks();
	Uint32 lastFrame = SDL_GetTicks();
	gameValues::lastSpawn = SDL_GetTicks();

	std::string scoreString = "SCORE: " + std::to_string(gameValues::score);
	windowComponentPTRContainer::lblScorePTR->setText(scoreString);

	while (!windowComponentPTRContainer::windowPTR->isClosed()) {
		iStart = SDL_GetTicks();

		windowComponentPTRContainer::backgroundPTR->draw();
		windowComponentPTRContainer::background1PTR->draw();

		if (gameValues::gameActive) {
			if (!gameValues::paused) {
				gameSpawnLogic(*windowComponentPTRContainer::btnPlayPTR);
			}
			else {
				while (gameValues::paused) {
					std::cout << "\n\nYOU HAVE PAUSED THE GAME!\n";
					system("pause");
					gameValues::paused = false;
				}
			}
		}
		else {
			mainMenuSpawnLogic(*windowComponentPTRContainer::btnPlayPTR);
			if (colorDisplacement == 255) {
				inc = false;
			}
			else if (colorDisplacement == 0) {
				inc = true;
			}
			/*if (btnPlayPTR->m_Rect->m_Width == windowValues::btnPlayWidth) {
				btnSizeinc = false;
			}
			else if (btnPlayPTR->m_Rect->m_Width == smallestSizeBtn) {
				btnSizeinc = true;
			}*/

			windowComponentPTRContainer::btnPlayPTR->m_Rect->m_R = (int)colorDisplacement;
			windowComponentPTRContainer::btnExitPTR->m_Rect->m_R = (int)colorDisplacement;
			
			//btnPlayPTR->m_Rect->m_Width += btnSizeinc ? 2 : -2;
			//int* tempPos = btnPlayPTR->getPos();
			//btnPlayPTR->setPos(tempPos[0] + (btnSizeinc ? -1 : 1), tempPos[1]);

			//btnExitPTR->m_Rect->m_Width += btnSizeinc ? 2 : -2;
			//tempPos = btnExitPTR->getPos();
			//btnExitPTR->setPos(tempPos[0] + (btnSizeinc ? -1 : 1), tempPos[1]);

			colorDisplacement += inc ? 1 : -1;

			if (windowValues::showMenu) {
				windowComponentPTRContainer::btnPlayPTR->draw();
				windowComponentPTRContainer::btnExitPTR->draw();
			}
		}


		drawAsteroids();
		drawLasers();
		drawHearts();

		windowComponentPTRContainer::lblLevelPTR->display();
		windowComponentPTRContainer::lblFPSPTR->display();
		windowComponentPTRContainer::lblScorePTR->display();
		windowComponentPTRContainer::lblTimePTR->display();
		windowComponentPTRContainer::playerPTR->draw();

		windowComponentPTRContainer::windowPTR->clear();
		pollEvents(*windowComponentPTRContainer::windowPTR, *windowComponentPTRContainer::backgroundPTR,*windowComponentPTRContainer::background1PTR, *windowComponentPTRContainer::btnPlayPTR, *windowComponentPTRContainer::btnExitPTR);


		
		windowValues::framesCount++;
		if (1000 / windowValues::framesCap > SDL_GetTicks() - iStart) { //to cap frames
			Uint32 toDelay = 1000 / windowValues::framesCap - (SDL_GetTicks() - iStart);
			SDL_Delay(toDelay);
		}
		if ((SDL_GetTicks() - lastFrame)/1000.0 >= 1) {
			std::string fpsString = "FPS: " + std::to_string(--windowValues::framesCount);
			windowComponentPTRContainer::lblFPSPTR->setText(fpsString);

			windowValues::framesCount = 0;
			lastFrame = SDL_GetTicks();

			if (gameValues::gameActive) {
				std::string timeUpdate = "TIME: " + std::to_string((SDL_GetTicks() - gameValues::startMS) / 1000);
				windowComponentPTRContainer::lblTimePTR->setText(timeUpdate);
			}
		}
		
	}


	return 0;
}