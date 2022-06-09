#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include <unistd.h>

void get_voisin(int x, int y, char *map[], Item voisins[4]){


	voisins[0].obj = map[y-1][x];
	voisins[1].obj = map[y+1][x];
	voisins[2].obj = map[y][x-1];
	voisins[3].obj = map[y][x+1];

	for(int i =0; i<4; i++){
		if(voisins[i].obj == '*'){
			voisins[i].obj = '$';
		}
	}

	voisins[0].x = x;
	voisins[0].y = y-1;

	voisins[1].x = x;
	voisins[1].y = y+1;

	voisins[2].x = x-1;
	voisins[2].y = y;

	voisins[3].x = x+1;
	voisins[3].y = y;

}

void set_voisin(Item *Objet, char *map[]){

	get_voisin(Objet->x,Objet->y,map,Objet->voisin);
}

void affiche_voisins(Item objet){
	printf("voisins de %c:\n",objet.obj);

	for(int i=0; i<4; i++){
		printf("	num %d : [%d,%d,%c]\n\n", i, objet.voisin[i].x, objet.voisin[i].y, objet.voisin[i].obj);
	}
}

int can_move(Item *objet, int dir, char *map[]){
	objet->voisin = malloc(4*sizeof(Item));
	set_voisin(objet,map);

	if((objet->voisin)[dir].obj == '#'){
		return 0;
	}

	else if((objet->voisin)[dir].obj == '$'){
		switch(objet->obj){
			case '$':
				return 0;
			case '@':
				return can_move(&((objet->voisin)[dir]),dir,map);

		}
	}

	return 1;
}

void Update_item_on_map(Item prev, Item next, char *map[], char *points[], int *score){
	modify_char_in_map(points[prev.y][prev.x],prev.x,prev.y,map);

	if(points[next.y][next.x] == '.' && next.obj == '$'){
		next.obj = '*';

		if(map[prev.y][prev.x] != '.'){
			*score += 1;
		}

	}
	else if(points[next.y][next.x] == ' ' && points[prev.y][prev.x] == '.' && next.obj == '$'){
		*score -= 1;
	}

	modify_char_in_map(next.obj,next.x,next.y,map);
}


void deplace(Item *manu, int dir, char *map[],char *points[], int *score){
	Item previous = *manu;
	Item current;

	switch(dir){
		case 0:
			manu->y = (manu->y)-1;break;
		case 1:
			manu->y = (manu->y)+1;break;
		case 2:
			manu->x = (manu->x)-1;break;
		case 3:
			manu->x = (manu->x)+1;break;
	}

	current = *manu;

	Update_item_on_map(previous,current,map,points,score);
}

void move(Item *manu, int dir, char *map[],char *points[], int *mov_j, int *mov_c, int *score,int retour, Mouvements **mvmts_manu,int dep_c){

	int dep_caisse = 0;
	Item *caisse;

	if(can_move(manu,dir,map)){
		if(!retour){

			if((manu->voisin)[dir].obj=='$'){
				caisse = &((manu->voisin)[dir]);

				deplace(caisse,dir,map,points,score);

				dep_caisse = 1;
				*mov_c += 1;
			}

			empiler(mvmts_manu,dir,dep_caisse);
			deplace(manu,dir,map,points,score);
			*mov_j += 1;

		}
		else{
			deplace(manu,dir,map,points,score);
			*mov_j -= 1;

			if(dep_c){
				caisse = &((manu->voisin)[Inverse_dir(dir)]);

				deplace(caisse,dir,map,points,score);
				*mov_c -= 1;
			}
		}
	}

}

void get_points_on_map(char *map[], char *points[], int lignes, int *n_points){

	int nombre_colonnes;

	for(int i = 0; i<lignes; i++){
		nombre_colonnes = strlen(map[i]);

		char *new_ligne = malloc((nombre_colonnes+1)*sizeof(char));

		for(int j=0; j<nombre_colonnes; j++){
			if(map[i][j] == '.'){
				new_ligne[j] = '.';
				*n_points += 1;
			}
			else{
				new_ligne[j] = ' ';
			}
		}

		new_ligne[nombre_colonnes] = '\0';
		points[i] = new_ligne;

	}

}

