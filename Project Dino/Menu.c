#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

extern int game_scene();
extern void draw_menu_buttons(int);
extern void draw_the_canvas();
extern void draw();

void menu_controls(int*, int*);

int menu() {

	int loop = 1, stop = 1, button = 0;

	while (loop) {
		Sleep(50);
		draw();

		menu_controls(&loop, &button);

		draw_menu_buttons(button);

		draw_the_canvas();
	}

	if (!button)
		game_scene();
	else {
		draw();
		stop = 0;
	}

	return stop;
}

void menu_controls(int * _loop, int * _button) {

	if (_kbhit()) {
		char input = _getch();

		if (input == 's' || input == 'w')
			*_button = 1 - *_button;
		if (input == 13)
			*_loop = 0;
	}
}