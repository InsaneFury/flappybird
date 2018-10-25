#include "columns.h"

#include <cmath>
#include <iostream>

namespace flappybird {
	namespace columns_enemys {
		using namespace std;

		const int colUpAmount = 5;
		const int colDownAmount = 5;
		Column columnsUp[colUpAmount];
		Column columnsDown[colDownAmount];
		int addDist;
		float time;

		void init() {

			time = 0;
			addDist = 0;

			for (int i = 0; i < colUpAmount; i++) {
				columnsUp[i].texture = LoadTexture("res/Textures/COLUMN.png");
				columnsUp[i].position.x = GetScreenWidth() + 50 + addDist;
				columnsUp[i].position.y = GetScreenHeight() - columnsUp[i].texture.height/2;
				columnsUp[i].collider.height = columnsUp[i].texture.height;
				columnsUp[i].collider.width = columnsUp[i].texture.width - columnsUp[i].texture.width/2;
				columnsUp[i].sourceRec.height = columnsUp[i].texture.height;
				columnsUp[i].sourceRec.width = columnsUp[i].texture.width;
				columnsUp[i].destRec = { columnsUp[i].position.x,columnsUp[i].position.y,(float)columnsUp[i].collider.width ,(float)columnsUp[i].collider.height };
				columnsUp[i].origin = { (float)columnsUp[i].collider.width/2 ,(float)columnsUp[i].collider.height/2 };
				columnsUp[i].rotation = 0;
				addDist += 20;
			}

			for (int i = 0; i < colDownAmount; i++) {
				columnsDown[i].texture = LoadTexture("res/Textures/COLUMN.png");
				columnsDown[i].position.x = GetScreenWidth() + 50 + addDist;
				columnsDown[i].position.y = 0 - columnsUp[i].texture.height / 2;
				columnsDown[i].collider.height = columnsDown[i].texture.height;
				columnsDown[i].collider.width = columnsDown[i].texture.width - columnsDown[i].texture.width / 2;
				columnsDown[i].sourceRec.width = columnsDown[i].texture.width;
				columnsDown[i].destRec = { columnsDown[i].position.x,columnsDown[i].position.y,(float)columnsDown[i].collider.width ,(float)columnsDown[i].collider.height };
				columnsDown[i].origin = { (float)columnsDown[i].collider.width / 2 ,(float)columnsDown[i].collider.height / 2 };
				columnsDown[i].rotation = 90;
				addDist += 20;
			}
		}

		void update() {
			time += GetFrameTime();
			if (time < 0.02) {
				for (int i = 0; i < colDownAmount; i++) {
				
					columnsDown[i].position.x += 5 * GetFrameTime();
					columnsDown[i].destRec = { columnsDown[i].position.x, columnsDown[i].position.y, (float)columnsDown[i].texture.width, (float)columnsDown[i].texture.height };
					cout << "INFO: down tower moving" << endl;
				}
				for (int i = 0; i < colUpAmount; i++) {

					columnsUp[i].position.x += 5 * GetFrameTime();
					columnsUp[i].destRec = { columnsUp[i].position.x, columnsUp[i].position.y, (float)columnsUp[i].texture.width, (float)columnsUp[i].texture.height };
					cout << "INFO: up tower moving" << endl;
				}
			}
		}

		void draw() {
			for (int i = 0; i < colDownAmount; i++) {
				DrawTexturePro(columnsDown[i].texture, columnsDown[i].sourceRec, columnsDown[i].destRec, columnsDown[i].origin, columnsDown[i].rotation, WHITE);
			}
			for (int i = 0; i < colUpAmount; i++) {
				DrawTexturePro(columnsUp[i].texture, columnsUp[i].sourceRec, columnsUp[i].destRec,columnsUp[i].origin, columnsUp[i].rotation,WHITE);
			}
		}

		void deInit() {
			for (int i = 0; i < colUpAmount; i++) {
				UnloadTexture(columnsUp[i].texture);
			}
			for (int i = 0; i < colDownAmount; i++) {
				UnloadTexture(columnsDown[i].texture);
			}
		}
	}
}
