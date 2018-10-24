#ifndef GUN_H
#define GUN_H

#include "raylib.h"

namespace flappybird {
	namespace gun {
		struct Shoot {
			Texture2D texture;
			Vector2 position;
			Vector2 speed;
			float radius;
			float rotation;
			int lifeSpawn;
			bool active;
			Color color;
			//Stuff to use DrawTexturePro
			// NOTE: Source rectangle (part of the texture to use for drawing)
			Rectangle sourceRec;
			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			Rectangle destRec;
			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			Vector2 origin;
		};

		extern const int PLAYER_MAX_SHOOTS;
		Shoot shoot[];

		void init();
		void update();
		void draw();
		void deInit();
	}
}
#endif // !GUN_H



