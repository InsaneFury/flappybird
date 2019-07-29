#include "player.h"

#include "Characters\Enemys\columns.h"
#include "Logic\game.h"
#include "Utility\animations.h"

namespace flappybird {
	namespace players {
		using namespace columns_enemys;
		using namespace game;

		Player player;
		Player player2;

		Sound birdFlap;
		Sound birdHit;

		//bool isDead;
		bool deadSFX;
		float delayTime = 0.1f;
		int currentFrame = 0;
	
		int GRAVITY = 2000;
		int PLAYER_ON_CLICK_ROTATION = -45;
		int GRAVITY_ROTATION = 250;
		float PLAYER_SPEED = -400;
		
		static float timer; 

		void init() {
			
			initPlayerOne();
			initPlayerTwo();

			//FrameTimeCounter
			timer = GetFrameTime();
			#ifdef AUDIO
				birdFlap = LoadSound("res/assets/Sound/flap.wav");
				birdHit = LoadSound("res/assets/Sound/hit.wav");
			#endif // AUDIO
		}

		void update() {
			timer += GetFrameTime();

			playerOneController();
			if (multiplayerOn) {
				playerTwoController();
			}
			
		}

		void draw() {
			DrawTexturePro(player.texture,player.sourceRec,player.destRec,
						   player.origin,player.rotation,player.color);
			if (multiplayerOn) {
				DrawTexturePro(player2.texture, player2.sourceRec, player2.destRec,
					player2.origin, player2.rotation, player2.color);
			}
			
		#ifdef _DEBUG
			DrawCircleV(player.position, player.radius, GREEN);
			if (multiplayerOn) {
				DrawCircleV(player2.position, player2.radius, GREEN);
			}
			
		#endif // DEBUG	
		}

		void deInit() {
			UnloadTexture(player.texture);
			if (multiplayerOn) {
				UnloadTexture(player2.texture);
			}
			
		#ifdef AUDIO
			UnloadSound(birdFlap);
			UnloadSound(birdHit);
		#endif // AUDIO	
		}

		void playerOneController() {
			// Player1 logic: acceleration
			bool buttonPressed = (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) ||
								  IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_RIGHT_TRIGGER_1));

			if (buttonPressed && !player.isDead) {
				if (player.position.y >= player.texture.height) {

					PlaySound(birdFlap);

					player.rotation = PLAYER_ON_CLICK_ROTATION;
					player.speed.y = PLAYER_SPEED;

					if (player.position.y <= player.texture.height) {
						player.position.y = player.texture.height;
					}

					currentFrame = 1;
					player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
					timer = 0;
				}
			}
			else {
				if (timer > delayTime) {
					if (player.rotation < 90) {
						player.rotation += GRAVITY_ROTATION * GetFrameTime();
					}
					currentFrame = 0;
					player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
				}
			}


			//player 1 dead condition
			if (player.isDead) {
				if (deadSFX) {
					PlaySound(birdHit);
					deadSFX = false;
				}
				currentFrame = 2;
				player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
			}

			//player 1 Gravity
			if (player.position.y != animations::ground_collider.y) {
				player.speed.y += GRAVITY * GetFrameTime();
				player.position.y += player.speed.y * GetFrameTime();
			}

			// Collision logic: player vs ground
			if (CheckCollisionCircleRec(player.position, player.radius, animations::ground_collider)) {
				currentFrame = 2;
				player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
				player.position.y = animations::ground_collider.y;
				player.isDead = true;
			}

