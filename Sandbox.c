# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>

void* resize(void* p, size_t length, size_t final){
  void* out = malloc(final);
  for(int i = 0; i < length; i++){
    memcpy(out,p,length);
  }
  free(p);
  return out;
}

void insert(int* arr, int v, int i,size_t length){
  length++;
  arr = realloc(arr, length*sizeof(int));
  int tmp = v;
  for(int j = i; j < length; j++){
    int tmp1 = arr[j];
    arr[j] = tmp;
    tmp = tmp1;
  }
}

int main(int argc, char *argv){
    int* arr = malloc(sizeof(int)*4);
    for(int i = 0; i < 4; i++){
      arr[i] = i;
    }
    resize(arr, 4*sizeof(int), 5*sizeof(int));
    printf("This is a blank function!\n");
    return 61;
}
