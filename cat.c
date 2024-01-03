#include <stdio.h>
#include <string.h>

void printFile(char path[], char param[]);

int main(int argc, char* argv[]) {
    if (argc > 3) {
        printf("Too many arguments!\n");
    } else if (argc == 2) {
        printFile(argv[1], "0");
    } else if (argc == 3){
        printf("%s\n",  argv[1]);
        printFile(argv[2], argv[1]);
    }
    return 0;
}

void printFile(char path[], char param[]) {
    FILE *fptr = fopen(path,"r");
    char symb, prev_symb;
    int b_flag, e_flag, n_flag, s_flag, t_flag;

    b_flag = strchr(param, 'b') != NULL ? 1 : 0;
    e_flag = strchr(param, 'e') != NULL ? 1 : 0;
    n_flag = strchr(param, 'n') != NULL ? 1 : 0;
    s_flag = strchr(param, 's') != NULL ? 1 : 0;
    t_flag = strchr(param, 't') != NULL ? 1 : 0;

    if(fptr != NULL) {
        int num_line = 1;
        while (symb != EOF) {
            if (!prev_symb && (b_flag || n_flag)) {
                printf("%d ", num_line);
                num_line++;
            }
            symb = fgetc(fptr);
            if ((prev_symb == '\n' && symb != '\n' && b_flag && symb != EOF) || (prev_symb == '\n' && n_flag && symb != EOF && !b_flag)) {
                printf("%d ", num_line);
                num_line++;
            }
            if (e_flag && symb == '\n' && prev_symb != '\n')
                printf("$");
            if (s_flag && symb == '\n' && prev_symb == '\n')
                continue;
            if (t_flag && symb == '\t') {
                printf("^I");
                continue;
            }
            printf("%c", symb);
            prev_symb = symb;
        }      
    } else {
        printf("No such file!");
    }
    fclose(fptr);
}
