#include "columns.h"

#include <cmath>
#include <iostream>

#include "Utility\animations.h"

namespace flappybird {
	namespace columns_enemys {
		using namespace std;
		using namespace animations;

		static const unsigned int COL_GAP = 150;
		static const unsigned int COL_SPEED = 300;
		static const unsigned int BIRD_GAP = 215;
		static const unsigned int MIN_RAND = 0;
		static const unsigned int MAX_RAND = 250;

		const int totalCols = 8;
		Column columnsUp[totalCols];
		Column columnsDown[totalCols];
		int random;
		float time;

		void init() {

			time = 0;

			for (int i = 0; i < totalCols; i++) {
				random = GetRandomValue(MIN_RAND, MAX_RAND);

				//Up Cols
				columnsUp[i].texture = LoadTexture("res/Textures/BOTTOM_COLUMN.png");

				columnsUp[i].position.x = GetScreenWidth() + COL_GAP + (COL_GAP + columnsUp[i].texture.width) * i;
				columnsUp[i].position.y = 0 - random;

				columnsUp[i].collider.height = columnsUp[i].texture.height;
				columnsUp[i].collider.width = columnsUp[i].texture.width - columnsUp[i].texture.width/2;

				//Down Cols
				columnsDown[i].texture = LoadTexture("res/Textures/TOP_COLUMN.png");

				columnsDown[i].position.x = GetScreenWidth() + COL_GAP + (COL_GAP + columnsUp[i].texture.width) * i;
				columnsDown[i].position.y = columnsUp[i].position.y + columnsUp[i].texture.height + BIRD_GAP;

				columnsDown[i].collider.height = columnsUp[i].texture.height;
				columnsDown[i].collider.width = columnsUp[i].texture.width - columnsUp[i].texture.width / 2;

			}
		
		}

		void update() {
			for (int i = 0; i < totalCols; i++) {
				random = GetRandomValue(MIN_RAND, MAX_RAND);
				
				columnsUp[i].position.x -= COL_SPEED * GetFrameTime();
				columnsDown[i].position.x -= COL_SPEED * GetFrameTime();

				columnsUp[i].collider.x = (int)columnsUp[i].position.x;
				columnsUp[i].collider.y = (int)columnsUp[i].position.y;

				columnsDown[i].collider.x = (int)columnsDown[i].position.x;
				columnsDown[i].collider.y = (int)columnsDown[i].position.y;


				if (columnsUp[i].position.x + columnsUp[i].texture.width <= 0) {
					// recicle up
					columnsUp[i].position.y = 0 - random;
					columnsUp[i].position.x = GetScreenWidth() + COL_GAP * 3;

					// recicle down
					columnsDown[i].position.y = columnsUp[i].position.y + columnsUp[i].texture.height + BIRD_GAP;
					columnsDown[i].position.x = GetScreenWidth() + COL_GAP * 3;
				}
			}			
		}

		void draw() {
			
			for (int i = 0; i < totalCols; i++) {
				DrawTextureV(columnsUp[i].texture,columnsUp[i].position,WHITE);
				DrawTextureV(columnsDown[i].texture, columnsDown[i].position, WHITE);
			}
		}

		void deInit() {
			for (int i = 0; i < totalCols; i++) {
				UnloadTexture(columnsUp[i].texture);
				UnloadTexture(columnsDown[i].texture);
			}
		}
	}
}
