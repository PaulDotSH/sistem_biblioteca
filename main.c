#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "linkedLists.h"
#include "io.h"
#include "utils.h"

#define mesaj "Daca operatia a fost valida aceasta a fost rulata cu succes\n"

enum command {add,delete,list,search,ret,borrow,save,quit,help,clear};

List* cartiUser;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


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
    if (strcmp(cmd,"ret\n")==0 || strcmp(cmd,"return\n")==0)
        return ret;
    if (strcmp(cmd,"help\n")==0)
        return help;
    return -1;
}

void AfisareOptiuni() {
    printf(ANSI_COLOR_GREEN "Scrie o comanda pentru a interactiona cu programul\n" ANSI_COLOR_RESET);
    printf("Comenziile prezente momentan sunt:\n");
    printf(ANSI_COLOR_RED "add, delete/del, list, search, borrow, return, save/s, quit/q, help\n" ANSI_COLOR_RESET);
}

void AfisareDeleteOptiuni(List* carti) {
    int optiune;
    do {
        printf(ANSI_COLOR_YELLOW "0. Back\n" ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_CYAN mesaj ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_CYAN mesaj ANSI_COLOR_RESET);
        }
            break;
    }
}

void AfisareSearchOptiuni(List* carti) {
    int optiune;
    do {
        printf(ANSI_COLOR_YELLOW "0. Back\n" ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_CYAN mesaj ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_CYAN mesaj ANSI_COLOR_RESET);
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
            printf(ANSI_COLOR_CYAN mesaj ANSI_COLOR_RESET);
        }
            break;
    }
}

void AfisareBorrowOptiuni(List* carti) {
    int optiune;
    do {
        printf(ANSI_COLOR_YELLOW "0. Back\n" ANSI_COLOR_RESET);
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
            //adauga intr o lista a cartilor pe care le are utilizatorul

            Carte* ret = BorrowByISBN(carti,input);
            if (ret) {
                Append(cartiUser, CreateNode(ret));
                return;
            }
            printf(ANSI_COLOR_RED "Nu sunt destule in stoc sau cartea nu exista\n" ANSI_COLOR_RESET);
        }
            break;
    }
}

void AfisareReturnOptiuni(List* carti) {
    int optiune;
    do {
        printf(ANSI_COLOR_YELLOW "0. Back\n" ANSI_COLOR_RESET);
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
            printf("Introdu ISBN-ul\n");
            char input[100];
            fgets(input,100,stdin);
            StrcpyWithoutNewline(input,input);
            //da un check aici daca cartea e in lista utilizatorului
            if (ReturnByISBN(carti,cartiUser,input) == 0) {
                DeleteByISBN(cartiUser,input);
                printf(ANSI_COLOR_GREEN "Ai returnat cartea!\n" ANSI_COLOR_RESET);
                return;
            } printf(ANSI_COLOR_RED "S-a produs o eroare :(\n" ANSI_COLOR_RESET);

        }
            break;
    }
}

int main() {


    cartiUser = malloc(sizeof(List));
    cartiUser->head = 0;
    cartiUser = ReadCarti(USER_JSON_PATH);
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
        switch (cmd) {
            case quit:
                return 0;
            case add:
                Append(carti, CreateNode(ReadCarte()));
                SaveCarti(JSON_PATH,carti);
                break;
            case list:
                Display(carti);
                break;
            case borrow:
                AfisareBorrowOptiuni(carti);
                SaveCarti(JSON_PATH,carti);
                SaveCarti(USER_JSON_PATH,cartiUser);
                break;
            case save:
                SaveCarti(JSON_PATH,carti);
                SaveCarti(USER_JSON_PATH,cartiUser);
                printf(ANSI_COLOR_RED mesaj ANSI_COLOR_RESET);
                break;
            case search:
                AfisareSearchOptiuni(carti);
                //WaitNext2();
                WaitNext();
                break;
            case help:
                AfisareOptiuni();
                break;
            case ret:
                AfisareReturnOptiuni(carti);
                SaveCarti(JSON_PATH,carti);
                SaveCarti(USER_JSON_PATH,cartiUser);
                break;
            case clear:
                clear_screen();
                break;
            case delete:
                AfisareDeleteOptiuni(carti);
                SaveCarti(JSON_PATH,carti);
                WaitNext();
                break;
            default:
                exit(-1);
        }
    }
}

