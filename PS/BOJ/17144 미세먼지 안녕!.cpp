#include<iostream>
#include<queue>
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
using namespace std;

struct AC {
	int y;
	int x;
} ac[2]; // 위, 아래 공기청정기

int R, C, T, map[50][50], dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 }, ans;
queue<pair<int, int>> Q; // 미세먼지 확산이 일어날 장소의 좌표를 저장한 큐

void input()
{
	ac[0].y = -1;
	scanf("%d %d %d", &R, &C, &T);
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
	{
		scanf("%d", &map[y][x]);
		if (map[y][x] == -1)
		{
			if (ac[0].y == -1)
			{
				ac[0].y = y;
				ac[0].x = x;
			}
			else
			{
				ac[1].y = y;
				ac[1].x = x;
			}
		}
		else if (map[y][x]) Q.push({ y, x });
	}
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= R || x >= C) return false;
	return true;
}

void spread()
{
	queue<pair<int, int>> NQ = {};
	int tmp[50][50] = {0,};
	while (!Q.empty())
	{
		int y = Q.front().first;
		int x = Q.front().second; Q.pop();
		int cnt = 0, val = map[y][x] / 5;
		tmp[y][x] += map[y][x];

		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && map[ny][nx] != -1)
			{
				tmp[ny][nx] += val;
				tmp[y][x] -= val;
			}
		}
	}

	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
	{
		if (map[y][x] == -1) continue;
		map[y][x] = tmp[y][x];

	}
}

int turn(int dir, int i)
{
	return !i ? (dir + 3) % 4 : (dir + 1) % 4;
}

void turnAc()
{
	int tmp[50][50] = { 0, };
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
		tmp[y][x] = map[y][x];

	for (int i = 0; i < 2; ++i)
	{
		// 초기 우측방향
		int dir = RIGHT;
		// 공기청정기의 좌표
		int ac_y = ac[i].y, y = ac_y;
		int ac_x = ac[i].x, x = ac_x + 1;
		tmp[y][x] = 0;

		int ny = y + dy[dir];
		int nx = x + dx[dir];

		while (ny != ac_y || nx != ac_x)
		{
			if (!isSafe(ny, nx))
			{
				dir = turn(dir, i);
				ny = y + dy[dir];
				nx = x + dx[dir];
			}
			
			tmp[ny][nx] = map[y][x];
			y = ny;
			x = nx;
			ny = y + dy[dir];
			nx = x + dx[dir];
		}
	}

	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
	{
		map[y][x] = tmp[y][x];
		if (tmp[y][x] && tmp[y][x] != -1) Q.push({ y, x });
	}
}

int main()
{
	input();
	for (int i = 0; i < T; ++i)
	{
		spread();
		turnAc();
	}
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
		if (map[y][x] != -1 && map[y][x]) ans += map[y][x];
	printf("%d\n", ans);
	return 0;
}