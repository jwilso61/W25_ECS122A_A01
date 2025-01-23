#include <stdio.h>

int main(){
    
    char out[50] = "";

    while(scanf("%s", out) != EOF)
    {
        printf("Hello %s!\n", out);
    }
    return 0;
}
