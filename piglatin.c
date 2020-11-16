# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>

bool isCapped(const char c) {
  return (c < 91) && (c>=65);
}

bool isVowel(const char chr) {
  char c = tolower(chr);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char *word_to_pig_latin(const char *word) {
  bool capped = isCapped(word[0]);
  if(isVowel(word[0])){
    size_t len = strlen(word)+4;
    char* out = malloc(sizeof(char)*len);
    memset(out, 0, sizeof(char)*len);
    if (capped){
      out[0] = toupper(word[0]);
    }else{
      out[0] = word[0];
    }
    int i = 1;
    for(; i < strlen(word); i++){
      out[i] = word[i];
    }
    strcat(out,"way");
    return out;
  }else{
    size_t len = strlen(word)+3;
    char* out = malloc(sizeof(char)*len);
    char end[len];
    memset(end,0,len*sizeof(char));
    int start = strcspn(word,"aeiouy");
    int i = strcspn(word,"aeiouy");
    if(capped){
      out[0] = toupper(word[i]);
    }else{
      out[0] = word[i];
    }
    i++;
    for(int j = 1; i < len-2; i++){
      out[j] = word[i];
      j++;
    }
    for(i = 0; i<start; i++){
      end[i] = tolower(word[i]);
    }
    strcat(out,end);
    strcat(out,"ay");
    return out;
  }
}

void test_pig_latin() {
    const char *cases[][2] = {
        { "exit", "exitway" },
        { "Yellow", "Ellowyay" },
        { "scram", "amscray" },
        { "blue", "ueblay" },
        { "Type", "Ypetay" },
        { "igloo", "iglooway" },
        { "Float", "Oatflay" },
        { "bandanda",  "andandabay" },
        { "Apple", "Appleway" },
        
        // feel free to add more cases above this line,
        // but leave the { NULL, NULL } line intact.
        { NULL, NULL }
    };
    
    size_t i = 0;
    int failed_cases = 0, passed_casses = 0;
    while(1) {
        const char *original = cases[i][0];
        const char *expected_latin = cases[i][1];
        
        if(!original || !expected_latin) {
            break;
        }
        
        char *actual_latin = word_to_pig_latin(original);
        printf("\n%s\n", actual_latin);
        if(!actual_latin || strcmp(expected_latin, actual_latin) != 0) {
            // printf("Test case failed: expected '%s' -> '%s', but got '%s'\n", original, expected_latin, actual_latin);
            
            failed_cases++;
        }
        else {
            passed_casses++;
        }
        
        free(actual_latin);
        
        i++;
    }
    
    printf("%d/%d cases passed\n", passed_casses, failed_cases + passed_casses);
}

int main(int argc, char *argv[]) {
    test_pig_latin();    
    return 0;
}
