#include<iostream>
#include<string.h>
#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
int N, L;
int map[100][100], ans, dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };
bool lamp[100][100];

int ABS(int x)
{
	return x < 0 ? -x : x;
}
bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

bool checkLamp(int y, int x, int dir, int val)
{
	lamp[y][x] = true;
	for (int i = 1; i < L; ++i)
	{
		y += dy[dir];
		x += dx[dir];
		// �̹� ���ΰ� �ְų� ����ų�, ���̰� �ٸ� ��� �Ұ���.
		if (lamp[y][x] || !isSafe(y, x) || map[y][x] != val) return false;
		lamp[y][x] = true;
	}

	return true;
}

bool getSome(int y, int x, int dir)
{	
	for (int i = 1; i < N; ++i)
	{
		int ny = y + dy[dir], nx = x + dx[dir], res = ABS(map[y][x] - map[ny][nx]);
		if (res > 1) return false; // ���� ���̰� 2 �̻��̸� �Ұ���
		else if (res == 1)
		{
			// ���� ��ġ�� ���� ��ġ Ȯ��
			if (map[y][x] < map[ny][nx])
			{
				if (lamp[y][x] || !checkLamp(y, x, (dir + 2) % 4, map[y][x])) return false;
			}
			// ���� ��ġ�� ���� ��ġ Ȯ��
			else
			{
				if (lamp[ny][nx] || !checkLamp(ny, nx, dir, map[ny][nx])) return false;
			}
		}
		y = ny; x = nx;
	}

	return true;
}

int main()
{
	scanf("%d %d", &N, &L);
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		scanf("%d", &map[y][x]);

	for (int y = 0; y < N; ++y)
		if (getSome(y, 0, RIGHT)) ++ans;
	memset(lamp, false, sizeof(lamp));
	for (int x = 0; x < N; ++x)
		if (getSome(0, x, DOWN)) ++ans;

	printf("%d\n", ans);
	return 0;
}