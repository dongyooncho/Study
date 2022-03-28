#include<iostream>
#include<queue>
#define SWAP(a,b) if (a != b) a^=b^=a^=b
#define EAST 0
#define SOUTH 1
#define WEST 2
#define NORTH 3
#define UP 4
#define DOWN 5
using namespace std;

int N, M, K, map[20][20], memo[20][20]; // ����, ���� �� ��� ������ �̸� ����� �迭
int dy[4] = { 0, 1, 0, -1 }, dx[4] = { 1, 0, -1, 0 }, dice[6] = { 3,5,4,2,1,6 }, dice_dir = 0, dice_x = 0, dice_y = 0; // �ֻ����� ����
int front, rear, top, ans;
pair<int, int> q[1000], qq[1000];
bool visited[20][20];
bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= M) return false;
	return true;
}

void BFS(int val)
{
	int cnt = 1;

	while (front != rear)
	{
		int y = q[++front].first;
		int x = q[front].second;

		for (int dir = 0; dir < 4; ++dir)
		{

			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && map[ny][nx] == val && !visited[ny][nx])
			{
				visited[ny][nx] = true; ++cnt;
				q[++rear] = qq[++top] = {ny, nx};
			}
		}
	}
	
	int res = val * cnt;

	while (top != -1)
	{
		int y = qq[top].first;
		int x = qq[top--].second;

		memo[y][x] = res;
	}
}

void roll(int dir)
{
	if (dir == EAST)
	{
		SWAP(dice[UP], dice[EAST]);
		SWAP(dice[DOWN], dice[WEST]);
		SWAP(dice[UP], dice[DOWN]);
	}
	else if (dir == SOUTH)
	{
		SWAP(dice[UP], dice[SOUTH]);
		SWAP(dice[DOWN], dice[NORTH]);
		SWAP(dice[UP], dice[DOWN]);
	}
	else if (dir == WEST)
	{
		SWAP(dice[UP], dice[WEST]);
		SWAP(dice[DOWN], dice[EAST]);
		SWAP(dice[UP], dice[DOWN]);
	}
	else if (dir == NORTH)
	{
		SWAP(dice[UP], dice[NORTH]);
		SWAP(dice[DOWN], dice[SOUTH]);
		SWAP(dice[UP], dice[DOWN]);
	}
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	for (int y = 0; y < N; ++y) for (int x = 0; x < M; ++x)
		scanf("%d", &map[y][x]);
	
	// ���� ���� ���.
	for (int y = 0; y < N; ++y) for (int x = 0; x < M; ++x)
	{
		front = rear = top = -1;
		if (!visited[y][x])
		{
			visited[y][x] = true;
			q[++rear] = {y, x};
			qq[++top] = { y,x };
			BFS(map[y][x]);
		}
	}
	for (int t = 0; t < K; ++t)
	{
		// �ֻ����� ������.
		roll(dice_dir);

		// �ֻ����� ��ġ�� �ٲ۴�.
		dice_y = dice_y + dy[dice_dir];
		dice_x = dice_x + dx[dice_dir];
		
		// ������ ��´�.
		ans += memo[dice_y][dice_x];

		// ���� ���� ������ �����Ѵ�.
		// �ð����
		if (dice[DOWN] > map[dice_y][dice_x]) dice_dir = (dice_dir + 1) % 4;
		// �ݽð����
		else if(dice[DOWN] < map[dice_y][dice_x]) dice_dir = (dice_dir + 3) % 4;
		// ���� ��� �׳� ������.

		int ny = dice_y + dy[dice_dir];
		int nx = dice_x + dx[dice_dir];
		// �ش� �������� ���� �� ���� ��� �ݴ� �������� ������.
		if (!isSafe(ny, nx)) dice_dir = (dice_dir + 2) % 4;
	}
	printf("%d\n", ans);

	return 0;
}