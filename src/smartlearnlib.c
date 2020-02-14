#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <mysql.h>
#include <string.h>
#include "smartlearnlib.h"


void get_params(int *size_x, int *size_y, int * position, int *windowed){
    
    FILE * pf;
    char * fullscreen;
    char * get_position;
    char * get_size_x;
    char * get_size_y;
    char * cursor;
    int inter;

    cursor = malloc(sizeof(char)*255);

    pf = fopen("parameters.conf","rt");
    printf("\ndebug : file opened\n");

    if(!pf)
        return;

    fullscreen = malloc(sizeof(char)*255);
    fgets(fullscreen,255,pf);
    if (strstr(fullscreen,"NO")){
        *windowed = 1;
        printf("\ndebug : is not fullscreen\n");
    }else{
        *windowed = 0;
    }

    get_position = malloc(sizeof(char)*255);
    fgets(get_position,255,pf);
    cursor = strstr(get_position,":");
    inter =atoi(cursor+2);
    *position = inter;
    printf("\ndebug : position is %d\n", *position);

    get_size_x = malloc(sizeof(char)*255);
    fgets(get_size_x,255,pf);
    cursor = strstr(get_size_x,":");
    inter = atoi(cursor+2);
    *size_x = inter; 
    printf("\ndebug : size x is %d\n", *size_x);

    get_size_y = malloc(sizeof(char)*255);
    fgets(get_size_y,255,pf);
    cursor = strstr(get_size_y,":");
    inter = atoi(cursor+2);
    *size_y = inter; 
    printf("\ndebug : size y is %d\n", *size_y);

    free(get_size_x);
    printf("\nfree 1\n");
    free(get_size_y);
    printf("\nfree 2\n");
    free(get_position);
    printf("\nfree 3\n");
    free(fullscreen);
    printf("\nfree 4\n");
    //free(cursor);
    printf("\nfree 5\n");
    fclose(pf);
    printf("\nclosed");
}



char * get_date(char * date){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(date, "%d/%d/%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
  printf("\n debug : date is %s", date);
  return date;
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}

GtkWidget * generate_window(char * title){
    GtkWidget* p_window;
    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    int size_x, size_y, windowed, position;

    get_params(&size_x, &size_y, &position, &windowed);
    printf("\ndebug : file closed with values:\nsize_x : %d\nsize_y : %d\nwindowed : %d\nposition : %d\n", size_x, size_y, windowed, position);

    switch(position){
        case 1 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_NONE);
                 printf("\ndebug : case is %d\n", position);
        break;
        case 2 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_CENTER);
        break;
        case 3 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_MOUSE);
        break;
        case 4 : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_CENTER_ALWAYS);
        break;
        default : gtk_window_set_position (GTK_WINDOW (p_window), GTK_WIN_POS_NONE);
    }

    if(windowed == 1){
        gtk_window_set_default_size(GTK_WINDOW(p_window), size_x, size_y);
    }
    if(windowed == 0){
        gtk_window_fullscreen (GTK_WINDOW(p_window));
    }

    gtk_window_set_title(GTK_WINDOW(p_window), title);

    return p_window;

};

MYSQL* open_database(){ // Don't forget to close the connexion !
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) 
    {
        printf("%s\n", mysql_error(con));
        printf("\ndebug : DTB init is not open\n");
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "developper", "project", 
            NULL, 0, NULL, 0) == NULL) 
    {
        printf("%s\n", mysql_error(con));
        printf("\ndebug : DTB connexion is not open\n");
        mysql_close(con);
        exit(1);
    }
    printf("\ndebug : Connexion to DTB Successful\n");
    return con;
}

MYSQL_RES * dbquery(MYSQL * con, char * query){
    if (mysql_query(con, query)) 
  {
      printf("\ndebug : error during query\n");
      finish_with_error(con);
  }
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) 
  {     
      printf("\ndebug : result is NULL\n");
      finish_with_error(con);
  }
    printf("\ndebug : request correctely sent\n");
    return result;
}

void dbinsert(MYSQL * con, char * query){
    if (mysql_query(con, query)) 
  {
      printf("\ndebug : error during query\n");
      finish_with_error(con);
  }
      printf("\ndebug : request correctely sent");
}

