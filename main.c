#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "linkedLists.h"
#include "io.h"
#include "utils.h"

#define mesaj "Daca operatia a fost valida aceasta a fost rulata cu succes\n"

enum command {add,delete,list,search,borrow,save,quit,help,clear};

void clear_screen()
{
#ifdef WINDOWS
    system("cls");
#else
    system("clear");
#endif
}

int parseCommand(char* cmd) {
    if (strcmp(cmd,"add\n")==0)
        return add;
    if (strcmp(cmd,"delete\n")==0 || strcmp(cmd,"del\n")==0)
        return delete;
    if (strcmp(cmd,"list\n")==0)
        return list;
    if (strcmp(cmd,"search\n")==0)
        return search;
    if (strcmp(cmd,"borrow\n")==0)
        return borrow;
    if (strcmp(cmd,"save\n")==0 || strcmp(cmd,"s\n")==0)
        return save;
    if (strcmp(cmd,"quit\n")==0 || strcmp(cmd,"q\n")==0)
        return quit;
    if (strcmp(cmd,"clear\n")==0)
        return clear;
    if (strcmp(cmd,"help\n")==0)
        return help;
    return -1;
}

void AfisareOptiuni() {
    printf("Scrie o comanda pentru a interactiona cu programul\n");
    printf("Comenziile prezente momentan sunt:\n");
    printf("add, delete/del, list, search, borrow, return, save/s, quit/q, help\n");
}

void AfisareDeleteOptiuni(List* carti) {
    int optiune;
    do {
        printf("0. Back\n");
        printf("1. Delete dupa index\n");
        printf("2. Delete dupa ISBN\n");
        scanf("%d", &optiune);
        clear_screen();
    } while (!(optiune > -1 && optiune < 3));
    int index;
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            printf("Introdu index-ul\n");
            scanf("%d", &index);
            if (index<0 || index > carti->len) {
                printf("Index out of bounds\n");
                AfisareDeleteOptiuni(carti);
                return;
            }
            DeleteByIndex(carti, index);
            printf(mesaj);
        }
            break;
        case 2:
        {
            WaitNext();
            printf("Introdu ISBN-ul\n");
            char input[100];
            fgets(input,100,stdin);
            StrcpyWithoutNewline(input,input);
            DeleteByISBN(carti,input);
            printf(mesaj);
        }
            break;
    }
}

void AfisareSearchOptiuni(List* carti) {
    int optiune;
    do {
        printf("0. Back\n");
        printf("1. Cauta carti disponibile\n");
        printf("2. Cauta carti dupa titlu\n");
        printf("3. Cauta carti dupa autor\n");
        printf("4. Cauta carti dupa genre\n");
        scanf("%d", &optiune);
        clear_screen();
    } while (!(optiune > -1 && optiune < 5));
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            DisplayCartiDisponibile(carti);
        }
            break;
        case 2:
        {
            WaitNext();
            printf("Introdu titlul\n");
            char input[100];
            fgets(input,100,stdin);
            StrcpyWithoutNewline(input,input);
            DisplayByTitle(carti,input);
            printf(mesaj);
        }
            break;
        case 3:
        {
            WaitNext();
            printf("Introdu autorul\n");
            char input[100];
            fgets(input,100,stdin);
            StrcpyWithoutNewline(input,input);
            DisplayByAutor(carti,input);
            printf(mesaj);
        }
            break;
        case 4:
        {
            WaitNext();
            printf("Introdu genre-ul\n");
            char input[100];
            fgets(input,100,stdin);
            StrcpyWithoutNewline(input,input);
            DisplayByGenre(carti,input);
            printf(mesaj);
        }
            break;
    }
}

void AfisareBorrowOptiuni(List* carti) {
    int optiune;
    do {
        printf("0. Back\n");
        printf("1. Imprumuta dupa ISBN\n");
        scanf("%d", &optiune);
        clear_screen();
    } while (!(optiune > -1 && optiune < 2));
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            WaitNext();
            printf("Introdu ISBN\n");
            char input[100];
            fgets(input,100,stdin);
            StrcpyWithoutNewline(input,input);
            (BorrowByISBN(carti,input)) ? printf("Ai imprumutat cartea cu succes\n") : printf("Nu sunt destule in stoc sau cartea nu exista\n");
        }
            break;
    }
}

void AfisareReturnOptiuni(List* carti) {
    int optiune;
    do {
        printf("0. Back\n");
        printf("1. Returneaza dupa ISBN\n");
        scanf("%d", &optiune);
        clear_screen();
    } while (!(optiune > -1 && optiune < 2));
    switch (optiune) {
        case 0:
            return;
        case 1:
        {
            WaitNext();
            printf("Introdu ISBN\n");
            char input[100];
            fgets(input,100,stdin);
            StrcpyWithoutNewline(input,input);
            //da un check aici daca cartea e in lista utilizatorului
        }
            break;
    }
}

int main() {
    List* carti = ReadCarti(JSON_PATH);
    AfisareOptiuni();
    char input[MAX_STRING_LENGTH];
    for (;;) {
        fgets(input,MAX_STRING_LENGTH,stdin);
        int cmd = parseCommand(input);
        if (cmd==-1) {
            WaitNext2();
            continue;
        }
        clear_screen();
        //printf("Cmd: %d\n",cmd);
        switch (cmd) {
            case quit:
                return 0;
            case add:
                Append(carti, CreateNode(ReadCarte()));
                break;
            case list:
                Display(carti);
                break;
            case borrow:
                AfisareBorrowOptiuni(carti);
                break;
            case save:
                SaveCarti(JSON_PATH,carti);
                printf(mesaj);
                break;
            case search:
                AfisareSearchOptiuni(carti);
                //WaitNext2();
                WaitNext();
                break;
            case help:
                AfisareOptiuni();
                break;
            case clear:
                clear_screen();
                break;
            case delete:
                AfisareDeleteOptiuni(carti);
                WaitNext();
                break;
            default:
                exit(-1);
        }
    }
}

