#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <mysql.h>
#include "smartlearnlib.h"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

GtkWidget * generate_window(char * title, int height, int width){
    GtkWidget* p_window;
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), title);
    gtk_window_set_default_size(GTK_WINDOW(p_window), height, width);
    gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_CENTER);
    return p_window;

};

MYSQL* open_database(){ // Don't forget to close the connexion !
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) 
    {
        printf("%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "developper", "project", 
            NULL, 0, NULL, 0) == NULL) 
    {
        printf("%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
    printf("\ndebug : Connexion to DTB Successful\n");
    return con;
}

MYSQL_RES * dbquery(MYSQL * con, char * query){
    if (mysql_query(con, query)) 
  {
      finish_with_error(con);
      printf("\ndebug : error during query\n");
  }
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {
      finish_with_error(con);
      printf("\ndebug : result is NULL\n");
  }
    return result;
}


void close_popup(GtkWidget* popup, int * lock){

    *lock = 0;
    printf("\ndebug : lock is 0\n");
}


void cours_form(GtkWidget* button, int * lock){

    if (*lock){
        printf("\ndebug : form already opened (lock : %d)\n", *lock);
        return;
    }else{
        *lock = 1;
        printf("\ndebug : log is %d\n", *lock);
    }

    printf("\ndebug : Formulaire lancé\n");
    char * title = "Création de cours";
    GtkWidget * grid, *principal_window, *nom, *label_nom, *description, *label_description, *categorie, *label_categorie, *new_cours_button;

    
    principal_window = generate_window(title, 800, 800);
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);
    gtk_grid_set_row_homogeneous (GTK_GRID(grid), TRUE);


    nom = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY(nom), 50);
    gtk_grid_attach(GTK_GRID(grid), nom, 1, 0, 1, 1);
    
    label_nom = gtk_label_new("Nom du cours");
    gtk_grid_attach(GTK_GRID(grid), label_nom, 0, 0, 1, 1);


    description = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY(description), 300);
    gtk_grid_attach(GTK_GRID(grid), description, 1, 1, 1, 1);
    
    label_description = gtk_label_new("Description");
    gtk_grid_attach(GTK_GRID(grid), label_description, 0, 1, 3, 2);

    g_signal_connect(principal_window, "destroy", G_CALLBACK(close_popup), lock);









    gtk_widget_show_all(principal_window);
}

void free_lock(GtkWidget * window, int * lock){
    free(lock);
    printf("lock is free");
}

void lessons(){
    printf("\ndebug : Cours lancé\n");
    char * title = "Mes cours";
    int * lock_ptr;
    lock_ptr = malloc(sizeof(lock_ptr));
    *lock_ptr = 0;
    GtkWidget * grid, *principal_window, *label_cours1, *label_cours2, *liste_cours, *cours_button;
    label_cours1 = gtk_label_new("Cours 1");
    label_cours2 = gtk_label_new("Cours 2");

    MYSQL* con = open_database();

    principal_window = generate_window(title, 800, 800);
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);

    liste_cours = gtk_list_box_new();
    gtk_list_box_prepend(GTK_LIST_BOX(liste_cours), GTK_WIDGET(label_cours1));
    gtk_list_box_prepend(GTK_LIST_BOX(liste_cours), GTK_WIDGET(label_cours2));
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(liste_cours), 0, 0, 1, 1);

    cours_button = gtk_button_new_with_label("Ajouter un cours");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cours_button), 0, 1, 1, 1);   
    printf("\nLesson : Lock : %d | %d\n",lock_ptr, *lock_ptr);
    g_signal_connect(cours_button, "clicked", G_CALLBACK(cours_form), lock_ptr);


    g_signal_connect(principal_window, "destroy", G_CALLBACK(free_lock), lock_ptr);
    
    
    
    
    gtk_widget_show_all(principal_window);
    mysql_close(con);
}

void transition_lessons(GtkWidget * principal_window){
    gtk_window_close(GTK_WINDOW(principal_window));
    lessons();
}

void home(){
    printf("\ndebug : Home lancé\n");
    char * title = "Menu principal";
    GtkWidget * grid, *principal_window, *cours_button, *label_cours;

    principal_window = generate_window(title, 800, 800);

    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);

    label_cours = gtk_label_new("Consulter, ajouter ou modifier mes cours");
    gtk_grid_attach(GTK_GRID(grid), label_cours, 0, 1, 1, 1);
    gtk_label_set_justify (GTK_LABEL(label_cours), GTK_JUSTIFY_CENTER);

    cours_button = gtk_button_new_with_label("Cours");
    gtk_grid_attach(GTK_GRID(grid), cours_button, 0, 0, 1, 1);
    g_signal_connect(cours_button, "clicked", G_CALLBACK(transition_lessons), principal_window);


    gtk_widget_show_all(principal_window);

}


void transition_home(GtkWidget * principal_window){
    gtk_window_close(GTK_WINDOW(principal_window));
    home();
}
