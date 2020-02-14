#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <io.h>
#include <stdbool.h>
//  RAPPEL : CF format_du_fichier_settings.md POUR LE FORMAT EN LECTURE/ECRITURE

typedef Struct settings {
    uint8_t taille_police;
    char carte[10];
    char fond[10];
}settings;

void create_default_settings_file(void) {
    char * path = "settings.txt";
    FILE * file = fopen(path, "wb");
    uint8_t taille_police = 20;
    char carte[10] = "white";
    char fond[10]  = "black";
    fwrite(&taille_police, 1, 1, file);
    fwrite(carte, 1, 10, file);
    fwrite(fond, 1, 10, file);
    fclose(file);
}

settings get_current_settings(void) {
    char * path = "settings.txt";
    FILE * file = fopen(path, "rb");
    uint8_t taille_police;
    char carte[10];
    char fond[10];
    fread(taille_police, 1, 1, file);
    fread(carte, 1, 10, file);
    fread(fond, 1, 10, file);
    settings current_settings;
    current_settings.taille_police = taille_police;
    current_settings.carte = carte;
    current_settings.fond = fond;
    return current_settings;
    fclose(file);
}

int8_t conf_file_is_valid(void) {
    char * path = "settings.txt";
    
}
