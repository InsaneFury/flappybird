#include "gameplay.h"

#include "Utility\pause_menu.h"
#include "Logic/game.h"
#include "Utility/animations.h"
#include "Characters\Player\player.h"
#include "Characters\Enemys\columns.h"
#include "Utility\buttons.h"
#include "Scenes\gameOver.h"

namespace flappybird {
	namespace gameplay {

		bool pause = false;
		bool tutorial = true;

		Texture2D gameplay_vintage;
		Texture2D gameplay_tutorial;

		buttons::BTNTEX pause_btn;

		Vector2 mousePoint;

		void init() {
			pause_btn.btn_texture = LoadTexture("res/assets/Textures/PAUSE_BTN.png");
			pause_btn.btnOnHover_texture = LoadTexture("res/assets/Textures/PAUSEONHOVER_BTN.png");
			buttons::createButton(pause_btn, pause_btn.btn_texture.height, pause_btn.btn_texture.width, 
				                 (float)(GetScreenWidth() - pause_btn.btn_texture.width - pause_btn.btn_texture.width/2), 
				                 (float)(pause_btn.btn_texture.height/2), WHITE);

			gameplay_vintage = LoadTexture("res/assets/Textures/VINTAGE.png");
			gameplay_tutorial = LoadTexture("res/assets/Textures/tutorial.png");
			
			players::init();
			columns_enemys::init();
			animations::init();
			pause_menu::init();
			gameOver::init();
		}

		void update(bool &isGameOver) {

			if (!isGameOver){

				mousePoint = GetMousePosition();
				if (pause == false && players::isDead == false && tutorial == false) {
					buttons::isMouseOverButton(pause_btn);
					if (CheckCollisionPointRec(mousePoint, pause_btn.size))
					{
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							pause = !pause;
						}
					}
				}
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					tutorial = false;
				}
		
				if (!pause && tutorial == false){
					animations::update();
					players::update();
					columns_enemys::update();
				}
				else if(players::isDead == false && tutorial == false) {
					pause_menu::update(isGameOver);
				}
				if (players::isDead) {
					gameOver::update(isGameOver);
				}
			}
		}

		void draw() {
			if (tutorial) {		
				DrawTexture(gameplay_tutorial, 0, 0, WHITE);
			}
			else {
				animations::drawBG();	
				columns_enemys::draw();
				players::draw();
				animations::draw();

				DrawText(FormatText("SCORE: %02i", players::player.score), 
					     GetScreenWidth() / 2 - MeasureText("SCORE: 00", 40) / 2, 50, 40, WHITE);

				if (pause == false && players::isDead == false) {
					buttons::draw(pause_btn);
				}

				if (pause && players::isDead == false) {
					pause_menu::draw();
				}

				if (players::isDead) {
					gameOver::draw();
				}
			}
			BeginBlendMode(BLEND_MULTIPLIED);
			DrawTexture(gameplay_vintage, 0, 0, WHITE);
			EndBlendMode();
		}

		void deInit() {
			gameOver::deInit();
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

