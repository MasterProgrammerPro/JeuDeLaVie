#include "jeu.h"

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

