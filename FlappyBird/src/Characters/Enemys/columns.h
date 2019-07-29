#ifndef COLUMNS_H
#define COLUMNS_H

#include "raylib.h"

namespace flappybird {
	namespace columns_enemys {		

		struct Column{
			Texture2D texture;
			Vector2 position;
			Rectangle collider;
			bool checkP1;
			bool checkP2;
			//Stuff to use DrawTexturePro
			// NOTE: Source rectangle (part of the texture to use for drawing)
			Rectangle sourceRec;
			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			Rectangle destRec;
			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			Vector2 origin;
		};

		void init();
		void update();
		void draw();
		void deInit();

	}
}
#endif // !COLUMNS_H