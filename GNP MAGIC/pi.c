#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>

void progressbar(__uint32_t num, __uint32_t final){
    __uint32_t percent = num*100/final;
    fprintf(stderr,"\r[");
    for(int i = 0; i < percent; i++){
        fprintf(stderr,"=");
    }
    fprintf(stderr,">");
    for(int i = percent; i < 100; i++){
        fprintf(stderr,"-");
    }
    fprintf(stderr, "](%d/%d)", num, final);
}

void pi(__uint32_t cycles){
    __uint32_t prec = 1024*1024*10;
    //Calculating the constant
        mpf_t mconst;
        mpf_init2(mconst, prec);
        mpf_set_ui(mconst, 10005);
        mpf_sqrt(mconst, mconst);
        mpf_mul_ui(mconst, mconst, 426880);
    //Generating Sigma
        mpf_t sum;
        mpf_init2(sum, prec);
        mpf_set_ui(sum, 0);
        mpz_t tmp;
        mpf_t term;
        mpf_t sterm1;
        mpf_t sterm2;
        mpz_init2(tmp,prec);
        mpf_init2(term, prec);
        mpf_init2(sterm1, prec);
        mpf_init2(sterm2, prec);
        for(__uint32_t i = 0; i < cycles; i++){
            mpz_fac_ui(tmp, 6*i);
            mpf_set_z(term, tmp);
            mpf_set_ui(sterm1, i);
            mpf_mul_ui(sterm1, sterm1, 545140134);
            mpf_add_ui(sterm1, sterm1, 13591409);
            mpf_mul(term, term, sterm1);
            mpz_fac_ui(tmp, 3*i);
            mpf_set_z(sterm1, tmp);
            mpz_fac_ui(tmp, i);
            mpf_set_z(sterm2, tmp);
            mpf_pow_ui(sterm2, sterm2, 3);
            mpf_mul(sterm1, sterm1, sterm2);
            mpf_set_si(sterm2, -262537412640768000);
            mpf_pow_ui(sterm2, sterm2, i);
            mpf_mul(sterm1, sterm1, sterm2);
            mpf_div(term, term, sterm1);
            mpf_add(sum, sum, term);
            if(i%100 == 0){
                progressbar(i, cycles);
            }
        }
        fprintf(stderr,"\n");
    //Calculating pi
        mpf_t pie;
        mpf_init2(pie, prec);
        mpf_div(pie, mconst, sum);
        gmp_printf("%.*Ff\n", 1000000, pie);
}

int main(int argc, char** argv){
    pi(100000);
}