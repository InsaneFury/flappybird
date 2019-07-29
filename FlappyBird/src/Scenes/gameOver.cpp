#include "gameOver.h"

#include "gameplay.h"
#include "Logic/game.h"
#include "Utility/buttons.h"

namespace flappybird {
	namespace gameOver {
		using namespace game;
		using namespace gameplay;

		enum gameOverMenu {
			retry_enum,
			menu_enum,
			quit_enum
		}gMenu;

		static int menuPos = 0;

		//Images
		Texture2D gameover_bg;
		Texture2D gameover_title;

		Vector2 title_position;

		buttons::BTNTEX retry;
		buttons::BTNTEX menu;
		buttons::BTNTEX quit;

		void init() {
			gameover_bg = LoadTexture("res/assets/Textures/GAMEOVER_BG.png");
			gameover_title = LoadTexture("res/assets/Textures/GAMEOVER_TITLE.png");

			retry.btn_texture = LoadTexture("res/assets/Textures/RETRY_BTN.png");
			retry.btnOnHover_texture = LoadTexture("res/assets/Textures/RETRYONHOVER_BTN.png");
			menu.btn_texture = LoadTexture("res/assets/Textures/MENU_BTN.png");
			menu.btnOnHover_texture = LoadTexture("res/assets/Textures/MENUONHOVER_BTN.png");
			quit.btn_texture = LoadTexture("res/assets/Textures/QUIT_BTN.png");
			quit.btnOnHover_texture = LoadTexture("res/assets/Textures/QUITONHOVER_BTN.png");

			title_position = { (float)(screenWidth / 2 - gameover_title.width / 2) + 10, 
				               (float)(screenHeight / 2 - gameover_title.height / 2) - 180 };

			buttons::createButton(retry, retry.btn_texture.height, retry.btn_texture.width, 
				                 (float)(GetScreenWidth() / 2 - retry.btn_texture.width / 2), 
				                 (float)(GetScreenHeight() - 400), WHITE);

			buttons::createButton(menu, menu.btn_texture.height, menu.btn_texture.width, 
				                 (float)(GetScreenWidth() / 2 - menu.btn_texture.width / 2), 
				                 (float)(GetScreenHeight() - 330), WHITE);

			buttons::createButton(quit, quit.btn_texture.height, quit.btn_texture.width, 
				                 (float)(GetScreenWidth() / 2 - quit.btn_texture.width / 2), 
				                 (float)(GetScreenHeight() - 260), WHITE);

		}

		void update() {

			if (joystick) {
				joystickInput();
			}
			else {
				mouseInput();
			}	
		}

		void draw() {
			ClearBackground(WHITE);
			//Draw UI
			DrawTexture(gameover_bg, 0, 0, WHITE);
			DrawTextureEx(gameover_title, title_position, 0, 1, WHITE);

			//Draw buttons
			buttons::draw(retry);
			buttons::draw(menu);
			buttons::draw(quit);
		}

		void deInit() {
			//images
			UnloadTexture(gameover_bg);
			UnloadTexture(gameover_title);
			//buttons
			UnloadTexture(retry.btn_texture);
			UnloadTexture(menu.btn_texture);
			UnloadTexture(quit.btn_texture);
		}

		void joystickInput() {

			if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
				if (menuPos > 1) {
					menuPos = 0;
				}
				else {
					menuPos++;
				}
				gMenu = static_cast<gameOverMenu>(menuPos);
			}
			if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
				if (menuPos <= 0) {
					menuPos = 2;
				}
				else {
					menuPos--;
				}
				gMenu = static_cast<gameOverMenu>(menuPos);
			}

			switch (gMenu) {
			case retry_enum:
				retry.isHover = true;
				menu.isHover = false;
				quit.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					actualScene = Game;
					gameplay::pause = false;
					gameplay::tutorial = true;
					gameplay::init();
				}

				break;
			case menu_enum:
				menu.isHover = true;
				retry.isHover = false;
				quit.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					gameplay::init();
					gameplay::pause = false;
					gameplay::tutorial = true;
					actualScene = Menu;
				}
				break;
			case quit_enum:
				quit.isHover = true;
				retry.isHover = false;
				menu.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					isGameOver = true;
				}
				break;
			default:
				break;
			}
		}

		void mouseInput() {
			//mouse
			Vector2 mousePoint = GetMousePosition();

			buttons::isMouseOverButton(retry);
			if (CheckCollisionPointRec(mousePoint, retry.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
					gameplay::pause = false;
					gameplay::tutorial = true;
					gameplay::init();
				}
			}
			buttons::isMouseOverButton(menu);
			if (CheckCollisionPointRec(mousePoint, menu.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					gameplay::init();
					gameplay::pause = false;
					gameplay::tutorial = true;
					actualScene = Menu;
				}
			}
			buttons::isMouseOverButton(quit);
			if (CheckCollisionPointRec(mousePoint, quit.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					isGameOver = true;
				}
			}
		}
	}
}


		
		