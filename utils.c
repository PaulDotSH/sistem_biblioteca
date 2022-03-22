//
// Created by admin on 22/03/2022.
//

#include "utils.h"
#include "stdio.h"

void StrcpyWithoutNewline(char* dest, char* src) {
    while (*src!='\n') { *dest++=*src++; }
    *dest=0;
}

void WaitNext() {
    char x;
    do {
        x = getchar();
    }
    while(x == '\0');
}

void WaitNext2() {
    scanf("%*[^\n]%*c");
}
