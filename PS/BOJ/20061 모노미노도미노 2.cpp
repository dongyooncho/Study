#include<iostream>
#include<queue>
using namespace std;

int N, ans, ans2;
int T[10000], Y[10000], X[10000], tc;
bool blue[4][6], green[6][4];
queue<bool> BQ, GQ;
queue<int> BBQ, GBQ;
void putBlock()
{
	int sy = 5, sx = 5, y = 5, x = 5;

	if (T[tc] == 1)
	{
		while (x >= 2)
		{
			if (blue[Y[tc]][x]) sx = x - 1;
			--x;
		}
		BBQ.push(sx);
		blue[Y[tc]][sx] = true;
	}
	else if (T[tc] == 2)
	{
		while (x >= 2)
		{
			if (blue[Y[tc]][x]) sx = x - 1;
			--x;
		}
		BBQ.push(sx); BBQ.push(sx - 1);
		blue[Y[tc]][sx] = blue[Y[tc]][sx - 1] = true;
	}
	else
	{
		while (x >= 2)
		{
			if (blue[Y[tc]][x] || blue[Y[tc] + 1][x]) sx = x - 1;
			--x;
		}
		BBQ.push(sx);
		blue[Y[tc]][sx] = blue[Y[tc] + 1][sx] = true;
	}

	if (T[tc] == 1)
	{
		while (y >= 2)
		{
			if (green[y][X[tc]]) sy = y - 1;
			--y;
		}
		GBQ.push(sy);
		green[sy][X[tc]] = true;
	}
	else if (T[tc] == 2)
	{
		while (y >= 2)
		{
			if (green[y][X[tc]] || green[y][X[tc] + 1]) sy = y - 1;
			--y;
		}
		GBQ.push(sy);
		green[sy][X[tc]] = green[sy][X[tc] + 1] = true;
	}
	else
	{
		while (y >= 2)
		{
			if (green[y][X[tc]]) sy = y - 1;
			--y;
		}
		GBQ.push(sy); GBQ.push(sy - 1);
		green[sy][X[tc]] = green[sy - 1][X[tc]] = true;
	}
}

void boomBlock()
{
	queue<int> Q;
	int b_start = BBQ.front(), g_start = GBQ.front();
	while (!BBQ.empty())
	{
		int x = BBQ.front(); BBQ.pop();
		bool isFull = true;
		for (int y = 0; y < 4; ++y)
			if (!blue[y][x]) isFull = false;
		
		if (isFull) Q.push(x);
	}
	if (Q.size())
	{
		int size = Q.size();
		int sx = Q.front();
		Q = {};
		ans += size;

		for (int y = 0; y < 4; ++y)
		{
			for (int x = sx - size; x >= 0; --x)
			{
				Q.push(blue[y][x]); blue[y][x] = false;
			}

			for (int x = sx; !Q.empty(); --x)
			{
				blue[y][x] = Q.front(); Q.pop();
			}
		}
	}

	while (!GBQ.empty())
	{
		int y = GBQ.front(); GBQ.pop();
		bool isFull = true;
		for (int x = 0; x < 4; ++x)
			if (!green[y][x]) isFull = false;

		if (isFull) Q.push(y);
	}

	if (Q.size())
	{
		int size = Q.size();
		int sy = Q.front();
		Q = {};
		ans += size;

		for (int x = 0; x < 4; ++x)
		{
			for (int y = sy - size; y >= 0; --y)
			{
				Q.push(green[y][x]); green[y][x] = false;
			}

			for (int y = sy; !Q.empty(); --y)
			{
				green[y][x] = Q.front(); Q.pop();
			}
		}
	}
}

void eraseBlock()
{
	queue<int> Q;
	int cnt = 0;

	for (int x = 0; x < 2; ++x)
	{
		bool isErase = false;
		for (int y = 0; y < 4; ++y)
			if (blue[y][x]) isErase = true;

		if (isErase) ++cnt;
	}

	if (cnt)
	{
		int sx = 5;
		for (int y = 0; y < 4; ++y)
		{
			for (int x = sx - cnt; x >= 0; --x)
			{
				Q.push(blue[y][x]); blue[y][x] = false;
			}

			for (int x = sx; !Q.empty(); --x)
			{
				blue[y][x] = Q.front(); Q.pop();
			}
		}

		cnt = 0;
	}

	for (int y = 0; y < 2; ++y)
	{
		bool isErase = false;
		for (int x = 0; x < 4; ++x)
			if (green[y][x]) isErase = true;

		if (isErase) ++cnt;
	}

	if (cnt)
	{
		int sy = 5;
		for (int x = 0; x < 4; ++x)
		{
			for (int y = sy - cnt; y >= 0; --y)
			{
				Q.push(green[y][x]); green[y][x] = false;
			}

			for (int y = sy; !Q.empty(); --y)
			{
				green[y][x] = Q.front(); Q.pop();
			}
		}
		cnt = 0;
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d %d %d", &T[i], &Y[i], &X[i]);

	for (tc = 0; tc < N; ++tc)
	{
		putBlock();
		boomBlock();
		eraseBlock();
	}
	for (int y = 0; y < 4; ++y) for (int x = 2; x < 6; ++x)
		if (blue[y][x]) ++ans2;
	for (int x = 0; x < 4; ++x) for (int y = 2; y < 6; ++y)
		if (green[y][x]) ++ans2;
	printf("%d\n", ans);
	printf("%d\n", ans2);
	return 0;
}