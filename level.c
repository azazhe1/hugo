/**
 * \file level.c
 * \brief Programme pour les level.
 * \author Quentin.L
 *
 * Programme pour recuperer un level dans le fichier source des level et le stocker dans un tableau a double entrée.
 * On recuper aussi la postion du manutencier.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
/**
 * \def MAX_LIGNE
 * \brief Définit le nombre max de caratere des ligne du fichier levels.lvl : 100.
*/

int level_choisi()
{
	int level=1;
	printf("Donner un level : ");
	scanf("%d",&level);
	printf("Level choisi : %d\n",level);
	return level;
}


/**
 * \fn void init_tableau(char tab[], int taille_ligne)
 * \brief fonction pour initialiser un tableau de char a 1 entrée.
 *
 * \param tab Tableau a initialiser.
 * \param taille_ligne Taille des ligne du tableau
 * \return Pas de return car fonction void.
 */
void init_tableau(char tab[], int taille_ligne)
{
	for(int i=0; i<=taille_ligne; i++)
	{
		tab[i]='\0';
	}
}


/**
 * \fn void init_tableau2(char** tab, int taille_ligne , int taille_collone)
 * \brief Fonction pour initialiser un tableau de char a 2 entrée.
 *
 * \param tab Tableau a initialiser.
 * \param taille_ligne Nombre de ligne du tableau.
 * \param taille_collone Taille des collones du tableau.
 * \return Pas de return car fonction void.
 */
void init_tableau2(char** tab, int taille_ligne , int taille_collone)
{


	for(int i=0; i<taille_ligne; i++)
	{
		for(int j=0; j<taille_collone; j++)
		{
			tab[i][j]='\0';
		}
	}
}


/**
 * \fn void afficher_tableau2(char** tab, char nbr_ligne, char taille_collone)
 * \brief Fonction pour afficher un tableau de char a 2 entrée.
 *
 * \param tab Tableau a afficher.
 * \param taille_ligne Nombre de ligne du tableau.
 * \param taille_collone Taille des collones du tableau.
 * \return Pas de return car fonction void.
 */
void afficher_tableau2(char** tab, int nbr_ligne)
{
	for(int i=0; i<nbr_ligne; i++)
	{
		printf("%s\n", tab[i]);
		/*
		for(int j=0; j<taille_collone; j++)
		{
			printf("%c", tab[i][j]);
		}
		printf("\n");
		*/
	}
}


/**
 * \fn void tableau_level(int nb_ligne, int ligne_debut, int taille_ligne)
 * \brief Fonction qui permet stocker le level dans un tableau.
 *
 * \param tab Tableau a double entree ou seront stocker la map.
 * \param ligne_debut Ligne de debut du niveau dans le fichier levels.lvl.
 * \return Pas de return car fonction void.
 */
void tableau_level(char** tab, int ligne_debut, int nb_ligne,int ligne_plus_grande,int *pos_manu_x, int *pos_manu_y)
{
	FILE *fichier= NULL;
	char chaine[MAX_LIGNE];
	int compteur_map=0;
	int compteur_ligne=0;
	char caractere_actuel;

	init_tableau2(tab,nb_ligne,ligne_plus_grande);

	fichier = fopen("levels.lvl", "r");

	//placement du pointeur au debut de la map
	for(int j=0; j<ligne_debut-2;j++) // Moins 2 car au debut du fichier il y a 2 ligne vide qui ne sont pas compté par a la comande fscanf
	{
		fscanf(fichier,"%[^\n]\n",chaine);
	}
	while((caractere_actuel=fgetc(fichier))!='\n')

	init_tableau(chaine, MAX_LIGNE);

	//on parcours le level ne recuperant chaque caractere de chaque ligne et on le stock dans le tableau
	while((caractere_actuel=fgetc(fichier))!=';' && caractere_actuel!=EOF)
	{
		if(caractere_actuel!='\n')
		{
			tab[compteur_map][compteur_ligne]=caractere_actuel;
            // On recuper la postion de manu
            if(tab[compteur_map][compteur_ligne] == '@')
            {
                *pos_manu_x = compteur_ligne;
                *pos_manu_y = compteur_map;
            }
			compteur_ligne++;
		}
		else
		{
			compteur_map++;
			compteur_ligne=0;
		}
	}
	fclose(fichier);
}


