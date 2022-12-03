#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

//helper function for arrays from my github
//Assuming 0 is divisible by everything, so starting with 1
int* create_array_rand(int length){

    int* ptr = malloc(length * sizeof(int));
    for(int i=0; i<length; i++){
        ptr[i] = rand()%100;
    }
    return ptr;
}

int fizz(int x){
    if ((x%5==0) || (x%3==0)){
        return 1;
    } else {return 0;}
}
int buzz(int x){
    if ((x%11==0) || (x%13==0)){
        return 1;
    } else {return 0;}
}
int fizzbuzz(int x){
    //This is a combination of the fizz and buzz condition, so we can write it like this
    if (fizz(x) && buzz(x)){
        return 1;
    } else {return 0;}
}

void printer(int x){
    //Check the stricter condition first
    if (fizzbuzz(x)){printf("fizzbuzz ");}
    else if (fizz(x)){printf("fizz ");}
    else if (buzz(x)){printf("buzz ");}
    else {printf("%d ", x);}
}
void basicFizzBuzz(int x){
    printer(x);
}


int main(){

    int len = 100;
    //int* array = create_array_rand(len);
    for(int i = 0; i<len;i++){
        basicFizzBuzz(i+1);
    }

    return 0;
}