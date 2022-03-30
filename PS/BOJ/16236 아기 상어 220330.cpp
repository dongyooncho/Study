#include<iostream>
#include<queue>
using namespace std;

int N, ssize = 2, eatcnt = 0, ans, sx, sy, ex, ey, mdist;
int map[20][20];
int dx[4] = { -1, 0, 1, 0 }, dy[4] = { 0, -1, 0, 1 };
queue<pair<int, pair<int, int>>> Q; // dist, {y, x}

int ABS(int val)
{
	return val < 0 ? -val : val;
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

bool BFS()
{
	bool visited[20][20] = { false, };
	ex = ey = mdist = 1000;
	Q.push({ 0, {sy, sx} });
	visited[sy][sx] = true;

	while (!Q.empty())
	{
		int dist = Q.front().first + 1;
		int y = Q.front().second.first;
		int x = Q.front().second.second; Q.pop();
		
		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx] && map[ny][nx] <= ssize)
			{
				visited[ny][nx] = true;
				Q.push({ dist, { ny, nx } });

				// �ش� ��ġ�� ���� �� �ִ� ����Ⱑ �ִٸ�
				if (map[ny][nx] && map[ny][nx] < ssize)
				{
					if (mdist > dist)
					{
						mdist = dist;
						ey = ny;
						ex = nx;
					}
					else if (mdist == dist)
					{
						if (ey < ny || (ey == ny && ex < nx)) continue;
						ey = ny;
						ex = nx;
					}
				}
			}
		}
	}

	// ���� �� �ִ� ����Ⱑ ���ٸ� false ��ȯ
	if (mdist == 1000) return false;
	else return true;
}

int main()
{
	scanf("%d", &N);
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		scanf("%d", &map[y][x]);
		if (map[y][x] == 9)
		{
			sy = y;
			sx = x;
			map[y][x] = 0;
		}
	}

	while (BFS())
	{
		// �ð� ���
		ans += mdist;
		// ��� ��ǥ �̵�
		sy = ey;
		sx = ex;
		map[sy][sx] = 0;

		++eatcnt;
		// ũ�⸸ŭ ����⸦ �Ծ��ٸ� ������.
		if (eatcnt == ssize)
		{
			eatcnt = 0;
			++ssize;
		}
	}

	printf("%d\n", ans);

	return 0;
}