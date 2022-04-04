#include<iostream>
#define MAX(a,b) a>b?a:b
int N, K, mSum, mMax;
int map[64][64], bin[7] = { 1, 2, 4, 8, 16, 32, 64 };
int Q[10000], front, rear, dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };
bool visited[64][64];

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= bin[N] || x >= bin[N]) return false;
	return true;
}

void spin(int sy, int sx, int ey, int ex, int lev)
{
	// lev이 맞으면 배열 회전
	if (ey - sy == bin[lev])
	{
		int QQ[10000], front = -1, rear = -1;
		for (int y = sy; y < ey; ++y) for (int x = sx; x < ex; ++x)
			QQ[++rear] = map[y][x];

		for (int x = ex - 1; x >= sx; --x) for (int y = sy; y < ey; ++y)
			map[y][x] = QQ[++front];

		return;
	}

	// lev보다 크다면 더 작은 크기로 나눔
	int my = (ey + sy) / 2;
	int mx = (ex + sx) / 2;
	spin(sy, sx, my, mx, lev);
	spin(sy, mx, my, ex, lev);
	spin(my, sx, ey, mx, lev);
	spin(my, mx, ey, ex, lev);
}

void melt()
{
	int tmp[64][64] = {0,};
	for (int y = 0; y < bin[N]; ++y) for (int x = 0; x < bin[N]; ++x)
	{
		if (!map[y][x]) continue;
		int cnt = 0;
		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && map[ny][nx]) ++cnt;
		}
		if (cnt < 3) --tmp[y][x];
	}
	for (int y = 0; y < bin[N]; ++y) for (int x = 0; x < bin[N]; ++x)
		map[y][x] += tmp[y][x];
}

int BFS(int y, int x)
{
	int cnt = 1;
	int Qy[10000], Qx[10000];
	front = rear = -1;
	Qy[++rear] = y; Qx[rear] = x;

	while (front != rear)
	{
		y = Qy[++front], x = Qx[front];

		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir], nx = x + dx[dir];
			if (isSafe(ny, nx) && map[ny][nx] && !visited[ny][nx])
			{
				visited[ny][nx] = true; ++cnt;
				Qy[++rear] = ny; Qx[rear] = nx;
			}
		}
	}

	return cnt;
}

int main()
{
	front = rear = -1;
	scanf("%d %d", &N, &K);

	for (int y = 0; y < bin[N]; ++y) for (int x = 0; x < bin[N]; ++x)
		scanf("%d", &map[y][x]);

	for (int i = 0; i < K; ++i)
		scanf("%d", &Q[++rear]);

	// K회 반복
	while (front != rear)
	{
		int lev = Q[++front];
		spin(0, 0, bin[N], bin[N], lev);
		melt();
	}
	
	// 남은 얼음의 양과 가장 큰 얼음을 계산
	for (int y = 0; y < bin[N]; ++y)for (int x = 0; x < bin[N]; ++x)
	{
		if (map[y][x] && !visited[y][x])
		{
			visited[y][x] = true;
			int res = BFS(y, x);
			mMax = MAX(mMax, res);
		}
		mSum += map[y][x];
	}
	printf("%d\n%d\n", mSum, mMax);

	return 0;
}