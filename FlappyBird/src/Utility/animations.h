#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "raylib.h"

	namespace flappybird {
		namespace animations {
			void init();
			void update();
			void draw();
			void deInit();
			void parallaxFX(Texture2D texture, Vector2 &originPoint);
		}
	}
#endif // !ANIMATIONS_H