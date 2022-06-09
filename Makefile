All: Projet

dep.o: deplacement.c
	gcc -Wall -g -c -o dep.o deplacement.c
ctrlz.o: ctrlz.c
	gcc -Wall -g -c -o -fsanitize=address ctrlz.o ctrlz.c
io.o : io.c
	gcc -Wall -g -c -o -fsanitize=address io.o io.c
modif_char.o: modif_char.c
	gcc -Wall -g -c -o -fsanitize=address modif_char.o modif_char.c
level.o : level_test.c
	gcc -Wall -g -c -o level.o level_test.c
menu.o: menu.c
	gcc -Wall -g -c -o -fsanitize=address menu.o menu.c
save.o: save.c
	gcc -Wall -g -c -o save.o save.c
Projet: dep.o ctrlz.o io.o modif_char.o level.o menu.o save.o
	gcc -Wall -o Projet dep.o ctrlz.o io.o modif_char.o level.o menu.o save.o
