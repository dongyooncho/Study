#include<iostream>
#include<algorithm>
#include<queue>
#define MAX(a,b) a>b?a:b
#define WHITE 0
#define RED 1
#define BLUE 2
using namespace std;

struct Piece {
	int y;
	int x;
	int dir;
} p[11];

int N, K, map[13][13], ans; // 쌓인 개수를 세는 변수
int dy[4] = { 0, 0, -1, 1 }, dx[4] = { 1, -1, 0, 0 }; // 우 좌 상 하 순서
vector<Piece *> group[13][13];

// 방향을 반대로 바꾸는 함수. 맵을 벗어나거나 파란색 맵일 때 사용
int tiltDir(int dir)
{
	return dir % 2 ? dir - 1 : dir + 1;
}

bool canReach(int y, int x)
{
	if (y < 1 || x < 1 || y > N || x > N || map[y][x] == BLUE) return false;
	return true;
}

bool movePiece()
{
	bool isEnd = false;
	for (int i = 1; i <= K; ++i)
	{
		int y = p[i].y, x = p[i].x;
		int ny = y + dy[p[i].dir];
		int nx = x + dx[p[i].dir];
		
		// 맵을 벗어나거나, 파란 바닥인 경우
		if (!canReach(ny, nx))
		{
			p[i].dir = tiltDir(p[i].dir);
			ny = y + dy[p[i].dir];
			nx = x + dx[p[i].dir];
			// 반대 방향도 갈 수 없다면
			if (!canReach(ny, nx)) continue;
		}

		int s = 0, e = group[y][x].size();
		// find
		for (int j = s; j < e; ++j)
			if (group[y][x][j] == &p[i])
			{
				s = j;
				break;
			}
		
		if (map[ny][nx] == RED)
		{
			// SWAP
			for (int l = s, r = e - 1; l < r; ++l, --r)
			{
				Piece *buf = group[y][x][l];
				group[y][x][l] = group[y][x][r];
				group[y][x][r] = buf;
			}
		}

		vector<Piece *> tmp = {};
		for (int j = 0; j < s; ++j)
			tmp.push_back(group[y][x][j]);
		for (int j = s; j < e; ++j)
		{
			group[y][x][j]->y = ny; group[y][x][j]->x = nx;
			group[ny][nx].push_back(group[y][x][j]);
		}
		
		group[y][x] = tmp;
		if (group[ny][nx].size() > 3)
		{
			isEnd = true;
			break;
		}
	}
	return isEnd;
}

int main()
{
	scanf("%d %d", &N, &K);
	for (int y = 1; y <= N; ++y) for (int x = 1; x <= N; ++x)
		scanf("%d", &map[y][x]);
	for (int id = 1; id <= K; ++id)
	{
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		p[id].dir = dir - 1;
		p[id].y = y;
		p[id].x = x;

		group[y][x].push_back(&p[id]);
	}

	while (ans <= 1000)
	{
		++ans;
		if (movePiece()) break;
	}

	printf("%d\n", ans == 1001 ? -1 : ans);
	return 0;
}