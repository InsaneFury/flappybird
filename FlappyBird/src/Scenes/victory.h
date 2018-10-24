#ifndef GAMEOVER_H
#define GAMEOVER_H

namespace flappybird {
	namespace victory {
		void init();
		void update(bool &isGameOver);
		void draw();
		void deInit();
		//bool isVictory();
	}
}
#endif // !GAMEOVER_H
