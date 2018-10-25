#include "animations.h"

namespace flappybird {
	namespace animations {

		PXTEX gameplay_bg;

		float timer;

		void init() {
			gameplay_bg.texture = LoadTexture("res/Textures/GAMEPLAY_BG.png");		
			gameplay_bg.pos = { 0,0 };
			gameplay_bg.speed = 5;
			timer = 0;
		}

		void update() {
			timer += GetFrameTime();
			if (timer > 0.02) {
				timer = 0;
				gameplay_bg.pos.x -= gameplay_bg.speed;
			}		
		}

		void draw() {
			parallaxFX(gameplay_bg.texture, gameplay_bg.pos);
		}

		void deInit() {
			UnloadTexture(gameplay_bg.texture);
		}

		void parallaxFX(Texture2D texture, Vector2 &position) {		
			DrawTexture(texture, position.x, position.y, WHITE);
			DrawTexture(texture, position.x + texture.width, position.y, WHITE);		
			if (position.x <= -texture.width) {
				position.x = 0;
			}
		}
	}
}