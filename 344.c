/* Resumed problem statement:
How many "i", "v", "x", "l", and "c" characters are required
to number the pages in the preface.

The input will consist of a sequence of integers in the range 1 to 100,
terminated by a zero.
Outputs:
1: 1 i, 0 v, 0 x, 0 l, 0 c

*/

#include <stdio.h>

void countRomans(int n, int *i, int *v, int *x, int *l, int *c)
{
    int tmp = n;
    
    /* c */
    *c += tmp/100;
    tmp = tmp%100;
    /* xc */
    *c += tmp/90;
    *x += tmp/90;
    tmp = tmp%90;
    /* l */
    *l += tmp/50;
    tmp = tmp%50;
    /* xl */
    *l += tmp/40;
    *x += tmp/40;
    tmp = tmp%40;
    /* x, xx, xxx */
    *x += tmp/10;
    tmp = tmp%10;
    /* ix */
    *x += tmp/9;
    *i += tmp/9;
    tmp = tmp%9;
    /* v */
    *v += tmp/5;
    tmp = tmp%5;
    /* iv */
    *v += tmp/4;
    *i += tmp/4;
    tmp = tmp%4;
    /* i, ii, iii */
    *i += tmp/1;

}

void solve(int n, int *i, int *v, int *x, int *l, int *c)
{
    int ni;
    /* for page 1 to page ni */
    for (ni = 1; ni <= n; ni++) {
        countRomans(ni,i,v,x,l,c);
    }
    
}

int main()
{
    int n;
    int i, v, x, l, c;

    while (scanf("%d\n",&n)==1) {
        if(0==n) break;
    	i=0, v=0, x=0, l=0, c=0;
        solve(n, &i, &v, &x, &l, &c);
    	printf("%d: %d i, %d v, %d x, %d l, %d c\n",
    	    n, i, v, x, l, c);
    }
    return(0);
}

