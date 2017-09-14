#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;

typedef struct {
    int index, value;
} Item;

bool istie = false;
int a[66], n, ltype, lstamp, lsh;
Item id[4], lim[4];

int generatePermutation(int total, int cur)
{
    int s = 0;
    for (int i = 0; i < cur; i++)
        s += id[i].value;
    if (s > total)
        return 1;
    else if (s == total) {
        int cstamp = cur, ctype = cur;
        for (int i = 0; i < cur - 1; i++)
            if (id[i].index == id[i + 1].index)
                ctype--;
        if (ctype > ltype || (ctype == ltype && cstamp < lstamp) ||
                (ctype == ltype && cstamp == lstamp
                 && id[cur - 1].value > lsh)) {
            ltype = ctype;
            lstamp = cstamp;
            lsh = id[cur - 1].value;
            memcpy(lim, id, sizeof(Item) * cur);
            istie = false;
        } else if (ctype == ltype && cstamp == lstamp
                && id[cur - 1].value == lsh) {
            istie = true;
        }
        return 0;
    } else if (cur < 4) {
        for (int i = (cur > 0 ? id[cur - 1].index : 0); i < n; i++) {
            id[cur].index = i;
            id[cur].value = a[i];
            if (generatePermutation(total, cur + 1))
                break;
        }
    }
    return 0;
}

int main()
{
    while (scanf("%d", &a[n = 0]) != EOF) {
        int b, i = 0, j = 1, lx = 1;
        while (scanf("%d", &a[++n]) && a[n]);
        sort(a, a + n);
        while (j < n) {
            if (a[i] == a[j])
                lx++;
            else
                lx = 1;
            if (lx > 5) {
                while (j < n && a[i] == a[++j]);
                if (j == n)
                    break;
                else
                    lx = 1;
            }
            a[++i] = a[j++];
        }
        n = i + 1;

        while (scanf("%d", &b) && b) {
            ltype = lstamp = lsh = 0;
            istie = false;
            memset(id, 0, sizeof(id));
            generatePermutation(b, 0);
            if (istie)
                printf("%d (%d): tie\n", b, ltype);
            else if (!ltype)
                printf("%d ---- none\n", b);
            else {
                printf("%d (%d):", b, ltype);
                for (int j = 0; j < lstamp; j++)
                    printf(" %d", lim[j].value);
                printf("\n");
            }

        }
    }
    return 0;
}
