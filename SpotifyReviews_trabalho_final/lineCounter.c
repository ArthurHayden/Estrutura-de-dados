#include <stdio.h>

int lineCounter (char *file) {
    FILE *fp = fopen(file, "r");
    int lines = 1;
    char ch;
    do{
        ch = fgetc(fp);
        if (ch == '\n'){
          lines++ ;
        }
    } while(ch != EOF);
    fclose(fp);
    return lines;
}