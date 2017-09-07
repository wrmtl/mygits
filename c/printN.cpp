#include <stdio.h>
#include <time.h>

#define MAX 100000

void printN(int N); 

int main(){

    printN(MAX);
    return 0;
}
void printN(int N){
    if(N){
        printN(N-1);
        printf("%d\n",N);
    }
    return;
}

