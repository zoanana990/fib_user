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

/* Source: CSAPP Chapter 2 Example 21 */
#define DETECT_OVERFLOW(x, y, carry) ((x) + (y) + (carry) < MAX(x, y) ? 1 : 0)

#define ULL_MAX_STR "18446744073709551616"
#define ULL_MAX 18446744073709551615

#define NEED_SIZE(x) (ROUND_UP_TO_64(x) >> 6) 

typedef struct fibnum{
    unsigned long long *num;
    size_t size;
}fib_t;

#define print_each_index(F) \
     for(int i=0; i<F->size; i++) \
        printf("num[%d] = %llu\n", i, F->num[i]) \
     

fib_t *fib_init(size_t);
void fib_free(fib_t *);
void fib_resize(fib_t *, size_t);
char *fib_itos(unsigned long long);
char *fib_stradd(char *, char *);
char *fib_strmul(char *, char *);
void fib_strncpy(char *, char *, size_t);
size_t fib_strlen(const char *);
char *fib_print(fib_t *);
void fib_assign(fib_t *, fib_t *);
unsigned int gcc_clz(unsigned long long);
unsigned int fib_clz(fib_t *);
unsigned int fib_msb(fib_t *);
int fib_cmp(fib_t *, fib_t *);
void fib_idxlsh(fib_t *, const unsigned int);
void fib_numlsh(fib_t *, unsigned int);
void fib_lsh(fib_t *, unsigned int, fib_t *);
void fib_add(fib_t *, fib_t *, fib_t *);
int fib_bitisone(fib_t *, size_t);
void fib_zero(fib_t *);
void fib_mul(fib_t *, fib_t *, fib_t *);
void fibnum_iter(unsigned int);
