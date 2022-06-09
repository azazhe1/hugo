#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void modify_char_in_map(char replace,int x,int y,char *map[]){

	int len = strlen(map[y]);
	char *line = malloc((1+len)*sizeof(char));

	memcpy(line,map[y],len);

	line[len] = '\0';

	map[y] = line;
  map[y][x] = replace;
}


/*
int main(){

	char *map[] ={"##########",
         	     "##########",
		     "##########"};
	for(int i=0; i<10; i++){
		Ntm('.',i,1,map);
	}

	printf("%s\n",map[1]);
}
*/
