
// Sample Solution UVA 532:
int R, L, C;
char dun[40][40][40];
int d[40][40][40];
int dead, born;
int arrx[64000], arry[64000], arrz[64000];
void play(int x, int y, int z, int depth)
{
    if (x < 0 || y < 0 || z < 0 || x >= R || y >= L || z >= C)
	return;
    if (dun[x][y][z] == '#')
	return;
    if (d[x][y][z] != -1)
	return;
    arrx[born] = x;
    arry[born] = y;
    arrz[born] = z;
    born++;
    d[x][y][z] = depth + 1;
}

void bfs()
{
    int x, y, z, dd;
    born = dead = 0;
    memset(d, -1, sizeof(d));
    for (x = 0; x < R; x++)
	for (y = 0; y < L; y++)
	    for (z = 0; z < C; z++)
		if (dun[x][y][z] == 'S') {
		    arrx[born] = x;
		    arry[born] = y;
		    arrz[born] = z;
		    born++;
		    d[x][y][z] = 0;
		}
    while (born > dead) {
	x = arrx[dead];
	y = arry[dead];
	z = arrz[dead];
	dead++;
	dd = d[x][y][z];
	if (dun[x][y][z] == 'E') {
	    cout << "Escaped in " << dd << " minute(s)." << endl;
	    return;
	}
	play(x + 1, y, z, dd);
	play(x - 1, y, z, dd);
	play(x, y + 1, z, dd);
	play(x, y - 1, z, dd);
	play(x, y, z + 1, dd);
	play(x, y, z - 1, dd);
    }
    cout << "Trapped!" << endl;
}

int main()
{
    while (cin >> R >> L >> C && R) {
	for (int i = 0; i < R; i++)
	    for (int j = 0; j < L; j++)
		cin >> dun[i][j];
	bfs();
    }
}
