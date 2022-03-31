#include<iostream>
#include<queue>
#include<string.h>
using namespace std;

struct S {
	int y;
	int x;
	int dir; // 현재 방향
	int prior[4][4]; // 방향 별 우선순위
	bool isDel;
} s[401];

int N, M, K, ans, scnt;
int map[20][20], dx[4] = { 0, 0, -1, 1 }, dy[4] = { -1, 1, 0, 0 }; // 상 하 좌 우 순
int history[20][20]; // 냄새가 지워지는 시간을 기록한 테이블

void mInput()
{
	memset(history, -1, sizeof(history));
	scanf("%d %d %d", &N, &M, &K);
	scnt = M; // 총 상어 수
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		scanf("%d", &map[y][x]);
		if (map[y][x])	s[map[y][x]] = { y, x,{ 0, }, false };
	}
	for (int id = 1; id <= M; ++id)
	{
		scanf("%d", &s[id].dir);
		--s[id].dir;
	}
	for (int id = 1; id <= M; ++id)
	{
		for (int dir = 0; dir < 4; ++dir) for (int m = 0; m < 4; ++m)
		{
			scanf("%d", &s[id].prior[dir][m]);
			--s[id].prior[dir][m];
		}
	}
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

bool findPlace(int shark_id, int comp_id)
{
	int y = s[shark_id].y;
	int x = s[shark_id].x;

	for (int i = 0; i < 4; ++i)
	{
		int dir = s[shark_id].prior[s[shark_id].dir][i];
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		// 빈 자리 먼저 탐색
		if (isSafe(ny, nx) && (map[ny][nx] == comp_id))
		{
			s[shark_id].dir = dir;
			s[shark_id].y = ny;
			s[shark_id].x = nx;
			return true;
		}
	}
	
	// 모두 실패 시 false 반환
	return false;
}

void moveShark()
{
	int tmp_map[20][20] = {0,}; // 상어의 이동 후 모습을 임시 저장한 배열

	// id 역순으로 상어를 움직임.
	for (int id = M; id > 0; --id)
	{
		if (s[id].isDel) continue;

		// 현재 자리에 냄새를 남기고 시간을 기록한다.
		map[s[id].y][s[id].x] = id;
		history[s[id].y][s[id].x] = ans + K - 1;

		// 빈 자리 탐색 실패 시 자기가 남긴 냄새 탐색
		if (!findPlace(id, 0))	findPlace(id, id);

		int ny = s[id].y;
		int nx = s[id].x;

		// 이미 자리에 상어가 있다면 쫓아냄.
		if (tmp_map[ny][nx])
		{
			s[tmp_map[ny][nx]].isDel = true;
			--scnt;
		}

		// 탐색 결과 자리로 이동
		tmp_map[ny][nx] = id;
	}
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		if (tmp_map[y][x]) map[y][x] = tmp_map[y][x];
}

void eraseHistory()
{
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		// 현재 시간과 같으면 지워진다.
		if (history[y][x] == ans)
		{
			history[y][x] = 0;
			map[y][x] = 0;
		}
	}
}

int main()
{
	mInput();

	while (ans <= 1000 && scnt > 1)
	{
		moveShark();
		eraseHistory();
		++ans;
	}

	printf("%d\n", ans > 1000 ? -1 : ans);

	return 0;
}
