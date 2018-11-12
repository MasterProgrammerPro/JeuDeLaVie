# Jeu De La Vie

Le Jeu de la Vie (ou Game of Life) est, en réalité, un automate cellulaire défini en 1970 par le mathématicien anglais John Conway. Il se compose d’un univers dans lequel évoluent des cellules vivantes suivant des règles d’évolution précises.

#### Règles :

* Une cellule morte au temps t devient vivante au temps t + 1 si et seulement si elle a exactement 3 cellules vivantes dans son voisinage.

* Une cellule vivante au temps t reste vivante au temps t + 1 si et seulement si elle a exactement 2 ou 3 cellules vivantes dans son voisinage, sinon elle meurt.

* Le voisinage utilisé est le 8-voisinage : pour une cellule donnée, ses voisines sont les 8 cellules qui l’entourent.

#### Comment Executer :

* executer : main < fichier grille >
* supprimer objects : make clean
* produire un archive : make dist

#### Les Touches :

*  entree : pour évoluer
* n : pour d'entree un nouvelle grille (max 30 characters)
* c : pour changer entre cyclique et non cyclique(cyclique par défaut)
* v : pour changer activer/desactiver vieillessement (desactive par défaut)
* r : pour reset des ages

#### Versions :

* v0.0 : Version initiale

* v0.1 : Tester s'il compile

* v1.0 : Version avec alloue_grille

* v1.1 : Version avec libere_grille, le premiere version qu'on peut simuler la jeu de la vie

* v2.0 : Version avec la touche 'n'

* v3.0 : Version avec Doxyfile

* v4.0 : Version avec compteur

* v5.0 : Version avec le touche 'c'

* v6.0 : Version avec le touche 'v'

* v7.0 : Version avec le touche 'r'

* v8.0 : version finale