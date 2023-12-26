#include <stdio.h>

void printFile(char path[], char param);

int main(int argc, char* argv[]) {
    // Debug mode - remove after final
    printf("You have entered %d arguments:\n", argc);
    if (argc > 2) {
        printf("Too many arguments!\n");
    } else if (argc == 2) {
        printFile(argv[1], '0');
    } else {
    }
    return 0;
}

void printFile(char path[], char param) {
    FILE *fptr = fopen(path,"r");
    char symb;
    if(fptr != NULL) {
        while (symb != EOF) {
            symb = fgetc(fptr);
            printf("%c", symb);
        }      
    } else {
        printf("No such file!");
    }
    fclose(fptr);
}
