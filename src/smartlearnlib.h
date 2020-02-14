/* terminates programm and flushes all streams */
void finish_with_error();
/* creates the window and sets its position and title */
GtkWidget * generate_window(char *, int, int);
/* initializes the connexion to the DB and returns it */
MYSQL* open_database();
/* executes a DB query and returns its result as a MY_SQL_RES pointer */
MYSQL_RES * dbquery();
/* resets lock onto a GtkWidget, allowing it to be opened again */
void close_popup();
/**/
void cours_form();
/**/
void free_lock();
/* creates widgets related to lessons : window & buttons */
void lessons();
/* closes window passed as argument and opens lessons-related widgets (via a call to lessons) */
void transition_lessons();
/* creates main window and related widgets */
void home();
/* closes window passed as argument and calls home() */
void transition_home();
/* executes a DB query without expecting a result, used to specify what db to work on and/or insert new values in the DB */
void dbinsert(MYSQL *, char *);