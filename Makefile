main : main.o grille.o jeu.o io.o
	gcc -o main main.o grille.o jeu.o io.o

main.o : main.c
	gcc -c main.c

grille.o : grille.c grille.h
	gcc -c grille.c

jeu.o : jeu.c jeu.h grille.h
	gcc -c jeu.c

io.o : io.c io.h jeu.h grille.h
	gcc -c io.c

clean : 
	rm *.o main