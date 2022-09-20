#include <stdio.h>
int main() {
    int list[2][3] = {{2,4,1},{5,8,1}};
    int list2[3][1] = {{3},{1},{8}};
    int result[2][1] = {{},{}};
    for (int i=0; i<2; i++){
        for (int j=0; j<3; j++){
            result[j][1]=  + list[i][j]*list2[j][1];
        }
    }
    printf("%u/n", result);
    return 0;
}
//So it seems that arrays are immutable, and that is quite a pain.
//Will come back to this at a later point