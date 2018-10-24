#include "animations.h"

namespace flappybird {
	namespace animations {

		Texture2D gameplay_bg;
		Texture2D stars_1;
		Texture2D stars_2;
		Color stars_1_color;
		Color stars_2_color;
		static float timer;
		static float delayTime = 0.01f;
		bool exchange_texture;

		void init() {
			gameplay_bg = LoadTexture("res/Textures/GAMEPLAY_BG.png");
			stars_1 = LoadTexture("res/Textures/STARS_1.png");
			stars_2 = LoadTexture("res/Textures/STARS_2.png");
			stars_1_color = WHITE;
			stars_2_color = WHITE;
			stars_1_color.a = 0;
			stars_2_color.a = 0;
			exchange_texture = false;
		}

		void update() {
			timer += GetFrameTime();
			if (timer > delayTime && exchange_texture == false) {
				if (stars_1_color.a < 255) {
					for (int i = 0; i < 255; i++) {
						stars_1_color.a++;
						timer = 0.0f;
						break;
					}
				}
				if (stars_1_color.a >= 254) {
					for (int i = 0; i <= 255; i--) {
						stars_1_color.a--;
						timer = 0.0f;
						break;
					}
					if (stars_1_color.a <= 0) {
						exchange_texture == true;
						timer = 0.0f;
					}
				}
			}
			if (timer > delayTime && exchange_texture == true) {
				if (stars_2_color.a < 255) {
					for (int i = 0; i <= 255; i++) {
						stars_2_color.a++;
						timer = 0.0f;
						break;
					}
				}
				else if (stars_2_color.a >= 255) {
					for (int i = 0; i <= 255; i++) {
						stars_2_color.a--;
						timer = 0.0f;
						break;
					}
					if (stars_2_color.a <= 0) {
						exchange_texture == false;
						timer = 0.0f;
					}
				}
			}
		}

		void draw() {
			DrawTexture(gameplay_bg, 0, 0, WHITE);
			if (exchange_texture == false) {
				DrawTexture(stars_1, 0, 0, stars_1_color);
			}
			else {
				DrawTexture(stars_2, 0, 0, stars_2_color);
			}
		}

		void deInit() {
			UnloadTexture(gameplay_bg);
			UnloadTexture(stars_1);
			UnloadTexture(stars_2);
		}
	}
}