/**
 * \fn void ligne_tableau()
 * \brief Fonction qui permet de recupere les infos de la postion du level dans le fichier.
 *
 * \return Pas de return car fonction void.
 */
int ligne_tableau(int level_choisi,int *nb_ligne, int *ligne_depart, int* ligne_plus_grande)
{
	FILE* fichier= NULL;
	char c[MAX_LIGNE];
	int caractere_actuel;
	init_tableau(c, MAX_LIGNE);

	fichier = fopen("levels.lvl","r");

	int controle_level=';';
	int controle_ligne='\n';

	int level_trouver=0;

	char level[10];
	snprintf(level,10,";LEVEL %d",level_choisi);

	// On recupere les lignes du fichier, on les affiche puis on les compare pour trouve
	// le level 1 a ce moment on connais la ligne de depart du niveau 1
	do
	{
		/*verifiation qu'on n'atteind pas la fin du fichier avant d'avoir trouver le niveau*/
		caractere_actuel=fgetc(fichier);
		if(caractere_actuel==EOF)
		{
				printf("Level non repertorié\n");
				level_trouver=1;
				break;
		}
		fseek(fichier,-1,SEEK_CUR); //On replace le curseur au debut de la la ligne pour continuer a compter les lignes

		fscanf(fichier,"%[^\n]\n",c);
		(*ligne_depart)++;

	}while(strcmp(c,level)!=0);

if(level_trouver==0)
{
	//on regarde si la ligne apres le level est pas une ligne de description
	while(1)
	{
		caractere_actuel=fgetc(fichier);
		if(caractere_actuel==controle_level) //si ';' alors on passe la ligne
		{
			while((caractere_actuel=fgetc(fichier))!=controle_ligne);
			(*ligne_depart)++;
		}
		else
		{
			break;
		}
	}
//	printf("la ligne de depart du niveau est : %d\n", ligne_depart);
	*ligne_plus_grande=strlen(c);

	//Ici on recuper chaque ligne on les compare pour trouve le level suivant on connais alors la ligne de fin
	//donc le nbr de ligne d'un niveau
	int compteur_ligne=0;
	while(1)
	{
		caractere_actuel=fgetc(fichier);
		compteur_ligne++;
		if(caractere_actuel==controle_ligne)
		{
			(*nb_ligne)++;
			if(*ligne_plus_grande<compteur_ligne) //On chercher la ligne la plus grande
			{
				*ligne_plus_grande=compteur_ligne;
			}
			compteur_ligne=0;
		}
		if(caractere_actuel==controle_level||caractere_actuel==EOF)
		{
			break;
		}
	}
//	printf("Le nombre de ligne du niveau est : %d\n", nb_ligne);
//	printf("La plus grnde ligne est : %d\n", ligne_plus_grande);
}
	fclose(fichier);
	return level_trouver;
}

/**
 * \fn void iniatilisation_jeu(char** tab)
 * \brief Initialise le jeu en renvoyant la position du manutencier au depart, le level de depart et un tableau permetant la modifiction pour le jeu.
 *
 * \return Pas de return car fonction void.
 */
 /*
int  main(int argc, char *argv[])
{
    ligne_tableau();
    //creation du tableau de depart
    char **tab_init= malloc(sizeof(*tab_init) * nb_ligne);

    for (int i = 0; i < 20; i++)
    {
        tab_init[i] = malloc(sizeof(**tab_init) * ligne_plus_grande);
    }

    //creation du talbeau pour les modification
    char **tab_jeu= malloc(sizeof(*tab_jeu) * nb_ligne);

    for (int i = 0; i < 20; i++)
    {
        tab_jeu[i] = malloc(sizeof(**tab_jeu) * ligne_plus_grande);
    }

    // Remplissage des tableau
    tableau_level(tab_init,ligne_depart);
    tableau_level(tab_jeu,ligne_depart);

    afficher_tableau2(tab_init,nb_ligne,ligne_plus_grande);
    //afficher_tableau2(tab_jeu,nb_ligne,ligne_plus_grande);
    return EXIT_SUCCESS;
}
*/
