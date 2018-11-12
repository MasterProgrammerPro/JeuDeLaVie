#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i]==-1) printf("| X "); else if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ", ligne[i]-1);
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	//printf("\n"); 
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 4); 
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int k=1, s = 1, v = 0;
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case 'n' :
			{//touche "n" pour d'entree un nouvelle grille(max 30 characters)
				char n[30];
				printf("fichier grille :");
				scanf("%s",n);
				init_grille_from_file(n,g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g);
				k = 1;
				break;
			}
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc,s,v);
				efface_grille(*g);
				printf("temps d'évolution: %d               ",k);
				affiche_grille(*g);
				printf("                                                 \r");
				k++;
				break;
			}
			case 'c' :
			{ //touche "c" pour changer entre cyclique et non cyclique
				s = 1 - s;
				break;
			}
			case 'v' :
			{ // touche "v" pour changer activer/desactiver vieillessement
				v = 1 - v;
				break;
			}
			case 'r' :
			{// touche "r" pour reset des ages
				reset_age(*g);
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
