# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>

size_t fileSize(FILE *f){
    fseek(f, 0L, SEEK_END);
    size_t pos = ftell(f);
    rewind(f);
    pos -= ftell(f);
    return pos;
}

size_t numLines(FILE *f){
    rewind(f);
    char* first = malloc(fileSize(f));
    fgets(first, fileSize(f), f);
    char* current = malloc(fileSize(f));
    int i = 0;
    while(current != first){
        i++;
        fgets(current, fileSize(f), f);
        printf("%s",current);
    }

    return i;
}

int main(size_t argc, char** argv){
    if(argc > 0){
        char* fname = argv[1];
        FILE *root = fopen(fname,"r");
        char* contents = malloc(fileSize(root));
        for(int i = 0; i < numLines(root); i++){
            fgets(contents, fileSize(root), root);
            printf("Value:\n %s", contents);
        }
        
    }else{
        printf("Incorrect Arguments!\n");
        return 42;
    }
}