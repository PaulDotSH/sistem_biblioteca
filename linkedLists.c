//
// Created by admin on 25/02/2022.
//

#define nullptr NULL
#define NULL 0

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "linkedLists.h"

void Append(List* l, node* n) {
    if (l->head==nullptr) {
        l->head=n;
        l->len++;
        return;
    }
    node* tmp = l->head;
    while (tmp->next!=nullptr)
        tmp=tmp->next;
    tmp->next=n;
    l->len++;
}

void DisplayNode(node* n) {
    printf("ISBN: %s\nTitlu: %s\nNumar Pagini: %d\nPret: %d\nStoc: %d\nTotal: %d\n",
           n->carte->ISBN,
           n->carte->Title,
           n->carte->Pages,
           n->carte->Price,
           n->carte->Available,
           n->carte->Total);
    printf("Autori: ");
    for (int i=0; i<n->carte->AuthorsLen; i++) {
        if (i+1!=n->carte->AuthorsLen)
            printf("%s, ",n->carte->Authors[i]);
        else
            printf("%s",n->carte->Authors[i]);
    }
    printf("\n");

    printf("Genuri: ");
    for (int i=0; i<n->carte->GenresLen; i++) {
        if (i+1!=n->carte->GenresLen)
            printf("%s, ",n->carte->Genres[i]);
        else
            printf("%s",n->carte->Genres[i]);
    }
    printf("\n---------------------\n");
}

void Display(List* l) {
    node* n = l->head;
    int i=0;
    while (n!=nullptr) {
        printf("Index carte: %d\n",i++);
        DisplayNode(n);
        n=n->next;
    }
    printf("\n");
}

node* CreateNode(Carte* carte) {
    node* n = malloc(sizeof(node));
    n->carte=carte;
    n->next=nullptr;
    return n;
}

node* GetNodeByIndex(List* l, int index) {
    int i=0;
    node* node = l->head;
    while (node->next!=nullptr && i++!=index) {
        node=node->next;
    }
    return node;
}

void FreeNode(node* node) {
    free(node->carte->ISBN);
    free(node->carte->Title);
    for (int i=0; i<node->carte->GenresLen; i++)
        free(node->carte->Genres[i]);
    for (int i=0; i<node->carte->AuthorsLen; i++)
        free(node->carte->Authors[i]);
    free(node);
}

void DeleteByIndex(List* l, int index) {
    node* curr = l->head;
    if (index==0) {
        l->head = l->head->next;
        l->len--;
        FreeNode(curr);
        return;
    }

    while (--index) {
        curr=curr->next;
    }
    node* tmp = curr->next;
    curr->next = curr->next->next;
    l->len--;
    FreeNode(tmp);
}

void DeleteByISBN(List* l, char* isbn) {
    if (strcmp(l->head->carte->ISBN,isbn) == 0) {
        node* curr = l->head;
        l->head = l->head->next;
        l->len--;
        FreeNode(curr);
        return;
    }

    node* curr = l->head;
    while (curr->next != NULL) {
        if (strcmp(l->head->carte->ISBN,isbn) == 0) {
            node* tmp = curr->next;
            curr->next = curr->next->next;
            FreeNode(tmp);
            l->len--;
            return;
        }
        curr=curr->next;
    }
}

void DisplayCartiDisponibile(List* carti) {
    node* tmp = carti->head;
    while (tmp!=NULL) {
        if (tmp->carte->Available>0) DisplayNode(tmp);
        tmp=tmp->next;
    }
}

void DisplayByAutor(List* carti, char* autor) {
    node* tmp = carti->head;
    while (tmp!=NULL) {
        for (int i=0; i<tmp->carte->AuthorsLen; i++) {
            if (strcmp(tmp->carte->Authors[i],autor)==0) {
                DisplayNode(tmp);
                break;
            }
        }
        tmp=tmp->next;
    }
}

void DisplayByGenre(List* carti, char* genre) {
    node* tmp = carti->head;
    while (tmp!=NULL) {
        for (int i=0; i<tmp->carte->GenresLen; i++) {
            if (strcmp(tmp->carte->Genres[i],genre)==0) {
                DisplayNode(tmp);
                break;
            }
        }
        tmp=tmp->next;
    }
}

void DisplayByTitle(List* carti, char* titlu) {
    node* tmp = carti->head;
    while (tmp!=NULL) {
        if (strcmp(tmp->carte->Title,titlu)==0) DisplayNode(tmp);
        tmp=tmp->next;
    }
}

Carte* BorrowByISBN(List* carti, char* isbn) {
    node* curr = carti->head;
    while (curr != NULL) {
        if (strcmp(curr->carte->ISBN,isbn)==0) {
            if (curr->carte->Available>0) {
                curr->carte->Available--;
                return curr->carte;
            }
            return NULL;
        }
        curr = curr->next;
    }
    return NULL;
}

int ReturnByISBN(List* carti, List* cartiUser, char* isbn) {
    node* curr = cartiUser->head;
    int ok=0;
    while (curr!=NULL) {
        if (strcmp(curr->carte->ISBN,isbn)==0) {
            ok=1;
            break;
        }
        curr = curr->next;
    }
    if (ok==0) return -1;
    //daca continuam, am gasit cartea la utilizator

    curr = carti->head;
    while (curr != NULL) {
        if (strcmp(curr->carte->ISBN,isbn)==0) {
            if (curr->carte->Available>=0) {
                curr->carte->Available++;
                return 0;
            }
            return -1;
        }
        curr = curr->next;
    }
    return -1;
}