void reset_map(char ***map,char ***points){
	*** map = '\0';
	*** points = '\0';

	free(map);
}

void load_level(char ***map,char ***points,int *nombre_points,Item *manu,int *nb_ligne,int carractere_depart,int ligne_plus_grande, int *cont){

	(*map) = malloc(sizeof(char*) * (*nb_ligne));
	(*points) = malloc(sizeof(char*) * (*nb_ligne));

	for (int i = 0; i < ligne_plus_grande; i++)
	{
			(*map)[i] = malloc(sizeof(char) * ligne_plus_grande);
			(*points)[i] = malloc(sizeof(char) * ligne_plus_grande);
	}


	tableau_level((*map), carractere_depart, *nb_ligne,ligne_plus_grande);
	get_points_on_map((*map), (*points), *nb_ligne, nombre_points);

	*cont = 1;
}

int main(){

	int dep_caisse = 0;
	int dir;
	int retour = 0;

	Item manu;
	manu.obj = '@';

	int cont = 0;
	int fin = 0;

	int mov_j = 0;
	int mov_c = 0;

	int ligne_plus_grande=0;
	int nb_ligne=0;
	int carractere_depart = 0;

	int nombre_points = 0;
	int score = 0;
	int level = 1;

	int select = 0;
	int cursor = 0;
	int n = 8;

	int x = 0;
	int y = 0;

	int solved;
	int finished = 0;

	char **map;
	char **points;

	Mouvements *pile_sauvegarde = NULL;
	Mouvements *Mouvements_manu = NULL;
//INITIALISATION||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
	level = level_choisi();

	int verif = ligne_tableau(level,&nb_ligne, &carractere_depart, &ligne_plus_grande, &x,&y);

	manu.x = x;
	manu.y = y;

	printf("%d %d\n",manu.x,manu.y);

	if(verif){

		load_level(&map,&points,&nombre_points,&manu,&nb_ligne,carractere_depart,ligne_plus_grande, &cont);

		//INITIALISATION|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


		while(!fin){
			if((score < nombre_points && dir != -1) || cont){

				cont = 0;

				printf("nombre de mouvements du joueur = %d\nnombre de mouvement de caisse = %d\n",mov_j,mov_c);
				printf("score : %d\n", score);
				afficher_tableau2(map,nb_ligne);


				dir = direction();

				printf("\033\143");

				if(dir == 126 && Mouvements_manu != NULL){

					dep_caisse = Mouvements_manu->dep_caisse;
					dir = retour_en_arriere(&Mouvements_manu);
					retour = 1;

				}else{

					retour = 0;

				}

				if(dir >= 0 && dir <= 3){
					move(&manu,dir,map,points,&mov_j,&mov_c,&score,retour,&Mouvements_manu,dep_caisse);
				}



				//afficher_tableau2(map,nb_ligne,ligne_plus_grande);
			}
			else{
				printf("\033\143");
				char *selection[] = {"EXIT","CONTINUE","RESTART","NEXT LEVEL","NEW LEVEL","SAVE","RELOAD SAVE","VIEW YOUR SOLUTION"};
				cursor = 0;
				while(cursor != 9 ){

					Update_select(&select,cursor,n);
					menu(selection,n,cursor,&select);

					if(solved == 1){
						printf("NO SOLUTION\n");
						solved = 0;
					}
					cursor = direction();
					printf("\e[1;1H\e[2J");
				}

				if(select == 0){
					fin = 1;
				}
				else if(select == 1){
					cont = 1;
				}
				else if(select == 3){
					level = level + 1;

					verif = ligne_tableau(level,&nb_ligne, &carractere_depart, &ligne_plus_grande,&x,&y);

					manu.x = x;
					manu.y = y;

					mov_c = 0;
					mov_j = 0;

					** map = '\0';
					** points = '\0';
					free(map);

					printf("ici\n");

					carractere_depart = 0;
					nb_ligne = 0;
					ligne_plus_grande = 0;

					if(!verif){
						printf("caca\n");
						level -= 1;
						verif = ligne_tableau(level,&nb_ligne, &carractere_depart, &ligne_plus_grande,&(manu.x),&(manu.y));
					}

					load_level(&map,&points,&nombre_points,&manu,&nb_ligne,carractere_depart,ligne_plus_grande, &cont);

					cont = 1;

					while(Mouvements_manu != NULL){
						sup(&Mouvements_manu);
					}
				}
				else if(select == 4){

					level = level_choisi();

					** map = '\0';
					** points = '\0';
					free(map);


					mov_c = 0;
					mov_j = 0;

					carractere_depart = 0;
					nb_ligne = 0;
					ligne_plus_grande = 0;

					verif = ligne_tableau(level,&nb_ligne, &carractere_depart, &ligne_plus_grande,&(manu.x),&(manu.y));

					if(verif){

						load_level(&map,&points,&nombre_points,&manu,&nb_ligne,carractere_depart,ligne_plus_grande, &cont);
					}

					cont = 1;
				}
				else if(select == 5){

					if(score >= nombre_points){
						finished = 1;
					}

					sauvegarde(&Mouvements_manu,level,finished);

					while(Mouvements_manu != NULL){
						sup_(&Mouvements_manu);
					}

					finished = 0;

				}
				else if(select == 7){
					solved = use_sauvegarde(&pile_sauvegarde,level);

					mov_c = 0;
					mov_j = 0;

					if(solved == 0){
						** map = '\0';
						** points = '\0';
						free(map);

						score = 0;
						nombre_points = 0;
						carractere_depart = 0;
						nb_ligne = 0;
						ligne_plus_grande = 0;

						verif = ligne_tableau(level,&nb_ligne, &carractere_depart, &ligne_plus_grande,&(manu.x),&(manu.y));

						if(verif){

							load_level(&map,&points,&nombre_points,&manu,&nb_ligne,carractere_depart,ligne_plus_grande, &cont);
						}

						cont = 1;

						while(pile_sauvegarde!=NULL){

							afficher_tableau2(map,nb_ligne);
							move(&manu,pile_sauvegarde->dir,map,points,&mov_j,&mov_c,&score,retour,&Mouvements_manu,dep_caisse);
							usleep(250000);
							printf("\033\143");
							sup(&pile_sauvegarde);

						}
					}
					else{
						printf("\n");
					}
				}
				else if(select == 6){
					solved = use_sauvegarde(&pile_sauvegarde,level);

					** map = '\0';
					** points = '\0';
					free(map);

					mov_c = 0;
					mov_j = 0;

					carractere_depart = 0;
					nb_ligne = 0;
					ligne_plus_grande = 0;
					score = 0;
					nombre_points = 0;

					verif = ligne_tableau(level,&nb_ligne, &carractere_depart, &ligne_plus_grande,&(manu.x),&(manu.y));

					if(verif){

						load_level(&map,&points,&nombre_points,&manu,&nb_ligne,carractere_depart,ligne_plus_grande, &cont);
					}

					cont = 1;

					while(pile_sauvegarde!=NULL){
						move(&manu,pile_sauvegarde->dir,map,points,&mov_j,&mov_c,&score,retour,&Mouvements_manu,dep_caisse);
						sup(&pile_sauvegarde);
					}

					pile_sauvegarde = NULL;

				}
				else if(select == 2){
					retour = 1;

					while(Mouvements_manu!=NULL){
						dep_caisse = Mouvements_manu->dep_caisse;
						dir = retour_en_arriere(&Mouvements_manu);
						move(&manu,dir,map,points,&mov_j,&mov_c,&score,retour,&Mouvements_manu,dep_caisse);
					}

					retour = 0;

				}
			}


		}
	}


}
