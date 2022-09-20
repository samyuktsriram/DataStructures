#include <stdio.h>
int main(void) {
    //This is how you do comments
    printf("Hello World!");
    
    float i = 0.00;
    for(i=0.0; i<0.000001; i += 0.0000001){
        printf("%f \n",i);
    }
    return 0;
}