#include <stdio.h>

int floorDiv(int a, int b){
    int fd = a/b;
    return fd;
};

main(){
    int a = 22;
    int b = 6;

    if(b==0){
        printf("\"division by zero!!\"\n");
        return 0;        
    }

    else{
        int fd = floorDiv(a,b);
        printf("%d\n", fd);
        return 0; 
    }
};