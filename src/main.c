#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <mysql.h>
#include "smartlearnlib.h"


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

