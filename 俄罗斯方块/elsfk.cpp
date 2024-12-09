#include "tetris.h"
#include <graphics.h>
#include <conio.h>

#include <mmsystem.h>
#pragma comment (lib , "winmm.lib")


int main() {
	initgraph(900, 1260);
	mciSendString("play d.mp3 repeat", 0, 0, 0);
	IMAGE kai;
	loadimage(&kai, "s.jpg");
	putimage(0, 300, &kai);

	while (1) {
		if (_kbhit()) {
			mciSendString("stop d.mp3", 0, 0, 0);
			tetris game(14, 22, 100, 150, 50);
			game.play();
		}

	}
	return 0;
}