#include "gameValues.h"

unsigned int gameValues::maxAsteroidSpawnCount = 2;
double gameValues::spawnInterval = 3;
int gameValues::laserMax = 2;

int gameValues::laserSize[2] = { 15,75 };
bool gameValues::first_time = true;
std::string gameValues::img_path;
float gameValues::backgroundSpeed = 1;

uint32_t gameValues::startMS = 0;;
uint32_t gameValues::lastMoveMS = 0;

int gameValues::score = 0;

const double gameValues::epsilon = 0.01;

bool gameValues::gameActive = false;
bool gameValues::paused = false;
unsigned int gameValues::menuLaserCount = 2;
std::vector<Asteroid*> gameValues::asteroidsList;
int gameValues::asteroidsSpawned = 0;
uint32_t gameValues::lastSpawn = 0;


std::vector<Laser*> gameValues::laserList;
std::vector<Heart*> gameValues::heartList;
int gameValues::left_rightMenu[] = { 0,0 };

int gameValues::asteroidHeight[2] = { 50,100 };
int gameValues::asteroidWidth[2] = { 20,50 };

int gameValues::lives = 3;
int gameValues::level = 1;