#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "raylib.h"

	namespace flappybird {
		namespace animations {
			
			struct PXTEX{
				Texture2D texture;
				Vector2 pos;
				int speed;
			};

			extern Rectangle ground_collider;
			
			void init();
			void update();
			void draw();
			void deInit();
			void parallaxFX(Texture2D texture, Vector2 &position);
		}
	}
#endif // !ANIMATIONS_H