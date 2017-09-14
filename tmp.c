
struct edge {
    int x, y, f, c, rev;
};
edge eg[500000];
int aj[5010][200];
int pc[5010];
int phi[5010];
int ex[5010];
int
 mac[6000];
int ac[5010];
int dead, born;
void push(int a)
{
    int x = eg[a].x;
    int y = eg[a].y;
    int gg = ex[x];
    if (gg > eg[a].c)
	gg = eg[a].c;
    eg[a].f += gg;
    eg[a].c -= gg;
    int k = eg[a].rev;
    eg[k].f -= gg;
    eg[k].c += gg;
    ex[x] -= gg;
    ex[y] += gg;
    if (ex[x] == 0) {
	dead = (dead + 1) % 6000;
	ac[x] = 0;
    }
    if (y && y < N - 1 && ac[y] == 0) {
	mac[born] = y;
	ac[y] = 1;
	born = (born + 1) % 6000;
    }
}

int maxflow()
{
    int i, j, k, t1, t2, t3;
    for (i = 0; i < M; i++)
	eg[i].f = 0;
    for (i = 1; i < N; i++) {
	ex[i] = 0;
	ac[i] = 0;
    }
    ex[0] = 1000000000;
    dead = born = 0;
    for (i = 0, j = pc[0]; i < j; i++)
	push(aj[0][i]);
    phi[0] = N;
    for (i = 1; i < N; i++)
	phi[i] = 0;
    while (dead != born) {
	i = mac[dead];
	t2 = 100000000;
	for (t1 = pc[i], j = 0; j < t1; j++) {
	    k = aj[i][j];
	    if (eg[k].c == 0)
		continue;
	    t3 = phi[eg[k].y] + 1;
	    if (t3 < t2)
		t2 = t3;
	    if (phi[i] == phi[eg[k].y] + 1) {
		push(k);
		j = t1 + 10;
	    }
	}
	if (j < t1 + 5)
	    phi[i] = t2;
    }
    int ans = 0;
    for (i = 0, j = pc[0]; i < j; i++)

    {
	k = aj[0][i];
	ans += eg[k].f;
    }
    cout << ans << endl;
    return (ans);
}

void init(int a)
{
    int i;
    N = a;
    for (i = 0; i < N; i++)
	pc[i] = 0;
    M = 0;
}

void addEdge(int x, int y, int c)
{
    eg[M].x = x;
    eg[M].y = y;
    eg[M].c = c;
    eg[M].f = 0;
    eg[M].rev = M + 1;
    eg[M + 1].rev = M;
    eg[M + 1].x = y;
    eg[M + 1].y = x;
    eg[M + 1].c = 0;
    eg[M + 1].f = 0;
    aj[x][pc[x]] = M;
    pc[x]++;
    aj[y][pc[y]] = M + 1;
    pc[y]++;
    M += 2;
} int n, m;

int B;
int oPt(int a, int b)
{
    return (2 * (a * m + b) + 1);
}

int iPt(int a, int b)
{
    return (2 * (a * m + b) + 2);
}

int main()
{
    int i, j, k;
    int q;
    cin >> q;
    while (q) {
	q--;
	cin >> n >> m;
	init(2 * m * n + 2);
	for (i = 0; i < n; i++)
	    for (j = 0; j < m; j++) {
		k = oPt(i, j);
		addEdge(iPt(i, j), k, 1);
		if (i == 0)
		    addEdge(k, N - 1, 1);
		else
		    addEdge(k, iPt(i - 1, j), 1);
		if (i == n - 1)
		    addEdge(k, N - 1, 1);
		else
		    addEdge(k, iPt(i + 1, j), 1);