			//player 1 refresh
			player.destRec = { player.position.x, player.position.y, (float)player.texture.width / 3,
																	 (float)player.texture.height };
		}

		void playerTwoController() {
			// Player2 logic: acceleration
			bool buttonPressed = (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) ||
								 (IsGamepadButtonPressed(GAMEPAD_PLAYER1, GAMEPAD_BUTTON_LEFT_TRIGGER_1)));

			if (buttonPressed && !player2.isDead) {

				if (player2.position.y >= player2.texture.height) {

					PlaySound(birdFlap);

					player2.rotation = PLAYER_ON_CLICK_ROTATION;
					player2.speed.y = PLAYER_SPEED;

					if (player2.position.y <= player.texture.height) {
						player2.position.y = player.texture.height;
					}

					currentFrame = 1;
					player2.sourceRec.x = (float)currentFrame*(float)player2.texture.width / 3;
					timer = 0;
				}
			}
			else {
				if (timer > delayTime) {
					if (player2.rotation < 90) {
						player2.rotation += GRAVITY_ROTATION * GetFrameTime();
					}
					currentFrame = 0;
					player2.sourceRec.x = (float)currentFrame*(float)player2.texture.width / 3;
				}
			}

			//player 2 Gravity
			if (player2.position.y != animations::ground_collider.y) {
				player2.speed.y += GRAVITY * GetFrameTime();
				player2.position.y += player2.speed.y * GetFrameTime();
			}

			// Collision logic: player vs ground
			if (CheckCollisionCircleRec(player2.position, player2.radius, animations::ground_collider)) {
				currentFrame = 2;
				player2.sourceRec.x = (float)currentFrame*(float)player2.texture.width / 3;
				player2.position.y = animations::ground_collider.y;
				player2.isDead = true;
			}

			//player 2 dead condition
			if (player2.isDead) {
				if (deadSFX) {
					PlaySound(birdHit);
					deadSFX = false;
				}
				currentFrame = 2;
				player2.sourceRec.x = (float)currentFrame*(float)player2.texture.width / 3;
			}

			//player 2 refresh
			player2.destRec = { player2.position.x, player2.position.y, (float)player2.texture.width / 3,
																	 (float)player2.texture.height };
		}

		void initPlayerOne() {
			//Player 1 ===========================================================================================
			player.texture = LoadTexture("res/assets/Textures/birdhero.png");
			player.position = { (float)GetScreenWidth() / 2 - player.texture.width / 2 - 200,
								(float)GetScreenHeight() / 2 - player.texture.height / 2 };
			player.color = WHITE;
			player.acceleration = { 0,0 };
			player.rotation = 0;
			player.speed.x = 0;
			player.speed.y = 0;
			player.radius = (float)(player.texture.width / 3) / 2 - 30;
			player.score = 0;
			player.isDead = false;
			deadSFX = true;

			// NOTE: Source rectangle (part of the texture to use for drawing)
			player.sourceRec = { 0.0f, 0.0f, (float)player.texture.width / 3, (float)player.texture.height };

			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			player.destRec = { player.position.x, player.position.y, (float)player.texture.width,
																	 (float)player.texture.height };

			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			player.origin = { ((float)player.texture.width / 3) / 2, (float)player.texture.height / 2 };
		}

		void initPlayerTwo() {
			//Player 2 ===========================================================================================
			player2.texture = LoadTexture("res/assets/Textures/birdhero.png");
			player2.position = { (float)GetScreenWidth() / 2 - player2.texture.width / 2 - 350,
								(float)GetScreenHeight() / 2 - player2.texture.height / 2 };
			player2.color = RED;
			player2.acceleration = { 0,0 };
			player2.rotation = 0;
			player2.speed.x = 0;
			player2.speed.y = 0;
			player2.radius = (float)(player2.texture.width / 3) / 2 - 30;
			player2.score = 0;
			player2.isDead = false;
			deadSFX = true;

			// NOTE: Source rectangle (part of the texture to use for drawing)
			player2.sourceRec = { 0.0f, 0.0f, (float)player2.texture.width / 3, (float)player2.texture.height };

			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			player2.destRec = { player2.position.x, player2.position.y, (float)player2.texture.width,
																	 (float)player2.texture.height };

			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			player2.origin = { ((float)player2.texture.width / 3) / 2, (float)player2.texture.height / 2 };
		}
	}
}