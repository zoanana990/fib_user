#include "fibnum.h"

/**
 * @brief Structure Definition 
 */

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

size_t fib_strlen(const char *str){
    /**
     * @brief Copy from GLIBC strlen
     * 
     */

    const char *char_ptr;
    const unsigned long int *longword_ptr;
    unsigned long int longword, himagic, lomagic;

    for (char_ptr = str; ((unsigned long int) char_ptr
                & (sizeof (longword) - 1)) != 0;
        ++char_ptr)
        if (*char_ptr == '\0')
            return char_ptr - str;

    longword_ptr = (unsigned long int *) char_ptr;

    himagic = 0x80808080L;
    lomagic = 0x01010101L;
    if (sizeof (longword) > 4){
        himagic = ((himagic << 16) << 16) | himagic;
        lomagic = ((lomagic << 16) << 16) | lomagic;
    }

    for (;;){
        longword = *longword_ptr++;

        if (((longword - lomagic) & ~longword & himagic) != 0){
            const char *cp = (const char *) (longword_ptr - 1);

            if (cp[0] == 0)
                return cp - str;
            if (cp[1] == 0)
                return cp - str + 1;
            if (cp[2] == 0)
                return cp - str + 2;
            if (cp[3] == 0)
                return cp - str + 3;
            if (sizeof (longword) > 4)
            {
                if (cp[4] == 0)
                    return cp - str + 4;
                if (cp[5] == 0)
                    return cp - str + 5;
                if (cp[6] == 0)
                    return cp - str + 6;
                if (cp[7] == 0)
                    return cp - str + 7;
            }
        }
    }
}

/* Fibonacci String Reverse */
void fib_strrev(char* s, int sSize){

     for(int i=0;i<sSize/2;i++)
     {
         char c = s[i];
         s[i] = s[sSize-1-i];
         s[sSize-1-i] = c;
     }
}

void fib_strncpy(char *dst, char *src, size_t n)
{
    // copy the string
    for (int i = 0; i < n; i++)
        *(dst + i) = *(src + i);

    *(dst + n) = '\0';
}

char *fib_itos(unsigned long long num){
    
    size_t s = 20;
    
    char *res = malloc(s);
    
    int j = 0;
    
    while(num != 0 && j < s){
        res[j] = num % 10 + '0';
        num /= 10, j++;
    }
    res[j] = '\0';

    s = fib_strlen(res);

    fib_strrev(res, s);

    res = realloc(res, s + 1);
    res[s] = '\0';
    
    return res;
}

/* NEED FREE */
char *fib_stradd(char *num1, char *num2){
    
    unsigned int l1 = fib_strlen(num1), l2 = fib_strlen(num2);
    
    if(fib_strlen(num1) < fib_strlen(num2)){
        return fib_stradd(num2, num1);
    }

    int carry = 0;
    int l = MAX(l1, l2);
    char *res = malloc(sizeof(char) * l + 1);

    int i = l1 - 1;
    for(int j = l2 - 1; i >= 0 && j >= 0; i--, j--){
        int sum = num1[i] - '0' + num2[j] - '0' + carry;
        res[i] = sum % 10 + '0';
        carry = sum / 10;
    }

    for (; i >= 0; i--) {
        int sum = num1[i] - '0' + carry;
        res[i] = sum % 10 + '0';
        carry = sum / 10;
    }

    if(carry){
        int k = l + 1;
        res = realloc(res, k + 1);
        res[k] = '\0';
        for(int i = k - 1; i > 0; i--)
            res[i] = res[i - 1];
        res[0] = '1';
    }else
        res[l1] = '\0';

    return res;
}

/* NEED FREE */
char *fib_strmul(char *num1, char *num2){
    
    size_t len1 = fib_strlen(num1), len2 = fib_strlen(num2), len = len1+len2;
    
    short *arr = malloc(sizeof(short) * len);
    
    for(int i=0; i<len; i++)
        arr[i] = 0;

    for(int i=len1-1; i >= 0; i--)
        for(int j=len2-1; j >= 0; j--)
            arr[i+j+1] += (num1[i]-'0') * (num2[j]-'0');
    
    for(int i=len-1; i > 0; i--){
        arr[i-1] += arr[i]/10;
        arr[i] %= 10;
    }
    
    char *s = malloc(sizeof(char)*(len+1));
    
    int index = 0, i = 0;
    
    if(arr[i]==0) i++; 
    
    while(i < len)
        s[index++] = arr[i++]+'0';
    
    s[index] = '\0';

    return s;
}

