#include <stdlib.h>
#include <stdio.h>

void redirect() {
	FILE *f;

	freopen_s(&f, "error_log.txt", "w", stderr);
}

/*
### Console
set title
set text attributes
set console window info
set console screen buffer size
delete menu {
	get console window
	get system menu
	}
create screen buffer
get std handle
*/
void err_title(int line) {
	fprintf(stderr, "Failed to set console title - line %d\n", line);

	exit(-1);
}

void err_text_attributes(int line) {
	fprintf(stderr, "Failed to set console text attributes - line %d\n", line);

	exit(-1);
}

void err_handler(int line) {
	fprintf(stderr, "Failed to get stdout handle - line %d\n", line);

	exit(-1);
}

void err_window_info(int line) {
	fprintf(stderr, "Failed to set console window info - line %d\n", line);

	exit(-1);
}

void err_buffer_size(int line) {
	fprintf(stderr, "Failed to set console screen buffer size - line %d\n", line);

	exit(-1);
}

void err_console_window(int line) {
	fprintf(stderr, "Failed to get console window handler - line %d\n", line);

	exit(-1);
}

void err_create_buffer(int line) {
	fprintf(stderr, "Failed to create console screen buffer - line %d\n", line);

	exit(-1);
}

void err_cursor_info(int line) {
	fprintf(stderr, "Failed to set console cursor info - line %d\n");

	exit(-1);
}
/*
### Initializations
memeory allocation
file opening
*/

void err_memory_alloc(int line) {
	fprintf(stderr, "Dynamic memory allocation failed - line %d\n", line);

	exit(-1);
}

void err_file_opening(int line) {
	fprintf(stderr, "Failed to open file - line %d\n", line);

	exit(-1);
}