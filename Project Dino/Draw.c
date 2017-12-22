#include <stdlib.h>
#include <stdio.h>
#include "c_struct.h"
#include "g_struct.h"

extern void set_console_pos(int, int);
extern int get_UI_Elements(UIElements**);
extern int get_Canvas_Elements(CanvasUIElements**);

// Draws a canvas for the game
void draw_the_canvas() {

	static CanvasUIElements * canvas_elements;
	static int nr_of_elements;

	if (canvas_elements == NULL) {
		nr_of_elements = get_Canvas_Elements(&canvas_elements);
	}

	for (int i = 0; i < nr_of_elements; i++)
		for (int j = 0; j < canvas_elements[i].z; j++) {
			set_console_pos(canvas_elements[i].x, canvas_elements[i].y + j);
			printf("%s", canvas_elements[i].sprite);
		}
}

void draw_menu_buttons(int button) {

	static UIElements * menu_elements;
	static int nr_of_elements;

	if (menu_elements == NULL) {
		nr_of_elements = get_UI_Elements(&menu_elements);
	}

	for (int i = 1; i < nr_of_elements; i++) {
		set_console_pos(menu_elements[i].x, menu_elements[i].y);
		printf("%s", menu_elements[i].sprite);
	}

	set_console_pos(menu_elements[0].x, menu_elements[0].y + button * 5);
	printf("%s", menu_elements[0].sprite);
}

// Draws the object _go to console
void draw_the_object(object * _go) {

	for (int i = 0, index = 0; i < _go->sprite.anchors.y; i++) {
		set_console_pos(_go->position.x, _go->position.y + i);

		for (int j = 0; j < _go->sprite.anchors.x; index++, j++) {
			if (_go->sprite.str[index] != ' ') {
				printf("%c", _go->sprite.str[index]);
			}
			else {
				set_console_pos(_go->position.x + j + 1, _go->position.y + i);
			}
		}
	}
}

void display_score(int score) {

	set_console_pos(41, 3);
	printf("---------------");
	set_console_pos(41, 4);
	printf("|  Scor: %d", score);
	set_console_pos(55, 4);
	printf("|");
	set_console_pos(41, 5);
	printf("---------------");
}