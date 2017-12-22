#pragma once
#include <Windows.h>

typedef struct {
	CHAR_INFO tmp_buffer[2500];
	COORD tmp_buffer_size;
	COORD tmp_buffer_start;
	SMALL_RECT region_to_read;
}BUFFER_DATA;