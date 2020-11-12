# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>

size_t my_strspn(const char *s, const char *accept){
    for(size_t i = 0; i < strlen(s);i++){
        for(size_t j = 0; j < strlen(accept)+1; j++){
            if(s[i] == accept[j]){
                return i;
            }
        }
    }
}

size_t my_strcspn(const char *s, const char *reject){
    size_t index = my_strspn(s,reject);
    return s[index] == 0 ? index : index-1;
}

char *my_strtok(char *s, const char *delims){
    // static variables maintain their value between
    // calls to the function in which they are declared.
    static char *next_token = NULL;
    
    if(s == NULL) {
        // If the first argument is NULL, we're
        // starting from the last token we found.
        s = next_token;
    }
    
    // ** (1) Your comment here.
    // What is the next line of code doing?
    //This is updating the local value of the pointer to the location of the next delimiter
    s += my_strspn(s, delims);
    
    // If we're at the end of the string, we're done
    if(*s == '\0') {
        return NULL;
    }
    
    // ** (2) Your comment here.
    // What is the next line of code doing?
    //This is finding the next location of the 
    next_token = s + my_strcspn(s, delims);
    
    // ** (3) Your comment here.
    // What is this if-statement doing and why?
    // If the next value is not null, we will null out the next token for the next iteration
    if(*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }
    
    return s;
}

int main(int argc, char *argv[]){   
    // strtok will modify its argument,
    // so we can't use a literal directly.
    char *s = strdup("10-31/2020");

    const char *delims = "-/";

    // The first call needs the string we're
    // tokenizing.
    char *tok_start = strtok(s, delims);

    while(tok_start != NULL) {
        // strtok will add null bytes to our
        // original string so that the things
        // it returns are effectively substrings
        printf("got a token: \"%s\"\n", tok_start);
        
        // Subsequent calls operating on the
        // same string need to pass NULL for
        // the first argument.
        tok_start = strtok(NULL, delims);
    }

    free(s);
    return 0;
}