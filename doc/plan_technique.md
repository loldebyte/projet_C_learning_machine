# DESCRIPTIF COMPLET

## Rappel des fonctionalités :

  * Settings
    * Possibilité de changer la couleur du fond d’écran  
    * Possibilité de changer la couleur de la carte  
    * Possibilité de choisir la taille de la police  
    * Possibilité d’activer / désactiver le son  
    * Activer / désactiver les aides à l’utilisation  
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
   * int conf_file_is_valid(const char * path) // renvoie -1 si le fichier existe mais n'a pas la bonne config, 0 s'il n'existe pas, 1 sinon.
   * void background_color_change(const char * color) // utiliser fgets et strstr puis fseek avec une valeur hardcodée(correspondant au contenu de create_default_settings_file) pour faire pointer le filestream au bon endroit
   * void card_color_change(const char * color)
   * void font_size_change(const char * font)
   * void sound(void) // change sound param, if sound = true then sound <- false else sound <- true
   * void help(void) // idem pour l'aide
2. Cours
   Pour implémenter les fonctionnalités liées aux cours, il est nécessaire de créer de nombreuses fonctions permettant aux fonctions spécifiques aux fonctionnalités listées de fonctionner correctement : 

   * void add_category(const char * new_categorie, )


2. Cours :
