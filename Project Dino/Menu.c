#include <stdint.h>
#include <Windows.h>
#include <conio.h>

extern void draw_the_canvas();

int menu() {

	int _loop = 1;

	for (; _loop;) {
		Sleep(200);
		system("cls");

		draw_the_canvas;
	}

	return 0;
}

int menu_controls(int * _loop) {
	if (_kbhit()) {
		char input = _getch();

		if (input == 'x')
			*_loop = 0;
	}
}