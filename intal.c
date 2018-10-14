//
//  intal.c
//  DAA_assignment
//

#include <stdio.h>
#include "intal.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MUL_DEBUG 0

typedef struct {
    unsigned char *digits;
    unsigned int digitCount;
} intal_t;

static intal_t* intal_alloc(unsigned long n){
    intal_t* intal;
    intal = malloc(sizeof(intal_t)); // memory for the struct
    intal->digits = calloc(n,sizeof(unsigned char));  //alloc memory for digits and initialise to '0'
    intal->digitCount = n;
    return intal;
}

void* intal_create(const char* str){
    if(str==NULL) return NULL;
    int i=0;
    unsigned long len = strlen(str);
    intal_t* intal = intal_alloc(len);
    int j=0;
    while(str[j]=='0'){ //To remove the initial zeroes.
      j++;
    }
    for(i=0; i < len-j; i++){
        if(str[i+j]<'0' || str[i+j]>'9'){ //if an element is not a digit then ignore the rest of the elements
            break;
        }
        intal->digits[i]=str[j+i] - '0';
    }
    intal->digitCount = i==0 ? 1 : i;
    return intal;
}

static int iszero(intal_t* intal){
    int ret=0;
    if(intal && intal->digitCount==1 && intal->digits[0]==0){
        ret = 1;
    }
    return ret;
}

static int isone(intal_t* intal){
    int ret=0;
    if(intal && intal->digitCount==1 && intal->digits[0]==1){
        ret = 1;
    }
    return ret;
}

char* intal2str(void* intal){
    if(intal==NULL) return NULL;
    intal_t* ip = (intal_t*)intal;
    char* str = malloc(sizeof(char) * (ip->digitCount+1));
    int i=0;
    for( ; i<ip->digitCount; i++){
        str[i] = ip->digits[i]+'0';
    }
    str[i]='\0';
    return str;
}

void intal_destroy(void* intal){
    if(intal!=NULL){
        intal_t* ip = (intal_t*)intal;
        free(ip->digits);
        free(ip);
    }
}

int intal_compare(void* intal1, void* intal2){
    if(intal1==NULL || intal2==NULL) return -2;
    intal_t* ip1 = (intal_t*)intal1;
    intal_t* ip2 = (intal_t*)intal2;
    if(ip1->digitCount > ip2->digitCount) return 1;
    else if(ip1->digitCount < ip2->digitCount) return -1;
    else{
        int compare = 0;
        for(int i=0; i<ip1->digitCount; i++){
            if (ip1->digits[i] != ip2->digits[i]) {
                compare = ip1->digits[i] < ip2->digits[i] ? -1 : 1;
                break;
            }
        }
        return compare;
    }
}

static intal_t* removeLeadingZeros(intal_t* ip) {
    int m=0;
    int len = ip->digitCount;
    while((m<len) && (ip->digits[m] == 0)){ //To remove the initial zeroes.
        m++;
    }
    if (m > 0) {
        intal_t* new = intal_alloc(len-m);
        memcpy(new->digits, ((ip->digits) + m), sizeof(unsigned char) * (len-m));
        intal_destroy(ip);
        ip = new;
    }
    return ip;
}

void* intal_increment(void* intal){
    if(intal==NULL) return NULL;
    intal_t* ip = (intal_t*)intal;
    int num;
    int carry = 1;
    for (int i = ip->digitCount-1; (i>=0) && (carry>0); i--) {
        num = ip->digits[i]+carry;
        carry = num/10;
        ip->digits[i] = num % 10;
    }
    if(carry!=0){
        intal_t* new_ip = intal_alloc(ip->digitCount + 1);
        new_ip->digits[0]=carry;
        memcpy((new_ip->digits)+1, ip->digits, sizeof(unsigned char) * ip->digitCount);
        intal_destroy(ip);
        ip = new_ip;
    }
    return ip;
}

void* intal_decrement(void* intal){
    if(intal==NULL) return NULL;
    intal_t* ip = (intal_t*)intal;
    if(iszero(ip) == 1) return ip;
    int borrow = 1;
    int num;
    for(int i = ip->digitCount -1; i>=0; i--){
        num=ip->digits[i] - borrow;
        if(num < 0){
             ip->digits[i] = num + 10;
            borrow = 1;
        } else{
            ip->digits[i] = num;
            borrow=0;
        }
    }
    if((ip->digitCount > 1) && (ip->digits[0]==0)){
        intal_t* new_ip = intal_alloc(ip->digitCount - 1);
        memcpy(new_ip->digits, ip->digits + 1, sizeof(unsigned char) * ip->digitCount-1);
        intal_destroy(ip);
        ip = new_ip;
    }
    return ip;
}

