#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "g_struct.h"

object obj_init(int, int, sprites*);
extern int menu();
extern int draw_the_canvas();

int x, y;

int main() {
	while (menu());

	return 0;
}

int game_scene() {

	sprites * go_sprites;
	set_sprites(&go_sprites);

	object go[3];
	first_init_objects(&go, &go_sprites);

	object player = obj_init(15, 20, &go_sprites[0]);
	
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

		player_handler(&jumped, &how_many, &player.position, &alive);

		draw_the_object(&player);

		object_handler(&go, &go_sprites, &player, &alive, &score);

		display_score(score);

		draw_the_canvas();
	}

	return 0;
}

// Load textures when the game starts
int set_sprites(sprites ** go_sprites) {

	FILE * go_file;
	fopen_s(&go_file, "GO_Elements.txt", "r");

	int nr, length;
	fscanf_s(go_file, "%d", &nr);
	*go_sprites = (sprites*)malloc(sizeof(sprites)*nr);

	for (int i = 0; i < nr; i++) {
		fscanf_s(go_file, "%d %d %d ", &(*go_sprites)[i].anchors.x, &(*go_sprites)[i].anchors.y, &(*go_sprites)[i].n_colliders);

		(*go_sprites)[i].colliders = (collider*)malloc(sizeof(collider)*(*go_sprites)[i].n_colliders);
		for (int j = 0; j < (*go_sprites)[i].n_colliders; j++) {
			fscanf_s(go_file, "%d %d %d %d ", &(*go_sprites)[i].colliders[j].position1.x, &(*go_sprites)[i].colliders[j].position1.y, &(*go_sprites)[i].colliders[j].position2.x, &(*go_sprites)[i].colliders[j].position2.y);
		}

		length = (*go_sprites)[i].anchors.x * (*go_sprites)[i].anchors.y + 1;
		(*go_sprites)[i].str = (char *)malloc(sizeof(char) * length);
		fgets((*go_sprites)[i].str, length, go_file);
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
int player_handler(int * _jump, int * _hm, pos * _position, int * _alive/*int * stop*/) {
	if (*_jump > 9) {
		if (*_hm == 0) {
			_position->y = _position->y - 1;
			*_jump = *_jump - 1;
			*_hm = 1;
		}
		else {
			*_hm = *_hm - 1;
		}
	}
	else {
		if (_position->y < 20 && *_jump > 0) {
			if (*_hm == 0) {
				_position->y = _position->y + 1;
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
		/*if (_input == 'w') {
			_position->y = _position->y - 1;
		}
		if (_input == 's') {
			_position->y = _position->y + 1;
		}
		if (_input == 'a') {
			_position->x = _position->x - 1;
		}
		if (_input == 'd') {
			_position->x = _position->x + 1;
		}*/
	}

	return 0;
}

// First initialization of game objects
// (they can't be firstly initialized by the handler
int first_init_objects(object * _go, sprites ** go_sprites) {
	for (int i = 0; i < 3; i++) {
		int _rand = get_random() + 1;

		_go[i] = obj_init(45 * (i + 2), 25 - (*go_sprites)[_rand].anchors.y, &(*go_sprites)[_rand]);
	}

	return 0;
}

// Function to check if the object is colliding with player
int collision_check(object * _go, object * _player) {
	int condition = 1;

	for (int i = 0; i < _go->sprite.n_colliders && condition == 1; i++) {
		for (int j = 0; j < _player->sprite.n_colliders && condition == 1; j++) {
			if (!(_player->sprite.colliders[j].position1.x + _player->position.x > _go->sprite.colliders[i].position2.x + _go->position.x || _player->sprite.colliders[j].position1.y + _player->position.y > _go->sprite.colliders[i].position2.y + _go->position.y ||
				_go->sprite.colliders[i].position1.x + _go->position.x > _player->sprite.colliders[j].position2.x + _player->position.x || _go->sprite.colliders[i].position1.y + _go->position.y > _player->sprite.colliders[j].position2.y + _player->position.y)) {
				condition = 0;
			}
		}
	}

	return condition;
}

// object handler
// handles object behavior, reinitialization and collision
int object_handler(object * _go, sprites ** go_sprites, object * _player, int * _alive, /*int * stop*/int * score) {
	int _rand = 0;

	for (int i = 0; i < 3; i++) {

		_go[i].position.x--;
		/*if (!*stop) {
		_go[i].position.x--;
		}*/

		if (_go[i].position.x > 2 && _go[i].position.x < 92) {
			draw_the_object(&_go[i]);

			if ((_go[i].position.x >= _player->position.x && _go[i].position.x < _player->position.x + _player->sprite.anchors.x) || (_go[i].position.x + _go[i].sprite.anchors.x - 1 >= _player->position.x && _go[i].position.x + _go[i].sprite.anchors.x - 1 < _player->position.x + _player->sprite.anchors.x))
				*_alive = collision_check(&_go[i], _player);
		}
		else if (_go[i].position.x <= 2) {
			_rand = get_random() + 1;

			_go[i] = obj_init(135, 25 - (*go_sprites)[_rand].anchors.y, &(*go_sprites)[_rand]);

			*score = *score + 1;
		}
	}

	return 0;
}

// initializes objects
// _x,_y are coordinates, _sprite[] is the array wich holds the sprite, _sizeX,_sizeY is sprites size
object obj_init(int _x, int _y, sprites * _sprite) {
	object _obj;

	_obj.position.x = _x;
	_obj.position.y = _y;
	_obj.sprite = *_sprite;

	return _obj;
}

// Sets the console cursor to (X,Y)
int set_console_pos(int _x, int _y) {
	static HANDLE cons_handle;
	if(cons_handle == NULL)
		cons_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD cons_coord;
	
	/*CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(cons_handle, &info);*/

	cons_coord.X = _x; cons_coord.Y = _y;
	x = _x; y = _y;

	SetConsoleCursorPosition(cons_handle, cons_coord);

	return 0;
}

// Draws the object _go to console
int draw_the_object(object * _go) {

	for (int i = 0, index = 0; i < _go->sprite.anchors.y; i++) {
		set_console_pos(_go->position.x, _go->position.y + i);

		for (int j = 0; j < _go->sprite.anchors.x; index++, j++) {

			if (_go->sprite.str[index] != ' ') {
				printf("%c", _go->sprite.str[index]);
				x++;
			}
			else {
				set_console_pos(x+1, y);
			}
		}
	}

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