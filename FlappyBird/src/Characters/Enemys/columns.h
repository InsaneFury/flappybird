#ifndef COLUMNS_H
#define COLUMNS_H

#include "raylib.h"

namespace flappybird {
	namespace columns_enemys {		

		struct Column{
			Texture2D texture;
			Vector2 position;
			Rectangle collider;
			int rotation;
		};

		void init();
		void update();
		void draw();
		void deInit();

	}
}
#endif // !COLUMNS_H