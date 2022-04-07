//
// Created by admin on 22/03/2022.
//


#include "io.h"
#include <stdio.h>
#include "utils.h"
#include <string.h>

char* createJson(List * carti)
{
    cJSON* Carti = cJSON_CreateArray();
    int len = carti->len;
    for (int i = 0; i < len; i++)
    {
        cJSON* _carte = cJSON_CreateObject();
        Carte carte = *GetNodeByIndex(carti,i)->carte;

        cJSON_AddItemToObject(_carte,"ISBN", cJSON_CreateString(carte.ISBN));
        cJSON_AddItemToObject(_carte,"Title", cJSON_CreateString(carte.Title));
        cJSON_AddItemToObject(_carte,"Price", cJSON_CreateNumber(carte.Price));
        cJSON_AddItemToObject(_carte,"Pages", cJSON_CreateNumber(carte.Pages));
        cJSON_AddItemToObject(_carte,"AuthorsLen", cJSON_CreateNumber(carte.AuthorsLen));
        cJSON_AddItemToObject(_carte,"Total", cJSON_CreateNumber(carte.Total));
        cJSON_AddItemToObject(_carte,"Available", cJSON_CreateNumber(carte.Available));
        cJSON_AddItemToObject(_carte,"GenresLen", cJSON_CreateNumber(carte.GenresLen));
        cJSON_AddItemToObject(_carte,"Genres", cJSON_CreateStringArray(carte.Genres, carte.GenresLen));
        cJSON_AddItemToObject(_carte,"Authors", cJSON_CreateStringArray(carte.Authors, carte.AuthorsLen));

        cJSON_AddItemToArray(Carti,_carte);
    }
    char* str = cJSON_Print(Carti);
    cJSON_Delete(Carti);
    return str;
}

void SaveCarti(char* filename, List* Carti) {
    FILE* fp = fopen(filename, "w+");
    fprintf(fp, "%s", createJson(Carti));
    fclose(fp);
}

List* ReadCarti(char* filename) {
    FILE* fp = fopen(filename, "r");

    fseek (fp, 0, SEEK_END);
    int fLen = ftell(fp);
    fseek (fp, 0, SEEK_SET);
    char* buffer = malloc(fLen);
    fread (buffer, 1, fLen, fp);
    fclose(fp);

    cJSON* tmp = cJSON_Parse(buffer);

    int len = cJSON_GetArraySize(tmp);

    List* carti = malloc(sizeof(List));
    carti->head=NULL;
    carti->len=0;

    for (int i=0; i<len; i++) {
        cJSON* item = cJSON_GetArrayItem(tmp,i);
        Carte* carte = malloc(sizeof(Carte));

        carte->Total = cJSON_GetNumberValue(cJSON_GetObjectItem(item,"Total"));
        carte->Available = cJSON_GetNumberValue(cJSON_GetObjectItem(item,"Available"));

        carte->ISBN = malloc(MAX_STRING_LENGTH*sizeof(char));
        strcpy(carte->ISBN,cJSON_GetStringValue(cJSON_GetObjectItem(item,"ISBN")));
        carte->Title = malloc(MAX_STRING_LENGTH*sizeof(char));
        strcpy(carte->Title,cJSON_GetStringValue(cJSON_GetObjectItem(item,"Title")));

        carte->Price = cJSON_GetNumberValue(cJSON_GetObjectItem(item,"Price"));
        carte->Pages = cJSON_GetNumberValue(cJSON_GetObjectItem(item,"Pages"));
        carte->AuthorsLen = cJSON_GetNumberValue(cJSON_GetObjectItem(item,"AuthorsLen"));
        carte->Authors = (char**)malloc((carte->AuthorsLen)*sizeof(char*));

        cJSON* authors = cJSON_GetObjectItem(item,"Authors");

        for (int j=0; j<carte->AuthorsLen; j++) {
            carte->Authors[j] = malloc(MAX_STRING_LENGTH*sizeof(char));
            strcpy(carte->Authors[j],cJSON_GetStringValue(cJSON_GetArrayItem(authors,j)));
        }

        carte->GenresLen = cJSON_GetNumberValue(cJSON_GetObjectItem(item,"GenresLen"));
        strcpy(carte->ISBN,cJSON_GetStringValue(cJSON_GetObjectItem(item,"ISBN")));
        carte->Genres = (char**)malloc(carte->GenresLen*sizeof(char*));
        cJSON* genres = cJSON_GetObjectItem(item,"Genres");
        for (int j=0; j<carte->GenresLen; j++) {
            carte->Genres[j] = malloc(MAX_STRING_LENGTH*sizeof(char));
            strcpy(carte->Genres[j],cJSON_GetStringValue(cJSON_GetArrayItem(genres,j)));
        }

        Append(carti, CreateNode(carte));
    }
    carti->len=len;

    cJSON_Delete(tmp);
    free(buffer);

    return carti;
}

//oribil
Carte* ReadCarte() {
    Carte* carte = malloc(sizeof(Carte));
    carte->ISBN = malloc(MAX_STRING_LENGTH*sizeof(char));
    carte->Title = malloc(MAX_STRING_LENGTH*sizeof(char));
    printf("Introdu isbn-ul cartii\n");
    scanf("%[^\n]", carte->ISBN);
    WaitNext();
    //fgets(carte->ISBN,MAX_STRING_LENGTH,stdin);
    printf("Introdu titlul cartii\n");
    scanf("%[^\n]", carte->Title);
    WaitNext();
    //fgets(carte->Title,MAX_STRING_LENGTH,stdin);

    //strcpyWithoutNewline(carte->ISBN,carte->ISBN);
    //strcpyWithoutNewline(carte->Title,carte->Title);
    printf("Introdu numarul de autori\n");

    scanf("%d",&carte->AuthorsLen);
    WaitNext();

    carte->Authors = (char**)malloc(carte->AuthorsLen*sizeof(char*));
    for (int i=0; i<carte->AuthorsLen; i++) {
        carte->Authors[i] = malloc(MAX_STRING_LENGTH*sizeof(char));
        printf("Introdu autorul cu numarul %d\n",i+1);
        //fgets(carte->Authors[i],MAX_STRING_LENGTH,stdin);
        scanf("%[^\n]", carte->Authors[i]);
        WaitNext();
        //strcpyWithoutNewline(carte->Authors[i],carte->Authors[i]);
    }

    printf("Introdu numarul de genuri\n");
    scanf("%d",&carte->GenresLen);
    WaitNext();

    carte->Genres = (char**)malloc(carte->GenresLen*sizeof(char*));
    for (int i=0; i<carte->GenresLen; i++) {
        carte->Genres[i] = malloc(MAX_STRING_LENGTH*sizeof(char));
        printf("Introdu genul cu numarul %d\n",i+1);
        //fgets(carte->Genres[i],MAX_STRING_LENGTH,stdin);
        scanf("%[^\n]", carte->Genres[i]);
        WaitNext();
        //strcpyWithoutNewline(carte->Genres[i],carte->Genres[i]);
    }

    printf("Introdu numarul de pagini\n");
    scanf("%d",&carte->Pages);
    printf("Introdu pretul cartii\n");
    scanf("%d",&carte->Price);
    printf("Introdu stocul total\n");
    scanf("%d",&carte->Total);
    printf("Introdu stocul prezent\n");
    scanf("%d\n",&carte->Available);

    return carte;
}