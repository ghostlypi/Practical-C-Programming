# include<stdio.h>
# include <stdlib.h>
# include<stdbool.h>
# include<string.h>

int most_common_element(int nums [], size_t length){
    int counts [100] = {0};
    for(int i = 0; i < length; i++){
        counts[nums[i]]++;
    }
    int max = 0;
    int maxi = 0;
    for(int i = 0; i < 100; i++){
        if(counts[i] > max){
            max = counts[i];
            maxi = i;
        }
    }
    return maxi;
}

int main(int argc, char *argv[]){
    int arr [100];
    srand(0);
    puts("{");
    for (int i = 0; i < 100; i++)
    {
        arr[i] = rand()%100;
        printf("%d, ",arr[i]);
    }
    puts("}");
    printf("%d\n",most_common_element(arr,100));
    return 0;
}