void close_window(GtkWidget * button, GtkWidget *principal_window){
    gtk_window_close(GTK_WINDOW(principal_window));
}

void close_popup(GtkWidget* popup, int * lock){

    *lock = 0;
    printf("\ndebug : lock is 0\n");
}

typedef struct form_lesson{
    GtkWidget * nom;
    GtkWidget * description;
    GtkWidget * principal_window;
    int statement;

}form_lesson;

typedef struct identified_entry{
    GtkWidget * entry;
    int identifier;
}identified_entry;

typedef struct identified_row{
    int identifier;
    const char * content;
}identified_row;

void insert_lesson (GtkWidget * button, form_lesson * submit){

    const gchar * text_nom;
    const gchar * text_description;
    gchar * text_date;
    char query[334];

    text_nom = gtk_entry_get_text(GTK_ENTRY(submit->nom));
    text_description = gtk_entry_get_text(GTK_ENTRY(submit->description));
    text_date = malloc(10);
    text_date = get_date(text_date);


    if (text_nom == 0 || text_description == 0){
        submit->statement = 0;
        return;
    }

    printf("\ndebug : Nom : %s | Description : %s | Date : %s\n", text_nom, text_description, text_date);
    sprintf(query, "INSERT INTO cours VALUES(NULL,'%s','%s','%s', NULL);", text_nom, text_date, text_description);
    free(text_date);
    printf("\nquery : %s\n", query);

    MYSQL* con = open_database();
    dbinsert(con, "use project;");
    dbinsert(con, query);
    mysql_close(con);
    gtk_window_close(GTK_WINDOW(submit->principal_window));

    
}

void cours_form(GtkWidget* button, int * lock){

    
    //////////////Lock checkout
    if (*lock){
        printf("\ndebug : form already opened (lock : %d)\n", *lock);
        return;
    }else{
        *lock = 1;
        printf("\ndebug : log is %d\n", *lock);
    }

    

    printf("\ndebug : Formulaire lancé\n");
    char * title = "Création de cours";
    GtkWidget * grid, *label_nom, *label_description, *creation_button;
    form_lesson * submit;
    submit = malloc(sizeof(submit));

    submit->statement = 0;
    
    submit->principal_window = generate_window(title);
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(submit->principal_window), grid);
    

    submit->nom = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY(submit->nom), 50);
    gtk_grid_attach(GTK_GRID(grid), submit->nom, 1, 0, 1, 1);
    
    label_nom = gtk_label_new("Nom du cours");
    gtk_grid_attach(GTK_GRID(grid), label_nom, 0, 0, 1, 1);
    //text_nom = gtk_entry_get_text(submit->nom);


    submit->description = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY(submit->description), 300);
    gtk_grid_attach(GTK_GRID(grid), submit->description, 1, 1, 1, 1);
    
    label_description = gtk_label_new("Description");
    gtk_grid_attach(GTK_GRID(grid), label_description, 0, 1, 1, 1);
    //text_description = gtk_entry_get_text(description);


    creation_button = gtk_button_new_with_label("Créer");
    gtk_grid_attach(GTK_GRID(grid), creation_button, 0, 2, 1, 1 );
    g_signal_connect(creation_button, "clicked", G_CALLBACK(insert_lesson), submit);

    g_signal_connect(submit->principal_window, "destroy", G_CALLBACK(close_popup), lock);
    gtk_widget_show_all(submit->principal_window);

}

void free_lock(GtkWidget * window, int * lock){
    free(lock);
    printf("lock is free");
}

GtkWidget* load_questions(int identifier){
    MYSQL* con = open_database();
    MYSQL_RES * result;
    MYSQL_ROW row;
    GtkWidget * question_list;
    GtkWidget * result_list;
    char * entire_row;
    char * query;
    query = malloc(65);
    sprintf(query, "SELECT id_question, enonce FROM question where id_cours = %d", identifier);

    question_list = gtk_list_box_new();
    dbinsert(con, "use project");
    result = dbquery(con, query);
    int num_fields = mysql_num_fields(result);

    while (row = mysql_fetch_row(result)){
        entire_row = malloc(305);    
        printf("\ndebug : boucle\n"); 
        sprintf(entire_row, "%s:%s", row[0], row[1]);
        printf("\n row : %s\n", entire_row);
        result_list = gtk_label_new(entire_row);
        printf("\ndebug : result_list affectation : %s\n", entire_row);
        gtk_list_box_prepend(GTK_LIST_BOX(question_list), GTK_WIDGET(result_list));
        printf("\ndebug : added in listbox\n");
        free(entire_row);
        printf("\ndebug : entire_row liberated\n");
            
    }
    printf("\ndebug : sortie de boucle\n");
    printf("\ndebug : sortie de boucle\n");
    mysql_free_result(result);
    mysql_close(con);
    free(query);
    
    return question_list;

}

