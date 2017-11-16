#include <stdint.h>
#include <Windows.h>
#include <conio.h>

extern int draw_the_canvas();
extern int game_scene();
extern set_console_pos(int, int);

int menu() {

	int loop = 1, button = 0, stop = 0;

	for (; loop;) {
		Sleep(300);
		system("cls");

		menu_controls(&loop, &button);

		info_text();

		if (menu_buttons(button))
			loop = 0;

		draw_the_canvas();
	}

	if (!button)
		game_scene();
	else {
		system("cls");
		stop = 1;
	}

	return stop;
}

int menu_controls(int * _loop, int * _button) {
	int selected = 0;

	if (_kbhit()) {
		char input = _getch();

		if (input == 'x')
			*_loop = 0;

		if (input == 's' || input == 'w')
			*_button = (*_button + 1) % 2;

		if (input == 13) {
			*_loop = 0;
			selected = 1;
		}

	}

	return selected;
}

int menu_buttons(int _button) {

	set_console_pos(38, 9 + _button * 5);
	printf("->");

	set_console_pos(41, 8);
	printf("---------------");
	set_console_pos(41, 9);
	printf("|    Start    |");
	set_console_pos(41, 10);
	printf("---------------");

	set_console_pos(41, 13);
	printf("---------------");
	set_console_pos(41, 14);
	printf("|    Stop     |");
	set_console_pos(41, 15);
	printf("---------------");

	return 0;
}

int info_text() {
	set_console_pos(42, 5);
	printf("The Cha Lama");

	set_console_pos(15, 20);
	printf("Use 'w' or 's' to move the arrow up or down, and press Enter to select");
	set_console_pos(17, 21);
	printf("How to play: Press space bar to jump. Do not hit the cactus plants");

	return 0;
}