/** 
 * \file graph.c 
 * code principal pour version graphique
 * \author SENOL Mustafa
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"




int main (int argc, char ** argv)
{
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}
	
	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);
	
	paint_jeu(&g,&gc);
	
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
