#include<iostream>
int N, ans;
int prior[401][4], Q[400];
int map[400][400], score[5] = { 0,1,10,100,1000 }, dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 };

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

int main()
{
	scanf("%d", &N);
	int square = N*N;
	for (int i = 0; i < square; ++i)
	{
		scanf("%d", &Q[i]);
		scanf("%d %d %d %d", &prior[Q[i]][0], &prior[Q[i]][1], &prior[Q[i]][2], &prior[Q[i]][3]);
	}

	for (int i = 0; i < square; ++i)
	{
		int Y = 0, X = 0, max_like = -1, max_blank = -1;
		for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x) 
		{
			if (map[y][x]) continue;
			int like = 0, blank = 0;
			for (int dir = 0; dir < 4; ++dir)
			{
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				if (isSafe(ny, nx))
				{
					if (map[ny][nx] == 0) ++blank;
					else
					{
						for (int j = 0; j < 4; ++j)
							if (map[ny][nx] == prior[Q[i]][j]) ++like;
					}
				}
			}
			if (max_like < like || (max_like == like && max_blank < blank))
			{
				max_like = like;
				max_blank = blank;
				Y = y;
				X = x;
			}
		}
		map[Y][X] = Q[i];
	}

	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		int cnt = 0;
		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (isSafe(ny, nx))
			{
				for (int j = 0; j < 4; ++j)
					if (map[ny][nx] == prior[map[y][x]][j]) ++cnt;
			}
		}
		ans += score[cnt];
	}
	printf("%d\n", ans);

	return 0;
}