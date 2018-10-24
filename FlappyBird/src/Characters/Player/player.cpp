#include "player.h"

#include <cmath>
#include <iostream>

#include "Characters\Enemys\columns.h"
#include "Logic\game.h"
#include "Scenes\victory.h"

namespace flappybird {
	namespace players {
		using namespace columns_enemys;
		using namespace game;
		Player player;

		bool isMoving;

		float delayTime = 0.1f;
		int GRAVITY = 4;
		float PLAYER_SPEED = 100;
		float PLAYER_ROTATION_SPEED = 300.0f;
		int currentFrame = 0;

		static float timer; //Animations coming soon
		
		Vector2 mousePosition;
		Vector2 U;
		Vector2 UNormalized;


		void init() {
			player.texture = LoadTexture("res/Textures/space_ship.png");
			player.position = { (float)GetScreenWidth() / 2 - player.texture.width / 2 - 200,(float)GetScreenHeight() / 2 - player.texture.height / 2 };
			player.color = WHITE;
			player.acceleration = {0,0};
			player.rotation = 0;
			player.speed.x = 0;
			player.speed.y = 0;
			player.radius = (float)player.texture.width /3;
			player.score = 0;
			isMoving = false;

			U = { 0, 0 };
			UNormalized = { 0,0 };

			// NOTE: Source rectangle (part of the texture to use for drawing)
			player.sourceRec = { 0.0f, 0.0f, (float)player.texture.width/3, (float)player.texture.height };

			// NOTE: Destination rectangle (screen rectangle where drawing part of texture)
			player.destRec = { player.position.x, player.position.y, (float)player.texture.width, (float)player.texture.height};

			// NOTE: Origin of the texture (rotation/scale point), it's relative to destination rectangle size
			player.origin = { ((float)player.texture.width/3)/2, (float)player.texture.height/2 };

			//FrameTimeCounter
			timer = GetFrameTime();

		}

		void update() {
			timer += GetFrameTime();

			mousePosition = GetMousePosition();

			//Distancia entre player y mouse
			U = {  mousePosition.x - player.position.x  , mousePosition.y - player.position.y };

			//player.rotation = (atan2(U.y,U.x)*RAD2DEG);
	
			// Player logic: acceleration
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
				
				//player.rotation = 45;
				player.speed.y = -250 * GetFrameTime();

				currentFrame = 1;
				player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
				timer = 0;

			}
			else {
				if (timer > delayTime) {		
					currentFrame = 0;
					player.sourceRec.x = (float)currentFrame*(float)player.texture.width / 3;
				}
				
			}
			
			player.speed.y += GRAVITY * GetFrameTime();
			player.position.y += player.speed.y;

			// Collision logic: player vs columns
			/*
			for (int a = 0; a < MAX_BIG_METEORS; a++)
			{
				if (CheckCollisionCircles(player.position, player.radius, bigMeteor[a].position, bigMeteor[a].radius) && bigMeteor[a].active) {
					if (!victory::isVictory()) {
						actualScene = Gameover;
					}	
				}
			}
			*/

			player.destRec = { player.position.x, player.position.y, (float)player.texture.width/3, (float)player.texture.height };

		}

		void draw() {
			DrawTexturePro(player.texture,player.sourceRec,player.destRec,player.origin,player.rotation,player.color);
			if (isMoving) {
			
			}
		}

		void deInit() {
			UnloadTexture(player.texture);
		}
	}
}