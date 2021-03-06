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

/**
 * calcul de periode d'une colonie oscillente
 * \relatesalso grille
 * \param s int
 * \param v int
 * \param g grille
 * \returns la periode
 */
int oscillente(grille g,int s, int v)
{
	int k = 1;	
	grille g1, g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	evolue(&g1,&g2,s,v);
	while(equal(g,g1)==0 && k<M)
	{
		evolue(&g1,&g2,s,v);
		k++;
	}
	libere_grille(&g1);
	libere_grille(&g2);
	return k;
}

/**
 * calcul si un colonie est oscillente ou pas
 * \relatesalso grille
 * \param s int
 * \param v int
 * \param g grille
 * \returns 0 si pas oscillente, 1 si oscillente
 */
int oscillenteau(grille g,int s, int v)
{
	int k = 0,r=0;	
	grille g1, g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	evolue(&g1,&g2,s,v);
	while(equal(g,g1)==0 && k<M)
	{
		evolue(&g1,&g2,s,v);
		k++;
	}
	if(k==M || k==0)
	{
		r = 0;
		//printf("pas oscillent");
	}
	else
	{
		r = 1;
		//printf("oscillent");
	}
	libere_grille(&g1);
	libere_grille(&g2);
	return r;
}

/**
 * affichage si un colonie est oscillente ou pas
 * \relatesalso grille
 * \param s int
 * \param v int
 * \param g grille
 * \returns nothing
 */
void oscillentedeux(grille g, int s, int v)
{
	int k =0,r=0;
	grille g1, g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	while (k<M && r==0)
	{
		r = oscillenteau(g1,s,v);
		evolue(&g1,&g2,s,v);
		k++;
	}
	if(r==0)
	{
		printf("jamais oscillente                                  \r");
	}
	else if(k == 1)
	{
		printf("oscillente et son period est %d",oscillente(g,s,v));
	}
	else
	{
		//printf("oscillente et son period est %d",oscillente(g2,s,v));
		printf("va etre oscillente apres %d pas                    \r",k);
	}
}

/**
 * calcul la type de colonie
 * \relatesalso grille
 * \param s int
 * \param v int
 * \param g grille
 * \returns 0 si la colonie n'est pas oscillente,1 si il oscille jamais et 2 si il oscille
 */
int oscillentePaint(grille g, int s, int v)
{
	int k =0,r=0,q=0;
	grille g1,g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	while (k<M && r==0)
	{
		r = oscillenteau(g1, s,v);
		evolue(&g1,&g2,s,v);
		k++;
	}
	if(r==0)
	{
		q=0;
	}
	else if(k != 1)
	{
		q=1;
	}
	else
	{
		q=2;
	}
	libere_grille(&g1);
	libere_grille(&g2);
	return q;
}

/**
 * il calcul quand la colonie va etre oscillante
 * \relatesalso grille
 * \param s int
 * \param v int
 * \param g grille
 * \returns dans combien pas la colonie va etre oscillante
 */
int oscillentetrois(grille g, int s, int v)
{
	int k =0,r=0;
	grille g1, g2;
	alloue_grille(g.nbl,g.nbc,&g1);
	alloue_grille(g.nbl,g.nbc,&g2);
	copie_grille(g,g1);
	copie_grille(g,g2);
	while (k<M && r==0)
	{
		r = oscillenteau(g1,s,v);
		evolue(&g1,&g2,s,v);
		k++;
	}
	return k-1;
}
