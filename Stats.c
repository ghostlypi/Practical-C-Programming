# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>
# include<string.h>
# include<math.h>

double sum(const double *nums, size_t count){
    double sum = 0;
    for(int i = 0; i < count; i++){
        sum += nums[i];
    }
    return sum;
}

double mean(const double *nums, size_t count){
    return sum(nums,count)/count;
}

double stdev(const double *nums, size_t count){
    double avg = mean(nums, count);
    double sum = 0;
    for(int i = 0; i < count; i++){
        sum += (nums[i]-avg)*(nums[i]-avg);
    }
    return sqrt(sum/count);
}

void readArr(size_t count, double *arr){
    for(int i = 0; i< count; i++){
        scanf("%lf", &arr[i]);
    }
}

int main(int argc, char *argv[]){
    size_t count;
    printf("How many numbers will you enter? ");
    scanf("%zu", &count);
    double arr[count];
    printf("Enter %zu numbers, one per line:\n", count);
    readArr(count, arr);
    printf("%lf\n",sum(arr,count));
    printf("%lf\n",mean(arr,count));
    printf("%lf\n",stdev(arr,count));
    return 0;
}