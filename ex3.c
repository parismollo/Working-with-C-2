#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define NB 10

typedef struct fraction {
    long int num;
    long int den;
}fraction;

typedef struct point {
    fraction x;
    fraction y;
}point;

fraction build(long int n, long int d) {
    assert(d!=0);
    fraction f = {.num = n, .den=d};
    return f;
}

int eq_fraction(fraction f, fraction g) {
    if(f.num * g.den == g.num * f.den) {
        return 1;
    }
    return 0;
}

int is_int(fraction f) {
    if(f.num % f.den == 0) {
        return true;
    }
    return false;
}

fraction sum(fraction f, fraction g) {
    int new_den = f.den * g.den;
    int new_f_num = f.num * g.den;
    int new_g_num = g.num * f.den;
    int new_num = new_f_num+new_g_num;

    return build(new_num, new_den); 
}

fraction sub(fraction f, fraction g) {

    int new_den = f.den * g.den;
    int new_f_num = f.num * g.den;
    int new_g_num = g.num * f.den;
    int new_num = new_f_num-new_g_num;

    return build(new_num, new_den);
}

fraction mul(fraction f, fraction g) {
    return build(f.num*g.num, f.den*g.den);
}

long pgcd(long a, long b) {
    int x = a;
    int y = b;
    int r = 0;
    while (y != 0) {
        r = x % y;
        x = y;
        y = r;
    }
    return x;
}

fraction reduce(fraction f) {
    int new_num = f.num / pgcd(f.num, f.den);
    int new_den = f.den / pgcd(f.num, f.den);
    return build(new_num, new_den);
}

int compareFraction(fraction a, fraction b) {
    fraction new_a = reduce(a);
    fraction new_b = reduce(b);
    if (new_a.num == new_b.num && new_a.den == new_b.den) return 1;
    return 0;
}

int eq_point(point p1, point p2) {
    if (compareFraction(p1.x, p2.x) && compareFraction(p1.y, p2.y)) return 1;
    return 0;
}

double dist(point p1, point p2) {
    fraction a = sub(p1.x, p2.x);
    fraction b = sub(p1.y, p2.y);

    fraction sq_a = mul(a, a);
    fraction sq_b = mul(b, b);

    fraction c = reduce(sum(sq_a, sq_b));
    double d_c = (double) c.num / c.den;
    return sqrt(d_c);

}

void printFraction(fraction f) {
    printf("%ld/", f.num);
    printf("%ld", f.den);
    printf("\n");
}

int main() {
    fraction ex_fractions[] = {
        build(1, 1), build(1, 2), build(2, 4), build(-9,3), build(8, -20), build(-5,-1),build(1,-3)
    };
    int taille = sizeof(ex_fractions)/sizeof(ex_fractions[0]);
    for(int i=0; i<taille; i++) {
        printFraction(ex_fractions[i]);
    }

    fraction f2 = build(4, -2);
    fraction f3= build(8, 4);
    printf("\n");

    printFraction(f2);
    printFraction(f3);

    printf("\n");
    printf("eq_fraction: %d\n", eq_fraction(f2, f3));
    printf("is_int: %d\n", is_int(f2));
    printf("is_int: %d\n", is_int(f3));

    printf("\nmultiplication: ");
    printFraction(mul(f2,f3));
    printf("\nsum: ");
    printFraction(sum(f2,f3));
    printf("\nsub: ");
    printFraction(sub(f2,f3));

    printf("pgcd(221, 782) = %li\n", pgcd(221, 782));

    printf("Reduce: ");
    printFraction(reduce(f2));

    point a = {.x = build(2,4), .y = build(8, 6)};
    point b = {.x = build(2,4), .y = build(8, 6)};
    
    printf("a == b? -> %d\n", eq_point(a, b));
    printf("dist(a, b) = %f", dist(a, b));
    return EXIT_SUCCESS;
} 