/* NEED FREE */
char *fib_print(fib_t *F){

    char *temp[F->size];
    char *res = malloc(256);
    res[0] = '0', res[1] = '\0';
    for(int i = 0; i< F->size; i++){
        temp[i] = fib_itos(F->num[i]);
        for(int j = 0; j < i; j++)
            temp[i] = fib_strmul(temp[i], ULL_MAX_STR); 
        res = fib_stradd(temp[i], res);
    }

    // check redundant zeroes
    // unsigned int n = fib_strlen(res), index = 0;
    
    // for(int i = 0; i < n; i++)
    //     if(res[i] == '0')
    //         index++;

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

/** 
 * @brief Find the leading zero by shifting method
 * Reference: https://hackmd.io/@sysprog/c-numerics
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

unsigned int fib_msi(fib_t *F){

    unsigned int count = 0;
    for(int i=F->size - 1; i>=0; i--){
        if(F->num[i] == 0)
            count++;
        else break;
    }
    return F->size - count == 0 ? 1 : F->size - count;
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

/* Shift indexes */
void fib_idxlsh(fib_t *F, const unsigned int idx){

    fib_resize(F, F->size + idx);

    for(int i = F->size - 1; i >= idx; i--)
        F->num[i] = F->num[i-idx];

    for(int i = 0; i < idx; i++)
        F->num[i] = 0; 

}

/* Shift at most 63 bit */
void fib_numlsh(fib_t *F, unsigned int bit){

    for(int i = F->size - 1; i > 0; i--)
        F->num[i] = F->num[i] << bit | F->num[i - 1] >> (64 - bit);

    F->num[0] <<= bit;
}

/* left shift */
void fib_lsh(fib_t *F, unsigned int bit, fib_t *dst){
    
    fib_assign(F, dst);

    /**
     * @brief If we need to shift 64 bit, 129 bit...
     * we can first shift >> 63, then shift 1 bit
     */

    int count = 0, i;

    size_t msb = fib_msb(F);

    if(NEED_SIZE(msb) < NEED_SIZE(msb + bit))
        fib_resize(dst, NEED_SIZE(msb + bit));

    for(i = bit; i > 63; i >>= 6)
        count++;
        
    if(count)
        fib_idxlsh(dst, i);
    
    bit = bit - (count << 6);

    if(bit)
        fib_numlsh(dst, bit);
}

/* F = prev1 + prev2 */
void fib_add(fib_t *prev1, fib_t *prev2, fib_t *F){

    int m1 = fib_msb(prev1), m2 = fib_msb(prev2);
    int msb = MAX(m1, m2);
    int size = MAX(NEED_SIZE(m1), NEED_SIZE(m2));

    if(NEED_SIZE(msb) < NEED_SIZE(msb + 1)){
        fib_resize(F, NEED_SIZE(msb + 1));
    }else if(size > F->size)
        fib_resize(F, size);

    unsigned int carry = 0;

    for(int i=0; i<F->size; i++){
        
        unsigned long long p1 = (i < prev1->size) ? prev1->num[i] : 0;
        unsigned long long p2 = (i < prev2->size) ? prev2->num[i] : 0;
        unsigned long long sum = p1 + p2 + carry;
        F->num[i] = sum;
        carry = DETECT_OVERFLOW(p1, p2, carry); 
    }

    if(carry){
        fib_resize(F, F->size + 1);
        F->num[F->size - 1] = 1;
    }        
}

/* F = prev1 - prev2 */
void fib_sub(fib_t *Big, fib_t *Small, fib_t *F){
    
    /* if Small > Big, Swap */
    if(fib_cmp(Big, Small) == -1){
        fib_sub(Small, Big, F);
        return;
    }

    int sub_size = MAX(Big->size, Small->size);
    fib_resize(F, sub_size);

    long long int carry = 0;
    for (int i = 0; i < F->size; i++) {
        unsigned int B = (i < Big->size) ? Big->num[i] : 0;
        unsigned int S = (i < Small->size) ? Small->num[i] : 0;

        if(B < S || B < carry){
            /* get carry to do */
            F->num[i] = ULL_MAX - S + B - carry + 1;
            carry = 1;
        }else{
            F->num[i] = B - S - carry;
            carry = 0;
        }
    }

    /* F resize */
    size_t n = fib_msi(F);
    fib_resize(F, n);
}

/* This function is to test the bit is one */
int fib_bitisone(fib_t *prev2, size_t bit){
    
    int count = 0, mask = bit & 0x3F;
    
    while(bit > 63){
        /* check indexes */
        bit = bit >> 6;
        count++; 
    }

    mask = 1 << mask;

    /* check < 64 bit */
    return (prev2->num[count] & mask) ? 1 : 0;
}

void fib_zero(fib_t *F){
    F->size = 1;
    F->num = realloc(F->num, sizeof(unsigned long long) * 1);
    F->num[0] = 0;
}

/* F = prev1 * prev2 */
void fib_mul(fib_t *prev1, fib_t *prev2, fib_t *F){

    /**
     * @brief Multiple is left shift and add
     * @example, there are 1283 * 4567 
     * 4567 in binary is 
     * 0b0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0000_0001_0001_1101_0111
     * and the MSB(Most Significant Bit) is 12
     * the digit in one is 12, 8, 7, 6, 4, 2, 1, 0 (Here is a function)
     * Thus, 1283 * 4567 = (1283 << 12) + (1283 << 8) + (1283 << 7) + (1283 << 6)...
     */

    size_t m2 = fib_msb(prev2);
    


    fib_zero(F);
    fib_t *temp = fib_init(1);
    // printf("MMM\n");
    for(int i = 0; i <= m2; i++){
        // printf("M: %d\n", fib_bitisone(prev2, i));
        if(fib_bitisone(prev2, i)){           
            /* prev1 shift left and add to F */
            fib_lsh(prev1, i, temp);
            fib_add(F, temp, F);
        }
    }
    fib_free(temp);
}

/**
 * @brief Method, iteration, fast-doubling 
 */

void fibnum_iter(unsigned int n){
    
    fib_t *prev2 = fib_init(1);
    fib_t *prev1 = fib_init(1);
    prev1->num[0] = 1;
    fib_t *F = fib_init(1);

    for(int i=2; i<=n; i++){
        fib_add(prev1, prev2, F);
        fib_assign(prev1, prev2);
        fib_assign(F, prev1);
    }

    char *res = fib_print(F);
    free(res);
    return;
}

char* fibnum_fast_doubling(unsigned int n){
    
    /**
     * @brief Fast Doubling Method
     * F(2k)     = F(k) * (2F(k+1) - F(k))
     * F(2k + 1) = F(k) * F(k) + F(k+1) * F(k+1)
     */

    fib_t *f1 = fib_init(1); // F(k)
    fib_t *f2 = fib_init(1); // F(k + 1)
    f1->num[0] = 1;
    f2->num[0] = 1;
    fib_t *k1 = fib_init(1); // F(2k)
    fib_t *k2 = fib_init(1); // F(2k + 1)

    int msb = 63 - gcc_clz(10);


    /* Fast Doubling */
    for(unsigned long long i = 1UL << msb; i > 0; i>>=1){
        fib_t *t1 = fib_init(1), *f11 = fib_init(1), *f22 = fib_init(1);

        /* F(2k) = F(k) * [ 2 * F(k+1) ??? F(k) ] */
        fib_assign(f2, k1);  // k1 = f2
        fib_lsh(k1, 1, k1);  // k1 = k1 * 2
        fib_sub(k1, f1, k1); // k1 = k1 - f1
        fib_mul(k1, f1, t1); // k1 = f1 * k1
        fib_assign(t1, k1);

        /* F(2k+1) = F(k)^2 + F(k+1)^2 */
        fib_mul(f1, f1, f11); // f1 = f1 * f1
        fib_mul(f2, f2, f22); // f2 = f2 * f2
        fib_add(f11, f22, k2); // k2 = f2 + k2    
        fib_free(t1), fib_free(f11), fib_free(f22);

        if (n & i) {
            fib_assign(k2, f1);
            fib_assign(k1, f2);
            fib_add(f2, k2, f2);
        } else {
            fib_assign(k1, f1);
            fib_assign(k2, f2);
        }
    }

    char *s = fib_print(k1);

    fib_free(k1);
    fib_free(k2);
    fib_free(f1);
    fib_free(f2);

    return s;
}

#include <time.h>
int main(){
    
    for(int i = 0; i <=10000; i++){
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);
        char* s  = fibnum_fast_doubling(999);
        clock_gettime(CLOCK_MONOTONIC, &end);
        long long ut = (long long)(end.tv_sec * 1e9 + end.tv_nsec)
                 - (start.tv_sec * 1e9 + start.tv_nsec);
        printf("%ld\n", ut);
        free(s);
    }
    
    return 0;
}