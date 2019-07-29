#include "menu.h"

#include "Logic/game.h"
#include "Utility/buttons.h"

namespace flappybird {
	namespace menu {
		using namespace game;

		enum mainMenu {
			play_enum,
			multiplayer_enum,
			credits_enum,
			quit_enum
		}menu;

		static int menuPos = 0;

		//Images
		Texture2D menu_bg;
		Texture2D menu_title;

		Vector2 title_position;

		static buttons::BTNTEX play;
		static buttons::BTNTEX multiplayer;
		static buttons::BTNTEX credits;
		static buttons::BTNTEX quit;

		

		void init() {
			menu_bg = LoadTexture("res/assets/Textures/GAMEPLAY_BG.png");
			menu_title = LoadTexture("res/assets/Textures/TITLE_MENU.png");

			title_position = { (float)GetScreenWidth() / 2 - menu_title.width / 2,50 };

			play.btn_texture = LoadTexture("res/assets/Textures/PLAY_BTN.png");
			multiplayer.btn_texture = LoadTexture("res/assets/Textures/MULTIPLAYER_BTN.png"); 
			credits.btn_texture = LoadTexture("res/assets/Textures/CREDITS_BTN.png");
			quit.btn_texture = LoadTexture("res/assets/Textures/QUIT_BTN.png");

			play.btnOnHover_texture = LoadTexture("res/assets/Textures/PLAYONHOVER_BTN.png");
			multiplayer.btnOnHover_texture = LoadTexture("res/assets/Textures/MULTIPLAYERONHOVER_BTN.png"); 
			credits.btnOnHover_texture = LoadTexture("res/assets/Textures/CREDITSONHOVER_BTN.png");
			quit.btnOnHover_texture = LoadTexture("res/assets/Textures/QUITONHOVER_BTN.png");

			buttons::createButton(play, play.btn_texture.height, play.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - play.btn_texture.width / 2), 
				                 (float)(GetScreenHeight() - 400), WHITE);

			buttons::createButton(multiplayer, multiplayer.btn_texture.height, multiplayer.btn_texture.width,
				(float)(GetScreenWidth() / 2 - multiplayer.btn_texture.width / 2),
				(float)(GetScreenHeight() - 330), WHITE);

			buttons::createButton(credits, credits.btn_texture.height, credits.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - credits.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 260), WHITE);

			buttons::createButton(quit, quit.btn_texture.height, quit.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - quit.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 190), WHITE);

		}

		void update() {
			mouseInput();
			if (joystick) {
				joystickInput();
			}
		}

		void draw() {
			ClearBackground(WHITE);

			//Draw UI
			DrawTexture(menu_bg,0,0,WHITE);
			DrawTexture(menu_title, title_position.x, title_position.y, WHITE);

			//Draw buttons
			buttons::draw(play);
			buttons::draw(multiplayer);
			buttons::draw(credits);
			buttons::draw(quit);
			DrawText("v1.0", screenWidth - 50, screenHeight - 20, 20, WHITE);
		}

		void deInit() {
			//images
			UnloadTexture(menu_bg);
			UnloadTexture(menu_title);
			//buttons
			UnloadTexture(play.btn_texture);
			UnloadTexture(multiplayer.btn_texture);
			UnloadTexture(credits.btn_texture);
			UnloadTexture(quit.btn_texture);
			UnloadTexture(play.btnOnHover_texture);
			UnloadTexture(multiplayer.btnOnHover_texture);
			UnloadTexture(credits.btnOnHover_texture);
			UnloadTexture(quit.btnOnHover_texture);	
		}

		void mouseInput() {
			Vector2 mousePoint = GetMousePosition();

			buttons::isMouseOverButton(play);
			if (CheckCollisionPointRec(mousePoint, play.size)) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
				}
			}

			buttons::isMouseOverButton(multiplayer);
			if (CheckCollisionPointRec(mousePoint, multiplayer.size)) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
					multiplayerOn = true;
				}
			}

			buttons::isMouseOverButton(credits);
			if (CheckCollisionPointRec(mousePoint, credits.size)) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Credits;
				}
			}

			buttons::isMouseOverButton(quit);
			if (CheckCollisionPointRec(mousePoint, quit.size)) {
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					isGameOver = true;
				}
			}
		}

		void joystickInput() {

			if (IsGamepadButtonPressed(GAMEPAD_PLAYER1,GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
				if (menuPos > 2) {
					menuPos = 0;
				}
				else {
					menuPos++;
				}
				menu = static_cast<mainMenu>(menuPos);
			}
			if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
				if (menuPos <= 0) {
					menuPos = 3;
				}
				else {
					menuPos--;
				}
				menu = static_cast<mainMenu>(menuPos);
			}

			switch (menu){
			case play_enum:
				play.isHover = true;
				multiplayer.isHover = false;
				credits.isHover = false;
				quit.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					actualScene = Game;
				}
				
				break;
			case multiplayer_enum:
				multiplayer.isHover = true;
				play.isHover = false;
				quit.isHover = false;
				credits.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
				actualScene = Game;
				multiplayerOn = true;
				}
				break;
			case credits_enum:
				credits.isHover = true;
				play.isHover = false;
				multiplayer.isHover = false;
				quit.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
				actualScene = Credits;
				}
				break;
			case quit_enum:
				quit.isHover = true;
				play.isHover = false;
				multiplayer.isHover = false;
				credits.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
				isGameOver = true;
				}
				break;
			default:
				break;
			}
					
		}
	}
}

