#ifndef GAME_H
#define GAME_H

#include "raylib.h"

//#define AUDIO

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
		extern Music bgMusic;
		void runGame();
	}
}
#endif // !GAME_H



