#include<iostream>
#include<vector>
using namespace std;

int N, M, ans, m[100], T;
int map[50][50], dy[8] = { 0,-1,-1,-1,0,1,1,1 }, dx[8] = { -1,-1,0,1,1,1,0,-1 };
pair<int, int> tc[100];
vector<pair<int, int>> clouds;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

int getPos(int point)
{
	if (point < 0) return (point + N * 25) % N;
	if (point >= N) return point % N;

	return point;
}

void moveCloud()
{
	int dir = tc[T].first;
	int spd = tc[T].second;

	for (int i = 0; i < clouds.size(); ++i)
	{
		int ny = clouds[i].first + dy[dir] * spd;
		int nx = clouds[i].second + dx[dir] * spd;
		clouds[i].first = getPos(ny);
		clouds[i].second = getPos(nx);
	}
}

void rain(bool visited[][50])
{
	for (int i = 0; i < clouds.size(); ++i)
	{
		int y = clouds[i].first;
		int x = clouds[i].second;
		visited[y][x] = true;
		++map[y][x];
	}
}

void eraseCloud()
{
	// 구름 배열 초기화
	clouds = {};
}

void copyBug()
{
	for (int i =0; i < clouds.size(); ++i) for (int dir = 1; dir < 8; dir += 2)
	{
		int y = clouds[i].first;
		int x = clouds[i].second;
		int ny = y + dy[dir];
		int nx = x + dx[dir];
		// 범위 내에 있고, 물이 있는 칸이면 현재 칸에 물 복사
		if (isSafe(ny, nx) && map[ny][nx]) ++map[y][x];
	}

}

void newCloud(bool visited[][50])
{
	// 구름이 지워진 위치가 아니면서 1보다 크다면 큐에 추가.
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		if (map[y][x] > 1 && !visited[y][x])
		{
			clouds.push_back({ y, x });
			map[y][x] -= 2;
		}
	}
}

void Solve()
{
	bool visited[50][50] = { false, };

	moveCloud();
	rain(visited);
	// 카피에서 구름의 위치를 한번 더 사용하므로 나중에 지운다.
	copyBug();
	eraseCloud();
	newCloud(visited);
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		scanf("%d", &map[y][x]);
	for (int i = 0; i < M; ++i)
	{
		int dir, spd;
		scanf("%d %d", &dir, &spd);
		tc[i].first = dir - 1;
		tc[i].second = spd;
	}
	clouds.push_back({ N - 1, 0 });
	clouds.push_back({ N - 1, 1 });
	clouds.push_back({ N - 2, 0 });
	clouds.push_back({ N - 2, 1 });

	for (T = 0; T < M; ++T)
	{
		Solve();
	}

	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		ans += map[y][x];

	printf("%d\n", ans);
	return 0;
}