GtkWidget * load_courses(){
    MYSQL* con = open_database();
    MYSQL_RES * result;
    MYSQL_ROW row;
    GtkWidget * liste_cours;
    GtkWidget * result_list; // Created to stock each row into label
    char * entire_row;

    liste_cours = gtk_list_box_new();

    dbinsert(con, "use project");
    result = dbquery(con, "SELECT id_cours, nom_cours FROM cours");
    
    while ((row = mysql_fetch_row(result))) 
    {

        entire_row = malloc(55);    
        printf("\ndebug : boucle\n"); 
        sprintf(entire_row, "%s:%s", row[0], row[1]);
            printf("\n row : %s\n", entire_row);
            result_list = gtk_label_new(entire_row);
            printf("\ndebug : result_list affectation : %s\n", entire_row);
            gtk_list_box_prepend(GTK_LIST_BOX(liste_cours), GTK_WIDGET(result_list));
            printf("\ndebug : added in listbox\n");
            free(entire_row);
            
    }
    printf("\ndebug : sortie de boucle");
    mysql_free_result(result);
    mysql_close(con);
    
    return liste_cours;
}


identified_row get_row (GtkWidget * listbox){
    identified_row cours;
    //cours = malloc(sizeof(cours));
    GtkWidget * label;
    GtkListBoxRow * row;
    const char * temp;
    char * temp_number;
    char * final_id;
    int delimiter_position;

    final_id = malloc(3);
    for(int i=0; i<3; i++)
        *(final_id+i) = '\0'; 
    printf("\ndebug : get_row launched\n");
    row = gtk_list_box_get_selected_row(GTK_LIST_BOX(listbox));
    printf("\ndebug :  value is row\n");
    label = gtk_bin_get_child(GTK_BIN(row));
    printf("\ndebug : label set\n");
    temp = gtk_label_get_label(GTK_LABEL(label));
    printf("\ndebug : temp is %s\n", temp);
    cours.content = strchr(temp, ':') + 1;
    printf("\ndebug : content is %s\n", cours.content);
    temp_number = strchr(temp, ':');
    delimiter_position = temp_number - temp;
    printf("\ndebug : position = %d\n", delimiter_position);
    strncpy(final_id, temp, delimiter_position);
    printf("\ndebug : final id : %s\n", final_id);
    cours.identifier = atoi(final_id);
    printf("\ndebug : id : %d\n", cours.identifier);
    
    free(final_id);
    return cours;
    
}

void rename_cours(GtkWidget * button, identified_entry * cours){

    //""
    gchar * text_nom;
    int identifier;
    GtkWidget * entry;

    identifier = cours->identifier;
    entry = cours->entry;
    text_nom = malloc(50);
    char query[300];
    printf("\ndebug : rename protocol launched, id is %d\n", identifier);
    text_nom = gtk_entry_get_text(GTK_ENTRY(entry));
    printf("\ndebug : new text is %s\n", text_nom);
    sprintf(query, "UPDATE cours SET nom_cours = '%s' where id_cours = '%d'", text_nom, identifier);
    printf("\ndebug : query is %s\n", query);
    free(text_nom);

    MYSQL* con = open_database();
    dbinsert(con, "use project;");
    dbinsert(con, query);
    mysql_close(con);
    
}
void delete_from_cours(GtkWidget * button, int identifier){
    printf("\ndebug : delete started for %d\n", identifier);
    char query[300];
    sprintf(query, "DELETE FROM cours where id_cours = '%d'", identifier);
    MYSQL* con = open_database();
    dbinsert(con, "use project;");
    dbinsert(con, query);
    mysql_close(con);
    printf("\ndebug : delete endend correctely for %d\n", identifier);
}

