#include<iostream>
#include<string.h>
#include<queue>
#define MAX(a,b) a>b?a:b
using namespace std;
int r, R = 3, c, C = 3, K, ans, map[101][101];

struct Hist {
	int num;
	int cnt;
} hist[101];

struct comp {
	bool operator() (Hist &A, Hist &B)
	{
		if (A.cnt != B.cnt) return A.cnt > B.cnt;
		return A.num > B.num;
	}
};
priority_queue<Hist, vector<Hist>, comp> pq;

void copyMapA2B(int A[][101], int B[][101])
{
	for (int y = 1; y <= R; ++y) for (int x = 1; x <= C; ++x)
		B[y][x] = A[y][x];
}
void sortR()
{
	int maxC = 0, tmp[101][101] = {0,};
	for (int y = 1; y <= R; ++y)
	{
		memset(hist, 0, sizeof(hist));
		for (int x = 1; x <= C; ++x)
		{
			hist[map[y][x]].num = map[y][x];
			++hist[map[y][x]].cnt;
		}
		for (int i = 1; i < 101; ++i)
		{
			if (hist[i].num) pq.push(hist[i]);
		}
		
		int x = 1;
		while (!pq.empty())
		{
			int num = pq.top().num, cnt = pq.top().cnt; pq.pop();
			tmp[y][x++] = num;
			tmp[y][x++] = cnt;
			if (x > 100)
			{
				pq = {};
				break;
			}
		}

		maxC = MAX(maxC, x - 1);
	}

	C = maxC;
	copyMapA2B(tmp, map);
}

void sortC()
{
	int maxR = 0, tmp[101][101] = { 0, };
	for (int x = 1; x <= C; ++x)
	{
		memset(hist, 0, sizeof(hist));
		for (int y = 1; y <= R; ++y)
		{
			hist[map[y][x]].num = map[y][x];
			++hist[map[y][x]].cnt;
		}
		for (int i = 1; i < 101; ++i)
		{
			if (hist[i].num) pq.push(hist[i]);
		}

		int y = 1;
		while (!pq.empty())
		{
			int num = pq.top().num, cnt = pq.top().cnt; pq.pop();
			tmp[y++][x] = num;
			tmp[y++][x] = cnt;
			if (y > 100)
			{
				pq = {};
				break;
			}
		}

		maxR = MAX(maxR, y - 1);
	}

	R = maxR;
	copyMapA2B(tmp, map);
}
void (*func)() = NULL;
void changeFunc()
{
	func = sortC;
	if (R >= C) func = sortR;
}
void sortArr()
{
	func();
}

int main()
{
	scanf("%d %d %d", &r, &c, &K);
	for (int y = 1; y <= R; ++y) for (int x = 1; x <= C; ++x)
		scanf("%d", &map[y][x]);

	while (1)
	{
		if (map[r][c] == K) break;
		++ans;
		if (ans > 100) break;
		changeFunc();
		sortArr();
	}

	printf("%d\n", ans == 101 ? -1 : ans);
	return 0;
}