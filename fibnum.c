/**
 * @file fibnum.c
 * @author zoanana990
 * @brief 
 * @version 0.1
 * @date 2022-03-31
 * 
 * @copyright Copyright (c) 2022
 **/

#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* Source: https://hackmd.io/@zoanana990/linux2022-quiz3 */
#define ROUND_UP_TO_64(x) (((x) + 0x3F) & (~(0x3F)))

#define DETECT_OVERFLOW(x, y) ((x) + (y) < MAX(x, y) ? 1 : 0)

/**
 * @brief Structure Definition 
 */

typedef struct fibnum{
    unsigned long long *num;
    size_t size;
}fib_t;

fib_t *fib_init(size_t S){
    
    /* memory allocate */
    fib_t *F = malloc(sizeof(fib_t));
    F->num = malloc(sizeof(unsigned long long) * S);
    F->size = S;

    /* F->num initialization */
    for(int i=0; i<F->size; i++)
        F->num[i] = 0;
    
    return F;
}

void fib_free(fib_t *F){
    
    /* Boundary Condition */
    if(!F) return;

    free(F->num);
    free(F);
}

void fib_resize(fib_t *F, size_t S){

    if(!F || F->size == S) return;

    F->num = realloc(F->num, sizeof(unsigned long long) * S);

    /* if S is bigger than size, initialize the realloc zone */
    if(F->size < S)
        for(int i = F->size; i < S; i++)
            F->num[i] = 0;

    F->size = S;
}


char *fib_print(fib_t *F){

    int length = 3 * sizeof(unsigned long long) * F->size;
    char *res = malloc(sizeof(char) * length);

    /* let the interger to string */
    for(int i = 0; i < F->size; i++){

    }

    return res;
}

void fib_assign(fib_t *src, fib_t *dst){
    
    dst->size = src->size;
    fib_resize(dst, dst->size);
    
    for(int i = 0; i < dst->size; i++)
        dst->num[i] = src->num[i];
}

/**
 * @brief Arithmetic Operation, for example, shift, add,
 * substract, multiply...
 */

/** Find the leading zero by shifting method
 *  Reference: https://hackmd.io/@sysprog/c-numerics
 */
unsigned int gcc_clz(unsigned long long x){
    
    /* Boundary Condition */
    if (x == 0) return 64;

    int n = 1;
    if ((x >> 32) == 0) { n += 32; x <<= 32; }
    if ((x >> 48) == 0) { n += 16; x <<= 16; }
    if ((x >> 56) == 0) { n +=  8; x <<=  8; }
    if ((x >> 60) == 0) { n +=  4; x <<=  4; }
    if ((x >> 62) == 0) { n +=  2; x <<=  2; }

    n = n - (x >> 63);
    
    return n;
}

unsigned int fib_clz(fib_t *F){
    return gcc_clz(F->num[F->size-1]) + 64 * (F->size - 1);
}

unsigned int fib_msb(fib_t *F){
    return F->size * 64 - 1 - gcc_clz(F->num[F->size-1]);
}

/* Compare two Fibonaccir Number */
int fib_cmp(fib_t *prev1, fib_t *prev2){
    
    /**
     * @brief 
     * There are three situation
     * 1. prev1->size < prev2->size
     * 2. prev1->size > prev2->size
     * 3. prev1->size = prev2->size
     * 
     * @return 
     * prev1 is bigger: return 1
     * prev2 is bigger: return -1
     * equal: return 0
     */
    
    if(prev1->size > prev2->size)
        return 1;
    else if(prev1->size < prev2->size)
        return -1;
    else{
        for(int i = prev1->size; i >=0; i--){
            if(prev1->num[i] > prev2->num[i])
                return 1;
            else if(prev1->num[i] < prev2->num[i])
                return -1;
        }
        return 0;
    }
    
}


/* left shift */
void fib_lsh(fib_t *F, unsigned int bit){
    
    /* shift 0 ~ 63 bit */
    bit = bit & 0x3F;

    unsigned int msb = fib_msb(F);

    if(ROUND_UP_TO_64(msb) < ROUND_UP_TO_64(msb + bit))
        fib_resize(F, F->size + 1);
        
    /* Source: https://github.com/KYG-yaya573142/fibdrv/blob/master/bn_kernel.c */
    for(int i = F->size - 1; i > 0; i--)
        F->num[i] = F->num[i] << bit | F->num[i - 1] >> (63 - bit);
    
    F->num[0] <<= bit;
}

/* right shift */
void fib_rsh(fib_t *src, unsigned int bit){
    
}


/* F = prev1 + prev2 */
void fib_add(fib_t *prev1, fib_t *prev2, fib_t *F){
    
    /**
     * @brief There are two situations in fib_add
     * 1. if prev1 = prev2 -> fib_lsf(prev1, 1)
     * 2. need to resize
     */

    // if prev1 == prev2, left shift one bit
    if(!fib_cmp(prev1, prev2)){
        
        fib_lsh(prev1, 1);
        fib_assign(prev1, F); 
        return;

    }

    // else is prev1 > prev2
    int msb = MAX(fib_msb(prev1), fib_msb(prev2));

    unsigned int carry = 0;

    for(int i=0; i<F->size; i++){
        
        unsigned int p1 = (i < prev1->size) ? prev1->num[i] : 0;
        unsigned int p2 = (i < prev2->size) ? prev2->num[i] : 0;
        unsigned long long sum = p1 + p2 + carry;
        F->num[i] = p1 + p2;
        carry = DETECT_OVERFLOW(p1, p2); 
        printf("carry = %d\n", carry);
    }

    if(carry){
        printf("ADD\n");
        fib_resize(F, F->size + 1);
        F->num[F->size - 1] = 1;
    }
}

/* F = prev1 - prev2 */
void fib_sub(fib_t *prev1, fib_t *prev2, fib_t *F){

}

/* F = prev1 * prev2 */
void fib_mul(fib_t *prev1, fib_t *prev2, fib_t *F){

}

/**
 * @brief Method, iteration, fast-doubling 
 */

int main(){
    fib_t *F1 = fib_init(1);
    fib_t *F2 = fib_init(1);
    fib_t *F = fib_init(1);

    F1->num[0] = 0xFFFFFFFFFFFFFFFF;
    F2->num[0] = 1;
    F->num[0] = 0;

    fib_add(F1, F2, F);
    
    printf("F->size = %d, F->num[1] = %llu, F->num[0] = %llu\n", F->size, F->num[1], F->num[0]);

    fib_free(F2);
    fib_free(F1);
    fib_free(F);
    return 0;
}