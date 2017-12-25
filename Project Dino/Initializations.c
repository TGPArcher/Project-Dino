#include <stdlib.h>
#include <stdio.h>
#include "c_struct.h"
#include "g_struct.h"

int get_UI_Elements(UIElements ** _menu_elements) {
	FILE * menu_file;
	fopen_s(&menu_file, "Menu_UI_Elements.txt", "r");

	int nr;
	fscanf_s(menu_file, "%d", &nr);

	*_menu_elements = (UIElements*)malloc(sizeof(UIElements) * nr);

	for (int i = 0; i < nr; i++) {
		int element_length;

		fscanf_s(
			menu_file,
			"%d %d %d ", 
			&(*_menu_elements)[i].x, 
			&(*_menu_elements)[i].y, 
			&element_length);

		(*_menu_elements)[i].sprite = (char*)malloc(sizeof(char) * element_length);
		
		fgets((*_menu_elements)[i].sprite, element_length, menu_file);
		fseek(menu_file, SEEK_CUR, 1);
	}

	fclose(menu_file);

	return nr;
}

int get_Canvas_Elements(CanvasUIElements ** _canvas_elements) {
	FILE * canvas_file;
	fopen_s(&canvas_file, "Canvas_UI_Elements.txt", "r");

	int nr;
	fscanf_s(canvas_file, "%d", &nr);

	*_canvas_elements = (CanvasUIElements*)malloc(sizeof(CanvasUIElements) * nr);

	for (int i = 0; i < nr; i++) {
		int element_length;

		fscanf_s(
			canvas_file,
			"%d %d %d %d ",
			&(*_canvas_elements)[i].x,
			&(*_canvas_elements)[i].y,
			&(*_canvas_elements)[i].z,
			&element_length);

		(*_canvas_elements)[i].sprite = (char*)malloc(sizeof(char)*element_length);
		
		fgets((*_canvas_elements)[i].sprite, element_length, canvas_file);
		fseek(canvas_file, SEEK_CUR, 1);
	}

	fclose(canvas_file);

	return nr;
}

// Load textures when the game starts
void set_sprites(sprites ** go_sprites) {

	FILE * go_file;
	fopen_s(&go_file, "GO_Elements.txt", "r");

	int nr;
	fscanf_s(go_file, "%d", &nr);

	*go_sprites = (sprites*)malloc(sizeof(sprites)*nr);

	for (int i = 0, sprite_length = 0; i < nr; i++) {
		fscanf_s(
			go_file,
			"%d %d %d ",
			&(*go_sprites)[i].anchors.x,
			&(*go_sprites)[i].anchors.y,
			&(*go_sprites)[i].n_colliders);

		(*go_sprites)[i].colliders = 
			(collider*)malloc(sizeof(collider)*(*go_sprites)[i].n_colliders);
		
		for (int j = 0; j < (*go_sprites)[i].n_colliders; j++) {
			fscanf_s(
				go_file,
				"%d %d %d %d ",
				&(*go_sprites)[i].colliders[j].position1.x,
				&(*go_sprites)[i].colliders[j].position1.y,
				&(*go_sprites)[i].colliders[j].position2.x,
				&(*go_sprites)[i].colliders[j].position2.y);
		}

		sprite_length = (*go_sprites)[i].anchors.x * (*go_sprites)[i].anchors.y + 1;
		
		(*go_sprites)[i].str = (char *)malloc(sizeof(char) * sprite_length);
		
		fgets((*go_sprites)[i].str, sprite_length, go_file);
		fseek(go_file, SEEK_CUR, 1);
		
		if((*go_sprites)[i].str[0] == '-')
			(*go_sprites)[i].str[0] = ' ';
	}

	fclose(go_file);
}