#include <stdio.h>
#include "define.h"

void Update_select(int *select,int cursor,int n){
	switch(cursor){
		case 3:
			if(*select<n-1){
				*select += 1;
			}
			break;
		case 2:
			if(*select>0){
				*select -= 1;
			}
			break;
	}
}

void menu(char **selection, int n, int cursor, int * select){

	for(int i=0; i<n; i++){
		if(i == *select){
			printf("\033[0;33m");
			printf("=> ");
		}else{
			printf("\033[0;37m");
			printf("   ");
		}

		printf("%s		",selection[i]);
	}

	printf("\033[0;37m");
	printf("\n");


}
/*
int main(){
	int cursor = 0;
	int select = 0;
	int n = 2;
	char *selection[] = {"EXIT","NEW LEVEL"};


	while(1){
		Update_select(&select,cursor,n);
		printf("%d\n",select);
		menu(selection,n,cursor,&select);
		cursor = direction();
	}


}*/
