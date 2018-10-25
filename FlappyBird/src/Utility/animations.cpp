#include "animations.h"

namespace flappybird {
	namespace animations {

		Texture2D gameplay_bg;

		Vector2 originPoint;
		Vector2 destPoint;

		float timer;
		int parallaxSpeed;

		void init() {
			gameplay_bg = LoadTexture("res/Textures/GAMEPLAY_BG.png");		
			originPoint = { 0,0 };
			timer = 0;
			parallaxSpeed = 5;
		}

		void update() {
			timer += GetFrameTime();
			if (timer > 0.02) {
				timer = 0;
				originPoint.x -= parallaxSpeed;
			}		
		}

		void draw() {
			parallaxFX(gameplay_bg, originPoint);
		}

		void deInit() {
			UnloadTexture(gameplay_bg);
		}

		void parallaxFX(Texture2D texture, Vector2 &originPoint) {		
			DrawTexture(texture, originPoint.x, originPoint.y, WHITE);
			DrawTexture(texture, originPoint.x + texture.width, originPoint.y, WHITE);		
			if (originPoint.x <= -texture.width) {
				originPoint.x = 0;
			}
		}
	}
}