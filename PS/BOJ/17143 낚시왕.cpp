#include<iostream>
#include<vector>
using namespace std;

int R, C, M, ans;
int dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, 1, -1 }; // 상 하 우 좌
int map[101][101];

struct S {
	int spd;
	int dir;
	int size;
	bool isDel;
} s[10001];

void copyMapA2B(int A[][101], int B[][101])
{
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
		B[y][x] = A[y][x];
}

int tiltDir(int dir)
{
	return dir % 2 ? dir - 1 : dir + 1;
}

void fishing(int x)
{
	for (int y = 0; y < R; ++y)
		if (map[y][x])
		{
			int now = map[y][x]; map[y][x] = 0;
			ans += s[now].size;
			s[now].isDel = true;
			break;
		}
}

void moveShark()
{
	int tmp[101][101] = {0,};
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
	{
		int now = map[y][x];
		if (now)
		{
			// 상하이동
			if (s[now].dir < 2)
			{
				int ny = y + dy[s[now].dir] * s[now].spd;
				int cnt = 0, div = 0, mod = 0;

				div = ny / (R - 1);

				mod = (ny) % (R - 1);
				mod = (mod + (R - 1)) % (R - 1);
				if (ny < 0 && mod)
					div--;
				if (div % 2)
				{
					ny = (R - 1) - mod;
					s[now].dir = tiltDir(s[now].dir);
				}
				else ny = mod;

				if (tmp[ny][x])
				{
					int opp = tmp[ny][x];
					if (s[now].size > s[opp].size)
					{
						s[opp].isDel = true;
						tmp[ny][x] = now;
					}
					else s[now].isDel = true;
				}
				else
					tmp[ny][x] = now;
			}
			else
			{
				int nx = x + dx[s[now].dir] * s[now].spd;
				int cnt = 0, div = 0, mod = 0;

				div = nx / (C - 1);

				mod = (nx) % (C - 1);
				mod = (mod + (C - 1)) % (C - 1);
				if (nx < 0 && mod)
					div--;

				if (div % 2)
				{
					nx = (C - 1) - mod;
					s[now].dir = tiltDir(s[now].dir);
				}
				else nx = mod;

				if (tmp[y][nx])
				{
					int opp = tmp[y][nx];
					if (s[now].size > s[opp].size)
					{
						s[opp].isDel = true;
						tmp[y][nx] = now;
					}
					else s[now].isDel = true;
				}
				else
					tmp[y][nx] = now;
			}
			
		}
	}
	copyMapA2B(tmp, map);
}

int main()
{
	scanf("%d %d %d", &R, &C, &M);
	for (int i = 1; i <= M; ++i)
	{
		int y, x, spd, dir, size;
		scanf("%d %d %d %d %d", &y, &x, &spd, &dir, &size);
		s[i].dir = dir - 1;
		s[i].spd = spd;
		s[i].size = size;
		s[i].isDel = false;
		map[y - 1][x - 1] = i;
	}

	for (int i = 0; i < C; ++i)
	{
		fishing(i);
		moveShark();
	}

	printf("%d\n", ans);
	return 0;
}