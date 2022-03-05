#pragma once
#include "Asteroid.h"
#include "Laser.h"
#include "Heart.h"
#include <vector>
#include <string>

struct gameValues { //put in seperate file
public:
	static bool gameActive;
	static bool paused;

	static float backgroundSpeed;

	static std::vector<Asteroid*> asteroidsList;
	static unsigned int maxAsteroidSpawnCount;
	static int asteroidsSpawned;
	static uint32_t lastSpawn;
	static double spawnInterval;

	static std::vector<Laser*> laserList;
	//max lasers shootable?
	static std::vector<Heart*> heartList;
	static int lives;

	static unsigned int menuLaserCount;
	static int left_rightMenu[2];

	static uint32_t startMS;
	static uint32_t lastMoveMS;

	static int score;

	static const double epsilon;

	static std::string img_path;

	static bool first_time;

	static int laserSize[2];
	static int laserMax;

	static int asteroidWidth[2];
	static int asteroidHeight[2];

	static int level;
};