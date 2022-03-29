#include<iostream>
#include<vector>
#include<string.h>
#define EAST 0
#define WEST 1
#define NORTH 2
#define SOUTH 3
using namespace std;

struct ON {
	int y;
	int x;
	int dir;
};

vector<ON> on;
vector<pair<int, int>> node; // �µ��� �����ؾ��ϴ� ��ǥ
int N, M, K, W, map[22][22], ans; // ���� �µ�
bool wall[22][22][4], visited[22][22]; // �� ����
int dx[4][3] = 
{
	// E
	{
		1, 1, 1,
	},
	// W
	{
		-1, -1, -1,
	},
	// N
	{
		0, -1, 1,
	},
	// S
	{
		0, 1, -1,
	},
},
dy[4][3] = 
{
	// E
	{
		0, -1, 1,
	},
	// W
	{
		0, 1, -1,
	},
	// N
	{
		-1, -1, -1,
	},
	// S
	{
		1, 1, 1,
	},
};

bool isBlock(int y, int x, int i, int dir)
{
	if (i == 0)	return wall[y][x][dir];
	else if (i == 1)
		switch (dir)
		{
		case EAST:
			return (wall[y][x][NORTH] || wall[y - 1][x][dir]);
		case WEST: 
			return (wall[y][x][SOUTH] || wall[y + 1][x][dir]);
		case NORTH:
			return (wall[y][x][WEST] || wall[y][x - 1][dir]);
		case SOUTH:
			return (wall[y][x][EAST] || wall[y][x + 1][dir]);
		}
	else if (i == 2)
		switch (dir)
		{
		case EAST:
			return (wall[y][x][SOUTH] || wall[y + 1][x][dir]);
		case WEST:
			return (wall[y][x][NORTH] || wall[y - 1][x][dir]);
		case NORTH:
			return (wall[y][x][EAST] || wall[y][x + 1][dir]);
		case SOUTH:
			return (wall[y][x][WEST] || wall[y][x - 1][dir]);
		}

	return false;
}

bool isSafe(int y, int x)
{
	if (y < 1 || x < 1 || y > N || x > M) return false;
	return true;
}

void getSome(int y, int x, int dir, int val)
{
	if (val == 0) return;

	map[y][x] += val;

	for (int i = 0; i < 3; ++i)
	{
		if (isBlock(y, x, i, dir)) continue;

		int ny = y + dy[dir][i];
		int nx = x + dx[dir][i];
		
		if (isSafe(ny, nx) && !visited[ny][nx])
		{
			visited[ny][nx] = true;
			getSome(ny, nx, dir, val - 1);
		}
	}
}

void heat()
{
	for (auto obj : on)
	{
		memset(visited, false, sizeof(visited));
		// ��ǳ�� �ٷ� ���� ��ǥ
		int y = obj.y + dy[obj.dir][0];
		int x = obj.x + dx[obj.dir][0];

		getSome(y, x, obj.dir, 5);
	}
}

void controlTemp()
{
	int temp_map[22][22] = {0,};

	for (int y = 1; y <= N; ++y) for (int x = 1; x <= M; ++x)
	{
		for (int dir = 0; dir < 4; ++dir)
		{
			if (dir == WEST || dir == NORTH || wall[y][x][dir]) continue; // �ߺ��� ���ϱ� ���� �����ʰ� �Ʒ� �������θ� ��.
			int ny = y + dy[dir][0];
			int nx = x + dx[dir][0];

			if (isSafe(ny, nx))
			{
				int res = (map[y][x] - map[ny][nx]) / 4;

				temp_map[y][x] -= res;
				temp_map[ny][nx] += res;
			}
		}
	}

	for (int y = 1; y <= N; ++y) for (int x = 1; x <= M; ++x)
		map[y][x] += temp_map[y][x];
}

void cooldown()
{
	for (int y = 1; y <= N; ++y) for (int x = 1; x <= M; ++x)
		if ((y == 1 || x == 1 || y == N || x == M) && map[y][x])
			--map[y][x];
}

bool isOK()
{
	for (int i = 0; i < node.size(); ++i)
	{
		int y = node[i].first;
		int x = node[i].second;

		if (map[y][x] < K)	return false;
	}

	return true;
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);

	for (int y = 1; y <= N; ++y)
		for (int x = 1; x <= M; ++x)
		{
			int num;
			scanf("%d", &num);
			if (num == 5)
				node.push_back({ y, x });
			else if (num)
				on.push_back({ y, x, num - 1 });
		}

	scanf("%d", &W);
	for (int i = 0; i < W; ++i)
	{
		// dir�� 0�̸� ��, 1�̸� ������ �� ����
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		if (dir)
			wall[y][x][EAST] = wall[y][x + 1][WEST] = true;
		else
			wall[y][x][NORTH] = wall[y - 1][x][SOUTH] = true;
	}

	while (ans < 101)
	{
		heat();
		controlTemp();
		cooldown();
		++ans;
		if (isOK()) break;
	}

	printf("%d\n", ans);

	return 0;
}