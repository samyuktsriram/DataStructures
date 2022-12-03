#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//helper function for arrays from my github and 1-a
//Assuming 0 is divisible by everything, so starting with 1
int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%100;
    }
    return ptr;
}

int fizz(int* f, int nf, int x){
    for(int i = 0; i< nf; i++){
        if (x%f[i]==0){
        return 1;
        }
    }
    return 0;
}
int buzz(int* b, int nb, int x){
    for(int i = 0; i< nb; i++){
        if (x%b[i]==0){
        return 1;
        }
    }
    return 0;
}

int fizzbuzz(int f_cond, int b_cond){
    //This is a combination of the fizz and buzz condition, so we can write it like this
    if (f_cond && b_cond){
        return 1;
    } else {return 0;}
}

void printer(int* f, int* b, int nf, int nb, int x){
    //Check the stricter condition first
    //Assigning to variables to avoid repetitive calls of fizz while checking
    int f_cond = fizz(f,nf,x);
    int b_cond = buzz(b,nb,x);
    if (fizzbuzz(f_cond, b_cond)){printf("fizzbuzz ");}
    else if (f_cond){printf("fizz ");}
    else if (b_cond){printf("buzz ");}
    else {printf("%d ", x);}
}
void advancedFizzBuzz(int*a, int m, int* b, int nb,  int* f, int nf){
    //loop through a, call printer on each element.
    for(int i=0; i<m; i++){
        printer(f,b,nf,nb,a[i]);
    }
}


int main(){

    int len = 100;
    //int* array = create_array_rand(len);
    int* array = malloc(len * sizeof(int));
    for(int i = 0; i<len;i++){
        array[i] = i+1;
    }

    int f[2] = {37, 4};
    int b[3] = {11,13,5};

    advancedFizzBuzz(array, len, b, 3, f, 2);

    free(array);

    return 0;
}