#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>

void fib(size_t digits, mpz_t res){
    size_t dig = 0;
    mpz_t newnum;
    mpz_init(newnum);
    mpz_t oldnum;
    mpz_init(oldnum);
    mpz_set_ui(oldnum, 1);
    mpz_set_ui(newnum, 1);
    while(dig < digits){
        mpz_add(res,oldnum,newnum);
        char* mpzstr = malloc(mpz_sizeinbase(res,10)+1);
        mpz_get_str(mpzstr, 10, res);
        dig = strlen(mpzstr);
        free(mpzstr);
        mpz_set(oldnum,newnum);
        mpz_set(newnum,res);
    }
}

int main(int argc, char **argv){
    mpz_t val;
    mpz_init(val);
    sfib(10,val);
    gmp_printf("%Zd\n", val); 
    fib(10,val);
    gmp_printf("%Zd\n", val);
    return 0;
}