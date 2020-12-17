#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define dim 30

void WORD(FILE *f, char *s, int *correct, int *read);
bool modifyWord(char word[], char *result);

int main(){
    char *word;
    int end = 0, noWord = 0;
    FILE *f = fopen("file.txt", "r");
    if (f == NULL){
        printf ("file err\n");
        return 0;
    }
    word = (char *)malloc(sizeof(char)*dim);
    WORD(f, word, &end, &noWord);
    printf ("result: %s\nend_code: %d\nno_word_code: %d\n", word, end, noWord);
    fclose(f);

    return 0;
}

void WORD(FILE *f, char *s, int *end, int *noWord){
    char letter, word[dim];
    int i = 0;

    letter = fgetc(f);
    if (letter == EOF){
        *noWord = 1;
        *end = 1;
        return;
    }
    else if ((letter >= 48 && letter <= 57) || (letter >= 97 && letter <= 122)){
        while (feof(f) != 1 && letter != '#'){
            //this if is useless
            if (letter != '#'){
                word[i] = letter;
                i++;
            }
            letter = fgetc(f);  
        }
        printf ("w: %s\n", word);
        if (modifyWord(word, s) == false){
            *end = 0;
            *noWord = 1;
        }
        else if (modifyWord(word, s) == true){
            *end = 0;
            *noWord = 0;
        }
        //to shit the pointer to the next char
        if (letter == '#')
            letter = fgetc(f);
    }
    else if (letter == '#'){
        letter = fgetc(f);
        if ((letter >= 48 && letter <= 57) || (letter >= 97 && letter <= 122)){
            word[i] = letter;
            i++;
            while (feof(f) != 1 && letter != '#'){
                letter = fgetc(f);
                if (letter != '#'){
                    word[i] = letter;
                    i++;
                }
            }
            printf ("w: %s\n", word);
            if (modifyWord(word, s) == false){
                *end = 0;
                *noWord = 1;
            }
            else if (modifyWord(word, s) == true){
                *end = 0;
                *noWord = 0;
            }
        }
        else{
            *noWord = 1;
            *end = 0;
            return;
        }
    }
}

bool modifyWord(char word[], char *result){
    int i = 0, k = 0;
    bool flag = false;

    for (; i<strlen(word); i++){
        if (word[i] >= 97 && word[i] <= 122){
            result[k] = word[i];
            k++;
            flag = true;
        }
    }

    return flag;
}