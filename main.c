#define ABCD
#ifndef ABCD
#include <stdio.h>
#include "intal.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(){
    char str1[100] = "268435455";
    char str2[100] = "268435457";
    char str3[100] = "PESU";
    char *str4;
    void *intal1;
    void *intal2;
    void *intal3;
    void *sum;
    void *diff;
    void *product;
    void *quotient;
    void *quotient2;
    void *exp;
    
    intal1 = intal_create(str1); //4999
    
    intal2 = intal_create(str2); //2001
    
    strcpy(str3, "PESU");
    intal3 = intal_create(str3); //PESU
    
    str4 = intal2str(intal1);
    printf("First intal: %s\n", str4); //4999
    free(str4);
    
    str4 = intal2str(intal2);
    printf("Second intal: %s\n", str4); //2001
    free(str4);

    str4 = intal2str(intal3);
    printf("Third intal: %s\n", str4); //0
    free(str4);
    
    intal3 = intal_create("xyz");
    
    printf("Max of two intals: %s\n",(intal_compare(intal1, intal2) > 0) ? intal2str(intal1) : intal2str(intal2));
    
    intal1 = intal_increment(intal1);
    str4 = intal2str(intal1);
    printf("First intal after increment : %s\n", str4);
    free(str4);
    
    intal3 = intal_increment(intal3);
    str4 = intal2str(intal3);
    printf("third intal after increment : %s\n", str4);
    
    intal2 = intal_decrement(intal2);
    str4 = intal2str(intal2);
    printf("second intal after decrement : %s\n", str4);
    free(str4);
    
    intal3 = intal_decrement(intal3);
    str4 = intal2str(intal3);
    printf("Third intal after decrement : %s\n", str4);
    free(str4);
    
    sum = intal_add(intal1, intal2); //7000
    printf("Sum: %s\n", intal2str(sum));
    
    diff = intal_diff(intal1, intal2); //0
    printf("diff: %s\n", intal2str(diff));
    
    product = intal_multiply(intal1, intal2);
    printf("product: %s\n", intal2str(product));
    
    intal_destroy(intal1);
    intal_destroy(intal2);
    intal_destroy(intal3);
    
    /*unsigned long long ull1 = 0x123456789;
    unsigned long long ull2 = 0x123456789;
    char s[1000];
    char *is1, *is2, *is3;
    for (; ull2 > 0; ) {
        sprintf(s, "%llu", ull1);
        intal1 = intal_create(s);
        is1 = intal2str(intal1);
        
        sprintf(s, "%llu", ull2);
        intal2 = intal_create(s);
        is2 = intal2str(intal2);
        
        intal3 = intal_diff(intal1, intal2);
        is3 = intal2str(intal3);
        
        quotient = intal_divide(intal1, intal2);
        printf("div: %s\n",intal2str(quotient));
        
        sprintf(s, "%llu", (ull1 - ull2));
        //
        if ((strcmp(is3, s)) == 0) {
            //printf(" PASS\n");
        } else {
            printf ("FAILED %s, %s, %s, %s", is1, is2, is3, s);
            break;
        }
        intal_destroy(intal1);
        intal_destroy(intal2);
        intal_destroy(intal3);
        free(is1);
        free(is2);
        free(is3);
        ull1 += ull2;
        ull2 -= 0x1234;
    }*/
        
    return 0;
}
#else
//A sample client for intal.h

//Expected output for this client:
/*
 First intal: 4999
 Second intal: 2001
 Two intals after increment and decrement:
 5000
 2000
 Max of two intals: 5000
 Sum: 7000
 Diff: 3000
 Product: 10000000
 Quotient: 2
 5000 ^ 2: 25000000
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intal.h"

int main(int argc, char const *argv[]) {
    char str1[100] = "4999";
    char str2[100] = "2001";
    char str3[100] = "PESU";
    char *str4;
    void *intal1;
    void *intal2;
    void *intal3;
    void *sum;
    void *diff;
    void *product;
    void *quotient;
    void *quotient2;
    void *exp;
    
    intal1 = intal_create(str1); //4999
    intal2 = intal_create(str2); //2001
    strcpy(str3, "PESU");
    intal3 = intal_create(str3);//0
    
    str4 = intal2str(intal1);
    printf("First intal: %s\n", str4); //4999
    free(str4);
    str4 = intal2str(intal2);
    printf("Second intal: %s\n", str4); //2001
    free(str4);
    str4 = intal2str(intal3);
    printf("Third intal: %s\n", intal2str(intal3)); //0
    free(str4);
    
    intal1 = intal_increment(intal1); //5000
    intal2 = intal_decrement(intal2); //2000
    intal3 = intal_decrement(intal3); //0
    
    printf("Intals after increment and decrement:\n");
    str4 = intal2str(intal1);
    printf("%s\n", str4); //5000
    free(str4);
    str4 = intal2str(intal2);
    printf("%s\n", str4); //2000
    free(str4);
    str4 = intal2str(intal3);
    printf("%s\n", str4); //0
    free(str4);
    
    printf("Max of two intals: %s\n", //5000
           (intal_compare(intal1, intal2) > 0) ? intal2str(intal1) : intal2str(intal2));
    
    sum = intal_add(intal1, intal2); //7000
    printf("Sum: %s\n", intal2str(sum));
    
    diff = intal_diff(intal1, intal2); //3000
    printf("Diff: %s\n", intal2str(diff));
    
    product = intal_multiply(intal1, intal2); //10000000
    printf("Product: %s\n", intal2str(product));
    
    quotient = intal_divide(intal1, intal2); //2
    printf("Quotient: %s\n", intal2str(quotient));
    
    exp = intal_pow(intal1, quotient); //5000^2 = 25000000
    printf("%s ^ %s: %s\n", intal2str(intal1), intal2str(quotient), intal2str(exp));
    
    quotient2 = intal_divide(intal1, intal3); // divide-by-zero, so NaN
    if(!quotient2) printf("Divide-by-zero\n");
    
    //Make sure you destroy all the intals created.
    intal_destroy(sum);
    intal_destroy(diff);
    intal_destroy(product);
    intal_destroy(quotient);
    intal_destroy(quotient2);
    intal_destroy(exp);
    intal_destroy(intal1);
    intal_destroy(intal2);
    return 0;
}
#endif
