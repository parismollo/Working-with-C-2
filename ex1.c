#include <stdio.h>
#include <stdlib.h>

int f(int);
int g(int);

int g(int n) {
    if (n==1) return 1;
    return 3 * f(n/2);
}

int f(int n) {
    if(n==1) return 2;
    return 2 * g(n-1);
}

int main() {
    printf("f(20): %d",f(20));
    return EXIT_SUCCESS;
}