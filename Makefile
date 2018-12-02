CFLAGS = -g -Wall
IFLAGS = -Iinclude
OPATH = obj/
CPATH = src/
CPPFLAGS += -Iinclude -I/usr/include/cairo
LDFLAGS += -lcairo -lm -lX11


vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

ifeq (TEXTE,$(MODE))

main : main.o libjeu.a io.o
	gcc $(CFLAGS) -o main $(OPATH)main.o $(OPATH)io.o -L./lib/ -ljeu $(LDFLAGS)
	mkdir -p bin/
	mv $@ bin/

main.o : main.c
grille.o : grille.c grille.h
jeu.o : jeu.c jeu.h grille.h
io.o : io.c io.h jeu.h grille.h


%.o : 
	gcc $(CFLAGS) -c $< $(CPPFLAGS) $(LDFFLAGS)
	mkdir -p obj/
	mv $@ $(OPATH)

libjeu.a : grille.o jeu.o
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)jeu.o
	ranlib libjeu.a
	mkdir -p lib/
	mv libjeu.a lib/
else

main : graph.o libjeu.a io.o	
	gcc $(CFLAGS) -o main $(OPATH)graph.o $(OPATH)io.o -L./lib/ -ljeu $(LDFLAGS)
	mkdir -p bin/
	mv main bin/

graph.o : graph.c
grille.o : grille.c grille.h
jeu.o : jeu.c jeu.h grille.h
io.o : io.c io.h jeu.h grille.h


%.o : 
	gcc $(CFLAGS) -c $< $(CPPFLAGS) $(LDFFLAGS)
	mkdir -p obj/
	mv $@ $(OPATH)

libjeu.a : grille.o jeu.o
	ar -crv libjeu.a $(OPATH)grille.o $(OPATH)jeu.o
	ranlib libjeu.a
	mkdir -p lib/
	mv libjeu.a lib/

endif

clean : 
	rm obj/* bin/*
	
dist :
	tar -c src include doc  Makefile -Jf archive.tar.xz
