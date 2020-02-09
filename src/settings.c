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

void create_default_settings_file(const char * path) {
    file = fopen(path, "wb");
    uint8_t taille_police = 20;
    char carte[10] = "white";
    char fond[10]  = "black";
    fwrite(&taille_police, 1, 1, file);
    fwrite(carte, 1, 10, file);
    fwrite(fond, 1, 10, file);
}