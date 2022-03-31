// 상어가 빈 칸을 지날 때 어떤 행동을 해야할까?
#include<iostream>
#define SWAP(a, b) if(a!=b) a ^= b ^= a ^= b
struct F {
	int y;
	int x;
	int dir;
	bool isDel;
};

F fish[17];
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dx[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int map[4][4], ans, sy, sx, sdir;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y > 3 || x > 3) return false;
	return true;
}

int turnDir(int dir)
{
	switch (dir)
	{
	case 0:
		return 1;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 4;
	case 4:
		return 5;
	case 5:
		return 6;
	case 6:
		return 7;
	case 7:
		return 0;
	}
}

void copyMapA2B(int A[][4], int B[][4])
{
	for (int y = 0; y < 4; ++y) for (int x = 0; x < 4; ++x)
		B[y][x] = A[y][x];
}

void copyFishA2B(F *A, F *B)
{
	for (int i = 0; i < 17; ++i)
		B[i] = A[i];
}

void moveFish(int sy, int sx)
{
	for (int A = 1; A < 17; ++A)
	{
		if (fish[A].isDel) continue;

		int y = fish[A].y;
		int x = fish[A].x;
		int dir = fish[A].dir;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		while (!isSafe(ny, nx) || (ny == sy && nx == sx))
		{
			dir = turnDir(dir);
			ny = y + dy[dir];
			nx = x + dx[dir];
		}

		if (map[ny][nx])
		{
			int B = map[ny][nx];
			fish[B].y = y;
			fish[B].x = x;
		}

		fish[A].y = ny;
		fish[A].x = nx;
		fish[A].dir = dir;

		SWAP(map[y][x], map[ny][nx]);
	}
}

void getSome(int y, int x, int val)
{
	int id = map[y][x];
	int dir = fish[id].dir;
	int res = val + id;

	map[y][x] = 0;
	fish[id].isDel = true;

	if (ans < res) ans = res;

	int cmap[4][4];
	F cfish[17];
	moveFish(y, x);

	copyMapA2B(map, cmap);
	copyFishA2B(fish, cfish);

	for (int dist = 1; dist < 4; ++dist)
	{
		int ny = y + dy[dir] * dist;
		int nx = x + dx[dir] * dist;

		if (!isSafe(ny, nx)) break;
		if (map[ny][nx]) // 0인 친구를 만나면 진행할 필요가 없고 오류를 발생시킬 것임.
			getSome(ny, nx, res);

		copyMapA2B(cmap, map);
		copyFishA2B(cfish, fish);
	}
}

int main()
{
	for (int y = 0; y < 4; ++y) for (int x = 0; x < 4; ++x)
	{
		int id, dir;
		scanf("%d %d", &id, &dir);
		fish[id] = {y, x, dir - 1, false};
		map[y][x] = id;
	}

	getSome(0, 0, 0);
	printf("%d\n", ans);

	return 0;
}