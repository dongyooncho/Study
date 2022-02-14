#include<iostream>
#include<string.h>
#define INF 10002
int N, map[100][100], dist[100][100], dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };
int Qx[10001], Qy[10001], front, rear;

void init()
{
	front = rear = -1;
	for (register int i = 0; i < N; ++i)
		memset(dist[i], INF, 4*N);
}

bool isSafe(int y, int x)
{
	return (y < 0 || x < 0 || y >= N || x >= N) ? false : true;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		scanf("%d ", &N);
		init();
		for (int y = 0; y < N; ++y)
			for (int x = 0; x < N; ++x)
			{
				char num;
				scanf("%c ", &num);
				map[y][x] = num - '0';
			}

		Qx[++rear] = 0;
		Qy[rear] = 0;
		dist[0][0] = 0;

		while (front != rear)
		{
			front = (front + 1) % 10001;
			int y = Qy[front];
			int x = Qx[front];

			for (int dir = 0; dir < 4; ++dir)
			{
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				if (isSafe(ny, nx) && dist[ny][nx] > (dist[y][x] + map[ny][nx]))
				{
					dist[ny][nx] = (dist[y][x] + map[ny][nx]);
					rear = (rear + 1) % 10001;
					Qy[rear] = ny;
					Qx[rear] = nx;
				}
			}
		}

		printf("#%d %d\n", tc, dist[N-1][N-1]);
	}
	return 0;
}