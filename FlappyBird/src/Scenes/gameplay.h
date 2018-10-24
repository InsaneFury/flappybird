#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace flappybird {
	namespace gameplay {
		void init();
		void update(bool &isGameOver);
		void draw();
		void deInit();

		extern bool pause;
		extern bool tutorial;
	}
}
#endif // !GAMEPLAY_H


