#include<iostream>
#define ALPHA 9
int N, ans;
int map[500][500], Y, X, dir = 1, cnt = 0, dist = 1;
int dy[4] = { -1, 0, 1, 0 }, dx[4] = { 0, -1, 0, 1 }; // 상좌하우
int wdx[4][10] = { 
	{ -1, 1, -2, -1, 1, 2, -1, 1, 0, 0 },
	{ 0, 0, -1, -1, -1, -1, -2, -2, -3, -2 },
	{ 1, -1, 2, 1, -1, -2, 1, -1, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 2, 2, 3, 2 },
}, wdy[4][10] = {
	{ 0, 0, -1, -1, -1, -1, -2, -2, -3, -2 },
	{ 1, -1, 2, 1, -1, -2, 1, -1, 0, 0 },
	{ 0, 0, 1, 1, 1, 1, 2, 2, 3, 2 },
	{ -1, 1, -2, -1, 1, 2, -1, 1, 0, 0 },
}; // 10번은 a위치.
double percent[9] = {
	0.01, 0.01, 
	0.02, 0.07, 0.07, 0.02, 
	0.1, 0.1, 
	0.05
};

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

void wind()
{
	int ny = Y + dy[dir];
	int nx = X + dx[dir];
	int pivot = map[ny][nx];
	map[ny][nx] = 0;

	int sand = 0;

	for (int i = 0; i < 9; ++i)
	{
		ny = Y + wdy[dir][i];
		nx = X + wdx[dir][i];

		int val = pivot * percent[i];
		sand += val;

		if (isSafe(ny, nx))	map[ny][nx] += val;
		else ans += val;
	}
	pivot -= sand;

	ny = Y + wdy[dir][ALPHA];
	nx = X + wdx[dir][ALPHA];
	if (isSafe(ny, nx)) map[ny][nx] += pivot;
	else ans += pivot;
}

void moveTor()
{
	Y += dy[dir];
	X += dx[dir];
}

void turnTor()
{
	switch (dir)
	{
	case 0:
		dir = 1;
		break;
	case 1:
		dir = 2;
		break;
	case 2:
		dir = 3;
		break;
	case 3:
		dir = 0;
		break;
	}
}

int main()
{
	scanf("%d", &N);
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		scanf("%d", &map[y][x]);
	Y = X = N / 2;

	int i = 0;
	while (Y != 0 || X != 0)
	{
		if (Y == 3 && X == 0)
			int u = 0;
		wind();
		moveTor();
		++i;

		if (i == dist)
		{
			i = 0;
			++cnt;
			turnTor();
		}
		if (cnt == 2)
		{
			cnt = 0;
			++dist;
		}
	}

	printf("%d\n", ans);

	return 0;
}