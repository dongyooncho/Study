#include<iostream>
#include<queue>
#define BLANK -2
using namespace std;

int N, M, ans, score[401];
int map[20][20], dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };
int maxBlockSize, maxRainbowSize, py, px;
queue<pair<int, int>> Q, EQ;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

void BFS(int y, int x, bool visited[][20][20])
{
	queue<pair<int, int>> tmpQ = {};
	int color = map[y][x], blockCnt = 0, rainbowCnt = 0;
	Q.push({ y,x }); visited[color][y][x] = true;
	tmpQ.push({ y,x });
	++blockCnt;

	while (!Q.empty())
	{
		int y = Q.front().first;
		int x = Q.front().second; Q.pop();
		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && (map[ny][nx] == color || map[ny][nx] == 0) && !visited[color][ny][nx])
			{
				visited[color][ny][nx] = true;
				Q.push({ ny, nx });
				tmpQ.push({ ny, nx });
				++blockCnt;
				if (map[ny][nx] == 0) ++rainbowCnt;
			}
		}
	}

	if (maxBlockSize == blockCnt && maxRainbowSize == rainbowCnt)
	{
		if (py < y || (py == y && px < x))
		{
			py = y;
			px = x;
			EQ = tmpQ;
		}
	}
	else if (maxBlockSize < blockCnt || (maxBlockSize == blockCnt && maxRainbowSize < rainbowCnt))
	{
		py = y;
		px = x;
		maxBlockSize = blockCnt; maxRainbowSize = rainbowCnt;
		EQ = tmpQ;
	}
}

int findBlock()
{
	maxBlockSize = maxRainbowSize = py = px = -1;
	bool visited[6][20][20] = { false, };
	for (int color = 1; color <= M; ++color)
	{
		for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		{
			if ((map[y][x] == color)&& !visited[color][y][x])
				BFS(y, x, visited);
		}
	}

	return maxBlockSize;
}

void eraseBlock()
{
	ans += score[EQ.size()];
	while (!EQ.empty())
	{
		int y = EQ.front().first;
		int x = EQ.front().second; EQ.pop();
		map[y][x] = BLANK;
	}
}

void gravity()
{
	queue<int> QQ;
	for (int x = 0; x < N; ++x)
	{
		int y = N - 1, sy = N - 1, ny;

		while (sy >= 0)
		{
			if (y < 0)
			{
				y = sy;
				while (!QQ.empty())
				{
					map[y--][x] = QQ.front(); QQ.pop();
				}
				sy = -1;
			}
			else if (map[y][x] == -1)
			{
				ny = y;
				y = sy;
				// Q다털기
				while (!QQ.empty())
				{
					map[y--][x] = QQ.front(); QQ.pop();
				}
				//y 올리기
				y = sy = ny - 1;
			}
			else if (map[y][x] == BLANK)
				--y;
			else
			{
				QQ.push({ map[y][x] });
				map[y--][x] = BLANK;
			}
		}
	}
}

void turn()
{
	queue<int> QQ;
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		QQ.push(map[y][x]);

	for (int x = 0; x < N; ++x) for (int y = N - 1; y >= 0; --y)
	{
		map[y][x] = QQ.front();
		QQ.pop();
	}
}

int main()
{
	for (int i = 0; i < 401; ++i)
		score[i] = i*i;
	scanf("%d %d", &N, &M);
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		scanf("%d", &map[y][x]);

	while (1)
	{
		if (findBlock() < 2) break;
		eraseBlock();
		gravity();
		turn();
		gravity();
	}

	printf("%d\n", ans);

	return 0;
}