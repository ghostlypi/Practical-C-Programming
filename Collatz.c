# include <stdio.h>
# include <stdlib.h>

unsigned short collatz(int val){
    if(val == 1){
        return 0;
    }
    return val % 2 == 0 ? 1+collatz(val/2) : 1+collatz((val*3)+1);
}

int* maxcollatz(int cap){
    int max = 0;
    int maxi = 0;
    for(int i = 3; i < cap; i+=2){
        int value = collatz(i);
        max = value > max ? value : max;
        maxi = max == value ? i : maxi;
    }
    int* out = malloc(2*sizeof(int));
    out[1] = max;
    out[0] = maxi;
    return out;
}

double* maxcollatzratio(int cap){
    int max = 0;
    int maxi = 0;
    double maxr = 0;
    for (int i = 3; i < cap; i += 2){
        int value = collatz(i);
        double ratio = ((double)value/i);
        maxr = ratio > maxr ? ratio : maxr;
        maxi = maxr == ratio ? i : maxi;
        max = maxr == ratio ? value : max;
    }
    double* out = malloc(3*sizeof(double));
    out[2] = maxr;
    out[1] = max;
    out[0] = maxi;
    return out;
}

int main(int argc, char* argv){
    int* arr = maxcollatz(100000);
    double* arr2 = maxcollatzratio(100000);
    printf("%d has a stopping time of %d\n", arr[0], arr[1]);
    printf("%.0lf has a stopping time of %.0lf and a ratio of %.2lf\n",arr2[0],arr2[1],arr2[2]);
    free(arr);
    free(arr2);
    return 0;
}