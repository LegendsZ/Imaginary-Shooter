#pragma once
#include "Heart.h"
#include "Asteroid.h"
#include "Laser.h"

#include "gameValues.h"
#include "windowValues.h"
#include "windowComponentPTRContainer.h"



//smaller helper methods
Heart* spawnHeart(int x, int y) {
	return new Heart(x, y);
}
Asteroid* spawnAsteroid(int w, int h, int x, int y) {
	gameValues::asteroidsSpawned++;
	return new Asteroid(w, h, x, y, asteroidPNG_path);
}
Laser* spawnLaser(int w, int h, int x, int y) {
	return new Laser(w, h, x, y, laserPNG_path);
}

//assume obj1 is below obj2
bool collision(Rect* obj1, Rect* obj2) {
	int* obj1Pos = obj1->getPos();
	int* obj2Pos = obj2->getPos();

	if (abs(obj1Pos[1] - obj2Pos[1]) <= ADJUSTMENT_FACTOR * 5) {
		if (obj1Pos[0] >= obj2Pos[0] && obj1Pos[0] <= obj2Pos[0] + obj2->m_Width) {
			return true;
		}
		else if (obj1Pos[0] + obj1->m_Width >= obj2Pos[0] && obj1Pos[0] + obj1->m_Width <= obj2Pos[0] + obj2->m_Width) {
			return true;
		}
		else if (obj1Pos[0] < obj2Pos[0] && obj1Pos[0] + obj1->m_Width > obj2Pos[0] + obj2->m_Width) {
			return true;
		}
	}

	return false;
}

