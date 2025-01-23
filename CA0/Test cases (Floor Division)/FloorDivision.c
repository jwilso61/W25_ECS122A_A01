#include <stdio.h>

int main(){
    unsigned long long a = 0;
    unsigned long long b = 0;

    scanf("%llu %llu", &a, &b);
    
    if (b == 0) {printf("division by zero!!\n"); } 
    else { printf("%llu\n", a / b); }
    
    return 0;
}