#include <stdio.h>
#include <Windows.h>
#include <conio.h>

typedef char sprites[10][10];

typedef struct object {
	int owner;
	int x, y, _lx, _ly;
	sprites sprite;
}object;

object obj_init(int, int, int, char[], int, int);
void set_console_pos(int, int);
void draw_the_object(object);
void draw_the_canvas();

int x, y, scor = 0;

void main() {

	x = 0; y = 0;
	set_console_pos(x, y);

	// make another function to initialize all game objects with a simple call
	object cactus = obj_init(90, 20, 2, " ### ##### ### ##### ### ", 5, 5);
	object player = obj_init(5, 20, 1, "     ##  #   ########## #######  #   #  ", 8, 5);

	// make another function to handle easier the drawing of all game objects
	// also an game object array will be handy here
	/*draw_the_object(cactus);
	draw_the_object(player);*/

	int alive = 1;
	while (alive) {
		Sleep(200);
		system("cls");

		// implement an movement function for the enviroment
		cactus.x--;
		if (cactus.x >= 0) {
			draw_the_object(cactus);
		}
		draw_the_object(player);

		// if you can please optimize the canvas drawing function, it will help you a lot.
		draw_the_canvas();

		// inplement an movement for the player and when the key will be pressed the player will jump
		// also do not forgot about gravity, the player should fall after he jumps
		if (_kbhit()) {
			char _input = _getch();

			if (_input == ' ') {
				alive = 0;
			}
		}
	}
}

// make a bigger _sprite array and add size parameters - done
// or better try to find a way how to pass the array without doing any costly loop - still having to think about it
object obj_init(int _x, int _y, int _owner, char _sprite[], int _sizeX, int _sizeY) {
	object _obj;

	_obj.x = _x;
	_obj.y = _y;
	_obj._lx = _sizeX;
	_obj._ly = _sizeY;
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

	for (int i = 0; i < _go._ly; i++) {
		set_console_pos(_go.x, _go.y + i);

		for (int j = 0; j < _go._lx; j++) {

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