#include "gameplay.h"

#include "Utility\pause_menu.h"
#include "Logic/game.h"
#include "Utility/animations.h"
#include "Characters\Player\player.h"
#include "Characters\Enemys\columns.h"
#include "Utility\buttons.h"
#include "Scenes\victory.h"

namespace flappybird {
	namespace gameplay {

		bool pause = false;
		bool tutorial = true;

		Texture2D gameplay_vintage;
		Texture2D gameplay_tutorial;

		buttons::BTNTEX pause_btn;

		Vector2 mousePoint;

		void init() {
			pause_btn.btn_texture = LoadTexture("res/Textures/PAUSE_BTN.png");
			pause_btn.btnOnHover_texture = LoadTexture("res/Textures/PAUSEONHOVER_BTN.png");
			buttons::createButton(pause_btn, pause_btn.btn_texture.height, pause_btn.btn_texture.width, (float)(GetScreenWidth() - pause_btn.btn_texture.width - pause_btn.btn_texture.width/2), (float)(pause_btn.btn_texture.height/2), WHITE);

			gameplay_vintage = LoadTexture("res/Textures/VINTAGE.png");
			gameplay_tutorial = LoadTexture("res/Textures/tutorial.png");
			animations::init();
			players::init();
			columns_enemys::init();
			pause_menu::init();
			victory::init();

		}

		void update(bool &isGameOver) {

			if (!isGameOver){

				mousePoint = GetMousePosition();
				if (pause == false) {
					buttons::isMouseOverButton(pause_btn);
					if (CheckCollisionPointRec(mousePoint, pause_btn.size))
					{
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							pause = !pause;
						}
					}
				}
				if (IsKeyPressed(KEY_SPACE)) {
					tutorial = false;
				}
		
				if (!pause && tutorial == false){
					animations::update();
					players::update();
					columns_enemys::update();
				}
				else {
					pause_menu::update(isGameOver);
				}
				/*if (victory::isVictory()) {
					victory::update(isGameOver);
				}*/
			}
		}

		void draw() {
			if (tutorial) {		
				DrawTexture(gameplay_tutorial, 0, 0, WHITE);
			}
			else {
				animations::draw();
				players::draw();
				columns_enemys::draw();
				//DrawText(FormatText("SCORE: %02i", columns_enemys::destroyedMeteorsCount), GetScreenWidth() / 2 - MeasureText("SCORE: 00", 40) / 2, 50, 40, WHITE);
				if (pause == false) {
					buttons::draw(pause_btn);
				}

				if (pause) {
					pause_menu::draw();
				}
				/*if (victory::isVictory()) {
					victory::draw();
				}*/
			}
				
			

			BeginBlendMode(BLEND_MULTIPLIED);
			DrawTexture(gameplay_vintage, 0, 0, WHITE);
			EndBlendMode();
		}

		void deInit() {
			victory::deInit();
			pause_menu::deInit();
			animations::deInit();
			players::deInit();
			columns_enemys::deInit();
			UnloadTexture(gameplay_vintage);
			UnloadTexture(gameplay_tutorial);
			UnloadTexture(pause_btn.btn_texture);
		}
	}
}

