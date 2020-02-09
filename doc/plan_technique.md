# DESCRIPTIF COMPLET

## Rappel des fonctionalités :

  * Settings
    * Possibilité de changer la couleur du fond d’écran  
    * Possibilité de changer la couleur de la carte  
    * Possibilité de choisir la taille de la police  
  * Cours
    * Possibilité de créer un cours dans une catégorie  
    * Possibilité de créer une catégorie ou d’en effacer une  
    * Possibilité de renommer un cours, ou de l’effacer  
    * Possibilité d’ajouter une description / de la modifier  
  * Questions
    * Possibilité de choisir chaque question comportant le cours (au moins 1) / de les modifier  
    * Possibilité de choisir si la question est à réponse textuelle ou QCM  
    * Possibilité d’ajouter une image / schéma à la question  
  * Réponses
    * Possibilité de choisir chaque réponse attendue / de les modifier  
  * Séance d’entraînement
    * Possibilité de créer une séance  
    * Possibilité de renommer / supprimer une séance  
    * Possibilité d’ajouter plusieurs cours (au moins 1) / enlever des cours  
    * Possibilité de choisir le temps imparti de la séance (peut être nul)  
    * Possibilité d’ajouter une description / de la modifier  
    * Possibilité de choisir le nombre de fautes maximum avant échec  
  * Export / sauvegardes
    * Les cours et les séances sont sauvegardées à la création  
    * Possibilité d’exporter ses cours / séances  
    * Possibilité d’importer des cours / séances  


## Implémentation des fonctionnalités :

1. Settings :
   Pour implémenter les settings, il est necéssaire de créer des fonctions de lecture du fichier settings et les fonctions necéssaire à la modification des settings individuels.  
   En l'occurence, pour 5 fonctionnalités 5 fonctions spécifiques sont requises, en plus de la fonction qui crée le fichier config originel, celle qui ouvre le fichier (qui ne sera jamais utilisée telle quelle mais sert a construire les fonctions spécifiques) et celle qui si le fichier existe, il est valide :
   
   * void create_default_settings_file(const char * path) // crée un fichier config avec les parametres par defaut
   * FILE * open_config(const char * path) // renvoie un stream vers le fichier config (appelle create_default_settings_file si le fichier n'existe pas ou si <> renvoie -1)
   * int8_t conf_file_is_valid(const char * path) // renvoie -1 si le fichier existe mais n'a pas la bonne config, 0 s'il n'existe pas, 1 sinon.
   * void background_color_change(const char * color) // utiliser fgets et strstr puis fseek avec une valeur hardcodée(correspondant au contenu de create_default_settings_file) pour faire pointer le filestream au bon endroit
   * void card_color_change(const char * color)
   * void font_size_change(const char * font)
   * Struct settings get_current_settings(const char * path)

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
   * gtk_widget_show_all(GtkWidget * Contenant)// affiche all tha shit was put in Contenant

   La subtilité de GTK est que tout widget (typé GtkWidget *) possède une notion d'héritage du widget supérieur. En clair, chaque widget possède une hiérarchie en fonction d'où il est placé (dans une fenêtre, une boite de dialogue, etc). Les fonctions utilisables sur un widget peuvent donc être appliquées sur tous les "sous-widgets" qu'il contient.

   La gestion des events avec GTK se fait via des signals avec :
   * g_signal_connect(G_OBJECT(widget_qui_accueil_le_signal),"nom_du_signal", G_CALLBACK(fonction_appelée), ptr * parametre_à_passer_à_la_fonction)

   Pour disposer plusieurs widgets (comme les boutons, les espaces de saisies, etc.) dans un seul container, il faut utiliser une Gtkwidget * grid, qui va cadrier l'espace du conteneur en plusieurs "sous-conteneurs" dans lesquels on va pouvoir "l'attacher":
   * void * gtk_grid_attach(GTK_GRID(grid), gp * contenu, int case_x, int case_y, int largeur_en_case ,int_hauteur_en_case); // l'origine du repère se situe en haut à gauche

5. MySQL
  #include<mysql.h>
   L'installation du projet nécessite la création de la base de donnée, qui va accueillir, entre autre, les cours, les catégories, les questions, etc. Pour ce faire, une fonction peut être créée afin d'automatiser cette installation, à condition de renseigner le username et le password d'un user qui possède les droits nécessaires à cette création.
   * int setup_database(char* username, char* password);
  A noter que cette fonction en appellera plusieurs autres 
   * MYSQL* mysql_init(NULL) // Function qui initialise la connection à mysql, connexion qu'on va stocker dans une variable MYSQL*
   * mysql_real_connect(MYSQL* connexion, "localhost", "username", "password", NULL, 0, NULL, 0) // renvoie NULL si la connexion est refusée ou échoue
   * mysql_query(MYSQL* connexion, char* instruction_sql) // Renvoie NULL si failed
   On peut donc faire passer n'importe quelle instruction avec mysql_query, à condition que la connexion ai été ouverte avec un user qui possède suffisament de droits.

