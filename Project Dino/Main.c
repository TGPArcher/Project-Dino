#include <stdio.h>
#include <Windows.h>

typedef char sprites[5][6];

typedef struct object {
	int owner;
	int x, y;
	sprites sprite;
}object;

object obj_init(int, int, int, char[][6]);
void set_console_pos(int, int);
void draw_the_object(object);

int x, y;

void main() {

	x = 0; y = 0;
	set_console_pos(x, y);

	object cactus = obj_init(90, 20, 2, " ### ##### ### ##### ### ");

	draw_the_object(cactus);

}

// make a bigger _sprite array and add size parameters
// or better try to find a way how to pass the array without doing any costly loop
object obj_init(int _x, int _y, int _owner, char _sprite[26]) {
	object _obj;

	_obj.x = _x;
	_obj.y = _y;
	_obj.owner = _owner;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			_obj.sprite[i][j] = _sprite[i * 5 + j];
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

	for (int i = 0; i < 5; i++) {
		set_console_pos(_go.x, _go.y + i);

		for (int j = 0; j < 5; j++) {
			printf("%c", _go.sprite[i][j]);
		}
	}

	set_console_pos(0, y++); y++;
}