/** 
 * \file io.c 
 * code pour affichage
 * \author SENOL Mustafa
 */

#include "io.h"



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
			case 'p' :
			{//test oscillente
				oscillente(*g,s,v);
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
				//paint_jeu(g, gc);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void paint(cairo_surface_t *surface, grille g,int c, int v)
{	
	int CSIZE = 52,i,j,k=0;
	char age[2];
	age[1]= '\n';  
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(surface);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);

	// filled rectangle
	for(i=0; i<g.nbl; i++)
	{
		for(j=0; j<g.nbc; j++)
		{			
			cairo_rectangle(cr,j*52+30,i*52+30,50,50);
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
					cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
					cairo_set_font_size(cr,0.5*CSIZE);
					cairo_set_source_rgb(cr,1.0,0.0,0.0);
					cairo_move_to(cr,j*52+49,i*52+62);
					cairo_show_text(cr,age);
				}
			}
		}
	}
	cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*CSIZE);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,30,(i+1)*52);
	if(v==0)
	{	
	cairo_show_text(cr,"vieillissement pas active");
	}
	else
	{
	cairo_show_text(cr,"vieillissement active");
	}
	i++;
	cairo_select_font_face(cr,"serif",CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr,0.5*CSIZE);
	cairo_set_source_rgb(cr,1.0,1.0,1.0);
	cairo_move_to(cr,30,(i+1)*52);
	if(c==0)
	{	
	cairo_show_text(cr,"non cyclique");
	}
	else
	{
	cairo_show_text(cr,"cyclique");
	}
	cairo_destroy(cr); // destroy cairo mask
}




int paint_jeu(grille *g, grille *gc)
{
	int s = 1, v = 0;	
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

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);
	printf("\n\n\n%d",XKeysymToKeycode(dpy, 'n'));	
	// run the event loop
	while(1)
	{
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1)
		{
			paint(cs,*g,s,v);
		
		}
		if(e.xbutton.button == 1)
		{
			evolue(g,gc,s,v);
			paint(cs,*g,s,v);
		}	
		if(e.xkey.keycode == 54)//c
		{
			s = 1 - s;
		}
		if(e.xkey.keycode == 55)//v
		{
			v = 1 - v;
		}
		if(e.xkey.keycode == 57)//n
		{
			char n[30];
			printf("                                 \rfichier grille : ");
			scanf("%s",n);
			init_grille_from_file(n,g);
			alloue_grille (g->nbl, g->nbc, gc);
			paint(cs,*g,s,v);
		}
		else if(e.xbutton.button==3) break;
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}



/*
else if(e.type == ButtonPress)
		{
			if(e.xbutton.button == 1)
			{
				
			}











*/





































