#include<iostream>
int N, M, ans, map[10][10], dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int visited[10][10];

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N)
		return false;
	return true;
}
void getSome(int y, int x, int time, int used, int cross)
{
	visited[y][x] = time;
	if (y == N - 1 && x == N - 1) return;
	for (int dir = 0; dir < 4; dir++)
	{
		int ny = y + dy[dir], nx = x + dx[dir];
		if (isSafe(ny, nx))
		{
			if (map[ny][nx] == 1 && visited[ny][nx] > time)
				getSome(ny, nx, time + 1, used, false);
			else if (!cross && map[ny][nx] > 1 && visited[ny][nx] > (time + map[ny][nx] - time%map[ny][nx]))
				getSome(ny, nx, time + (map[ny][nx] - time%map[ny][nx]), used, true);
			else if (!used && !cross && map[ny][nx] == 0)
				getSome(ny, nx, time + (M - time%M), true, true);
		}

	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				visited[i][j] = 987654321;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				scanf("%d", &map[i][j]);

		getSome(0, 0, 0, false, false);

		printf("#%d %d\n", tc, visited[N - 1][N - 1]);
	}

	return 0;
}
