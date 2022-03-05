#pragma once
#include "Button.h"

//ptrs to hold window components
class windowComponentPTRContainer {
private:
public:
	static Window* windowPTR;
	static Rect* backgroundPTR;
	static Rect* background1PTR ;
	static Rect* playerPTR;
	static Text* lblScorePTR;
	static Text* lblFPSPTR;
	static Text* lblTimePTR;
	static Text* lblLevelPTR;
	static Button* btnPlayPTR;
	static Button* btnExitPTR;
};