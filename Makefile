CFLAGS = -g -Wall
IFLAGS = -Iinclude
OPATH = obj/
CPATH = src/

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin


main : main.o grille.o jeu.o io.o
	gcc $(CFLAGS) -o main $(OPATH)main.o $(OPATH)grille.o $(OPATH)jeu.o $(OPATH)io.o
	mv $@ bin/

main.o : main.c
grille.o : grille.c grille.h
jeu.o : jeu.c jeu.h grille.h
io.o : io.c io.h jeu.h grille.h

%.o : 
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

clean : 
	rm obj/* bin/*
	
dist :
	tar -c src include doc  Makefile -Jf archive.tar.xz