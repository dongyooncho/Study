#if 0
/**
 * T.O (코드 채점 진행이 되지 않음.)
*/
#include<iostream>

int N, M, map[1000][1000];
int dx[2] = { 1, 0 }, dy[2] = { 0, 1 };
int DP[1000][1000];
bool visited[1000][1000];

void DFS(int y, int x)
{
	for(int dir = 0; dir < 2; ++dir)
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (ny < N && nx < M && (!visited[ny][nx] || (DP[ny][nx] < DP[y][x] + map[ny][nx])))
		{
			visited[ny][nx] = true;
			DP[ny][nx] = DP[y][x] + map[ny][nx];
			DFS(ny, nx);
		}
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			scanf("%d", &map[i][j]);

	DP[0][0] = map[0][0];
	visited[0][0] = true;
	DFS(0, 0);

	printf("%d\n", DP[N-1][M-1]);

	return 0;
}
#endif
#if 1
#include<iostream>
#include<queue>
using namespace std;

int N, M, map[1000][1000];
int dx[2] = { 1, 0 }, dy[2] = { 0, 1 };
int DP[1000][1000];
bool visited[1000][1000];
queue<pair<int, int>> Q;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= M) return false;
	return true;
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			scanf("%d", &map[i][j]);

	DP[0][0] = map[0][0];
	Q.push({0, 0});
	while (!Q.empty())
	{
		int y = Q.front().first;
		int x = Q.front().second; Q.pop();

		for (int dir = 0; dir < 2; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (isSafe(ny, nx) && (!visited[ny][nx] || (DP[ny][nx] < DP[y][x] + map[ny][nx])))
			{
				visited[ny][nx] = true;
				DP[ny][nx] = DP[y][x] + map[ny][nx];
				Q.push({ny, nx});
			}
		}
	}
	printf("%d\n", DP[N - 1][M - 1]);

	return 0;
}
#endif