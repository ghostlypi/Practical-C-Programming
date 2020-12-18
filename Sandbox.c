# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>


int main(size_t argc, char *argv){
    FILE *fp;
    char buffer[250*sizeof(char)];
    fp = fopen("Thing.txt", "w");
    fputs("Hello World!", fp);
    fclose(fp);
    fp = fopen("Thing.txt", "r");
    fgets(buffer, sizeof(char)*250, (FILE*) fp);
    printf("%s\n", buffer);
    fclose(fp);
    return 0;
}





// int main (size_t argc, char* argv){
//     return 61;
// }