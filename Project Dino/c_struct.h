#pragma once

// menu ui elements structure
// int x,y for coordinates
// char sprite for string
typedef struct UIElements {
	int x, y;
	char * sprite;
}UIElements;

// canvas ui elements structure
// int x,y for coordinates
// int z for iterations
// char sprite for string
typedef struct CanvasUIElements {
	int x, y, z;
	char * sprite;
}CanvasUIElements;