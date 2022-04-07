//
// Created by admin on 25/02/2022.
//

#ifndef SISTEM_BIBLIOTECA_L_LINKEDLISTS_H
#define SISTEM_BIBLIOTECA_L_LINKEDLISTS_H

#define JSON_PATH "db.json"
#define USER_JSON_PATH "user.json"

#include "carte.h"
typedef struct node node;
struct node {
    Carte* carte;
    node* next;
};

typedef struct List List;
struct List {
    node* head;
    int len;
};
int ReturnByISBN(List* carti, List* cartiUser, char* isbn);
void Append(List* l, node* n);
void DisplayNode(node* n);
void Display(List* l);
void SaveCarti(char* filename, List* Carti);
node* GetNodeByIndex(List* l, int index);
node* CreateNode(Carte* carte);
List* ReadCarti(char* filename);
void DeleteByIndex(List* l, int index);
void DeleteByISBN(List* l, char* isbn);
void DisplayByAutor(List* carti, char* autor);
void DisplayByTitle(List* carti, char* titlu);
void DisplayCartiDisponibile(List* carti);
void DisplayByGenre(List* carti, char* genre);
Carte* BorrowByISBN(List* carti, char* isbn);

#endif //SISTEM_BIBLIOTECA_L_LINKEDLISTS_H