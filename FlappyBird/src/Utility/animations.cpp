#include "animations.h"

#include "Characters\Player\player.h"

namespace flappybird {
	namespace animations {

		PXTEX gameplay_bg;
		PXTEX gameplay_ground;
		Rectangle ground_collider;
		int COLLIDER_GROUND_ADJUSTMENT = 15;

		float generalSpeedTime = 0.02f;

		float timer;

		void init() {

			gameplay_bg.texture = LoadTexture("res/Textures/GAMEPLAY_BG.png");		
			gameplay_bg.pos = { 0,0 };
			gameplay_bg.speed = 200;
			gameplay_ground.texture = LoadTexture("res/Textures/GAMEPLAY_GROUND.png");
			gameplay_ground.pos = { 0,(float)GetScreenHeight() - (float)gameplay_ground.texture.height + (float)gameplay_ground.texture.height/2 };
			gameplay_ground.speed = 500;

			ground_collider.height = gameplay_ground.texture.height;
			ground_collider.width = gameplay_ground.texture.width;
			ground_collider.x = gameplay_ground.pos.x;
			ground_collider.y = gameplay_ground.pos.y + COLLIDER_GROUND_ADJUSTMENT;

			timer = 0;
		}

		void update() {
			timer += GetFrameTime();
			if (!players::isDead) {
				gameplay_bg.pos.x -= gameplay_bg.speed * GetFrameTime();
				gameplay_ground.pos.x -= gameplay_ground.speed * GetFrameTime();
			}		
		}

		void draw() {
			parallaxFX(gameplay_ground.texture, gameplay_ground.pos);
		#ifdef _DEBUG
			DrawRectangleLinesEx(ground_collider, 2, GREEN);
		#endif // DEBUG

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

		void drawBG() {
			parallaxFX(gameplay_bg.texture, gameplay_bg.pos);
		}
	}
}