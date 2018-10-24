#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

namespace flappybird {
	namespace players {
		struct Player {
			Texture2D texture;
			Vector2 position;
			Vector2 speed;
			Color color;
			float radius;
			float rotation;
			Vector2 acceleration;
			int score;
			//Stuff to use DrawTexturePro
			// NOTE: Source rectangle (part of the texture to use for drawing)
			Rectangle sourceRec;
			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			Rectangle destRec;
			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			Vector2 origin;
		};

		extern Player player;
		extern float PLAYER_SPEED;

		void init();
		void update();
		void draw();
		void deInit();
	}
}
#endif // !PLAYER_H
