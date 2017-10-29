#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

// Structure for textures in a simple format
typedef struct raw_sprites {
	char str[150];
	int x, y;
}raw_sprites;

// Game Object's structure (owner, coord, sprite, spr_coord)
typedef struct object {
	int owner;
	int x, y;
	char sprite[10][15];
	int sx, sy;
}object;

object obj_init(int, int, int, char[], int, int);
void set_console_pos(int, int);
void draw_the_object(object);
void draw_the_canvas();
void set_sprites(raw_sprites *);
int get_random();
void player_handler(int *, int *, int *, int *);
void first_init_objects(object *, raw_sprites[]);
void object_handler(object *, raw_sprites[]);

int x, y, scor = 0;

void main() {

	set_console_pos(0, 0);

	raw_sprites go_sprites[3];
	set_sprites(&go_sprites);

	object go[3];
	first_init_objects(&go, go_sprites);

	object player = obj_init(15, 20, 1, "     ##  #   ########## #######  #   #  ", 8, 5);

	// player functionality
	int jumped = 0;
	int how_many = 0;

	// For stoping the game
	int alive = 1;

	while (alive) {
		draw_the_object(player);

		draw_the_canvas();

		object_handler(&go, go_sprites);

		player_handler(&jumped, &how_many, &player.y, &alive);

		Sleep(50);
		system("cls");
		scor++;
	}
}

// Load textures when the game starts
void set_sprites(raw_sprites * go_sprites) {
	//static raw_sprites go_sprites[3];

	strcpy_s(go_sprites->str, 150, " ### ##### ### ##### ### ");
	go_sprites->x = 5;
	go_sprites->y = 5;

	go_sprites++;
	strcpy_s(go_sprites->str, 150, " ## #### ## ");
	go_sprites->x = 4;
	go_sprites->y = 3;

	go_sprites++;
	strcpy_s(go_sprites->str, 150, "      ###      ##### ##   ### #### ##### ##   ### ");
	go_sprites->x = 10;
	go_sprites->y = 5;
}

// Get a "random" number
// Made for selecting random texture for enviroment
int get_random() {
	int _res = rand() % 3;

	return _res;
}

// handles player behavior on keyboard input
void player_handler(int * _jump, int * _hm, int * _y, int * _alive) {
	if (*_jump > 0) {
		if (*_hm == 0) {
			*_y = *_y - 1;
			*_jump = *_jump - 1;
			*_hm = 1;
		}
		else {
			*_hm = *_hm - 1;
		}
	}
	else {
		if (*_y < 20) {
			if (*_hm == 0) {
				*_y = *_y + 1;
				*_hm = 1;
			}
			else {
				*_hm = *_hm - 1;
			}
		}
	}

	if (_kbhit()) {
		char _input = _getch();

		if (_input == 's') {
			*_alive = 0;
		}
		if (_input == ' ') {
			if (*_jump == 0) {
				*_jump = 9;
				*_hm = 0;
			}
		}
	}
}

// First initialization of game objects
// (they can't be firstly initialized by the handler
void first_init_objects(object * _go, raw_sprites go_sprites[]) {
	for (int i = 0; i < 3; i++) {
		int _rand = get_random();

		*(_go + i) = obj_init(45 * (i + 2), 25 - go_sprites[_rand].y, 2, go_sprites[_rand].str, go_sprites[_rand].x, go_sprites[_rand].y);
	}
}

// object handler
// handles object behavior and reinitialization
void object_handler(object * _go, raw_sprites go_sprites[]) {
	int _rand = 0;

	for (int i = 0; i < 3; i++) {

		if (_go->x > 2 && _go->x < 92) {
			draw_the_object(*_go);
		}
		else if (_go->x <= 2) {
			_rand = get_random();

			*_go = obj_init(135, 25 - go_sprites[_rand].y, 2, go_sprites[_rand].str, go_sprites[_rand].x, go_sprites[_rand].y);
		}

		_go->x--;
		*_go++;
	}
}

// make a bigger _sprite array and add size parameters - done
// or better try to find a way how to pass the array without doing any costly loop - still having to think about it
object obj_init(int _x, int _y, int _owner, char _sprite[], int _sizeX, int _sizeY) {
	object _obj;

	_obj.x = _x;
	_obj.y = _y;
	_obj.sx = _sizeX;
	_obj.sy = _sizeY;
	_obj.owner = _owner;

	for (int i = 0; i < _sizeY; i++) {
		for (int j = 0; j < _sizeX; j++) {
			_obj.sprite[i][j] = _sprite[i * _sizeX + j];
		}
	}

	return _obj;

}

// Sets the console cursor to (X,Y)
void set_console_pos(int _x, int _y) {
	HANDLE cons_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cons_coord;

	cons_coord.X = _x; cons_coord.Y = _y;
	x = _x; y = _y;

	SetConsoleCursorPosition(cons_handle, cons_coord);
}

// Draws the object _go to console
void draw_the_object(object _go) {

	for (int i = 0; i < _go.sy; i++) {
		set_console_pos(_go.x, _go.y + i);

		for (int j = 0; j < _go.sx; j++) {

			if (_go.sprite[i][j] != ' ') {
				printf("%c", _go.sprite[i][j]);
				x++;
			}
			else {
				set_console_pos(x+1, y);
			}
		}

	}

	set_console_pos(0, 30);
}

// Draws a canvas for the game
void draw_the_canvas() {

	for (int i = 2; i < 98; i++) {
		set_console_pos(i, 1);
		printf("-");

		set_console_pos(i, 25);
		printf("-");
	}

	for (int i = 1; i <= 25; i++) {
		set_console_pos(0, i);
		printf("||");

		set_console_pos(98, i);
		printf("||");
	}

	set_console_pos(41, 3);
	printf("----------------");
	set_console_pos(41, 4);
	printf("|  Scor: %d", scor);
	set_console_pos(56, 4);
	printf("|");
	set_console_pos(41, 5);
	printf("----------------");

	set_console_pos(0, 30);
}