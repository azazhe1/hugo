typedef struct item{
	char obj;
	int x;
	int y;
	struct item * voisin;
}Item;

typedef struct mouvements{
        int dir;
				int dep_caisse;
        struct mouvements *linked;

}Mouvements;

#define MAX_LIGNE  100
#define clrscr() printf("\e[1;1H\e[2J");

void replace_caract(char *map[],int x, int y, char *caract);
void copier(char **list, int x);
void empiler(Mouvements **p, int dir, int dep_caisse);
void sup(Mouvements **p);
int retour_en_arriere(Mouvements **p);

void init_tableau(char tab[], int taille_ligne);
void init_tableau2(char** tab, int taille_ligne , int taille_collone);
void afficher_tableau2(char** tab, int nbr_ligne);
void tableau_level(char** tab, int ligne_debut, int nb_ligne,int ligne_plus_grande);
int ligne_tableau(int level_choisi,int *nb_ligne, int *carractere_depart, int* ligne_plus_grande,int *pos_manu_x, int *pos_manu_y);
int level_choisi();

int direction();
int Inverse_dir(int dir);
void modify_char_in_map(char replace,int x,int y,char *map[]);
void Update_select(int *select,int cursor,int n);
void menu(char **selection, int n, int cursor, int * select);

void sauvegarde(Mouvements **Mapile, int num, int fin);
void sup_(Mouvements **p);
int use_sauvegarde(Mouvements **Mapile, int level);
