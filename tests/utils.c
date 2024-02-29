#include "../head.h"

int countLines(FILE *f) {
    char ch;
    int count = 0;

    while((ch = fgetc(f)) != EOF) {
        if(ch == '\n') {
            count++;
        }
    }

    return count;
}