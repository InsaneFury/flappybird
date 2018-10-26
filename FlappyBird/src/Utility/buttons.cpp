#include "buttons.h"

namespace flappybird {
	namespace buttons {

		//use for create a button
		void createButton(BTN &button, int height, int width,int posX,int posY, int strokeThick, int fontSize, Color btnColor,Color strokeColor,Color textColor) {

			button.size.height = (float)height;
			button.size.width = (float)width;
			button.size.x = posX;
			button.size.y = posY;
			button.fontsize = fontSize;
			button.strokeThick = strokeThick;
			button.textColor = textColor;
			button.color = btnColor;
			button.strokeColor = strokeColor;
		}

		//use for create a Texture button
		void createButton(BTNTEX &button, int height, int width, int posX, int posY, Color btnColor) {
			button.size.height = (float)height;
			button.size.width = (float)width;
			button.size.x = posX;
			button.size.y = posY;
			button.color = btnColor;
			button.isHover = false;
		}

		//use for alpha FX when mouse point is over the button
		void isMouseOverButton(BTN &button) {
			Vector2 mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, button.size)) {
				button.color.a = 120;
			}
			else {
				button.color.a = 255;
			}
		}

		//use for change btn texture when mouse point is over the button
		void isMouseOverButton(BTNTEX &button) {
			Vector2 mousePoint = GetMousePosition();

			if (CheckCollisionPointRec(mousePoint, button.size)) {
				button.isHover = true;
			}
			else {
				button.isHover = false;
			}
		}

		//use for draw a button
		void draw(BTN button, const char *text) {
			DrawRectangleRec(button.size, button.color);
			DrawText(text, button.size.x - (MeasureText(text, button.fontsize) / 2) + button.size.width/2, button.size.y  - (button.fontsize / 2) + button.size.height/2, button.fontsize, button.textColor);
			DrawRectangleLinesEx(button.size, button.strokeThick, button.strokeColor);
		}

		//use for draw a button
		void draw(BTNTEX button) {
			if (!button.isHover)
			{
				DrawTexture(button.btnOnHover_texture, button.size.x, button.size.y, button.color);
			}
			else {
				DrawTexture(button.btn_texture, button.size.x, button.size.y, button.color);
			}
		}
	}
}