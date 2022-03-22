//
// Created by admin on 25/02/2022.
//

#ifndef SISTEM_BIBLIOTECA_L_CARTE_H
#define SISTEM_BIBLIOTECA_L_CARTE_H
#include "stdlib.h"
#include "stdio.h"
#define MAX_STRING_LENGTH 50
#include "cjson/cJSON.h"

typedef struct Carte Carte;
struct Carte {
    char* ISBN;
    char* Title;
    int AuthorsLen;
    char** Authors;
    int GenresLen;
    char** Genres;
    unsigned int Pages;
    unsigned int Price;
    unsigned int Total;
    unsigned int Available;
};

#endif //SISTEM_BIBLIOTECA_L_CARTE_H
