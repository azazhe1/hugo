#include <stdio.h>
#include <stdlib.h>
#include "define.h"


int Inverse_dir(int dir){
	switch(dir){
		case 0:
			return 1;
		case 1:
			return 0;
		case 2:
			return 3;
		case 3:
			return 2;
	}

	return -1;
}

void empiler(Mouvements **p, int _dir, int _dep_caisse){
	Mouvements *el = malloc(sizeof(Mouvements));

	el->dir = _dir;
	el->dep_caisse = _dep_caisse;

	if(*p == NULL){
		el->linked = NULL;
		*p = el;
	}
	else{
		el->linked = *p;
		*p = el;
	}
}

void sup(Mouvements **p){
	Mouvements *el;
	el = *p;
	*p = (*p)->linked;
	free(el);
}
int retour_en_arriere(Mouvements **p){
	int dir;
	int back_dir = -1;

	if(*p != NULL){
		dir = (*p)->dir;
		back_dir = Inverse_dir(dir);

		sup(p);
	}

	return back_dir;
}
