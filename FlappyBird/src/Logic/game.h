#ifndef GAME_H
#define GAME_H

#include "raylib.h"

#define AUDIO

#if defined(PLATFORM_RPI)
#define XBOX360_NAME_ID     "Microsoft X-Box 360 pad"
#define PS3_NAME_ID         "PLAYSTATION(R)3 Controller"
#else
#define XBOX360_NAME_ID     "Xbox 360 Controller"
#define PS3_NAME_ID         "PLAYSTATION(R)3 Controller"
#endif

namespace flappybird {
	namespace game {
		extern int screenWidth;
		extern int screenHeight;

		enum ActualScene {
			Menu,
			Game,
			Gameover,
			Credits
		};

		extern ActualScene actualScene;
		extern bool multiplayerOn;
		extern bool joystick;
		extern bool isGameOver;
		extern Music bgMusic;
		void runGame();
	}
}
#endif // !GAME_H



