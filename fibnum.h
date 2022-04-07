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
#define DETECT_OVERFLOW(x, y) ((x) + (y) < MAX(x, y) ? 1 : 0)
#define ULL_MAX_STR "18446744073709551616"

typedef struct fibnum{
    unsigned long long *num;
    size_t size;
}fib_t;


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
void fib_lsh(fib_t *, unsigned int);
void fib_add(fib_t *, fib_t *, fib_t *);

/**
 * @brief 
 * fib(100)
 *    10           1
 * | xxx | 18446744073709551616|
 * 10* XXX + 1
 * 
 * 18446744073709551616 * XXX + 18446744073709551616
 */