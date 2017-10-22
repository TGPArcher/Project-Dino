#include <stdio.h>
#include <Windows.h>

typedef char sprites[10][10];

typedef struct object {
	int owner;
	int x, y, _lx, _ly;
	sprites sprite;
}object;

object obj_init(int, int, int, char[], int, int);
void set_console_pos(int, int);
void draw_the_object(object);

int x, y;

void main() {

	x = 0; y = 0;
	set_console_pos(x, y);

	object cactus = obj_init(90, 20, 2, " ### ##### ### ##### ### ", 5, 5);
	object player = obj_init(5, 20, 1, "     ##  #   ########## #######  #   #  ", 8, 5);

	draw_the_object(cactus);
	draw_the_object(player);

	// To be removed
	// Testing the movement, looks good, needs work, also don't forget about game loop
	for (int i = 0; i < 100; i++) {
		getchar();
		system("cls");

		player.x++;
		draw_the_object(player);
		draw_the_object(cactus);
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
			printf("%c", _go.sprite[i][j]);
		}
	}

	set_console_pos(0, 30); //y++;
}