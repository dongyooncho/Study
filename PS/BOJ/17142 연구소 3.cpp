// ���̷����� ���� �ڸ��� ä���� �ʾƵ� ��� ������, �̵� ��η� ���� �� �ִ�.
// �׷��� 2�� �ڸ��� �湮�� ���������� �ð��� üũ���� �ʰ� �Ͽ� �ذ�
#include<iostream>
#include<vector>
#include<queue>
#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b
#define INF 10000
using namespace std;

int N, M, map[51][51], ans = INF, dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };
vector<pair<int, int>> pos;
queue<pair<int, pair<int, int>>> Q; // time, {y, x}

void copyMapA2B(int A[][51], int B[][51])
{
	for (int y = 1; y <= N; ++y) for (int x = 1; x <= N; ++x)
		B[y][x] = A[y][x];
}

bool isSafe(int y, int x)
{
	if (y < 1 || x < 1 || y > N || x > N) return false;
	return true;
}

bool noZero()
{
	for (int y = 1; y <= N; ++y) for (int x = 1; x <= N; ++x)
		if (map[y][x] == 0) return false;
	return true;
}

void BFS(int val)
{
	for (int i = 0; i < pos.size(); ++i)
	{
		if (val & (1 << i)) Q.push({ 0, { pos[i].first, pos[i].second } });
	}
	int max = 0, tmp[51][51];
	bool visited[51][51];
	copyMapA2B(map, tmp);
	while (!Q.empty())
	{
		int time = Q.front().first;
		int y = Q.front().second.first;
		int x = Q.front().second.second; Q.pop();

		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && (map[ny][nx] == 0 || map[ny][nx] == 2))
			{
				if (map[ny][nx] == 0) max = MAX(max, time + 1);
				map[ny][nx] = 3;
				Q.push({ time + 1, {ny, nx} });
			}
		}
	}

	if (noZero()) ans = MIN(ans, max);
	copyMapA2B(tmp, map);
}

void combination(int prev, int val, int cnt)
{
	if (cnt == M)
	{
		BFS(val);
		return;
	}

	for (int i = prev + 1; i < pos.size(); ++i)
	{
		if (val & (1 << i)) continue;
		combination(i, val | (1<<i), cnt + 1);
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int y = 1; y <= N; ++y) for (int x = 1; x <= N; ++x)
	{
		scanf("%d", &map[y][x]);
		if (map[y][x] == 2) pos.push_back({y, x});
	}

	combination(-1, 0, 0);

	printf("%d\n", ans == INF ? -1 : ans);

	return 0;
}