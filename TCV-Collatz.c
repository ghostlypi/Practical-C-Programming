# include <stdio.h>
# include <stdlib.h>

unsigned short collatz(int val){
    if(val == 1){
        return 0;
    }
    if(val % 2 == 0){
        return 1+collatz(val/2);
    }
    else{
        return 1+collatz((val*3)+1);
    }
}

double* maxcollatzratio(int cap){
    int max = 0;
    int maxi = 0;
    int rmax = 0;
    int rmaxi = 0;
    double rmaxr = 0;
    for (int i = 3; i < cap; i += 2){
        int value = collatz(i);
        double ratio = ((double)value/i);
        if (value > max){
            max = value;
        }
        if (max == value){
            maxi = i;
        }
        if(ratio > rmaxr){
            rmaxr = ratio;
        }
        if (rmaxr == ratio){
            rmaxi =i;
        }
        if (rmaxr == ratio){
            rmax = value;
        }
    }
    double* out = malloc(5*sizeof(double));
    out[4] = rmaxr;
    out[3] = rmax;
    out[2] = rmaxi;
    out[1] = max;
    out[0] = maxi;
    return out;
}

int main(int argc, char* argv){
    double* arr2 = maxcollatzratio(100000);
    printf("%d has a stopping time of %d\n", arr2[0], arr2[1]);
    printf("%.0lf has a stopping time of %.0lf and a ratio of %.2lf\n",arr2[2],arr2[3],arr2[4]);
    free(arr2);
    return 0;
}