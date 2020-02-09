# CE FICHIER SERT DE REFERENCE POUR LE FORMAT DU FICHIER SETTINGS

## RAPPEL DES VALEURS A STOCKER DANS LE FICHIER

 * couleur du fond d'écran  => string
 * couleur de la carte      => string
 * taille de la police      => int
 * son (activé/désactivé)   => bool
 * aides                    => bool

 ## STRUCTURE DU FICHIER

 * 1 byte (uint8_t)    => booléen "aide" (0 = off, 1 = on)
 * 1 byte (uint8_t)    => son (0 = off, 1 = on)
 * 1 byte (uint8_t)    => taille police
 * 10 bytes (char)     => string "couleur" de la carte
 * 10 bytes (char)     => string "couleur" du fond d'écran

 ## VALEURS PAR DEFAUT

 * aide = on, en mémoire : 1
 * son = on en mémoire : 1
 * taille de la police = 20, en mémoire : 20
 * couleur de la carte = "white", en mémoire :  98 108 97 99 107
 * couleur du fond = "black", en mémoire :      119 104 105 116 101