#if 0
// �Ź� BFS Ž�� 8ms.
#include<iostream>
#include<queue>
#define SWAP(a, b) if (a!=b) a^=b^=a^=b
#define E 0
#define S 1
#define W 2
#define N 3
#define U 4
#define D 5
using namespace std;

int R, C, K, ans, map[20][20], dx[4] = { 1, 0, -1, 0 }, dy[4] = {0, 1, 0, -1};
int dice[6] = {3, 5, 4, 2, 1, 6}, Y, X, dir = 0;
queue<pair<int, int>> Q;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= R || x >= C) return false;
	return true;
}

void getScore(int y, int x, int num)
{
	int res = num;
	bool visited[20][20] = { false, };
	Q.push({y, x});
	visited[y][x] = true;

	while (!Q.empty())
	{
		int y = Q.front().first;
		int x = Q.front().second; Q.pop();

		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx] && map[ny][nx] == num)
			{
				res += num;
				visited[ny][nx] = true;
				Q.push({ny, nx});
			}
		}
	}

	ans += res;
}

void roll()
{

	if (!isSafe(Y + dy[dir], X + dx[dir]))	dir = (dir + 2) % 4;

	Y += dy[dir]; X += dx[dir];
	switch (dir)
	{
	case E:
		SWAP(dice[U], dice[E]);
		SWAP(dice[D], dice[W]);
		break;
	case S:
		SWAP(dice[U], dice[S]);
		SWAP(dice[D], dice[N]);
		break;
	case W:
		SWAP(dice[U], dice[W]);
		SWAP(dice[D], dice[E]);
		break;
	case N:
		SWAP(dice[U], dice[N]);
		SWAP(dice[D], dice[S]);
		break;
	}
	SWAP(dice[U], dice[D]);

	getScore(Y, X, map[Y][X]);
}

int turnDir(int dir)
{
	// �ݽð�
	if (map[Y][X] > dice[D])
	{
		switch (dir)
		{
		case E:
			return N;
		case S:
			return E;
		case W:
			return S;
		case N:
			return W;
		}
	}
	// �ð�
	else if (map[Y][X] < dice[D])
	{
		switch (dir)
		{
		case E:
			return S;
		case S:
			return W;
		case W:
			return N;
		case N:
			return E;
		}
	}
	// ���� ����
	else return dir;
}

int main()
{
	scanf("%d %d %d", &R, &C, &K);
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
		scanf("%d", &map[y][x]);

	for (int i = 0; i < K; ++i)
	{
		roll();
		dir = turnDir(dir);
	}

	printf("%d\n", ans);
	return 0;
}
#endif
#if 1
// BFS Ž�� �� ���. 0ms
#include<iostream>
#include<queue>
#define SWAP(a, b) if (a!=b) a^=b^=a^=b
#define E 0
#define S 1
#define W 2
#define N 3
#define U 4
#define D 5
using namespace std;

int R, C, K, ans, map[20][20], dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };
int dice[6] = { 3, 5, 4, 2, 1, 6 }, Y, X, dir = 0, score[20][20];
bool visited[20][20];
queue<pair<int, int>> Q;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= R || x >= C) return false;
	return true;
}

void BFS(int sy, int sx)
{
	queue<pair<int, int>> tmp;
	int res = map[sy][sx];
	Q.push({ sy, sx }); tmp.push({ sy, sx });
	while (!Q.empty())
	{
		int y = Q.front().first;
		int x = Q.front().second; Q.pop();

		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];
			if (isSafe(ny, nx) && map[ny][nx] == map[sy][sx] && !visited[ny][nx])
			{
				visited[ny][nx] = true;
				res += map[ny][nx];
				Q.push({ ny, nx }); tmp.push({ ny, nx });
			}
		}
	}

	while (!tmp.empty())
	{
		int y = tmp.front().first;
		int x = tmp.front().second; tmp.pop();
		score[y][x] = res;
	}
}

void getScore()
{
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
	{
		if (!visited[y][x])
		{
			visited[y][x] = true;
			BFS(y, x);
		}
	}
}

void roll()
{
	// �ֻ��� ȸ��
	switch (dir)
	{
	case E:
		SWAP(dice[U], dice[E]);
		SWAP(dice[D], dice[W]);
		break;
	case S:
		SWAP(dice[U], dice[S]);
		SWAP(dice[D], dice[N]);
		break;
	case W:
		SWAP(dice[U], dice[W]);
		SWAP(dice[D], dice[E]);
		break;
	case N:
		SWAP(dice[U], dice[N]);
		SWAP(dice[D], dice[S]);
		break;
	}
	SWAP(dice[U], dice[D]);

	// �ֻ��� �̵�
	Y += dy[dir]; X += dx[dir];
	// ���� ���
	ans += score[Y][X];
}

void turnDir()
{
	// �ݽð�
	if (map[Y][X] > dice[D])
	{
		switch (dir)
		{
		case E:
			dir = N;
			break;
		case S:
			dir = E;
			break;
		case W:
			dir = S;
			break;
		case N:
			dir = W;
			break;
		}
	}
	// �ð�
	else if (map[Y][X] < dice[D])
	{
		switch (dir)
		{
		case E:
			dir = S;
			break;
		case S:
			dir = W;
			break;
		case W:
			dir = N; 
			break;
		case N:
			dir = E; 
			break;
		}
	}
	
	// ���� ����� �ݴ�������� ����
	if (!isSafe(Y + dy[dir], X + dx[dir])) dir = (dir + 2) % 4;
}

int main()
{
	scanf("%d %d %d", &R, &C, &K);
	for (int y = 0; y < R; ++y) for (int x = 0; x < C; ++x)
		scanf("%d", &map[y][x]);

	getScore();

	for (int i = 0; i < K; ++i)
	{
		roll();
		turnDir();
	}

	printf("%d\n", ans);
	return 0;
}
#endif