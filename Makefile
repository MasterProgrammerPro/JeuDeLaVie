main : main.o grille.o jeu.o io.o
	gcc -g -o main main.o grille.o jeu.o io.o -lm

main.o : main.c
	gcc -g -c main.c

grille.o : grille.c grille.h
	gcc -g -c grille.c

jeu.o : jeu.c jeu.h grille.h
	gcc -g -c jeu.c

io.o : io.c io.h jeu.h grille.h
	gcc -g -c io.c

clean : 
	rm *.o main
	
dist :
	tar -c main.c grille.c grille.h jeu.c jeu.h io.c io.h  Makefile -Jf archive.tar.xz