#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "raylib.h"

namespace flappybird {
	namespace gameplay {
		void init();
		void update();
		void draw();
		void deInit();

		extern bool pause;
		extern bool tutorial;
		extern float timer;
		extern float startWaitTime;
	}
}
#endif // !GAMEPLAY_H


