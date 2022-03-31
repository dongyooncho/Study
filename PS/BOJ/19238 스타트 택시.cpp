#include<iostream>
#include<queue>
using namespace std;

struct Person {
	int y;
	int x;
	int ey;
	int ex;
}p[402];

int N, M, fuel, cnt, pid, used;
int map[20][20], Y, X; // 백준의 위치
int dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

bool pickUp()
{	
	used = 0;
	if (map[Y][X]) pid = map[Y][X];
	else
	{
		int min_dist = 401;

		queue<pair<int, pair<int, int>>> Q;
		bool visited[20][20] = { false, };

		Q.push({ 0, {Y, X} });
		visited[Y][X] = true;

		while (!Q.empty() && min_dist > Q.front().first)
		{
			int dist = Q.front().first;
			int y = Q.front().second.first;
			int x = Q.front().second.second; Q.pop();

			for (int dir = 0; dir < 4; ++dir)
			{
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				if (isSafe(ny, nx) && map[ny][nx] != -1 && !visited[ny][nx])
				{
					visited[ny][nx] = true;

					if (map[ny][nx])
					{
						if (min_dist > dist + 1)
						{
							min_dist = dist + 1;
							pid = map[ny][nx];
						}
						else if (min_dist == dist + 1)
						{
							if (ny > p[pid].y || (ny == p[pid].y && nx > p[pid].x)) continue;
							pid = map[ny][nx];
						}
					}

					Q.push({ dist + 1, { ny, nx } });
				}
			}
		}

		used += min_dist;
	}

	Y = p[pid].y;
	X = p[pid].x;
	map[Y][X] = 0;

	fuel -= used;
	return (pid && fuel > 0);
}

bool arrive()
{
	used = 0;
	bool suc = false;
	int min_dist = 0;
	int target_y = p[pid].ey;
	int target_x = p[pid].ex;

	queue<pair<int, pair<int, int>>> Q;
	bool visited[20][20] = { false, };

	Q.push({ 0,{ Y, X } });
	visited[Y][X] = true;

	while (!Q.empty() && !suc)
	{
		int dist = Q.front().first;
		int y = Q.front().second.first;
		int x = Q.front().second.second; Q.pop();

		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && map[ny][nx] != -1 && !visited[ny][nx])
			{
				visited[ny][nx] = true;

				if (ny == target_y && nx == target_x)
				{
					min_dist = dist + 1;
					suc = true;
					break;
				}

				Q.push({ dist + 1,{ ny, nx } });
			}
		}
	}

	Y = target_y; X = target_x;
	used = min_dist;
	fuel -= used;

	return (suc && fuel >= 0);
}

int main()
{
	scanf("%d %d %d", &N, &M, &fuel);
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		scanf("%d", &map[y][x]);
		if (map[y][x]) map[y][x] = -1;
	}
	scanf("%d %d", &Y, &X);
	--Y; --X;
	for (int i = 1; i <= M; ++i)
	{
		int sy, sx, ey, ex;
		scanf("%d %d %d %d", &sy, &sx, &ey, &ex);
		p[i] = { sy - 1, sx - 1, ey - 1, ex - 1 };
		map[sy - 1][sx - 1] = i;
	}

	while (cnt < M)
	{
		pid = 0;
		if (!pickUp()) break;
		if (!arrive()) break;

		fuel += used * 2;
		cnt++;
	}
	printf("%d\n", (cnt == M && fuel > 0)? fuel : -1);
	return 0;
}