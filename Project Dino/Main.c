#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>

typedef struct collider {
	int x1, y1, x2, y2;
}collider;

// Structure for textures in a simple format
typedef struct raw_sprites {
	char str[150];
	int x, y;
	int n_colliders;
	collider colliders[3];
}raw_sprites;

// Game Object's structure (coord, sprite, spr_coord)
typedef struct object {
	int x, y;
	char sprite[10][15];
	int sx, sy;
	int n_colliders;
	collider colliders[3];
}object;

object obj_init(int, int, char[], int, int, int, collider[]);
void set_console_pos(int, int);
void draw_the_object(object);
void draw_the_canvas();
void set_sprites(raw_sprites *);
int get_random();
void player_handler(int *, int *, int *, int *);
void first_init_objects(object *, raw_sprites[]);
int collision_check(object, object);
void object_handler(object *, raw_sprites[], object, int*);

int x, y, scor = 0;

void main() {

	set_console_pos(0, 0);

	raw_sprites go_sprites[4];
	set_sprites(&go_sprites);

	object go[3];
	first_init_objects(&go, go_sprites);

	object player = obj_init(15, 20, go_sprites[3].str, go_sprites[3].x, go_sprites[3].y, go_sprites[3].n_colliders, go_sprites[3].colliders);

	// player functionality
	int jumped = 0;
	int how_many = 0;

	// For stoping the game
	int alive = 1;

	while (alive) {
		Sleep(50);
		system("cls");

		player_handler(&jumped, &how_many, &player.y, &alive);

		draw_the_object(player);

		object_handler(&go, go_sprites, player, &alive);

		draw_the_canvas();
	}
}

// Load textures when the game starts
void set_sprites(raw_sprites * go_sprites) {

	strcpy_s(go_sprites->str, 150, " ### ##### ### ##### ### ");
	go_sprites->x = 5;
	go_sprites->y = 5;
	go_sprites->n_colliders = 1;
	go_sprites->colliders[0].x1 = 0;
	go_sprites->colliders[0].y1 = 0;
	go_sprites->colliders[0].x2 = 4;
	go_sprites->colliders[0].y2 = 4;

	go_sprites++;
	strcpy_s(go_sprites->str, 150, " ## #### ## ");
	go_sprites->x = 4;
	go_sprites->y = 3;
	go_sprites->n_colliders = 1;
	go_sprites->colliders[0].x1 = 0;
	go_sprites->colliders[0].y1 = 0;
	go_sprites->colliders[0].x2 = 3;
	go_sprites->colliders[0].y2 = 2;

	go_sprites++;
	strcpy_s(go_sprites->str, 150, "      ###      ##### ##   ### #### ##### ##   ### ");
	go_sprites->x = 10;
	go_sprites->y = 5;
	go_sprites->n_colliders = 2;
	go_sprites->colliders[0].x1 = 0;
	go_sprites->colliders[0].y1 = 2;
	go_sprites->colliders[0].x2 = 3;
	go_sprites->colliders[0].y2 = 4;
	go_sprites->colliders[1].x1 = 5;
	go_sprites->colliders[1].y1 = 0;
	go_sprites->colliders[1].x2 = 9;
	go_sprites->colliders[1].y2 = 4;

	go_sprites++;
	strcpy_s(go_sprites->str, 150, "     ##  #   ########## #######  #   #  ");
	go_sprites->x = 8;
	go_sprites->y = 5;
	go_sprites->n_colliders = 2;
	go_sprites->colliders[0].x1 = 0;
	go_sprites->colliders[0].y1 = 0;
	go_sprites->colliders[0].x2 = 7;
	go_sprites->colliders[0].y2 = 3;
	go_sprites->colliders[1].x1 = 1;
	go_sprites->colliders[1].y1 = 4;
	go_sprites->colliders[1].x2 = 5;
	go_sprites->colliders[1].y2 = 4;
}

