/** 
 * \file io.c 
 * code pour affichage
 * \author SENOL Mustafa
 */

#include "io.h"
int temps=0;


/**
 * alloue et initalise la grille g à partir d'un fichier
 * \param *g int
 * \returns nothing
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

/**
 * affichage d'une ligne de la grille
 * \param int* ligne
 * \param c int
 * \returns nothing
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i]==-1) printf("| X "); else if (ligne[i] == 0 ) printf ("|   "); else printf ("| %d ", ligne[i]-1);
	printf("|\n");
	return;
}

/**
 * affichage d'une grille
 * \param g grille
 * \returns nothing
 */
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

/**
 * effacement d'une grille
 * \relatesalso grille
 * \param g grille
 * \returns nothing
 */
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 4); 
}

/**
 * debute le jeu
 * \relatesalso grille
 * \param g grille*
 * \param gc grille*
 * \returns nothing
 */
void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int k=1, s = 1, v = 0;
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case 'n' :
			{//touche "n" pour d'entree un nouvelle grille(max 30 characters)
				char n[30];
				printf("                                 \rfichier grille : ");
				scanf("%s",n);
				init_grille_from_file(n,g);
				alloue_grille (g->nbl, g->nbc, gc);
				affiche_grille(*g);
				k = 1;
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
			
			case 'o' :
			{//test oscillente
				oscillentedeux(*g,s,v);
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



/**
 * affichage graphique
 * \relatesalso grille
 * \param g grille
 * \param surface cairo_surface_t*
 * \param c int
 * \param v int
 * \param o int
 * \returns nothing
 */
void paint(cairo_surface_t *surface, grille g,int c, int v, int o)
{	 
	char temp[100];
	sprintf(temp,"%d",temps);
	
	char age[2];
	age[1]= '\n';  
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	// filled rectangle
	for(int i=0; i<g.nbl; i++)
	{
		for(int j=0; j<g.nbc; j++)
		{			
			cairo_rectangle(cr,j*CSIZE+30,i*CSIZE+30,CSIZE-1,CSIZE-1);
			if (g.cellules[i][j] == -1)
			{				
				cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
				cairo_fill(cr);
			}
			else if (g.cellules[i][j] == 0)
			{
				cairo_set_source_rgb (cr, 1.0, 1.0, 1.0);
				cairo_fill(cr);
			}
			else
			{ 				
				cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
				cairo_fill(cr);
				if(v==1)
				{
					sprintf(age,"%d",g.cellules[i][j]-1);
					cairo_select_font_face(cr,"fantasy",CAIRO_FONT_SLANT_ITALIC, CAIRO_FONT_WEIGHT_NORMAL);
					cairo_set_font_size(cr,0.5*CSIZE);
					cairo_set_source_rgb(cr,0.0,0.0,0.0);
					cairo_move_to(cr,j*CSIZE+45,i*CSIZE+56);
					cairo_show_text(cr,age);
				}
			}
		}
	}
	cairo_select_font_face(cr,"monospace",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*CSIZE);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,30,(g.nbl+2)*CSIZE);
	cairo_show_text(cr,"temps passe : ");
	cairo_show_text(cr,temp);
	cairo_move_to(cr,30,(g.nbl+3)*CSIZE);
	if(v==0)
	{	
		cairo_show_text(cr,"vieillissement pas active");
	}
	else
	{
		cairo_show_text(cr,"vieillissement active");
	}
	
	cairo_select_font_face(cr,"monospace",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*CSIZE);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,30,(g.nbl+4)*CSIZE);
	
	if(c==0)
	{	
		cairo_show_text(cr,"non cyclique");
	}
	else
	{
		cairo_show_text(cr,"cyclique");
	}
	cairo_select_font_face(cr,"monospace",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*CSIZE);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,30,(g.nbl+5)*CSIZE);
	if(o == 1)
	{
		if(oscillentePaint(g,c,v)==0)
		{			
			cairo_show_text(cr,"jamais oscillente");
		}
		else if(oscillentePaint(g,c,v)==1)
		{			
			char dans[1000];
			sprintf(dans,"%d",oscillentetrois(g,c,v));
			cairo_show_text(cr,"va etre oscillente dans ");
			cairo_show_text(cr,dans);
		}
		else if(oscillentePaint(g,c,v)==2)
		{
			char per[1000];
			sprintf(per,"%d",oscillente(g,c,v));			
			cairo_show_text(cr,"oscillente et sa periode est ");
			cairo_show_text(cr,per);
		}
	}
	cairo_destroy(cr); // destroy cairo mask
}



/**
 * debut jeu en graphique
 * \relatesalso grille
 * \param g grille*
 * \param gc grille*
 * \returns nothing
 */
void paint_jeu(grille *g, grille *gc)
{
	int s = 1, v = 0, o = 0;
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL)))
	{
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "Game of Life");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);
	//printf("\n\n\n%d",XKeysymToKeycode(dpy, 'r'));	
	// run the event loop
	while(1)
	{
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1)
		{
			paint(cs,*g,s,v,o);
		
		}
		if(e.xbutton.button == 1)
		{
			evolue(g,gc,s,v);
			temps++;
			paint(cs,*g,s,v,o);
		}	
		
		if(e.xkey.keycode == 32)//o
		{
			o = 1 - o;
			paint(cs,*g,s,v,o);
		}
		if(e.xkey.keycode == 54)//c
		{
			s = 1 - s;
			paint(cs,*g,s,v,o);
		}
		if(e.xkey.keycode == 55)//v
		{
			v = 1 - v;
			paint(cs,*g,s,v,o);
		}
		if(e.xkey.keycode == 27)//r
		{
			reset_age(*g);
			paint(cs,*g,s,v,o);
		}
		if(e.xkey.keycode == 57)//n
		{
			temps=0;
			char n[30];
			printf("                                 \rfichier grille : ");
			scanf("%s",n);
			init_grille_from_file(n,g);
			alloue_grille (g->nbl, g->nbc, gc);
			paint(cs,*g,s,v,o);
		}
		else if(e.xbutton.button==3) break;
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
}