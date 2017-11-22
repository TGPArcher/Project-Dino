#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "c_struct.h"

extern int game_scene();
extern set_console_pos(int, int);

int menu() {
	UIElements * menu_elements;
	get_UI_Elements(&menu_elements);

	int loop = 1, button = 0, stop = 0;

	while (loop) {
		Sleep(300);
		system("cls");

		menu_controls(&loop, &button);

		menu_buttons(button, menu_elements);

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

	if (_kbhit()) {
		char input = _getch();

		if (input == 's' || input == 'w')
			*_button = (*_button + 1) % 2;

		if (input == 13)
			*_loop = 0;

	}

	return 0;
}

int menu_buttons(int _button, UIElements * _menu_elements) {

	for (int i = 1; i < 10; i++) {
		set_console_pos(_menu_elements[i].x, _menu_elements[i].y);
		printf("%s", _menu_elements[i].sprite);
	}

	set_console_pos(_menu_elements[0].x, _menu_elements[0].y + _button * 5);
	printf("%s", _menu_elements[0].sprite);

	return 0;
}

// Draws a canvas for the game
int draw_the_canvas() {

	static CanvasUIElements * _canvas_elements;
	if (_canvas_elements == NULL)
		get_Canvas_Elements(&_canvas_elements);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < _canvas_elements[i].z; j++) {
			set_console_pos(_canvas_elements[i].x, _canvas_elements[i].y + j);
			printf("%s", _canvas_elements[i].sprite);
		}
	}

	set_console_pos(0, 30);

	return 0;
}

int get_UI_Elements(UIElements ** _menu_elements) {
	FILE * menu_file;
	fopen_s(&menu_file, "Menu_UI_Elements.txt", "r");

	int nr;
	fscanf_s(menu_file, "%d", &nr);
	*_menu_elements = (UIElements*)malloc(sizeof(UIElements) * nr);

	for (int i = 0; i < nr; i++) {
		int l;

		fscanf_s(menu_file, "%d %d %d ", &(*_menu_elements)[i].x, &(*_menu_elements)[i].y, &l);

		(*_menu_elements)[i].sprite = (char*)malloc(sizeof(char) * l);
		fgets((*_menu_elements)[i].sprite, l, menu_file);
		fseek(menu_file, SEEK_CUR, 1);
	}

	fclose(menu_file);

	return 0;
}

int get_Canvas_Elements(CanvasUIElements ** _canvas_elements) {
	FILE * canvas_file;
	fopen_s(&canvas_file, "Canvas_UI_Elements.txt", "r");

	int nr;
	fscanf_s(canvas_file, "%d", &nr);
	*_canvas_elements = (CanvasUIElements*)malloc(sizeof(CanvasUIElements) * nr);

	for (int i = 0; i < nr; i++) {
		int l;

		fscanf_s(canvas_file, "%d %d %d %d ", &(*_canvas_elements)[i].x, &(*_canvas_elements)[i].y, &(*_canvas_elements)[i].z, &l);

		(*_canvas_elements)[i].sprite = (char*)malloc(sizeof(char)*l);
		fgets((*_canvas_elements)[i].sprite, l, canvas_file);
		fseek(canvas_file, SEEK_CUR, 1);
	}

	fclose(canvas_file);

	return 0;
}