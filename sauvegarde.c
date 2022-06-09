#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include <string.h>


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
void remplacer_file(char *name){
  char *filename = "sauvegarde.txt";
  FILE *fp = NULL;
  fp=fopen(filename,"r");
  char *newfilename = "replique.txt";
  FILE *newfp = NULL;
  newfp = fopen(newfilename,"w");
  char *texte = malloc(sizeof(char *));
  fscanf(fp,"%[^\n]\n", texte);
  while(strcmp(texte, name) != 0){
    fprintf(newfp,"%s\n",texte);
    fscanf(fp,"%[^\n]\n", texte);
  }
  fscanf(fp,"%[^\n]\n", texte);
  while(fscanf(fp,"%[^\n]\n", texte) != EOF){
    fprintf(newfp,"%s\n",texte);
  }

  fclose(fp);
  fclose(newfp);
  remove(filename);
  rename(newfilename, filename);
}

void reverse(char tab[], int n)
{
    int aux[n];

    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = tab[i];
    }

    for (int i = 0; i < n; i++) {
        tab[i] = aux[i];
    }
}

int is_in(char *name){
	int value = 0;
  char *filename = "sauvegarde.txt";
  FILE *fp = NULL;
  fp=fopen(filename,"r");
  char *texte = malloc(sizeof(char *));
  //texte[0] = '\0';
  if(fp == NULL){
		printf("Error: impossible de sauvegarder");
	}else{
	   while(fscanf(fp,"%[^\n]\n", texte) != EOF){
       if(strcmp(texte, name) == 0){
         value = 1;
       }
     }
   }
	return value;
}

void sauvegarde(Mouvements **p, char *level){
	char *filename = "sauvegarde.txt";
	FILE *fp = fopen(filename,"a");
	char *namelevel = malloc(sizeof(char *));
	char *tableau = (char *) malloc( 40 );
	Mouvements *ptr = NULL;
	ptr = (*p);
	char newtab[5];
  namelevel[0] = ';';
  strcat(namelevel,level);

	if(fp == NULL){
		printf("Error: impossible de sauvegarder");
	}
	if(*p == NULL){
	}else{
		    if(is_in(namelevel) == 0){
		fprintf(fp,"%s\n",namelevel);
		while((ptr) != NULL){
			newtab[0] = '/';
			newtab[1] = (ptr->dep_caisse) + '0';
			newtab[2] = ',';
			newtab[3] = (ptr->dir) + '0';
			newtab[4] ='\0';
			strcat(tableau,newtab);
			ptr = ptr->linked;

		}
		reverse(tableau, strlen(tableau));
		fprintf(fp,"%s\n",tableau);

	}else{
    remplacer_file(namelevel);
    fp = fopen(filename,"a");
    fprintf(fp,"%s\n",namelevel);
		while((ptr) != NULL){
			newtab[0] = '/';
			newtab[1] = (ptr->dep_caisse) + '0';
			newtab[2] = ',';
			newtab[3] = (ptr->dir) + '0';
			newtab[4] ='\0';
			strcat(tableau,newtab);
			ptr = ptr->linked;

		}
		reverse(tableau, strlen(tableau));
		fprintf(fp,"%s\n",tableau);

  }
}
  //free(ptr);
//  free(tableau);
	fclose(fp);
}
void use_sauvegarde(char *name,Mouvements **Mapile){
  char *filename = "sauvegarde.txt";
  FILE *fp = NULL;
  fp=fopen(filename,"r");
  char *texte = malloc(sizeof(char *));
  //texte[0] = '\0';
  if(fp == NULL){
		printf("Error: impossible lancer la sauvegarde");
	}else{
    if(is_in(name) == 0){
      printf("il n'y a pas de sauvegarde\ns");
    }else{
      fscanf(fp,"%[^\n]\n", texte);
      while(strcmp(texte, name) != 0){
        fscanf(fp,"%[^\n]\n", texte);
      }
      fscanf(fp,"%[^\n]\n", texte);
      printf("le pile vaut %s\n",texte );
    }
  }
}

int main(void){
	Mouvements *Mapile = NULL;
	//struct item manu;
	//char vall = '$';
	empiler(&Mapile, 1 ,0);
	empiler(&Mapile, 3 ,1);
	empiler(&Mapile, 2 ,1);
	empiler(&Mapile, 0 ,1);
	empiler(&Mapile, 0 ,0);
	sauvegarde(&Mapile,"LEVEL 1");
  use_sauvegarde(";LEVEL 1",&Mapile );
}
