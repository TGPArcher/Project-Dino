#include <Windows.h>
#include "console.h"

extern err_title(int);
extern err_text_attributes(int);
extern err_handler(int);
extern err_window_info(int);
extern err_buffer_size(int);
extern err_console_window(int);
extern err_create_buffer(int);
extern err_cursor_info(int);

void console_intialization();
void handler_initialization();
void set_console_window();
void draw();
void read_from_stdout(BUFFER_DATA*);
void write_to_back_screen(BUFFER_DATA*);
void swap();
void set_cursor_info(int, int);
void set_console_pos(int, int);
void cls();

HANDLE stdout_handle;
HANDLE screen[2];

int active_screen = 0;

void console_initializations() {
	handler_initialization();

	set_console_window();

	set_cursor_info(100, 0);

	if ((SetConsoleTitle(L"The Cha Lama")) == 0)
		err_title(36);

	if ((SetConsoleTextAttribute(stdout_handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY)) == 0)
		err_text_attributes(39);

	cls();
}

void set_console_window() {

	SMALL_RECT window_size = { .Left = 0,.Top = 0,.Right = 99,.Bottom = 24 };
	COORD buffer_size = { .X = 100,.Y = 25 };
	for (int i = 0; i < 2; i++) {
		if ((SetConsoleWindowInfo(screen[i], TRUE, &window_size)) == 0)
			err_window_info(50);
		if ((SetConsoleScreenBufferSize(screen[i], buffer_size)) == 0)
			err_buffer_size(52);
	}

	HWND handler;
	if ((handler = GetConsoleWindow()) == NULL)
		err_console_window(57);

	HMENU sysMen = GetSystemMenu(handler, FALSE);

	DeleteMenu(sysMen, SC_CLOSE, MF_BYCOMMAND);
	DeleteMenu(sysMen, SC_MINIMIZE, MF_BYCOMMAND);
	DeleteMenu(sysMen, SC_MAXIMIZE, MF_BYCOMMAND);
	DeleteMenu(sysMen, SC_SIZE, MF_BYCOMMAND);

	buffer_size.Y++;
	if ((SetConsoleScreenBufferSize(stdout_handle, buffer_size)) == 0)
		err_buffer_size(64);
	
}

void handler_initialization() {
	if ((stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE)) == INVALID_HANDLE_VALUE)
		err_handler(73);

	for (int i = 0; i < 2; i++)
		if ((screen[i] = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL)) == INVALID_HANDLE_VALUE)
			err_create_buffer(76);
}

void draw() {
	BUFFER_DATA transport_buffer = {
		.tmp_buffer_size = {.X = 100,.Y = 25 },
		.tmp_buffer_start = { .X = 0, .Y = 0 },
		.region_to_read = {.Left = 0,.Top = 0,.Right = 99,.Bottom = 24 } };

	read_from_stdout(&transport_buffer);

	write_to_back_screen(&transport_buffer);

	swap();

	cls();
}

void read_from_stdout(BUFFER_DATA *_transport_buffer) {
	ReadConsoleOutput(
		stdout_handle,
		_transport_buffer->tmp_buffer,
		_transport_buffer->tmp_buffer_size,
		_transport_buffer->tmp_buffer_start,
		&_transport_buffer->region_to_read);
}

void write_to_back_screen(BUFFER_DATA *_transport_buffer) {
	WriteConsoleOutput(
		screen[1 - active_screen],
		_transport_buffer->tmp_buffer,
		_transport_buffer->tmp_buffer_size,
		_transport_buffer->tmp_buffer_start,
		&_transport_buffer->region_to_read);
}

void swap() {
	active_screen = 1 - active_screen;

	SetConsoleActiveScreenBuffer(screen[active_screen]);
}

void set_cursor_info(int size, int visible) {
	CONSOLE_CURSOR_INFO info = { .dwSize = size,.bVisible = visible };

	for (int i = 0; i < 2; i++)
		if ((SetConsoleCursorInfo(screen[i], &info)) == 0)
			err_cursor_info(130);
}

// Sets the console cursor to (X,Y)
void set_console_pos(int x, int y) {
	COORD cons_coord = { .X = x,.Y = y};

	SetConsoleCursorPosition(stdout_handle, cons_coord);
}

void cls() {
	static int once = 1;
	static BUFFER_DATA clear_buffer = {
		.tmp_buffer_size = { .X = 100,.Y = 25 },
		.tmp_buffer_start = { .X = 0,.Y = 0 },
		.region_to_read = { .Left = 0,.Top = 0,.Right = 99,.Bottom = 24 } };

	if (once) {
		read_from_stdout(&clear_buffer);
		once = 0;
	}

	WriteConsoleOutput(
		stdout_handle,
		clear_buffer.tmp_buffer,
		clear_buffer.tmp_buffer_size,
		clear_buffer.tmp_buffer_start,
		&clear_buffer.region_to_read);

	write_to_back_screen(&clear_buffer);
}