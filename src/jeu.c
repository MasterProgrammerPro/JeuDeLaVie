/** 
 * \file jeu.c 
 * code pour le jeu
 * \author SENOL Mustafa
 */

#include "jeu.h"

/**
 * compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont cycliques.
 * \relatesalso grille
 * \param i int
 * \param j int
 * \param g grille
 * \returns le nombre de voisins vivants de la cellule (i,j)
 */
int compte_voisins_vivants_cyclique (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}

/**
 * compte le nombre de voisins vivants de la cellule (i,j)
 * les bords sont cycliques.
 * \relatesalso grille
 * \param i int
 * \param j int
 * \param g grille
 * \returns le nombre de voisins vivants de la cellule (i,j)
 */
int compte_voisins_vivants_non_cyclique (int i, int j, grille g)
{
	int v = 0, l=g.nbl, c = g.nbc;
    if (i-1 >= 0)
    {
        v+= est_vivante(i-1,j,g);
        if (j-1 >= 0)
        {
            v+= est_vivante(i-1,j-1,g);
            v+= est_vivante(i,j-1,g);
        }
        if (j+1 < c)
        {
            v+= est_vivante(i-1,j+1,g);
            v+= est_vivante(i,j+1,g);
        }
    }
    if(i+1 < l)
    {
        v+= est_vivante(i+1,j,g);
        if(j-1 >= 0)
        {
            v+= est_vivante(i+1,j-1,g);
        }
        if(j+1 < c)
        {
            v+= est_vivante(i+1,j+1,g);
        }
    }
	return v;
}

/**
 * fait évoluer la grille g d'un pas de temps
 * \relatesalso grille
 * \param g grille*
 * \param gc grille*
 * \param s int
 * \param k int
 * \returns nothing
 */
void evolue (grille *g, grille *gc, int s, int k ){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	int (* compte_voisins_vivants) (int, int, grille);
	if(s == 1)
	{
		compte_voisins_vivants = &compte_voisins_vivants_cyclique;
	}
	else
	{
		compte_voisins_vivants= &compte_voisins_vivants_non_cyclique;
	}
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			v = (*compte_voisins_vivants)(i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if ( v!=2 && v!= 3 )
				{
					set_morte(i,j,*g);
				}
				else if (k == 1)
				{
					vieillir(i,j,*g);
					if ( g->cellules[i][j] > 9 )
					{
						set_morte(i,j,*g);
					}
				}
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 && g->cellules[i][j] != -1) set_vivante(i,j,*g);
			}
		}
	}
	return;
}

int oscillente(grille g,int s, int v)
{
	int k = 1;	
	grille g1, g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	evolue(&g,&g1,s,v);
	while(equal(g,g2)==0 && k<1000)
	{
		evolue(&g,&g1,s,v);
		k++;
	}
	return k;
}

int oscillenteau(grille g,int s, int v)
{
	int k = 1,r=0;	
	grille g1, g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	evolue(&g,&g1,s,v);
	while(equal(g,g2)==0 && k<1000)
	{
		evolue(&g,&g1,s,v);
		k++;
	}
	if(k==1000 || k==1)
	{
		r = 0;
	}
	else
	{
		r = 1;
	}
	return r;
}

void oscillentedeux(grille g, int s, int v)
{
	int k =0,r=0;
	grille g1, g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	evolue(&g,&g1,s,v);
	while (k<1000 && r==0)
	{
		r = oscillenteau(g1,s,v);
		k++;
	}
	if(r==0)
	{
		printf("jamais oscillente                                  \r");
	}
	else if(k != 1)
	{
		printf("va etre oscillente apres %d pas                    \r",k);
	}
	else
	{
		printf("oscillente et son period est %d",oscillente(g,s,v));
	}
}





































