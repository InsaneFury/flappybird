#include "columns.h"

#include "Utility\animations.h"
#include "Characters\Player\player.h"

namespace flappybird {
	namespace columns_enemys {
		using namespace std;
		using namespace animations;
		using namespace players;

		static const int COL_INTERNAL_SPACE = 20;
		static const unsigned int COL_GAP = 150;
		static const unsigned int COL_SPEED = 300;
		static const unsigned int BIRD_GAP = 215;
		static const unsigned int MIN_RAND = 0;
		static const unsigned int MAX_RAND = 250;

		const int totalCols = 8;
		Column columnsUp[totalCols];
		Column columnsDown[totalCols];
		int random;

		void init() {
			
			for (int i = 0; i < totalCols; i++) {
				random = GetRandomValue(MIN_RAND, MAX_RAND);

				//Up Cols
				columnsUp[i].texture = LoadTexture("res/assets/Textures/COLUMN.png");

				columnsUp[i].position.x = GetScreenWidth() + COL_GAP + (COL_GAP + columnsUp[i].texture.width) * i;
				columnsUp[i].position.y = 0 - random;

				columnsUp[i].collider.height = columnsUp[i].texture.height;
				columnsUp[i].collider.width = columnsUp[i].texture.width;
				columnsUp[i].collider.x = 0;
				columnsUp[i].collider.y = 0;

				columnsUp[i].sourceRec = { 0.0f, 0.0f, (float)columnsUp[i].texture.width, 
													   (float)columnsUp[i].texture.height };

				columnsUp[i].destRec = { columnsUp[i].position.x, columnsUp[i].position.y, 
										(float)columnsUp[i].texture.width,(float)columnsUp[i].texture.height };

				columnsUp[i].origin = { 0,0 };

				columnsUp[i].check = false;

				//Down Cols
				columnsDown[i].texture = LoadTexture("res/assets/Textures/COLUMN.png");

				columnsDown[i].position.x = GetScreenWidth() + COL_GAP + (COL_GAP + columnsUp[i].texture.width) * i;
				columnsDown[i].position.y = columnsUp[i].position.y + columnsUp[i].texture.height + BIRD_GAP;

				columnsDown[i].collider.height = columnsUp[i].texture.height;
				columnsDown[i].collider.width = columnsUp[i].texture.width;
				columnsDown[i].collider.x = 0;
				columnsDown[i].collider.y = 0;

				columnsDown[i].sourceRec = { 0.0f, 0.0f, (float)columnsDown[i].texture.width,
													   (float)columnsDown[i].texture.height };

				columnsDown[i].destRec = { columnsDown[i].position.x, columnsDown[i].position.y,
										(float)columnsDown[i].texture.width,(float)columnsDown[i].texture.height };

				columnsDown[i].origin = { (float)columnsDown[i].texture.width,
										(float)columnsDown[i].texture.height };

				columnsDown[i].check = false;
			}
		}

		void update() {
			if (!isDead) {
				for (int i = 0; i < totalCols; i++) {
					//Movement
					random = GetRandomValue(MIN_RAND, MAX_RAND);

					columnsUp[i].position.x -= COL_SPEED * GetFrameTime();
					columnsDown[i].position.x -= COL_SPEED * GetFrameTime();

					columnsUp[i].collider.x = (int)columnsUp[i].position.x;
					columnsUp[i].collider.y = (int)columnsUp[i].position.y;

					columnsDown[i].collider.x = (int)columnsDown[i].position.x;
					columnsDown[i].collider.y = (int)columnsDown[i].position.y;
					
					//Collision
					if (CheckCollisionCircleRec(player.position,player.radius, columnsUp[i].collider)) {
						isDead = true;
					}

					if (CheckCollisionCircleRec(player.position, player.radius, columnsDown[i].collider)) {
						isDead = true;
					}

					if (columnsUp[i].position.x + columnsUp[i].texture.width < player.position.x && 
						!isDead && columnsUp[i].check == false) {
						columnsUp[i].check = true;
						player.score++;
					}

					//Recicle
					if (columnsUp[i].position.x + columnsUp[i].texture.width <= 0) {
						// recicle up
						columnsUp[i].position.y = 0 - random;
						columnsUp[i].position.x = GetScreenWidth() + COL_GAP * 3;
						columnsUp[i].check = false;

						// recicle down
						columnsDown[i].position.y = columnsUp[i].position.y + columnsUp[i].texture.height + BIRD_GAP;
						columnsDown[i].position.x = GetScreenWidth() + COL_GAP * 3;
						columnsDown[i].check = false;
					}

					columnsDown[i].destRec = { columnsDown[i].position.x, columnsDown[i].position.y,
										(float)columnsDown[i].texture.width,(float)columnsDown[i].texture.height };

					columnsUp[i].destRec = { columnsUp[i].position.x, columnsUp[i].position.y,
										(float)columnsUp[i].texture.width,(float)columnsUp[i].texture.height };
				}
			}
			
		}

		void draw() {
			
			for (int i = 0; i < totalCols; i++) {
				DrawTexturePro(columnsDown[i].texture, columnsDown[i].sourceRec,
					columnsDown[i].destRec, columnsDown[i].origin, 180, WHITE);
				DrawTexturePro(columnsUp[i].texture, columnsUp[i].sourceRec,
					columnsUp[i].destRec, columnsUp[i].origin, 0, WHITE);

			#ifdef _DEBUG
				//See colliders
				DrawRectangleLinesEx(columnsUp[i].collider, 2, GREEN);
				DrawRectangleLinesEx(columnsDown[i].collider, 2, GREEN);
			#endif // DEBUG
		
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
