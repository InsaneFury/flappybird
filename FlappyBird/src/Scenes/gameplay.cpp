#include "gameplay.h"

#include "Utility\pause_menu.h"
#include "Logic/game.h"
#include "Utility/animations.h"
#include "Characters\Player\player.h"
#include "Characters\Enemys\columns.h"
#include "Utility\buttons.h"
#include "Scenes\gameOver.h"
#include <iostream>

namespace flappybird {
	namespace gameplay {

		bool pause = false;
		bool tutorial = true;
		bool playersAreDead = false;

		float startWaitTime = 4;
		float timer = startWaitTime;

		Texture2D gameplay_vintage;
		Texture2D gameplay_SP_PC;
		Texture2D gameplay_SP_JS;
		Texture2D gameplay_MP_PC;
		Texture2D gameplay_MP_JS;

		buttons::BTNTEX pause_btn;

		Vector2 mousePoint;

		void init() {
			pause_btn.btn_texture = LoadTexture("res/assets/Textures/PAUSE_BTN.png");
			pause_btn.btnOnHover_texture = LoadTexture("res/assets/Textures/PAUSEONHOVER_BTN.png");
			buttons::createButton(pause_btn, pause_btn.btn_texture.height, pause_btn.btn_texture.width, 
				                 (float)(GetScreenWidth() - pause_btn.btn_texture.width - pause_btn.btn_texture.width/2), 
				                 (float)(pause_btn.btn_texture.height/2), WHITE);

			gameplay_vintage = LoadTexture("res/assets/Textures/VINTAGE.png");
			gameplay_SP_PC = LoadTexture("res/assets/Textures/SP_PC.png");
			gameplay_SP_JS = LoadTexture("res/assets/Textures/SP_JS.png");
			gameplay_MP_PC = LoadTexture("res/assets/Textures/MP_PC.png");
			gameplay_MP_JS = LoadTexture("res/assets/Textures/MP_JS.png");
			
			players::init();
			columns_enemys::init();
			animations::init();
			pause_menu::init();
			gameOver::init();
		}

		void update() {
			
			if (!game::isGameOver){
				if (!tutorial) {
					timer -= GetFrameTime();
				}
				if (game::multiplayerOn) {
					playersAreDead = players::player.isDead && players::player2.isDead;
				}
				else {
					playersAreDead = players::player.isDead;
				}

				mousePoint = GetMousePosition();
				if (!pause && !playersAreDead && !tutorial && (timer < 0)) {
					if (game::joystick) {
						if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_RIGHT)) {
							pause = !pause;
						}
					}
					if (IsKeyPressed(KEY_ESCAPE)) {
						pause = !pause;
					}
					buttons::isMouseOverButton(pause_btn);
					if (CheckCollisionPointRec(mousePoint, pause_btn.size))
					{
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							pause = !pause;
						}
					}
				}

				if (IsKeyPressed(KEY_W) || IsGamepadButtonReleased(GAMEPAD_PLAYER1,GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					tutorial = false;
				}
		
				if ((!pause && !tutorial) && (timer < 0)){
					animations::update();
					players::update();
					columns_enemys::update();
				}
				else if((!playersAreDead && !tutorial) && (timer < 0)) {
					pause_menu::update();
				}
				if (playersAreDead) {
					gameOver::checkHiScore();
					timer = startWaitTime;
					gameOver::update();
				}
			}
		}

		void draw() {
			if (tutorial) {
				if (game::joystick && !game::multiplayerOn) {
					DrawTexture(gameplay_SP_JS, 0, 0, WHITE);
				}
				else if (game::joystick && game::multiplayerOn) {
					DrawTexture(gameplay_MP_JS, 0, 0, WHITE);
				}
				else if (!game::joystick && !game::multiplayerOn) {
					DrawTexture(gameplay_SP_PC, 0, 0, WHITE);
				}
				else if (!game::joystick && game::multiplayerOn) {
					DrawTexture(gameplay_MP_PC, 0, 0, WHITE);
				}	
			}
			else {
				animations::drawBG();	
				columns_enemys::draw();

				DrawText(FormatText("SCORE: %02i", players::player.score), 
					     GetScreenWidth() / 2 - MeasureText("SCORE: 00", 40) / 2, 50, 40, YELLOW);

				if (timer > 0) {
					DrawText(FormatText("%02i", static_cast<int>(timer)),
						GetScreenWidth() / 2 - MeasureText("00", 80) / 2, GetScreenHeight() / 2 - MeasureText("00", 80) / 2, 80, YELLOW);
				}
				else {
					players::draw();
				}
				animations::draw();
				if (!pause && !playersAreDead && (timer < 0)) {
					buttons::draw(pause_btn);
				}

				if (pause && !playersAreDead && (timer < 0)) {
					pause_menu::draw();
				}

				if (playersAreDead) {
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

			#ifndef AUDIO
				players::deInit();
			#endif // !AUDIO

			columns_enemys::deInit();
			UnloadTexture(gameplay_vintage);
			UnloadTexture(gameplay_SP_PC);
			UnloadTexture(pause_btn.btn_texture);
		}

	}
}

