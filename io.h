//
// Created by admin on 22/03/2022.
//

#ifndef SISTEM_BIBLIOTECA_L_IO_H
#define SISTEM_BIBLIOTECA_L_IO_H

#include "linkedLists.h"

char* createJson(List * carti);
void SaveCarti(char* filename, List* Carti);
List* ReadCarti(char* filename);
Carte* ReadCarte();

#endif //SISTEM_BIBLIOTECA_L_IO_H
