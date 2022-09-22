
#include<stdio.h>

int main(){
    int x = 3;
    int *y;
    y = &x;
    *y = *y + 1;
    printf("%d",x);
    return 0;
}
