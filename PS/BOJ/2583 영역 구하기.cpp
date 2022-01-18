#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int N, M, K, map[100][100], dy[4] = { 0,1,0,-1 }, dx[4] = { 1, 0, -1, 0 };
bool visited[100][100];
queue<pair<int, int>> Q;
struct comp {
	bool operator()(int a, int b) {
		return a > b;
	}
};
priority_queue<int, vector<int>, comp> PQ;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= M || x >= N) return false;
	return true;
}

int BFS()
{
	int res = 1;
	while (!Q.empty())
	{
		int y = Q.front().first;
		int x = Q.front().second;
		Q.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx] && map[ny][nx] == 0)
			{
				visited[ny][nx] = true;
				res++;
				Q.push({ny, nx});
			}
		}
	}
	return res;
}

int main()
{
	scanf("%d %d %d", &M,&N,&K);
	for (int i = 0; i < K; i++)
	{
		int sy, sx, ey, ex;
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		for (int y = sy; y < ey; y++)
			for (int x = sx; x < ex; x++)
				map[y][x] = 1;
	}
	for (int y = 0; y < M; y++)
		for (int x = 0; x < N; x++)
			if (!visited[y][x] && map[y][x] == 0)
			{
				visited[y][x] = true;
				Q.push({y,x});
				PQ.push(BFS());
			}
				
	printf("%d\n", PQ.size());

	while (!PQ.empty())
	{
		printf("%d ", PQ.top());
		PQ.pop();
	}
	printf("\n");

	return 0;
}