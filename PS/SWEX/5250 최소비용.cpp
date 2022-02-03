#include<iostream>
#define MIN(a,b) a<b?a:b
int map[100][100], N, min, dx[4] = { 0,1,0,-1 }, dy[4] = {1,0,-1,0};
int visited[100][100], front, rear;

struct point {
	int nx;
	int ny;
};

point queue[100000];

void init()
{
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			visited[i][j] = 987654321;
}

bool isSafe(int y, int x)
{
	if (y >= 0 && y < N && x >= 0 && x < N) return true;
	return false;
}

void getSome()
{
	++rear;
	queue[rear].ny = 0, queue[rear].nx=0;
	visited[0][0] = 0;
	while (front != rear)
	{
		++front;
		int y = queue[front].ny, x = queue[front].nx;
		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir], nx = x + dx[dir];
			if (isSafe(ny, nx))
			{
				int dif = visited[y][x] + (map[ny][nx] - map[y][x] < 0 ? 0 : map[ny][nx] - map[y][x]) + 1;
				if ((dif) < visited[ny][nx])
				{
					visited[ny][nx] = dif;
					rear++;
					queue[rear].ny = ny, queue[rear].nx=nx;
				}
				
			}
		}
	}
	
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc=1; tc<=T; tc++)
	{
		init();
		min = 987654321;
		scanf("%d", &N);
		for (int y = 0; y < N; y++)
			for (int x = 0; x < N; x++)
				scanf("%d", &map[y][x]);

		getSome();

		printf("#%d %d\n",tc ,visited[N-1][N-1]);
	}
	return 0;
}