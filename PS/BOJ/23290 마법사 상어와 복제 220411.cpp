#include<iostream>
#include<vector>
using namespace std;

struct F {
	int y;
	int x;
	int dir;
};

int M, S, ans, T;
int dy[8] = { 0, -1, -1, -1, 0, 1, 1, 1 }, dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 }, smell[5][5], sy, sx, maxFish, sdir[3];
int sdy[4] = { -1, 0, 1, 0 }, sdx[4] = { 0, -1, 0, 1 };
bool visited[5][5];
vector<F> map[5][5], egg[5][5];

// 유효한 좌표인지 확인하는 함수.
bool isSafe(int y, int x)
{
	if (y < 1 || x < 1 || y > 4 || x > 4) return false;
	return true;
}

// 반시계 방향 45도 회전
int turnDir(int dir)
{
	return (dir - 1 + 8) % 8;
}

void copy()
{
	for (int y = 1; y < 5; ++y) for (int x = 1; x < 5; ++x) for (int k = 0; k < map[y][x].size(); ++k)
		egg[y][x].push_back(map[y][x][k]);
}

void moveFish()
{
	vector<F> tmp[5][5];
	for (int y = 1; y < 5; ++y) for (int x = 1; x < 5; ++x) for (int k = 0; k < map[y][x].size(); ++k)
	{
		int dir = map[y][x][k].dir;
		int ny = map[y][x][k].y + dy[dir];
		int nx = map[y][x][k].x + dx[dir];
		int cnt = 0;
		while (!isSafe(ny, nx) || smell[ny][nx] || (ny == sy && nx == sx))
		{
			++cnt;
			dir = turnDir(dir);
			ny = map[y][x][k].y + dy[dir];
			nx = map[y][x][k].x + dx[dir];

			if (cnt > 7) break;
		}

		if (cnt == 8)
		{
			tmp[y][x].push_back({y,x,dir});
			continue;
		}
		tmp[ny][nx].push_back({ ny, nx, dir });
	}

	for (int y = 1; y < 5; ++y) for (int x = 1; x < 5; ++x)
		map[y][x] = tmp[y][x];
}

void DFS(int y, int x, int val, int cnt, int dirs[])
{
	if (cnt == 3)
	{
		if (maxFish < val)
		{
			maxFish = val;
			for (int i = 0; i < 3; ++i)
				sdir[i] = dirs[i];
		}
		return;
	}

	for (int dir = 0; dir < 4; ++dir)
	{
		int ny = y + sdy[dir];
		int nx = x + sdx[dir];
		if (isSafe(ny, nx))
		{
			dirs[cnt] = dir;
			if (!visited[ny][nx])
			{
				// 기존에 물고기를 잡아먹었던적이 있으면 기억해둔다.
				bool tmp = visited[ny][nx];
				visited[ny][nx] = true;
				DFS(ny, nx, val + map[ny][nx].size(), cnt + 1, dirs);
				visited[ny][nx] = tmp;
			}
			else
				DFS(ny, nx, val, cnt + 1, dirs);
		}
	}
}

void moveShark()
{
	maxFish = -1;
	for (int dir = 0; dir < 4; ++dir)
	{
		int dirs[3] = { -1, -1, -1 };
		int ny = sy + sdy[dir];
		int nx = sx + sdx[dir];
		if (isSafe(ny, nx))
		{
			visited[ny][nx] = true;
			dirs[0] = dir;
			DFS(ny, nx, map[ny][nx].size(), 1, dirs);
			visited[ny][nx] = false;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		int ny = sy + sdy[sdir[i]];
		int nx = sx + sdx[sdir[i]];

		// 냄새가 사라지는 시간을 저장.
		if (map[ny][nx].size()) smell[ny][nx] = T + 2;
		map[ny][nx] = {};

		sy = ny;
		sx = nx;
	}
}

void delSmell()
{
	for (int y = 1; y < 5; ++y) for (int x = 1; x < 5; ++x)
		if (smell[y][x] == T) smell[y][x] = 0;
}

void complete()
{
	for (int y = 1; y < 5; ++y) for (int x = 1; x < 5; ++x)
	{
		for (int k = 0; k < egg[y][x].size(); ++k)
			map[y][x].push_back(egg[y][x][k]);

		egg[y][x] = {};
	}
}

int main()
{
	scanf("%d %d", &M, &S);
	for (int i = 0; i < M; ++i)
	{
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		map[y][x].push_back({ y, x, dir - 1 });
	}
	scanf("%d %d", &sy, &sx);

	for (T = 0; T < S; ++T)
	{
		copy();
		moveFish();
		moveShark();
		delSmell();
		complete();
	}

	for (int y = 1; y <= 4; ++y) for (int x = 1; x <= 4; ++x)
		ans += map[y][x].size();

	printf("%d\n", ans);
	return 0;
}