// Get a "random" number
// Made for selecting random texture for enviroment
int get_random() {
	int _res = rand() % 3;

	return _res;
}

// handles player behavior on keyboard input
void player_handler(int * _jump, int * _hm, int * _y, int * _alive) {
	if (*_jump > 9) {
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
		if (*_y < 20 && *_jump > 0) {
			if (*_hm == 0) {
				*_y = *_y + 1;
				*_jump = *_jump - 1;
				*_hm = 1;
			}
			else {
				*_hm = *_hm - 1;
			}
		}
	}

	if (_kbhit()) {
		char _input = _getch();

		if (_input == 'x') {
			*_alive = 0;
		}
		if (_input == ' ') {
			if (*_jump == 0) {
				*_jump = 18;
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

		*(_go + i) = obj_init(45 * (i + 2), 25 - go_sprites[_rand].y, go_sprites[_rand].str, go_sprites[_rand].x, go_sprites[_rand].y, go_sprites[_rand].n_colliders, go_sprites[_rand].colliders);
	}
}

// Function to check if the object is colliding with player
int collision_check(object _go, object _player) {
	int condition = 1;

	for (int i = 0; i < _go.n_colliders && condition == 1; i++) {
		for (int j = 0; j < _player.n_colliders && condition == 1; j++) {
			if (((_go.colliders[i].y1 + _go.y >= _player.colliders[j].y1 + _player.y && _go.colliders[i].y1 + _go.y <= _player.colliders[j].y2 + _player.y) &&
				(_go.colliders[i].x1 + _go.x >= _player.colliders[j].x1 + _player.x && _go.colliders[i].x1 + _go.x <= _player.colliders[j].x2 + _player.x)) ||
				((_go.colliders[i].y2 + _go.y >= _player.colliders[j].y1 + _player.y && _go.colliders[i].y2 + _go.y <= _player.colliders[j].y2 + _player.y) &&
				(_go.colliders[i].x2 + _go.x >= _player.colliders[j].x1 + _player.x && _go.colliders[i].x2 + _go.x <= _player.colliders[j].x2 + _player.x))) {
				condition = 0;
			}
		}
	}

	return condition;
}

// object handler
// handles object behavior, reinitialization and collision
void object_handler(object * _go, raw_sprites go_sprites[], object _player, int * _alive) {
	int _rand = 0;

	for (int i = 0; i < 3; i++) {

		_go->x--;

		if (_go->x > 2 && _go->x < 92) {
			draw_the_object(*_go);

			if ((_go->x >= _player.x && _go->x < _player.x + _player.sx) || (_go->x + _go->sx - 1 >= _player.x && _go->x + _go->sx - 1 < _player.x + _player.sx))
				*_alive = collision_check(*_go, _player);
		}
		else if (_go->x <= 2) {
			_rand = get_random();

			*_go = obj_init(135, 25 - go_sprites[_rand].y, go_sprites[_rand].str, go_sprites[_rand].x, go_sprites[_rand].y, go_sprites[_rand].n_colliders, go_sprites[_rand].colliders);

			scor++;
		}

		*_go++;
	}
}

// initializes objects
// _x,_y are coordinates, _sprite[] is the array wich holds the sprite, _sizeX,_sizeY is sprites size
object obj_init(int _x, int _y, char _sprite[], int _sizeX, int _sizeY, int _collider_number, collider _colliders[]) {
	object _obj;

	_obj.x = _x;
	_obj.y = _y;
	_obj.sx = _sizeX;
	_obj.sy = _sizeY;

	for (int i = 0; i < _sizeY; i++) {
		for (int j = 0; j < _sizeX; j++) {
			_obj.sprite[i][j] = _sprite[i * _sizeX + j];
		}
	}

	for (int i = 0; i < _collider_number; i++) {
		_obj.n_colliders = _collider_number;
		_obj.colliders[i] = _colliders[i];
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