void* intal_add(void* intal1, void* intal2){
    if(intal1 == NULL || intal2 == NULL) return NULL;
    intal_t* ip1 = (intal_t*)intal1;
    intal_t* ip2 = (intal_t*)intal2;
    int len =  ip1->digitCount > ip2->digitCount ? ip1->digitCount : ip2->digitCount;
    intal_t* sum = intal_alloc(len);    
    int carry = 0;
    int num;
    int i,j,k;
    for (i = ip1->digitCount-1, j = ip2 ->digitCount-1 , k = len-1; i>=0 && j>=0 ; i--,j--,k--) {
        num = ip1->digits[i] + ip2->digits[j] + carry;
        carry = num/10;
        sum->digits[k] = num % 10;
    }
    if(j>=0){
        i=j;
        ip1=ip2;
    }
    for(;i>=0;i--,k--){
        num=ip1->digits[i]+carry;
        carry=num/10;
        sum->digits[k] = num % 10;
    }
    if(carry > 0){
        intal_t* new_ip = intal_alloc(len + 1);
        new_ip->digits[0]=carry;
        // memcpy
        for(int i=0; i < sum->digitCount; i++){
            new_ip->digits[i+1]=sum->digits[i];
        }
        intal_destroy(sum);
        sum = new_ip;
    }
    return sum;
 }

