#include<iostream>
#include<vector>
#define R 0
#define D 1
#define L 2
#define U 3
using namespace std;

struct ON {
	int y;
	int x;
	int dir;
};

int N, M, K, W, ans;
int map[20][20],
dy[4][3] = {
	{0, -1, 1},
	{ 1, 1, 1 },
	{ 0, 1, -1 },
	{ -1, -1, -1 },
},
dx[4][3] = {
	{1, 1, 1},
	{0, 1, -1},
	{ -1, -1, -1 },
	{ 0, -1, 1 },
};
bool wall[4][20][20];
vector<pair<int, int>> node;
vector<ON> on;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= M) return false;
	return true;
}

// 연산 횟수를 줄이기 위해 로직 수정: 8 -> 4ms
//int turnDir(int dir, int RL)
//{
//	if (RL == 0) return dir; // 그대로
//	else if (RL == 1) return (dir - 1 + 4) % 4; // 좌측
//	else if (RL == 2) return (dir + 1) % 4; // 우측
//	else return (dir + 2) % 4; // 반대방향
//}

int turnDir(int dir, int RL)
{
	if (RL == 0) return dir; // 그대로
	else if (RL == 1)
	{
		switch (dir)
		{
		case R:
			return U;
		case U:
			return L;
		case L:
			return D;
		case D:
			return R;
		}
	}
	else if (RL == 2)
	{
		switch (dir)
		{
		case R:
			return D;
		case D:
			return L;
		case L:
			return U;
		case U:
			return R;
		}
	}
	else
	{
		switch (dir)
		{
		case R:
			return L;
		case U:
			return D;
		case L:
			return R;
		case D:
			return U;
		}
	}
}

void DFS(int y, int x, int dir, int val, bool visited[][20])
{
	if (!val) return;
	for (int i = 0; i < 3; ++i)
	{
		int ny = y + dy[dir][i];
		int nx = x + dx[dir][i];

		if (isSafe(ny, nx) && !visited[ny][nx] && !wall[turnDir(dir, i)][y][x] && !wall[turnDir(dir, -1)][ny][nx])
		{
			map[ny][nx] += val;
			visited[ny][nx] = true;
			DFS(ny, nx, dir, val - 1, visited);
		}
	}
}

void wind()
{
	for (int device = 0; device < on.size(); ++device)
	{
		bool visited[20][20] = {false,};
		int y = on[device].y;
		int x = on[device].x;
		int dir = on[device].dir;
		int ny = y + dy[dir][0];
		int nx = x + dx[dir][0];

		map[ny][nx] += 5;
		DFS(ny, nx, dir, 4, visited);
	}
}

void controlTemp()
{
	int tmp[20][20] = {0,};
	for (int y = 0; y < N; ++y) for (int x = 0; x < M; ++x) for (int dir = 0; dir < 2; ++dir)
	{
		int ny = y + dy[dir][0];
		int nx = x + dx[dir][0];
		if (isSafe(ny, nx) && !wall[dir][y][x])
		{
			int res = (map[y][x] - map[ny][nx]) / 4;
			tmp[ny][nx] += res;
			tmp[y][x] -= res;
		}
	}

	for (int y = 0; y < N; ++y) for (int x = 0; x < M; ++x)
		map[y][x] += tmp[y][x];
}

void decreaseTemp()
{
	for (int y = 0; y < N; ++y) for (int x = 0; x < M; ++x)
		if ((y == 0 || x == 0 || y == N - 1 || x == M - 1) && map[y][x])
			--map[y][x];
}

bool isEnd()
{
	for (int i = 0; i < node.size(); ++i)
		if (map[node[i].first][node[i].second] < K)
			return false;

	return true;
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	for (int y = 0; y < N; ++y)for (int x = 0; x < M; ++x)
	{
		scanf("%d", &map[y][x]);
		int val[4] = { R, L, U, D };
		if (map[y][x] == 5) node.push_back({ y, x });
		else if (map[y][x]) on.push_back({ y, x, val[map[y][x] - 1] });
		map[y][x] = 0;
	}

	scanf("%d", &W);
	for (int i = 0; i < W; ++i)
	{
		int y, x, t;
		scanf("%d %d %d", &y, &x, &t);
		--y; --x;
		if (t) wall[R][y][x] = wall[L][y][x + 1] = true;
		else wall[U][y][x] = wall[D][y - 1][x] = true;
	}

	while (ans < 101)
	{
		wind();
		controlTemp();
		decreaseTemp();
		++ans;
		if (isEnd()) break;
	}

	printf("%d\n", ans);
	return 0;
}