#include <stdio.h>
#include <string.h>

void red();
void reset();
void finder(char needle[], char stash_path[], char param[]);
void print_result(char line[], char needle[]);
int check_needle(char line[], char needle[]);

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
    printf("%s %s\n", param, needle);
    if(fptr != NULL) {
        while (symb != EOF) {
            char tmp_line[1000] = "";
            int counter = 0;
            while (symb != '\n') {
                symb = fgetc(fptr);
                if (symb != '\n') {
                    tmp_line[counter] = symb;
                    counter++;
                } else {
                    symb = ' ';
                    break;
                }
            }
            if (check_needle(tmp_line, needle))
                print_result(tmp_line, needle);
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

void print_result(char line[], char needle[]) {
    int counter = 0;
    while (counter < (int) strlen(line)) {
        int needle_counter = 0;
        if (line[counter] != needle[0] && line[counter] != '\0') {
            printf("%c", line[counter]);
        } else {
            char tmp_word[1000] = " ";
            while (line[counter] == needle[needle_counter]) {
                tmp_word[needle_counter] = line[counter];
                counter++;
                needle_counter++;
            }
            if (strlen(tmp_word) == strlen(needle)) {
                red();
                printf("%s ", tmp_word);
                reset();
            } else {
                tmp_word[needle_counter] = line[counter];
                printf("%s", tmp_word);
            }
        }
        counter++;
    }
    printf("\n");
}

int check_needle(char line[], char needle[]) {
    int flag = 0;
    int counter = 0;
    while (counter < (int) strlen(line)) {
        int correct_chars_counter = 0;
        if (line[counter] == needle[0]) {
            counter++;
            for(int i = 1; i < (int) strlen(needle); i++) {
                correct_chars_counter += (line[counter] == needle[i]);
                counter++;
            }
            if (correct_chars_counter + 1 == (int) strlen(needle)) {
                flag = 1;
                break;
            }
        } else {
            counter++;
        }
    }
    return flag; 
}