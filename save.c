#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "define.h"

void level_change(int num,char *namelevel){
  snprintf(namelevel,10,";LEVEL %d", num);
}

void empiler_(Mouvements **p, int _dir, int _dep_caisse){
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

void sup_(Mouvements **p){
	Mouvements *el;
	el = *p;
	*p = (*p)->linked;
	free(el);
}

int is_in(char *name){
	int value = 0;
  char *filename = "sauvegarde.txt";
  FILE *fp = NULL;
  fp=fopen(filename,"r");
  char *texte = malloc(sizeof(char*)*10000);
  if(fp == NULL){
		printf("Error: impossible de sauvegarder");
	}else{
	   while(fscanf(fp,"%[^\n]\n", texte) != EOF){
       if(strcmp(texte, name) == 0){
         value = 1;
       }
     }
   }
   free(texte);
	fclose(fp);
	return value;
}

void remplacer_file(char *name){
  char *filename = "sauvegarde.txt";
  FILE *fp = NULL;
  fp=fopen(filename,"r");
  char *newfilename = "replique.txt";
  FILE *newfp = NULL;
  newfp = fopen(newfilename,"w");
  char *texte =  malloc(sizeof(char*)*10000);
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
  free(texte);
}

void sauvegarde(Mouvements **Mapile, int num, int fin){
  char *filename = "sauvegarde.txt";
	FILE *fp  = NULL;
	fp = fopen(filename,"a");
	char namelevel[10];
	Mouvements *ptr = NULL;
  ptr = *Mapile;
  char newtab[5];
  level_change(num,namelevel);
  if(fp == NULL){
    printf("Error : NE PEUT PAS SAVE");
  }else{
    if(is_in(namelevel) == 1){
      remplacer_file(namelevel);
      fp = fopen(filename,"a");
      fprintf(fp,"%s\n",namelevel);
      while(ptr != NULL){
  			newtab[0] = (ptr->dir) + '0';
  			newtab[1] = ',';
  			newtab[2] = (ptr->dep_caisse) + '0';
  			newtab[3] = '/';
  			newtab[4] ='\0';
  			ptr = ptr->linked;
        fprintf(fp,"%s",newtab);
      }

    }else{
      fprintf(fp,"%s\n",namelevel);
      while(ptr != NULL){
  			newtab[0] = (ptr->dir) + '0';
  			newtab[1] = ',';
  			newtab[2] = (ptr->dep_caisse) + '0';
  			newtab[3] = '/';
  			newtab[4] ='\0';
  			ptr = ptr->linked;
        fprintf(fp,"%s",newtab);
      }

    }
    if(fin == 1){
      fprintf(fp, "%s\n","A");
    }else{
      fprintf(fp, "%s\n","B");
    }

  }
  fclose(fp);
}
int use_sauvegarde(Mouvements **Mapile, int level){
  char *filename = "sauvegarde.txt";
  FILE *fp  = NULL;
  fp = fopen(filename,"r");
  char namelevel[10];
  int value = 2;
  level_change(level,namelevel);
  char *texte = malloc(sizeof(char *)* 10000);
  if(is_in(namelevel) == 1)
  fscanf(fp,"%[^\n]\n", texte);
  while(strcmp(texte, namelevel) != 0){
    fscanf(fp,"%[^\n]\n", texte);
  }
  fscanf(fp,"%[^\n]\n", texte);
  for(int i = 0; i<(strlen(texte)-4); i++){
    empiler_(Mapile,texte[i] -'0', texte[i + 2] -'0');
    i = i +3;
  }
  if(texte[strlen(texte) -1] == 'A'){
    value = 0;
  }else if(texte[strlen(texte) -1] == 'B'){
    value = 1;
  }else{
    printf("pas de sauvegarde\n");
  }
  free(texte);
  fclose(fp);


  return value;
}
/*
int main(void){
    Mouvements *Mapile = NULL;
    empiler_(&Mapile, 1,2);
    empiler_(&Mapile, 0,3);
    empiler_(&Mapile, 1,0);
    empiler_(&Mapile, 4,0);
    empiler_(&Mapile, 1,3);
    sauvegarde(&Mapile, 2, 0);
    sauvegarde(&Mapile,3,1);
    sauvegarde(&Mapile,4,1);
    sauvegarde(&Mapile,2,0);
    while(Mapile != NULL){
      sup_(&Mapile);
    }

    printf("%d\n",use_sauvegarde(&Mapile));
    while(Mapile != NULL){
      sup_(&Mapile);
    }
}
*/