//below are main methods
void mainMenuSpawnLogic(Button& reference) {
	if (gameValues::left_rightMenu[0] < gameValues::menuLaserCount) { //left side
		int x = rand() % (reference.getPos()[0] - gameValues::laserSize[0] - ADJUSTMENT_FACTOR);
		gameValues::laserList.push_back(spawnLaser(gameValues::laserSize[0], gameValues::laserSize[1], x, windowValues::windowHeight + gameValues::laserSize[1]));
		gameValues::left_rightMenu[0]++;
	}
	if (gameValues::left_rightMenu[1] < gameValues::menuLaserCount) { //left side
		int x = rand() % (reference.getPos()[0] - gameValues::laserSize[0] - ADJUSTMENT_FACTOR) + reference.getPos()[0] + reference.m_Rect->m_Width;
		gameValues::laserList.push_back(spawnLaser(gameValues::laserSize[0], gameValues::laserSize[1], x, windowValues::windowHeight + gameValues::laserSize[1]));
		gameValues::left_rightMenu[1]++;
	}
	for (int i = 0; i < gameValues::laserList.size(); i++) {
		Laser* tempRef = gameValues::laserList[i];
		if (tempRef->getPos()[1] <= 0 - tempRef->m_Rect->m_Height) {
			gameValues::laserList.erase(gameValues::laserList.begin() + i);
			if (tempRef->getPos()[0] <= reference.getPos()[0]) {
				gameValues::left_rightMenu[0]--;
			}
			else {
				gameValues::left_rightMenu[1]--;
			}
			tempRef->~Laser();
		}
	}

	if ((SDL_GetTicks() - gameValues::lastMoveMS) / 1000.0 >= gameValues::epsilon) {
		for (int i = 0; i < gameValues::laserList.size(); i++) {
			Laser* tempRef = gameValues::laserList[i];
			tempRef->setPos(tempRef->getPos()[0], tempRef->getPos()[1] - tempRef->speed);
		}
		gameValues::lastMoveMS = SDL_GetTicks();


		if (!gameValues::first_time) {
			int* tempPos = windowComponentPTRContainer::backgroundPTR->getPos();
			int* tempPos1 = windowComponentPTRContainer::background1PTR->getPos();

			if (abs(tempPos[1]) == 1) {
				int displacement = tempPos[1] == 1 ? -1 : 1;
				windowComponentPTRContainer::backgroundPTR->setDisplacement(0, displacement);
				windowComponentPTRContainer::background1PTR->setDisplacement(0, displacement);
				tempPos = windowComponentPTRContainer::backgroundPTR->getPos();
				tempPos1 = windowComponentPTRContainer::background1PTR->getPos();
			}
			else if (abs(tempPos1[1]) == 1) {
				int displacement = tempPos1[1] == 1 ? -1 : 1;
				windowComponentPTRContainer::backgroundPTR->setDisplacement(0, displacement);
				windowComponentPTRContainer::background1PTR->setDisplacement(0, displacement);
				tempPos = windowComponentPTRContainer::backgroundPTR->getPos();
				tempPos1 = windowComponentPTRContainer::background1PTR->getPos();
			}

			if (windowComponentPTRContainer::backgroundPTR->current_img_path == mainMenuPNG_path && tempPos[1] == 0) {
				windowComponentPTRContainer::backgroundPTR->setPos(0, 0);
				windowComponentPTRContainer::background1PTR->setPos(0, -windowValues::windowHeight);
				gameValues::first_time = true;
				windowValues::showMenu = true;
				return;
			}

			if (tempPos1[1] == 0) {
				std::string tempRef = mainMenuPNG_path;
				windowComponentPTRContainer::backgroundPTR->changeImage(tempRef);
			}
			else if (tempPos[1] == 0) {
				std::string tempRef = mainMenuPNG_path;
				Rect* tempHolder = windowComponentPTRContainer::backgroundPTR;
				windowComponentPTRContainer::backgroundPTR = windowComponentPTRContainer::background1PTR;
				windowComponentPTRContainer::background1PTR = tempHolder;

				windowComponentPTRContainer::backgroundPTR->changeImage(tempRef);

				tempPos = windowComponentPTRContainer::backgroundPTR->getPos();
				tempPos1 = windowComponentPTRContainer::background1PTR->getPos();
			}

			if (tempPos1[1] < tempPos[1] && tempPos1[1] > 0) {
				windowComponentPTRContainer::backgroundPTR->setPos(tempPos[0], tempPos1[1] - windowValues::windowHeight);
			}
			else if (tempPos[1] < tempPos1[1] && tempPos[1] > 0) {
				windowComponentPTRContainer::background1PTR->setPos(tempPos1[0], tempPos[1] - windowValues::windowHeight);
			}
			else {
				int x = (tempPos[1]) % 4;
				if (x != 0) {
					windowComponentPTRContainer::backgroundPTR->setDisplacement(0, x);
					windowComponentPTRContainer::background1PTR->setDisplacement(0, x);
				}
				windowComponentPTRContainer::backgroundPTR->setPos(tempPos[0], tempPos[1] + gameValues::backgroundSpeed * (4));
				windowComponentPTRContainer::background1PTR->setPos(tempPos1[0], tempPos1[1] + gameValues::backgroundSpeed * (4));
			}


			if (windowComponentPTRContainer::playerPTR->getPos()[1] < windowValues::windowHeight + windowComponentPTRContainer::playerPTR->m_Height) {
				windowComponentPTRContainer::playerPTR->setPos(windowComponentPTRContainer::playerPTR->getPos()[0], windowComponentPTRContainer::playerPTR->getPos()[1] + 4);
			}
			else if (windowComponentPTRContainer::playerPTR->getPos()[0] != windowValues::windowWidth / 2 - windowValues::playerWidth / 2) {
				windowComponentPTRContainer::playerPTR->setPos(windowValues::windowWidth / 2 - windowValues::playerWidth / 2, windowComponentPTRContainer::playerPTR->getPos()[1]);
			}
		}
	}


}
void loserResetAll() {
	gameValues::gameActive = false;
	gameValues::first_time = false;
	windowValues::showMenu = false;

	gameValues::level = 1;
	gameValues::startMS = 0;
	gameValues::maxAsteroidSpawnCount = 2;
	gameValues::spawnInterval = 3;
	gameValues::laserMax = 2;
	Asteroid::minMax[0] = 1;
	Asteroid::minMax[1] = 2;

	double elapsedTime = (SDL_GetTicks() - gameValues::startMS) / 1000.0;
	std::string elapsedTimeString(16, '\0');
	auto written = std::snprintf(&elapsedTimeString[0], elapsedTimeString.size(), "%.2f", elapsedTime);
	elapsedTimeString.resize(written);
	std::string timeUpdate = "TIME: " + elapsedTimeString;
	windowComponentPTRContainer::lblTimePTR->setText(timeUpdate);
}
void gameSpawnLogic(Button& reference) {
	//game progression

	/* EASIEST
	unsigned int gameValues::maxAsteroidSpawnCount = 2;
	double gameValues::spawnInterval = 3;
	int gameValues::laserMax = 2;
	*/
	std::string levelString = "";
	switch (gameValues::asteroidsSpawned) {
	case 3:
		if (gameValues::level == 2) {
			break;
		}
		gameValues::spawnInterval -= 1;
		gameValues::maxAsteroidSpawnCount += 1;
		gameValues::level++;
		levelString = "LEVEL: " + std::to_string(gameValues::level);
		windowComponentPTRContainer::lblLevelPTR->setText(levelString);
		break;
	case 8:
		if (gameValues::level == 3) {
			break;
		}
		gameValues::spawnInterval -= 0.5;
		gameValues::maxAsteroidSpawnCount += 1;
		gameValues::laserMax++;
		gameValues::level++;
		levelString = "LEVEL: " + std::to_string(gameValues::level);
		windowComponentPTRContainer::lblLevelPTR->setText(levelString);
		break;
	case 13:
		if (gameValues::level == 4) {
			break;
		}
		gameValues::spawnInterval -= 0.6;
		gameValues::laserMax += 1;
		Asteroid::minMax[0] = 2;
		Asteroid::minMax[1] = 3;
		gameValues::level++;
		levelString = "LEVEL: " + std::to_string(gameValues::level);
		windowComponentPTRContainer::lblLevelPTR->setText(levelString);
		break;
	case 18:
		if (gameValues::level == 5) {
			break;
		}
		gameValues::maxAsteroidSpawnCount += 2;
		gameValues::spawnInterval -= 0.5;
		gameValues::laserMax += 1;
		gameValues::level++;
		levelString = "LEVEL: " + std::to_string(gameValues::level);
		windowComponentPTRContainer::lblLevelPTR->setText(levelString);
		break;
	case 80:
		gameValues::spawnInterval -= 0.1;
		/*case 75:
			if (gameValues::level == 6) {
				break;
			}
			gameValues::maxAsteroidSpawnCount += 2;
			gameValues::spawnInterval -= 0.5;
			gameValues::level++;
			levelString = "LEVEL: " + std::to_string(gameValues::level);
			lblLevelPTR->setText(levelString);
			break;*/
	}


	/*HARDEST
	gameValues::maxAsteroidSpawnCount = 6;
	gameValues::spawnInterval = 0.3;// 0.4;
	gameValues::laserMax = 5;
	gameValues::level = 999;
	*/


	if ((SDL_GetTicks() - gameValues::lastSpawn) / 1000.0 >= gameValues::spawnInterval) {
		if (windowComponentPTRContainer::backgroundPTR->current_img_path != mainMenuPNG_path && gameValues::asteroidsList.size() < gameValues::maxAsteroidSpawnCount) {
			int width = rand() % gameValues::asteroidWidth[0] + gameValues::asteroidWidth[1];
			int height = rand() % gameValues::asteroidHeight[0] + gameValues::asteroidHeight[1];
			int x = rand() % (windowValues::windowWidth - width);
			gameValues::asteroidsList.push_back(spawnAsteroid(width, height, x, -height));
			gameValues::lastSpawn = SDL_GetTicks();
		} //spawns asteroid
	}

	for (int i = 0; i < gameValues::laserList.size(); i++) {
		Laser* tempRef = gameValues::laserList[i];
		if (tempRef->getPos()[1] <= 0 - tempRef->m_Rect->m_Height) { //destroy laser
			gameValues::laserList.erase(gameValues::laserList.begin() + i);
			if (gameValues::left_rightMenu[0] != 0 || gameValues::left_rightMenu[1] != 0) {
				if (tempRef->getPos()[0] <= reference.getPos()[0]) {
					gameValues::left_rightMenu[0]--;
				}
				else {
					gameValues::left_rightMenu[1]--;
				}
			}
			tempRef->~Laser();
		}
	} //removes lasers

	for (int i = 0; i < gameValues::asteroidsList.size(); i++) { //checks laser/asteroid/player collisions
		Asteroid* tempRef = gameValues::asteroidsList[i];
		bool goNext = false;
		for (int q = 0; q < gameValues::laserList.size(); q++) {
			Laser* tempRefNested = gameValues::laserList[q];
			if (collision(tempRefNested->m_Rect, tempRef->m_Rect)) { //destroy laser collided asteroid
				//std::string scoreString = "SCORE: " + std::to_string(gameValues::score);
				//lblScorePTR->setText(scoreString);
				gameValues::score++;
				std::string scoreString = "SCORE: " + std::to_string(gameValues::score);
				windowComponentPTRContainer::lblScorePTR->setText(scoreString);
				Mix_PlayChannelTimed(-1, windowComponentPTRContainer::windowPTR->explosion_effect, 1, 350);
				gameValues::laserList.erase(gameValues::laserList.begin() + q);
				if (gameValues::left_rightMenu[0] != 0 || gameValues::left_rightMenu[1] != 0) {
					if (tempRefNested->getPos()[0] <= reference.getPos()[0]) {
						gameValues::left_rightMenu[0]--;
					}
					else {
						gameValues::left_rightMenu[1]--;
					}
				}
				tempRefNested->~Laser();

				gameValues::asteroidsList.erase(gameValues::asteroidsList.begin() + i);
				tempRef->~Asteroid();
				goNext = true;
			}
		}

		if (collision(windowComponentPTRContainer::playerPTR, tempRef->m_Rect)) { //checks asteroid/player collisions
			if (--gameValues::lives == 0) {
				loserResetAll();


				for (int p = gameValues::asteroidsList.size() - 1; p >= 0; p--) {
					Asteroid* tempLast = gameValues::asteroidsList[p];
					gameValues::asteroidsList.erase(gameValues::asteroidsList.begin() + p);
					tempLast->~Asteroid();
				}

				for (int p = gameValues::laserList.size() - 1; p >= 0; p--) {
					Laser* tempLast = gameValues::laserList[p];
					gameValues::laserList.erase(gameValues::laserList.begin() + p);
					tempLast->~Laser();
				}

				for (int p = gameValues::heartList.size() - 1; p >= 0; p--) {
					Heart* tempLast = gameValues::heartList[p];
					gameValues::heartList.erase(gameValues::heartList.begin() + p);
					tempLast->~Heart();
				}
				return;
			}
			else {
				Heart* tempHeart = gameValues::heartList[gameValues::heartList.size() - 1];
				gameValues::heartList.erase(gameValues::heartList.begin() + gameValues::heartList.size() - 1);
				tempHeart->~Heart();

				gameValues::asteroidsList.erase(gameValues::asteroidsList.begin() + i);
				tempRef->~Asteroid();
				continue;
			}

		}
		if (goNext) {
			continue;
		}
		if (tempRef->getPos()[1] >= windowValues::windowHeight + tempRef->m_Rect->m_Height) { //destroy asteroid
			gameValues::asteroidsList.erase(gameValues::asteroidsList.begin() + i);
			tempRef->~Asteroid();
			if (--gameValues::lives == 0) {
				loserResetAll();

				for (int p = gameValues::asteroidsList.size() - 1; p >= 0; p--) {
					Asteroid* tempLast = gameValues::asteroidsList[p];
					gameValues::asteroidsList.erase(gameValues::asteroidsList.begin() + p);
					tempLast->~Asteroid();
				}

				for (int p = gameValues::laserList.size() - 1; p >= 0; p--) {
					Laser* tempLast = gameValues::laserList[p];
					gameValues::laserList.erase(gameValues::laserList.begin() + p);
					tempLast->~Laser();
				}

				for (int p = gameValues::heartList.size() - 1; p >= 0; p--) {
					Heart* tempLast = gameValues::heartList[p];
					gameValues::heartList.erase(gameValues::heartList.begin() + p);
					tempLast->~Heart();
				}
				return;
			}
			else {
				Heart* tempHeart = gameValues::heartList[gameValues::heartList.size() - 1];
				gameValues::heartList.erase(gameValues::heartList.begin() + gameValues::heartList.size() - 1);
				tempHeart->~Heart();
				continue;
			}
		}
	}


	if ((SDL_GetTicks() - gameValues::lastMoveMS) / 1000.0 >= gameValues::epsilon) {
		for (int i = 0; i < gameValues::asteroidsList.size(); i++) {
			Asteroid* tempRef = gameValues::asteroidsList[i];
			tempRef->setPos(tempRef->getPos()[0], tempRef->getPos()[1] + tempRef->speed);
		}

		int* tempPos = windowComponentPTRContainer::backgroundPTR->getPos();
		int* tempPos1 = windowComponentPTRContainer::background1PTR->getPos();
		if (tempPos1[1] < tempPos[1] && tempPos1[1] > 0) {
			windowComponentPTRContainer::backgroundPTR->setPos(tempPos[0], tempPos1[1] - windowValues::windowHeight);
			if (gameValues::first_time) {
				windowComponentPTRContainer::backgroundPTR->changeImage(gameValues::img_path);
				//gameValues::first_time = false;
			}
		}
		else if (tempPos[1] < tempPos1[1] && tempPos[1] > 0) {
			windowComponentPTRContainer::background1PTR->setPos(tempPos1[0], tempPos[1] - windowValues::windowHeight);
			if (gameValues::first_time) {
				windowComponentPTRContainer::background1PTR->changeImage(gameValues::img_path);
				gameValues::first_time = false;
			}
		}
		else {
			windowComponentPTRContainer::backgroundPTR->setPos(tempPos[0], tempPos[1] + gameValues::backgroundSpeed * (!gameValues::first_time ? 1 : 4));
			windowComponentPTRContainer::background1PTR->setPos(tempPos1[0], tempPos1[1] + gameValues::backgroundSpeed * (!gameValues::first_time ? 1 : 4));
		}


		for (int i = 0; i < gameValues::laserList.size(); i++) {
			Laser* tempRef = gameValues::laserList[i];
			tempRef->setPos(tempRef->getPos()[0], tempRef->getPos()[1] - tempRef->speed);
		}
		tempPos = windowComponentPTRContainer::playerPTR->getPos();
		int newTempPos[2] = { tempPos[0],tempPos[1] };
		if (tempPos[1] >= windowValues::windowHeight - windowValues::playerHeight - ADJUSTMENT_FACTOR * 2 - windowComponentPTRContainer::lblFPSPTR->m_TextRect.h) {
			newTempPos[1] -= 4;
		}
		if (windowValues::mousePos[0] < tempPos[0] + windowComponentPTRContainer::playerPTR->m_Width / 2) {
			newTempPos[0] -= (abs(windowValues::mousePos[0] - (newTempPos[0] + windowComponentPTRContainer::playerPTR->m_Width / 2)) < ADJUSTMENT_FACTOR) ? abs(windowValues::mousePos[0] - (newTempPos[0] + windowComponentPTRContainer::playerPTR->m_Width / 2)) : ADJUSTMENT_FACTOR;
		}
		if (windowValues::mousePos[0] > tempPos[0] + windowComponentPTRContainer::playerPTR->m_Width / 2) {
			newTempPos[0] += (abs(windowValues::mousePos[0] - (newTempPos[0] + windowComponentPTRContainer::playerPTR->m_Width / 2)) < ADJUSTMENT_FACTOR) ? abs(windowValues::mousePos[0] - (newTempPos[0] + windowComponentPTRContainer::playerPTR->m_Width / 2)) : ADJUSTMENT_FACTOR;
		}
		windowComponentPTRContainer::playerPTR->setPos(newTempPos[0], newTempPos[1]);

		gameValues::lastMoveMS = SDL_GetTicks();
	}

}


//draw helper methods
void drawHearts() {
	for (int i = 0; i < gameValues::heartList.size(); i++) {
		gameValues::heartList[i]->draw();
	}
}
void drawAsteroids() {
	for (int i = 0; i < gameValues::asteroidsList.size(); i++) {
		gameValues::asteroidsList[i]->m_Rect->draw();
	}
}
void drawLasers() {
	for (int i = 0; i < gameValues::laserList.size(); i++) {
		gameValues::laserList[i]->m_Rect->draw();
	}
}