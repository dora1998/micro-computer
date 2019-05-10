#include <xc.h>

void main() {
    int a[2] = { 1000, 2000 };
    char b[2] = { 1, 2 };
    char c = 10;
    char *p, *q;
    int *r;
    
    p = &c;
    q = &(a[0]);
    r = b;
    
    q++;
    r++;
}
