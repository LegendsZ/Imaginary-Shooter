#pragma once
#include <string>
#include <vector>

//audio files
const std::string menuSound_path = "res/mainmenuMP3.mp3";
const std::string gameSound_path = "";
const std::string laser_effect_path = "";
const std::string burning_effect_path = "";
const std::string explosion_effect_path = "res/explosionWAV.wav";
const std::string click_effect_path = "";

//images
const std::string playerPNG_path = "res/playerPNG.png";
const std::string mainMenuPNG_path = "res/mainmenuPNG.png";
const std::string laserPNG_path = "res/laserPNG.png";
const std::string asteroidPNG_path = "res/asteroidPNG.png";
const std::string background0_path = "res/background0PNG.png";
const std::string background1_path = "res/background1PNG.png";
const std::string background2_path = "res/background2PNG.png";
const std::string heartPNG_path = "res/heartPNG.png";

//fonts
const std::string comicFont_path = "res/comic.ttf";

//arrayForCheck
const std::vector<std::string> arrayFiles = {
	//audio
	menuSound_path,
	explosion_effect_path,

	//fonts
	comicFont_path,

	//pics
	playerPNG_path,
	mainMenuPNG_path,
	laserPNG_path,
	asteroidPNG_path,
	background0_path,
	background1_path,
	background2_path,
	heartPNG_path,

	//DLLS
	"libfreetype-6.dll",
	"libjpeg-9.dll",
	"libmpg123-0.dll",
	"libpng16-16.dll",
	"libtiff-5.dll",
	"libwebp-7.dll",
	"SDL2.dll",
	"SDL2_image.dll",
	"SDL2_mixer.dll",
	"SDL2_ttf.dll",
	"zlib1.dll"
};