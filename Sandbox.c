# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include <ctype.h>

bool isCapped(const char c) {
  return (c < 91) && (c>=65);
}

char toLower(const char c){
  if (c < 91 && c > 64){
    return c + 32;
  }else{
    return c;
  }
}

char toUpper(const char c){
  if (c > 96 && c < 123){
    return c + 32;
  }else{
    return c;
  }
}

bool isVowel(const char chr) {
  char c = toLower(chr);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char *word_to_pig_latin(const char *word) {
  bool capped = isCapped(word[0]);
  if(isVowel(word[0])){
    size_t len = strlen(word)+4;
    char* out = malloc(sizeof(char)*len);
    if (capped){
      out[0] = toUpper(word[0]);
    }else{
      out[0] = word[0];
    }
    int i = 1;
    for(i < strlen(word); i++;){
      printf("%c",word[i]);
      out[i] = word[i];
    }
    out[i]='w';
    out[i+1]='a';
    out[i+2]='y';
    out[i+3]=0;
    return out;
  }else{
    size_t len = strlen(word)+3;
    char* end = malloc(sizeof(char)*len);
    char* out = malloc(sizeof(char)*len);
    int i = 0;
    while((i < len-2) && !isVowel(word[i])){
      end[i] = word[i];
      i++;
    }
    end[i+1]='a';
    end[i+2]='y';
    end[i+3]=0;
    if(capped){
      out[0] = toUpper(word[i]);
    }else{
      out[0] = word[i];
    }
    i++;
    int j;
    for(j = 1; i < len-2; i++){
      out[j] = word[i];
      j++;
    }
    i = 0;
    while(end[i]!=0){
      out[j] = end[i];
      i++;
      j++;
    }
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
