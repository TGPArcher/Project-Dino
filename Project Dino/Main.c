#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include <conio.h>

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
raw_sprites * set_sprites();

int x, y, scor = 0;

void main() {

	x = 0; y = 0;
	set_console_pos(x, y);

	raw_sprites *go_sprites = set_sprites;

	object go[3];
	// make another function to initialize all game objects with a simple call
	object cactus = obj_init(90, 20, 2, " ### ##### ### ##### ### ", 5, 5);
	object player = obj_init(5, 20, 1, "     ##  #   ########## #######  #   #  ", 8, 5);

	// make another function to handle easier the drawing of all game objects
	// also an game object array will be handy here
	/*draw_the_object(cactus);
	draw_the_object(player);*/

	// player functionality
	int jumped = 0;
	int how_many = 0;
	//

	int alive = 1;
	while (alive) {
		Sleep(100);
		system("cls");
		scor++;

		// implement an movement function for the enviroment
		cactus.x--;
		if (cactus.x >= 0) {
			draw_the_object(cactus);
		}
		draw_the_object(player);

		// if you can please optimize the canvas drawing function, it will help you a lot.
		draw_the_canvas();

		if (jumped > 0) {
			if (how_many == 0) {
				player.y--;
				jumped--;
				how_many = 1;
			}
			else {
				how_many--;
			}
		}
		else {
			if (player.y < 20) {
				if (how_many == 0) {
					player.y++;
					how_many = 1;
				}
				else {
					how_many--;
				}
			}
		}
		// inplement an movement for the player and when the key will be pressed the player will jump
		// also do not forgot about gravity, the player should fall after he jumps
		if (_kbhit()) {
			char _input = _getch();

			if (_input == 's') {
				alive = 0;
			}
			if (_input == ' ') {
				if (jumped == 0) {
					jumped = 9;
					how_many = 0;
				}
			}
		}
	}
}

// Load textures when the game starts
raw_sprites * set_sprites() {
	static raw_sprites go_sprites[3];

	strcpy_s(go_sprites[0].str, 150, " ### ##### ### ##### ### ");
	//go_sprites[0].str = " ### ##### ### ##### ### ";
	go_sprites[0].x = 5;
	go_sprites[0].y = 5;

	strcpy_s(go_sprites[1].str, 150, " ## #### ## ");
	//go_sprites[1].str = " ## #### ## ";
	go_sprites[1].x = 4;
	go_sprites[1].y = 3;

	strcpy_s(go_sprites[2].str, 150, "      ### ##### ##   ### #### ##### ##   ### ");
	//go_sprites[2].str = "      ### ##### ##   ### #### ##### ##   ### ";
	go_sprites[2].x = 10;
	go_sprites[2].y = 5;

	return &go_sprites;
}

void object_handler() {

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

void set_console_pos(int _x, int _y) {
	HANDLE cons_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cons_coord;

	cons_coord.X = _x; cons_coord.Y = _y;
	x = _x; y = _y;

	SetConsoleCursorPosition(cons_handle, cons_coord);
}

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