#pragma once

// game object collider
typedef struct collider {
	int x1, y1, x2, y2;
}collider;

// textures in a simple format
typedef struct raw_sprites {
	char * str;
	int x, y;
	int n_colliders;
	collider * colliders;
}raw_sprites;

// Game Object's structure (coord, sprite, spr_coord)
typedef struct object {
	int x, y;
	char sprite[10][15];
	int sx, sy;
	int n_colliders;
	collider colliders[3];
}object;