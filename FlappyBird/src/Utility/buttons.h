#ifndef BUTTONS_H
#define BUTTONS_H

#include "raylib.h"

namespace flappybird {
	namespace buttons {

		struct BTN {
			Rectangle size;
			int strokeThick;
			int fontsize;
			Color textColor;
			Color color;
			Color strokeColor;
		};

		struct BTNTEX {
			Texture2D btn_texture;
			Texture2D btnOnHover_texture;
			bool isHover;
			Rectangle size;
			Color color;
		};

		void createButton(BTN &button, int height, int width, int posX, int posY, int strokeThick, int fontSize, Color btnColor, Color strokeColor, Color textColor);
		void createButton(BTNTEX &button, int height, int width, int posX, int posY, Color btnColor);
		void isMouseOverButton(BTN &button);
		void isMouseOverButton(BTNTEX &button);
		void draw(BTN button, const char *text);
		void draw(BTNTEX button);

	}
}
#endif // !BUTTONS_H

