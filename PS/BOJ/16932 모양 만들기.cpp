// 1. 클러스터 분류 후 개수세기
// 2. 클러스터 주변의 0을 모두 탐색하기
// 3. 사방으로 어떤 종류의 클러스터와 만나는지 확인해서 가장 큰 애를 선택
#include<iostream>
#include<queue>
#define MAX(a, b) a>b?a:b
using namespace std;

int N, M, map[1000][1000], dx[4] = { 1,0,-1,0 }, dy[4] = { 0,1,0,-1 };
int ans, cluster, arr[500000]; // 현재 클러스터 번호, 클러스터 내 모양 개수 저장
bool checked[1000][1000];
bool visited[500000];
queue<pair<int, int>> Q, Q2;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= M) return false;
	return true;
}

int cluster_dfs(int y, int x, int c, int res)
{
	for (int dir = 0; dir < 4; dir++)
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (isSafe(ny, nx) && !checked[ny][nx])
		{
			checked[ny][nx] = true;

			if (map[ny][nx])
			{
				map[ny][nx] = c;
				res = cluster_dfs(ny, nx, c, res + 1);
			}
			else
				Q2.push({ny, nx});
		}
	}
	return res;
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int y = 0; y<N; y++)
		for (int x = 0; x < M; x++)
		{
			scanf("%d", &map[y][x]);
			if (map[y][x] == 1) Q.push({y, x});
		}

	while (!Q.empty())
	{
		int y = Q.front().first;
		int x = Q.front().second;
		Q.pop();

		if (!checked[y][x])
		{
			checked[y][x] = true;
			map[y][x] = ++cluster;
			arr[cluster] = cluster_dfs(y, x, cluster, 1);
		}
	}
	
	while (!Q2.empty())
	{
		int y = Q2.front().first;
		int x = Q2.front().second;
		Q2.pop();

		int res = 0, d[4] = { 0 };

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx))
				d[dir] = map[ny][nx];
		}

		for (int i = 0; i < 4; i++)
		{
			if (!visited[d[i]])
				res += arr[d[i]];
			visited[d[i]] = true;
		}
		for (int i = 0; i < 4; i++)
			visited[d[i]] = false;

		ans = MAX(ans, res);
	}

	printf("%d\n", ans + 1);

	return 0;
}