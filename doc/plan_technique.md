# DESCRIPTIF COMPLET

## Rappel des fonctionalités :

  * Settings
    * Taille de l'ecran
    * Plein ecran ou non
    * Position de l'ecran
  * Cours
    * Possibilité de créer un cours
    * Possibilité de renommer un cours, ou de l’effacer  
    * Possibilité d’ajouter une description / de la modifier
    * Consultation des cours, et des questions qu'il comporte
  * Export / sauvegardes
    * Les cours sont sauvegardées à la création  


## Implémentation des fonctionnalités :

1. Settings :
   Pour implémenter les settings, la fonction get_param permet de faire passer les adresses des variables permettant de créer la fenêtre. Une simple lecture du fichier et des affectations fournissent à la fonction de création de fenêtre le nécessaire pour son fonctionnement.

2. Cours
   Pour implémenter les fonctionnalités liées aux cours, il est nécessaire de créer de nombreuses fonctions permettant aux fonctions spécifiques aux fonctionnalités listées de fonctionner correctement : 

   * void add_category(const char * new_categorie, <wherever it is saved>)
   * void add_cours(const char * new_cours, const char * category, <wherever it is saved>)
   * void rename_cours(const char * old_name, const char * new_name, const char * category, <wherever it is saved>)
   * void edit_description(const char * text, const char * cours, const char * category, <wherever it is saved>)
   * PLUS les fonctions interagissant avec les wherever it is...

3. Questions
  
4. GUI
  #include <gtk/gtk.h> // gtk 3.0
   Avec GTK, la création des différents types d'interfaces et de leur contenu : "objets" (boutons, zone de saisie), "labels" (texte à afficher) passent par plusieurs étapes, et peuvent être comprises dans des fonctions afin d'optimiser le traitement:
   * GtkWidget * generate_window(gchar * titre_de_la_fenetre, int hauteur, int largeur)
   * gtk_widget_show_all(GtkWidget * Contenant)// affiche tout les widgets de contenant

   La subtilité de GTK est que tout widget (typé GtkWidget *) possède une notion d'héritage du widget supérieur. En clair, chaque widget possède une hiérarchie en fonction d'où il est placé (dans une fenêtre, une boite de dialogue, etc). Les fonctions utilisables sur un widget peuvent donc être appliquées sur tous les "sous-widgets" qu'il contient.

   La gestion des events avec GTK se fait via des signals avec :
   * g_signal_connect(G_OBJECT(widget_qui_accueil_le_signal),"nom_du_signal", G_CALLBACK(fonction_appelée), ptr * parametre_à_passer_à_la_fonction)

   Pour disposer plusieurs widgets (comme les boutons, les espaces de saisies, etc.) dans un seul container, il faut utiliser une Gtkwidget * grid, qui va cadrier l'espace du conteneur en plusieurs "sous-conteneurs" dans lesquels on va pouvoir "l'attacher":
   * void * gtk_grid_attach(GTK_GRID(grid), gp * contenu, int case_x, int case_y, int largeur_en_case ,int_hauteur_en_case); // l'origine du repère se situe en haut à gauche

   Lors d'un changement d'un menu à l'autre, on effectue une transition où la fenêtre va ouvrir celle du menu suivant et va se fermer ensuite. Comme les fenêtres appelées sont différentes, une fonction spécifique a été créée pour chaque transition vers un menu particulier.
   * void transition_menu(GtkWidget * principal_window){
        gtk_window_close(GTK_WINDOW(principal_window));// fermeture de la fenêtre actuelle
        menu();// ouverture du prochain menu (principal, cours, exercice, etc)
     }
   Contrairement aux pop-up, qui s'ouvre et se ferment en activant un verrou, qui n'autorise qu'une seule popup à être ouverte à la fois.
   * void close_popup(GtkWidget* popup, int * lock)// qui libère le verrou

5. MySQL
  #include<mysql.h>
   L'installation du projet nécessite la création de la base de donnée, qui va accueillir, entre autre, les cours, les catégories, les questions, etc. Pour ce faire, une fonction peut être créée afin d'automatiser cette installation, à condition de renseigner le username et le password d'un user qui possède les droits nécessaires à cette création.
   * int setup_database(char* username, char* password);
  A noter que cette fonction en appellera plusieurs autres 
   * MYSQL* mysql_init(NULL) // Function qui initialise la connection à mysql, connexion qu'on va stocker dans une variable MYSQL*
   * mysql_connect(MYSQL* connexion, "localhost", "username", "password", NULL, 0, NULL, 0) // renvoie NULL si la connexion est refusée ou échoue
   * mysql_query(MYSQL* connexion, char* instruction_sql) // Renvoie NULL si failed
   On peut donc faire passer n'importe quelle instruction avec mysql_query, à condition que la connexion ai été ouverte avec un user qui possède suffisament de droits.

   Pour simplifier les traitements et éviter les répétitions de codes, 3 fonctions principales ont été créée pour gérer la base de donnée :
   * MYSQL* open_database(); // renvoie un pointeur de structure MYSQL vers la connexion établie dans la fonction. Cette connexion est testée et affiche sur console les erreurs.
   * MYSQL_RES * dbquery(MYSQL * con, char * query) //Utilisée pour soumettre une requête renvoyant des données. On y introduit le ptr de connexion, la chaine contenant la requête et la valeur retournée est le résultat structuré MYSQL_RES, qu'on décomposera plus tard en MYSQL_ROW
   * void dbinsert(MYSQL * con, char * query) // Utilisée pour soumettre une requête qui ne renvoie rien. La requête est tout de même vérifiée avant. Idem que précédent pour les paramètres à passer
 