void modify_quiz (identified_row cours){
    printf("\ndebug : Modification de quizz lancé\n");

    GtkWidget * grid, *principal_window, *question_list, *modify_button, *add_button, *delete_cours, *rename;
    identified_entry * entry_cours;
    entry_cours = malloc(sizeof(entry_cours));
    int * lock_ptr;
    lock_ptr = malloc(sizeof(int));
    *lock_ptr = 0;
    principal_window = generate_window(cours.content);
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);

    question_list = load_questions(cours.identifier);
    printf("\ndebug : questions loaded\n");

    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(question_list), 0, 0, 1, 1);

    if(gtk_list_box_get_selected_row(GTK_LIST_BOX(question_list))){
        modify_button = gtk_button_new_with_label("Modifier");
        gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(modify_button), 1, 0, 1, 1);
    }

    add_button = gtk_button_new_with_label("Ajouter une question et sa réponse");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(add_button), 0, 1, 1, 1);   
    printf("\nLesson : Lock : %d | %d\n",lock_ptr, *lock_ptr);
    //g_signal_connect(add_button, "clicked", G_CALLBACK(cours_form), lock_ptr);

    entry_cours->entry = gtk_entry_new();
    entry_cours->identifier = cours.identifier;
    gtk_entry_set_text(GTK_ENTRY(entry_cours->entry), cours.content);
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(entry_cours->entry), 1, 0, 1, 1);

    rename = gtk_button_new_with_label("Renommer");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(rename), 2, 0, 1, 1 );
    g_signal_connect(rename, "clicked", G_CALLBACK(rename_cours), entry_cours);

    delete_cours = gtk_button_new_with_label("Supprimer le cours");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(delete_cours), 3, 1, 1, 1 );
    g_signal_connect(delete_cours, "clicked", G_CALLBACK(delete_from_cours), &entry_cours->identifier);
    g_signal_connect(delete_cours, "clicked", G_CALLBACK(close_window), principal_window);
    
    gtk_widget_show_all(principal_window);
}
void modify_quiz_transition(GtkWidget * button, GtkWidget * listbox){
    identified_row cours;
    cours = get_row(listbox);
    printf("\ndebug : transition ready with id %d and cours %s\n", cours.identifier, cours.content);
    modify_quiz(cours);
}

void lessons(){


    printf("\ndebug : Cours lancé\n");
    char * title = "Mes cours";
    int * lock_ptr;
    lock_ptr = malloc(sizeof(lock_ptr));
    *lock_ptr = 0;
    GtkWidget * grid, *principal_window, *liste_cours, *cours_button, *modify_button;

    principal_window = generate_window(title);
    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER(principal_window), grid);

    cours_button = gtk_button_new_with_label("Ajouter un cours");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cours_button), 0, 1, 1, 1);   
    printf("\nLesson : Lock : %d | %d\n",lock_ptr, *lock_ptr);
    g_signal_connect(cours_button, "clicked", G_CALLBACK(cours_form), lock_ptr);

    liste_cours = load_courses();

    printf("\n debug : load successful\n");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(liste_cours), 0, 0, 1, 1);
    
    
    cours_button = gtk_button_new_with_label("Rafraichir");
    gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(cours_button), 1, 1, 1, 1);
    g_signal_connect(cours_button, "clicked", G_CALLBACK(transition_lessons), principal_window);

    //if(gtk_list_box_get_selected_row(GTK_LIST_BOX(liste_cours))){
        modify_button = gtk_button_new_with_label("Modifier");
        gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(modify_button), 2, 1, 1, 1);
    //}
    g_signal_connect(modify_button, "clicked", G_CALLBACK(modify_quiz_transition), liste_cours);
    
    g_signal_connect(principal_window, "destroy", G_CALLBACK(free_lock), lock_ptr);


    gtk_widget_show_all(principal_window);

}

void transition_lessons(GtkWidget * button, GtkWidget *principal_window){
    gtk_window_close(GTK_WINDOW(principal_window));
    lessons();
}


void home(){
    printf("\ndebug : Home lancé\n");
    char * title = "Menu principal";
    GtkWidget * grid, *principal_window, *cours_button, *label_cours;

    principal_window = generate_window(title);

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

