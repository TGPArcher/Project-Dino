#pragma once

// point coordinates data
typedef struct pos {
	int x, y;
}pos;

// game object collider
typedef struct collider {
	pos position1, position2;
}collider;

// textures in a simple format
typedef struct sprites {
	char * str;
	pos anchors;
	int n_colliders;
	collider * colliders;
}sprites;

// Game Object's structure (coord, sprite)
typedef struct object {
	pos position;
	sprites sprite;
}object;