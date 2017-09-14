/* https://uva.onlinejudge.org/external/104/p10487.pdf
 Given is a set of integers and then a sequence of queries. A query gives you a number and asks to find
 a sum of two distinct numbers from the set, which is closest to the query number.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N_VALUE 1000
#define MAX_M_VALUE 25
#define A_INT_MAX 2147483647

int main()
{
    int nv[MAX_N_VALUE];
    int n, i, nq, q, idx, idx2, sum, diff, ce = 0;

    while(1)
    {
        /* read number of input integers, 0 to exit */
        scanf("%d", &n);
        if(!n) break;

        printf("Case %d:\n", ++ce);

        /* read all n numbers */
        for(i=0; i < n; i++)
        {
            scanf("%d", &nv[i]);
        }

        /* read number of input queries */
        scanf("%d", &nq);
        while(nq--)
        {
            /* read query value */
            scanf("%d", &q);

            /* find nearest sum of two elements */
            diff = A_INT_MAX;
            for(idx = 0; idx < (n-1); idx++)
            {
                for(idx2 = idx + 1; idx2 < n; idx2++)
                {
                    /* measure distance and keep the smallest
                     * if sum - q < prevous, save
                    */
                    if(  abs((nv[idx] + nv[idx2]) - q) < diff  )
                    {
                        diff = abs((nv[idx] + nv[idx2]) - q);
                        sum = nv[idx] + nv[idx2];
                    }
                }
            }
            printf("Closest sum to %d is %d.\n", q, sum);
        }
    }
    return 0;
}