void* intal_diff(void* intal1, void* intal2){
    if(intal1 == NULL || intal2 == NULL) return NULL;
    intal_t* ip1 = (intal_t*)intal1;
    intal_t* ip2 = (intal_t*)intal2;
    intal_t* temp;
    int len =  ip1->digitCount > ip2->digitCount ? ip1->digitCount : ip2->digitCount;
    intal_t* diff = intal_alloc(len);
    int comp = intal_compare(ip1, ip2);
    if (comp == 0) {
        return intal_alloc(1);
    } else if (comp == -1){
        temp = ip1;
        ip1 = ip2;
        ip2 = temp;
    }
    
    int i,j,k;
    int borrow = 0, result;
    for(i=ip1->digitCount-1, j=ip2->digitCount-1, k=len-1; i>=0 && j>=0; i--, j--, k--){
        result = ip1->digits[i] - borrow - ip2->digits[j];
        if(result < 0){
            borrow = 1;
            result += 10;
        } else {
            borrow = 0;
        }
        diff->digits[k] = result;
    }
    if(j>=0){
        i=j;
        ip1=ip2;
    }
    for(;i>=0;i--,k--){
        result = ip1->digits[i]-borrow;;
        if (result < 0) {
            result += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        diff->digits[k] = result;
    }
    diff = removeLeadingZeros(diff);
    return diff;
}


// get x / 10^n (quotient when divided by 10^n, nothing but left most 'n' digits)
// get x * 10^(n-length) (pad n-length zeros on the right)
static intal_t* get_leftmost(intal_t* ip, int m){
    if(m <= 0 || iszero(ip)==1){
        return intal_alloc(1);
    } else{
        intal_t* ret = intal_alloc(m);
        if(m > ip->digitCount) m = ip->digitCount;
        memcpy(ret->digits, ip->digits, sizeof(unsigned char) * m);
        return ret;
    }
}

// get x % 10^m (right most m digits)
static intal_t* get_rightmost(intal_t* ip, int m){
    if(m <= 0 || iszero(ip)==1){
        return intal_alloc(1);
    } else {
        intal_t* ret = intal_alloc(m);
        if(m > ip->digitCount) m = ip->digitCount;
        memcpy(ret->digits, ((ip->digits) + (ip->digitCount - m)), sizeof(unsigned char) * m);
        return ret;
    }
}

//https://brilliant.org/wiki/karatsuba-algorithm/#karatsuba-algorithm
static intal_t* karatsuba(intal_t* ip1, intal_t* ip2){
    char *xs, *ys, *rs;
    intal_t* result;
    xs = intal2str(ip1);
    ys = intal2str(ip2);
    
    if (MUL_DEBUG) {
        printf ("x=%s, y=%s\n", xs, ys);
    }
    
    if(iszero(ip1)==1 || iszero(ip2)==1) result = intal_alloc(1);
    else if(isone(ip1)==1) result = intal_create(intal2str(ip2));
    else if(isone(ip2)==1) result = intal_create(intal2str(ip1));
    else if ((ip1->digitCount == 1) && (ip2->digitCount == 1)) {
        int temp = ip1->digits[0] * ip2->digits[0];
        if (temp > 9) {
            result = intal_alloc(2);
            result->digits[0] = temp / 10;
            result->digits[1] = temp % 10;
        } else {
            result = intal_alloc(1);
            result->digits[0] = temp;
        }
    }
    else {
        int len =  ip1->digitCount > ip2->digitCount ? ip1->digitCount : ip2->digitCount;
        int m = (len/2) + (len%2); //ceil(float(n)/2)
        
        intal_t* xh = get_leftmost(ip1,ip1->digitCount - m); //floor(x / 10**m)
        intal_t* xl = get_rightmost(ip1,m); //x % (10**m)
        intal_t* yh = get_leftmost(ip2,ip2->digitCount - m);
        intal_t* yl = get_rightmost(ip2,m);
        
        intal_t* a = karatsuba(xh, yh);
        intal_t* d = karatsuba(xl, yl);
        intal_t* b = intal_add(xh, xl); //x_H + x_L
        intal_t* c = intal_add(yh, yl); // y_H + y_L
        intal_t* k = intal_add(a, d); //a+d
        intal_t* l = karatsuba(b, c); //karatsuba(x_H + x_L, y_H + y_L)
        intal_t* e = intal_diff(l, k); //karatsuba(x_H + x_L, y_H + y_L) -a -d
        
        intal_t* p = get_leftmost(a, a->digitCount + 2*m); //a*(10**(m*2))
        intal_t* q = get_leftmost(e, e->digitCount + m); //e*(10**m)
        intal_t* r = intal_add(p, q); //a*(10**(m*2)) + e*(10**m)
        result = intal_add(r, d);
        
        intal_destroy(xh);
        intal_destroy(xl);
        intal_destroy(yh);
        intal_destroy(yl);
        intal_destroy(a);
        intal_destroy(d);
        intal_destroy(b);
        intal_destroy(c);
        intal_destroy(e);
        intal_destroy(p);
        intal_destroy(q);
        intal_destroy(r);
        intal_destroy(k);
        intal_destroy(l);
    }
    rs = intal2str(result);
    if (MUL_DEBUG) {
        printf("x=%s, y=%s, result=%s\n", xs, ys, rs);
    }
    free(xs);
    free(ys);
    free(rs);
    return result;
}

void* intal_multiply(void* intal1, void* intal2) {
    if(intal1==NULL || intal2==NULL) return NULL;
    intal_t* ip1 = (intal_t*)intal1;
    intal_t* ip2 = (intal_t*)intal2;
    return karatsuba(ip1,ip2);
}

void* intal_divide(void* intal1, void* intal2){
    if(intal1==NULL || intal2==NULL) return NULL;
    intal_t* ip1 = (intal_t*)intal1;
    intal_t* ip2 = (intal_t*)intal2;
    if(iszero(ip2)) return NULL;
    else if(iszero(ip1) || intal_compare(ip1,ip2) == -1) return intal_alloc(1);
    else{
        intal_t* count = intal_alloc(1);
        intal_t* numerator = ip1;
        intal_t* temp = NULL;
        
        for(; intal_compare(numerator, ip2) > 0; ){
            count = intal_increment(count);
            numerator = intal_diff(numerator, ip2);
            if(temp){
                intal_destroy(temp);
            }
            temp = numerator;
        }
        return count;
    }
}

void* intal_pow(void* intal1, void* intal2){
    if(intal1==NULL || intal2==NULL) return NULL;
    intal_t* ip1 = (intal_t*)intal1;
    intal_t* ip2 = (intal_t*)intal2;
    if(iszero(ip1)) return intal_alloc(1);
    else if(iszero(ip2) || isone(ip1)) return intal_create("1");
    else{
        intal_t* tmp = NULL;
        intal_t* exp = intal_alloc(1);
        exp->digits[0] = 1;
        intal_t* count = intal_alloc(ip2->digitCount);
        memcpy(count->digits, ip2->digits, sizeof(unsigned char) * ip2->digitCount);
        for(;!iszero(count);count=intal_decrement(count)){
            exp = intal_multiply(exp, ip1);
            if (tmp) {
                intal_destroy(tmp);
            }
            tmp = exp;
        }
        intal_destroy(count);
        return exp;
    }
}
