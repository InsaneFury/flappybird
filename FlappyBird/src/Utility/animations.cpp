#include "animations.h"

namespace flappybird {
	namespace animations {

		PXTEX gameplay_bg;
		PXTEX gameplay_ground;
		Rectangle ground_collider;

		float timer;

		void init() {
			gameplay_bg.texture = LoadTexture("res/Textures/GAMEPLAY_BG.png");		
			gameplay_bg.pos = { 0,0 };
			gameplay_bg.speed = 2;
			gameplay_ground.texture = LoadTexture("res/Textures/GAMEPLAY_GROUND.png");
			gameplay_ground.pos = { 0,(float)GetScreenHeight() - (float)gameplay_ground.texture.height + (float)gameplay_ground.texture.height/2 };
			gameplay_ground.speed = 5;

			ground_collider.height = gameplay_ground.texture.height;
			ground_collider.width = gameplay_ground.texture.width;
			ground_collider.x = gameplay_ground.pos.x;
			ground_collider.y = gameplay_ground.pos.y;

			timer = 0;
		}

		void update() {
			timer += GetFrameTime();
			if (timer > 0.02) {
				timer = 0;
				gameplay_bg.pos.x -= gameplay_bg.speed;
				gameplay_ground.pos.x -= gameplay_ground.speed;
				ground_collider.x = gameplay_ground.pos.x;
			}		
		}

		void draw() {
			parallaxFX(gameplay_bg.texture, gameplay_bg.pos);
			parallaxFX(gameplay_ground.texture, gameplay_ground.pos);
		}

		void deInit() {
			UnloadTexture(gameplay_bg.texture);
			UnloadTexture(gameplay_ground.texture);
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