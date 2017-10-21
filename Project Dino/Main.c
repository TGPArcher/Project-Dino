#include <stdio.h>
#include <Windows.h>
#include <string.h>

//{ { ".###." },{ "#####" },{ ".###." },{ "#####" },{ ".###." } };

typedef char sprites[5][6];

typedef struct square {
	char display;
	int owner;
}square;

typedef struct object {
	int owner;
	int x, y;
	sprites sprite;
}object;

void initialize_the_game_rect(square *);
void initialize_the_game_object(square *, object);
void draw_the_image(square[][100]);

void main() {

	/*HANDLE cons_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cons_coord;
	cons_coord.X = 5; cons_coord.Y = 10;
	SetConsoleCursorPosition(cons_handle, cons_coord);*/

	square game_rect[25][100];
	object cactus;

	cactus.owner = 2;
	cactus.x = 90; cactus.y = 20;
	strcpy_s(cactus.sprite[0], 6, " ### "); strcpy_s(cactus.sprite[1], 6, "#####"); strcpy_s(cactus.sprite[2], 6, " ### "); strcpy_s(cactus.sprite[3], 6, "#####"); strcpy_s(cactus.sprite[4], 6, " ### ");

	initialize_the_game_rect(&game_rect);
	initialize_the_game_object(&game_rect, cactus);
	draw_the_image(game_rect);
}

void initialize_the_game_rect(square (* _gr)[25][100]) {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 100; j++) {
			(*_gr)[i][j].display = ' ';
			(*_gr)[i][j].owner = 0;
		}
	}
}

void initialize_the_game_object(square(*_gr)[25][100], object _obj) {
	for (int i = _obj.y; i < _obj.y + 5; i++) {
		for (int j = _obj.x; j < _obj.x + 5; j++) {
			if (_obj.sprite[i - _obj.y][j -_obj.x] != ' ') {
				(*_gr)[i][j].display = _obj.sprite[(i - _obj.y)][(j - _obj.x)];
				(*_gr)[i][j].owner = _obj.owner;
			}
		}
	}
}

void draw_the_image(square _gr[][100]) {
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 100; j++) {
			printf("%c", _gr[i][j].display);
		}

		printf("\n");
	}
}