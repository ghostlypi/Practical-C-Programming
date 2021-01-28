# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>

typedef struct{
    char value[255];
} String;

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
        substring[i-start] = string[i];
    }
}

int indexOf(char *string, char *key){
    int v = (int)(strchr(string, key[0])-string);
    char *next = malloc(strlen(string));
    substring(next, string, v, strlen(string));
    while(v != -1){
        for(int i = 0; i < strlen(key); i++){
            if((int)(strchr(string, key[i])-string)/8 != v+i){
                v = -1;
            }
        }
        if(v == -1 && strlen(next) != 0){
            v = (int)(strchr(next, key[0])-string);
            substring(next, next, v, strlen(next));
        }else{
            return v;
        }
    }
    return -1; 
}

void split(char *str, String *arr, size_t fs){
    size_t last = 0;
    size_t arrpos = 0;
    for(int i = 0; i < fs; i++){
        if(str[i] == ' ' || str[i] == '\t'){
            String substr;
            memset(substr.value,0,255);
            substring(substr.value, str, last,i);
            if(substr.value[0] != 0){
                arr[arrpos] = substr;
                arrpos++;
            }
            last = i+1;
        }
    }
    String substr;
    memset(substr.value,0,255);
    substring(substr.value, str, last,fs);
    arr[arrpos] = substr;
}

int main(size_t argc, char **argv){
    if(argc > 0){
        char* fname = argv[1];
        FILE *root = fopen(fname,"r");
        size_t fs = fileSize(root);
        char* contents = malloc(fs);
        char* output = malloc(fs);
        memset(contents,0,fs);
        memset(output,0,fs);
        stringify(contents,root);
        fclose(root);
        String *arr = malloc(sizeof(String)*fs);
        memset(arr,0,sizeof(String)*fs);
        split(contents,arr, fs);
        char* fragment = malloc(fs);
        memset(fragment,0,fs);
        substring(fragment, contents, 0, indexOf(contents,"class"));
        strcat(output, fragment);
        memset(fragment,0,fs);
        printf("%s",output);
        return 0;
    }else{
        printf("Incorrect Arguments!\n");
        return 42;
    }
}