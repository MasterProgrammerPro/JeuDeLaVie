/** 
 * \file io.h 
 * header pour affichage
 * \author SENOL Mustafa
 */

#ifndef __IO_H
#define __IO_H

#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#define SIZEX 1000
#define SIZEY 1000

//affichage d'un trait horizontal
void affiche_trait (int c);


//affichage d'une ligne de la grille
void affiche_ligne (int c, int* ligne);


//affichage d'une grille
void affiche_grille (grille g);


//effacement d'une grille
void efface_grille (grille g);


//debute le jeu
void debut_jeu(grille *g, grille *gc);

void paint(cairo_surface_t *surface, grille g,int c, int v);

int paint_jeu(grille *g,grille *gc);

#endif
