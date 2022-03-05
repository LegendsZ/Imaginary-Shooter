#pragma once

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

#define BTNPLAY_WIDTH 220
#define BTNPLAY_HEIGHT 100

#define PLAYER_WIDTH 75
#define PLAYER_HEIGHT 75

#define DEFAULT_FRAME_CAP 100

#define DEFAULT_VOLUME_LEVEL 50

#define ADJUSTMENT_FACTOR 25

struct windowValues {
public:
	static int windowWidth;
	static int windowHeight;

	static int btnPlayWidth;
	static int btnPlayHeight;

	static int playerWidth;
	static int playerHeight;

	static bool resetValues() {
		windowValues::windowWidth = WINDOW_WIDTH;
		windowValues::windowHeight = WINDOW_HEIGHT;

		windowValues::btnPlayWidth = BTNPLAY_WIDTH;
		windowValues::btnPlayHeight = BTNPLAY_HEIGHT;

		volumeLevel = DEFAULT_VOLUME_LEVEL;

		int playerWidth = PLAYER_WIDTH;
		int playerHeight = PLAYER_HEIGHT;

		mousePos[0] = 0;
		mousePos[1] = 0;

		framesCount = 0;
		framesCap = DEFAULT_FRAME_CAP;
		return true;
	}
	static bool showMenu;
	static int mousePos[2];

	static int framesCount;
	static int framesCap;

	static int volumeLevel;
};