CFLAGS = -g -Wall
IFLAGS = -Iinclude
OPATH = obj/
CPATH = src/

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin


main : main.o libjeu.a io.o
	gcc $(CFLAGS) -o main $(OPATH)main.o $(OPATH)io.o -L./lib/ -ljeu
	mv $@ bin/

main.o : main.c
grille.o : grille.c grille.h
jeu.o : jeu.c jeu.h grille.h
io.o : io.c io.h jeu.h grille.h



%.o : 
	gcc $(CFLAGS) -c $< $(IFLAGS)
	mv $@ $(OPATH)

libjeu.a : grille.o jeu.o
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)jeu.o
	ranlib libjeu.a
	mv libjeu.a lib/

clean : 
	rm obj/* bin/*
	
dist :
	tar -c src include doc  Makefile -Jf archive.tar.xz
