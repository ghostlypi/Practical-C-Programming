# include<stdio.h>
# include <stdlib.h>
# include<stdbool.h>
# include<string.h>

double* sort(double* arr,size_t length){
    if(length == 1){
        return arr;
    }else{
        size_t mid = length/2;
        double arr1 [mid];
        double arr2 [length-mid];
        for (size_t i = 0; i < mid; i++)
        {
            arr1[i] = arr[i];
        }
        for (size_t i = mid; i < length; i++)
        {
            arr2[i-mid] = arr[i];
        }
        double* out1 = sort(arr1,mid);
        double* out2 = sort(arr2,length-mid);
        size_t i = 0;
        size_t j = 0;
        size_t k = 0;
        while (j < mid && k < length - mid){
            if (out1[j] <= out2[k]){
                arr[i] = out1[j];
                j++;
            }else if (out1[j] >= out2[k]){
                arr[i] = out2[k];
                k++;
            }
            i++; 
        }
        while(j < mid){
            arr[i] = out1[j];
            i++;
            j++;
        }
        while(k < length-mid){
            arr[i] = out2[k];
            i++;
            k++; 
        }
        return arr;
    }
}



int main(int argc, char *argv){
    unsigned char testsize = 10;
    srand(0);
    double arr [testsize];
    puts("{");
    for(int i = 0; i < testsize; i++){
        arr[i] = rand()%100;
        printf("%lf, ",arr[i]);
    }
    puts("}\n");
    double* out = sort(arr,testsize);
    puts("{");
    for(int i = 0; i < testsize; i++){
        printf("%lf, ",out[i]);
    }
    puts("}");
    return 0;

    // printf("This is a blank function!\n");
    // return 61;
}