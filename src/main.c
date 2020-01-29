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

void destroy_window(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

int main(int argc,char **argv)
{
    
    gtk_init(&argc,&argv);
    
    char * title = "Learning cards";
    GtkWidget* headtitle;
    GtkWidget* principal_window;

    principal_window = generate_window(title, 1200, 800);
    headtitle = gtk_label_new("Bienvenue sur LearnCards\nLearn smart\nAppuyez sur une touche pour commencer !");
    
    gtk_container_add (GTK_CONTAINER(principal_window), headtitle);
    gtk_label_set_justify (GTK_LABEL(headtitle), GTK_JUSTIFY_CENTER);
	g_signal_connect(G_OBJECT(principal_window), "key_press_event", G_CALLBACK(destroy_window), NULL);
    
    gtk_widget_show_all(principal_window);// Showing all the widget under principal_window

    gtk_main();
    
    return EXIT_SUCCESS;
}
