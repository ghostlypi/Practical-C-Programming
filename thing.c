#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(int n)
{
    if (n % 2 == 0)
    {
        return false;
    }

    for (int divisor = 3; divisor < n / 2; divisor += 2)
    {
        if (n % divisor == 0)
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]){
    if(argc > 1){
        int n = atoi(argv[1]);
        if (is_prime(n))
        {
            puts("prime");
        }
        else
        {
            puts("composite");
        }
    }else{
        puts("Enter a Number");
    }

    return 0;
}