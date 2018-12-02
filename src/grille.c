/** 
 * \file grille.c 
 * code pour les grilles
 * \author SENOL Mustafa
 */

#include "grille.h"

/**
 * alloue et initalise la grille g à partir d'un fichier
 * \relatesalso grille
 * \param filename char*
 * \param g grille*
 * \returns nothing
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0,non_viables=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", & non_viables);
	for (n=0; n< non_viables; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		g->cellules[i][j]=-1;
	}

	
	fclose (pfile);
	return;
}

/**
 * recopie gs dans gd (sans allocation)
 * \relatesalso grille
 * \param gs grille
 * \param gd grille
 * \returns nothing
 */
void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

/**
 * alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 * \relatesalso grille
 * \param l int
 * \param c int
 * \param g	grille*
 * \returns nothing
 */
void alloue_grille (int l, int c, grille* g)
{
	g->nbl = l;
	g->nbc = c;
	g->cellules = malloc(l*sizeof(int *));
    for(int i=0; i< l; i++)
    {
        g->cellules[i] = malloc(c*sizeof(int));
    }
	for(int i =0; i < l; i++)
	{
		for(int j = 0; j < c; j++)
		{
			set_morte(i,j,*g);
		}
	}
}

/**
 * libère une grille
 * \relatesalso grille
 * \param g grille*
 * \returns nothing
 */
void libere_grille(grille* g)
{
	for(int i=0; i< g->nbl; i++)
    {
        free(g->cellules[i]);
    }
	free(g->cellules);
}

/**
 * reset ages de toutes les cellules
 * \relatesalso grille
 * \param g grille
 * \returns nothing
 */
void reset_age(grille g)
{
	for(int i = 0; i < g.nbl; i++)
	{
		for(int j =0; j < g.nbl; j++)
		{
			if (est_vivante(i,j,g))
			{	
				g.cellules[i][j] = 1;
			}
		}
	}
}

/**
 * test egalite de deux grilles
 * \relatesalso grille
 * \param g grille
 * \param g1 grille
 * \returns 1 if true ,0 if false
 */
int equal(grille g, grille g1)
{
	int r = 1;
	if(g.nbc != g1.nbc || g.nbl != g1.nbl)
	{
		r = 0;
	}
	for(int i = 0; i<g.nbc && r==1; i++)
	{
		for(int j = 0; j<g.nbl && r==1; j++)
		{
			if(g.cellules[j][i] != g1.cellules[j][i])
			{
				r = 0;
			}
		}
	}
	return r;
}