#include "pause_menu.h"

#include "Scenes/gameplay.h"
#include "Logic/game.h"
#include "buttons.h"
#include "Logic\game.h"

namespace flappybird {
	namespace pause_menu {
		using namespace game;
		using namespace gameplay;

		enum pauseMenu {
			resume_enum,
			retry_enum,
			menu_enum,
			quit_enum
		}pMenu;

		static int menuPos = 0;

		//Images
		Texture2D pause_bg;
		Texture2D pause_title;

		Vector2 title_position;

		buttons::BTNTEX resume;
		buttons::BTNTEX retry;
		buttons::BTNTEX menu;
		buttons::BTNTEX quit;
		buttons::BTNTEX mute;
		buttons::BTNTEX unmute;

		static bool isPlaying;

		void init() {
			pause_bg = LoadTexture("res/assets/Textures/PAUSE_BG.png");
			pause_title = LoadTexture("res/assets/Textures/PAUSE_TITLE.png");

			resume.btn_texture = LoadTexture("res/assets/Textures/RESUME_BTN.png");
			resume.btnOnHover_texture = LoadTexture("res/assets/Textures/RESUMEONHOVER_BTN.png");
			retry.btn_texture = LoadTexture("res/assets/Textures/RETRY_BTN.png");
			retry.btnOnHover_texture = LoadTexture("res/assets/Textures/RETRYONHOVER_BTN.png");
			menu.btn_texture = LoadTexture("res/assets/Textures/MENU_BTN.png");
			menu.btnOnHover_texture = LoadTexture("res/assets/Textures/MENUONHOVER_BTN.png");
			quit.btn_texture = LoadTexture("res/assets/Textures/QUIT_BTN.png");
			quit.btnOnHover_texture = LoadTexture("res/assets/Textures/QUITONHOVER_BTN.png");
			mute.btn_texture = LoadTexture("res/assets/Textures/MUTE_BTN.png");
			mute.btnOnHover_texture = LoadTexture("res/assets/Textures/MUTE_BTN.png");
			unmute.btn_texture = LoadTexture("res/assets/Textures/MUTEON_BTN.png");
			unmute.btnOnHover_texture = LoadTexture("res/assets/Textures/MUTEON_BTN.png");

			title_position = { (float)(screenWidth / 2 - pause_title.width / 2) + 10, 
				               (float)(screenHeight / 2 - pause_title.height / 2) - 180 };

			buttons::createButton(resume, resume.btn_texture.height, resume.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - resume.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 400), WHITE);

			buttons::createButton(retry, retry.btn_texture.height, retry.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - retry.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 330), WHITE);

			buttons::createButton(menu, menu.btn_texture.height, menu.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - menu.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 260), WHITE);

			buttons::createButton(quit, quit.btn_texture.height, quit.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - quit.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 190), WHITE);

			buttons::createButton(mute, mute.btn_texture.height, mute.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - mute.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 120), WHITE);

			buttons::createButton(unmute, unmute.btn_texture.height, unmute.btn_texture.width, 
								 (float)(GetScreenWidth() / 2 - unmute.btn_texture.width / 2), 
								 (float)(GetScreenHeight() - 120), WHITE);

			isPlaying = true;
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
			//Draw UI
			DrawTexture(pause_bg, 0, 0, WHITE);
			DrawTextureEx(pause_title, title_position, 0, 1, WHITE);

			//Draw buttons
			buttons::draw(resume);
			buttons::draw(retry);
			buttons::draw(menu);
			buttons::draw(quit);
			if (isPlaying) {
				buttons::draw(mute);
			}
			else {
				buttons::draw(unmute);
			}	
		}

		void deInit() {
			//images
			UnloadTexture(pause_bg);
			UnloadTexture(pause_title);
			//buttons
			UnloadTexture(resume.btn_texture);
			UnloadTexture(retry.btn_texture);
			UnloadTexture(menu.btn_texture);
			UnloadTexture(quit.btn_texture);
			UnloadTexture(mute.btn_texture);
			UnloadTexture(unmute.btn_texture);
		}

		void joystickInput() {

			if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_DOWN)) {
				if (menuPos > 2) {
					menuPos = 0;
				}
				else {
					menuPos++;
				}
				pMenu = static_cast<pauseMenu>(menuPos);
			}
			if (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
				if (menuPos <= 0) {
					menuPos = 3;
				}
				else {
					menuPos--;
				}
				pMenu = static_cast<pauseMenu>(menuPos);
			}

			if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_MIDDLE_LEFT)) {
				if (isPlaying) {
					PauseMusicStream(bgMusic);
					isPlaying = false;
					mute.isHover = true;
				}
				else {
					PlayMusicStream(bgMusic);
					isPlaying = true;
					mute.isHover = false;
				}
			}
			
			switch (pMenu) {
			case resume_enum:
				resume.isHover = true;
				retry.isHover = false;
				menu.isHover = false;
				quit.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					pause = !pause;
				}

				break;
			case retry_enum:
				resume.isHover = false;
				retry.isHover = true;
				menu.isHover = false;
				quit.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					actualScene = Game;
					pause_menu::pause = false;
					gameplay::tutorial = true;
					gameplay::timer = gameplay::startWaitTime;
					gameplay::init();
				}
				break;
			case menu_enum:
				resume.isHover = false;
				retry.isHover = false;
				menu.isHover = true;
				quit.isHover = false;
				if (IsGamepadButtonReleased(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) {
					gameplay::init();
					pause_menu::pause = false;
					gameplay::tutorial = true;
					actualScene = Menu;
				}
				break;
			case quit_enum:
				resume.isHover = false;
				retry.isHover = false;
				menu.isHover = false;
				quit.isHover = true;
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

			buttons::isMouseOverButton(resume);
			if (CheckCollisionPointRec(mousePoint, resume.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					pause = !pause;
				}
			}
			buttons::isMouseOverButton(retry);
			if (CheckCollisionPointRec(mousePoint, retry.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					actualScene = Game;
					pause_menu::pause = false;
					gameplay::tutorial = true;
					gameplay::timer = gameplay::startWaitTime;
					gameplay::init();
				}
			}
			buttons::isMouseOverButton(menu);
			if (CheckCollisionPointRec(mousePoint, menu.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					gameplay::init();
					pause_menu::pause = false;
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
			buttons::isMouseOverButton(mute);
			if (CheckCollisionPointRec(mousePoint, mute.size))
			{
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
					if (isPlaying) {
						PauseMusicStream(bgMusic);
						isPlaying = false;
					}
					else {
						PlayMusicStream(bgMusic);
						isPlaying = true;
					}
				}
			}
		}
	}
}