#include <stdio.h>
#include <string.h>

void red();
void reset();
void finder(char needle[], char stash_path[], char param[]);

int main(int argc, char* argv[]) {

    if (argc > 4) {
        printf("Too many arguments!\n");
    } else if (argc == 3) {
        finder(argv[1], argv[2], "0");
    } else if (argc == 4){
        finder(argv[2], argv[3], argv[1]);
    }
    return 0;
}

void finder(char needle[], char stash_path[], char param[]) {
    FILE *fptr = fopen(stash_path,"r");
    char symb;
    printf("%s", param);
    if(fptr != NULL) {
        while (symb != EOF) {
            symb = fgetc(fptr);
            if (symb != needle[0]) {
                printf("%c", symb);
                continue;
            } else {
                int flag = 1;
                char tmp[100];
                tmp[0] = symb;
                for (int i=1; i < (int) strlen(needle); i++) {
                    symb = fgetc(fptr);
                    tmp[i] = symb;
                    flag = (needle[i] == symb) ? 1 : 0;
                    if (!flag) {
                        printf("%s", tmp);
                        break;
                    }
                }
                if (flag) {
                    red();
                    printf("%s", needle);
                    reset();
                }
            }
        }      
    } else {
        printf("No such file!");
    }
    fclose(fptr);
}

void red() {
  printf("\033[1;31m");
}

void reset() {
  printf("\033[0m");
}
