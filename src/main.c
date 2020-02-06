#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <mysql.h>


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

/* void generate_cours_list(GtkWidget * liste_cours){
    gtk_list_box_prepend(GTK_LIST_BOX(liste_cours), GTK_WIDgtk_list_box_prepend(GTK_LIST_BOX(liste_cours), GTK_WIDGET(label_cours1));GET(label_cours1));
    gtk_list_box_prepend(GTK_LIST_BOX(liste_cours), GTK_WIDGET(label_cours2));
} WILL WORK WITH BDD IMPORTS*/ 

void lessons(){
    printf("\ndebug : Cours lancé\n");
    char * title = "Mes cours";
    GtkWidget * grid, *principal_window, *label_cours1, *label_cours2, *liste_cours;
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

int main(int argc,char **argv)
{
    
    gtk_init(&argc,&argv);
    
    char * title = "Learning cards";
    GtkWidget* grid, *headtitle, *principal_window, *button;

    principal_window = generate_window(title, 500, 500);
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);

    headtitle = gtk_label_new("Bienvenue sur LearnCards\nLearn smart");
    gtk_grid_attach(GTK_GRID(grid), headtitle, 0, 0, 3, 3);
    gtk_label_set_justify (GTK_LABEL(headtitle), GTK_JUSTIFY_CENTER);

    button = gtk_button_new_with_label("Commencer");
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 3, 3);
    g_signal_connect(button, "clicked", G_CALLBACK(transition_home), principal_window);

    
    gtk_widget_show_all(principal_window);// Showing all the widget under principal_window

    gtk_main();
    
    return EXIT_SUCCESS;
}

