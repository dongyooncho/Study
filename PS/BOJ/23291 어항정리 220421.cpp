#include<iostream>
#include<queue>
using namespace std;

queue<int> Q;
int N, K; // 어항의 수, 물고기 수의 차이
int arr[100][100], ans; // 어항, 시행횟수
int nextX[100], endPos[100], h[100];
int dy[4] = { 0, 1 }, dx[4] = { 1, 0 };

// 접었을 때 다음 시작점, 끝점을 미리 계산.
void countPos()
{
	nextX[0] = 1; endPos[0] = 1, h[0] = 1;
	int len = 2, cnt = 0;
	for (int i = 1; i < N;)
	{
		h[i] = len;
		nextX[i] = i + len - 1 + cnt;
		endPos[i] = nextX[i] + len - 1;
		++cnt;
		if (cnt == 2)
		{
			cnt = 0;
			++len;
		}
		i = nextX[i];
	}
}

void increaseMin()
{
	int min = 987654321;
	for (int i = 0; i < N; ++i)
	{
		if (min < arr[0][i]) continue;
		if (min > arr[0][i])
		{
			min = arr[0][i];
			Q = {};
		}
		Q.push(i);
	}

	while (!Q.empty())
	{
		++arr[0][Q.front()];
		Q.pop();
	}
}

void stacking()
{
	for (int p = 0; p < N && endPos[p] < N; p = nextX[p])
	{
		for (int x = nextX[p] - 1; x >= p; --x) for (int y = 0; arr[y][x]; ++y)
		{
			Q.push(arr[y][x]);
			arr[y][x] = 0;
		}

		for (int y = 1; !Q.empty(); ++y) for (int x = nextX[p]; x <= endPos[p]; ++x)
		{
			arr[y][x] = Q.front();
			Q.pop();
		}
	}
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}
void press()
{
	int sx = 0, tmp[100][100] = {0, };
	while (!arr[0][sx]) ++sx;

	for (int x = sx; x < N; ++x) for (int y = 0; arr[y][x]; ++y) for (int dir = 0; dir < 2; ++dir)
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (isSafe(ny, nx) && arr[ny][nx])
		{
			int d = (arr[y][x] - arr[ny][nx]) / 5;
			tmp[ny][nx] += d;
			tmp[y][x] -= d;
		}
	}

	for (int x = sx; x < N; ++x) for (int y = 0; arr[y][x]; ++y)
		arr[y][x] += tmp[y][x];

	for (int x = sx; arr[1][x]; ++x) for (int y = 0; arr[y][x]; ++y)
	{
		Q.push(arr[y][x]);
		arr[y][x] = 0;
	}

	for (int x = 0; !Q.empty(); ++x)
	{
		arr[0][x] = Q.front();
		Q.pop();
	}
}

void fold()
{
	int sx = 0;
	for (int h = 0; h < 2; ++h)
	{
		int half = (sx + N) >> 1;
		for (int y = h; y >= 0; --y) for (int x = half - 1; x >= sx; --x)
		{
			Q.push(arr[y][x]);
			arr[y][x] = 0;
		}

		for (int y = h + 1; !Q.empty(); ++y) for (int x = half; x < N; ++x)
		{
			arr[y][x] = Q.front();
			Q.pop();
		}
		sx = half;
	}
}

bool isEnd()
{
	int max = 0, min = 987654321;
	for (int i = 0; i < N; ++i)
	{
		if (max < arr[0][i]) max = arr[0][i];
		if (min > arr[0][i]) min = arr[0][i];
	}

	return (max - min) <= K;
}

int main()
{	
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &arr[0][i]);
	countPos();
	while (1)
	{
		increaseMin();
		stacking();
		press();
		fold();
		press();
		++ans;
		if(isEnd()) break;
	}

	printf("%d\n", ans);

	return 0;
}