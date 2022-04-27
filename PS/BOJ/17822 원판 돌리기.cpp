#include<iostream>
#define CW 0
#define CCW 1
int N, M, T, ans, tc;
int X[50], D[50], K[50];
int disk[51][50], head[51];

int turnDisk(int pos, int dir, int cnt)
{
	// 시계
	if (dir == CW)
	{
		return (pos - cnt + M) % M;
	}
	// 반시계
	else if (dir == CCW)
	{
		return (pos + cnt) % M;
	}
}

void turn()
{
	int x = X[tc], d = D[tc], k = K[tc];
	// x의 배수 선택
	for (int radius = x; radius <= N; radius += x)
		head[radius] = turnDisk(head[radius], d, k);
}

bool erase()
{
	bool res = false, visited[51][50] = { false, };
	for (int radius = 1; radius <= N; ++radius) for (int i = 0; i < M; ++i)
	{
		int cw = (i + 1) % M, ccw = (i + M - 1) % M;
		// 좌우비교
		if (disk[radius][i])
		{
			if (disk[radius][cw] == disk[radius][i]) visited[radius][i] = visited[radius][cw] = true;
			if (disk[radius][ccw] == disk[radius][i]) visited[radius][i] = visited[radius][ccw] = true;
		}
		// 큰 디스크와 비교
		if (radius == N) continue; // 마지막 디스크는 비교 대상이 없음
		int small_cursor = (head[radius] + i) % M, large_cursor = ((head[radius + 1] + i) % M);
		if (disk[radius][small_cursor])
		{
			if (disk[radius][small_cursor] == disk[radius + 1][large_cursor]) visited[radius][small_cursor] = visited[radius + 1][large_cursor] = true;
		}
	}

	for (int radius = 1; radius <= N; ++radius) for (int i = 0; i < M; ++i)
		if (visited[radius][i])
		{
			res = true;
			disk[radius][i] = 0;
		}
	return res;
}

void getAvg()
{
	int cnt = 0, sum = 0;
	double avg = 0;
	for (int r = 1; r <= N; ++r) for (int i = 0; i < M; ++i)
		if (disk[r][i])
		{
			++cnt;
			sum += disk[r][i];
		}

	avg = (double)sum / cnt;
	for (int r = 1; r <= N; ++r) for (int i = 0; i < M; ++i)
		if (disk[r][i])
		{
			if (disk[r][i] < avg) ++disk[r][i];
			else if (disk[r][i] > avg) --disk[r][i];
		}
}

int main()
{
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 1; i <= N; ++i) for (int j = 0; j < M; ++j)
		scanf("%d", &disk[i][j]);

	for (int i = 0; i < T; ++i)
		scanf("%d %d %d", &X[i], &D[i], &K[i]);

	for (tc = 0; tc < T; ++tc)
	{
		turn();
		if(!erase())
			getAvg();
	}
	for (int r = 1; r <= N; ++r) for (int i = 0; i < M; ++i)
		if (disk[r][i]) ans += disk[r][i];
	printf("%d\n", ans);
	return 0;
}