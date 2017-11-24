#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <Windows.h>
#include "g_struct.h"

object obj_init(int, int, char[], int, int, int, collider[]);
extern int menu();
extern int draw_the_canvas();

int x, y;

int main() {
	set_console_pos(0, 0);

	while (!menu());

	return 0;
}

int game_scene() {

	raw_sprites * go_sprites;
	set_sprites(&go_sprites);

	object go[3];
	first_init_objects(&go, &go_sprites);

	object player = obj_init(15, 20, go_sprites[0].str, go_sprites[0].x, go_sprites[0].y, go_sprites[0].n_colliders, go_sprites[0].colliders);

	// player functionality
	int jumped = 0;
	int how_many = 0;
	int stop = 0;

	// For stoping the game
	int alive = 1;

	// Game score
	int score = 0;

	while (alive) {
		Sleep(50);
		system("cls");

		player_handler(&jumped, &how_many, &player.y, &player.x, &alive, &stop);

		draw_the_object(player);

		object_handler(&go, &go_sprites, &player, &alive, &stop, &score);

		display_score(score);

		draw_the_canvas();
	}

	return 0;
}

// Load textures when the game starts
int set_sprites(raw_sprites ** go_sprites) {

	FILE * go_file;
	fopen_s(&go_file, "GO_Elements.txt", "r");

	int nr, len;
	fscanf_s(go_file, "%d", &nr);
	*go_sprites = (raw_sprites*)malloc(sizeof(raw_sprites)*nr);

	for (int i = 0; i < nr; i++) {
		fscanf_s(go_file, "%d %d %d ", &(*go_sprites)[i].x, &(*go_sprites)[i].y, &(*go_sprites)[i].n_colliders);

		(*go_sprites)[i].colliders = (collider*)malloc(sizeof(collider)*(*go_sprites)[i].n_colliders);
		for (int j = 0; j < (*go_sprites)[i].n_colliders; j++) {
			fscanf_s(go_file, "%d %d %d %d ", &(*go_sprites)[i].colliders[j].x1, &(*go_sprites)[i].colliders[j].y1, &(*go_sprites)[i].colliders[j].x2, &(*go_sprites)[i].colliders[j].y2);
		}

		fscanf_s(go_file, "%d ", &len);

		(*go_sprites)[i].str = (char *)malloc(sizeof(char)*len);
		fgets((*go_sprites)[i].str, len, go_file);
		(*go_sprites)[i].str[0] = ' ';
		fseek(go_file, SEEK_CUR, 1);
	}

	fclose(go_file);

	return 0;
}

// Get a "random" number
// Made for selecting random texture for enviroment
int get_random() {
	int _res = rand() % 3;

	return _res;
}

// handles player behavior on keyboard input
int player_handler(int * _jump, int * _hm, int * _y, int * _x, int * _alive, int * stop) {
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
		if (_input == 't') {
			*stop = 1;
		}
		if (_input == 'w') {
			*_y = *_y - 1;
		}
		if (_input == 's') {
			*_y = *_y + 1;
		}
		if (_input == 'a') {
			*_x = *_x - 1;
		}
		if (_input == 'd') {
			*_x = *_x + 1;
		}
	}

	return 0;
}

// First initialization of game objects
// (they can't be firstly initialized by the handler
int first_init_objects(object * _go, raw_sprites ** go_sprites) {
	for (int i = 0; i < 3; i++) {
		int _rand = get_random() + 1;

		_go[i] = obj_init(45 * (i + 2), 25 - (*go_sprites)[_rand].y, (*go_sprites)[_rand].str, (*go_sprites)[_rand].x, (*go_sprites)[_rand].y, (*go_sprites)[_rand].n_colliders, (*go_sprites)[_rand].colliders);
	}

	return 0;
}

// Function to check if the object is colliding with player
int collision_check(object * _go, object * _player) {
	int condition = 1;

	for (int i = 0; i < _go->n_colliders && condition == 1; i++) {
		for (int j = 0; j < _player->n_colliders && condition == 1; j++) {
			if (!(_player->colliders[j].x1 + _player->x > _go->colliders[i].x2 + _go->x || _player->colliders[j].y1 + _player->y > _go->colliders[i].y2 + _go->y ||
				_go->colliders[i].x1 + _go->x > _player->colliders[j].x2 + _player->x || _go->colliders[i].y1 + _go->y > _player->colliders[j].y2 + _player->y)) {
				condition = 0;
			}
		}
	}

	return condition;
}

// object handler
// handles object behavior, reinitialization and collision
int object_handler(object * _go, raw_sprites ** go_sprites, object * _player, int * _alive, int * stop, int * score) {
	int _rand = 0;

	for (int i = 0; i < 3; i++) {

		if (!*stop) {
		_go->x--;
		}

		if (_go->x > 2 && _go->x < 92) {
			draw_the_object(*_go);

			if ((_go->x >= _player->x && _go->x < _player->x + _player->sx) || (_go->x + _go->sx - 1 >= _player->x && _go->x + _go->sx - 1 < _player->x + _player->sx))
				*_alive = collision_check(_go, _player);
		}
		else if (_go->x <= 2) {
			_rand = get_random() + 1;

			*_go = obj_init(135, 25 - (*go_sprites)[_rand].y, (*go_sprites)[_rand].str, (*go_sprites)[_rand].x, (*go_sprites)[_rand].y, (*go_sprites)[_rand].n_colliders, (*go_sprites)[_rand].colliders);

			*score = *score + 1;
		}

		*_go++;
	}

	return 0;
}

// initializes objects
// _x,_y are coordinates, _sprite[] is the array wich holds the sprite, _sizeX,_sizeY is sprites size
object obj_init(int _x, int _y, char * _sprite, int _sizeX, int _sizeY, int _collider_number, collider * _colliders) {
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
int set_console_pos(int _x, int _y) {
	HANDLE cons_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cons_coord;

	cons_coord.X = _x; cons_coord.Y = _y;
	x = _x; y = _y;

	SetConsoleCursorPosition(cons_handle, cons_coord);

	return 0;
}

// Draws the object _go to console
int draw_the_object(object _go) {

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

	return 0;
}

int display_score(int score) {

	set_console_pos(41, 3);
	printf("---------------");
	set_console_pos(41, 4);
	printf("|  Scor: %d", score);
	set_console_pos(55, 4);
	printf("|");
	set_console_pos(41, 5);
	printf("---------------");

	return 0;
}