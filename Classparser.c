# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>

size_t fileSize(FILE *f){
    fseek(f, 0L, SEEK_END);
    size_t pos = ftell(f);
    rewind(f);
    return pos;
}

size_t numLines(FILE *f){
    rewind(f);
    size_t fs = fileSize(f);
    size_t i = 0;
    while(ftell(f) < fs){
        char* current = malloc(fs);
        fgets(current,fs,f);
        free(current);
        i++;
    }
    rewind(f);
    return i;
}

void stringify(char* string, FILE *f){
    size_t fs = fileSize(f);
    size_t lines = numLines(f);
    for(int i = 0; i < lines; i++){
        char* line = malloc(fs);
        fgets(line,fs,f);
        string = strcat(string,line);
        free(line);
    }
}

void substring(char *substring, char *string, int start, int end){
    for(int i = start; i < end; i++){
        substring = strcat(substring, string[i]);
    }
}

int indexOf(char *string, char *key){
    int v = strchr(string, key[0]);
    char *next = malloc(strlen(string));
    substring(next, string, v, strlen(string));
    while(v != -1){
        for(int i = 0; i < strlen(key); i++){
            if(strchr(string, key[i]) != v+i){
                v = -1;
            }
        }
        if(v == -1 && strlen(next) != 0){
            v = strchr(next, key[0]);
            substring(next, next, v, strlen(next));
        }else{
            return v;
        }
    }
    return -1; 
}

int main(size_t argc, char** argv){
    if(argc > 0){
        char* fname = argv[1];
        FILE *root = fopen(fname,"r");
        size_t fs = fileSize(root);
        char* contents = malloc(fs);
        stringify(contents,root);
        fclose(root);
        char** keywords = {"class","int","float","double","long","char","void","main"};
        char* output = malloc(fs);
    }else{
        printf("Incorrect Arguments!\n");
        return 42;
    }
}