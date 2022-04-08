#if 0
// 구슬을 차례대로 깨면 오류가 발생할 수 있음. ex ) 오류: 111 3333 1 3333 1 -> 1111 3333 1 -> 1, 실제: 11111 -> 0
// 지나간 구슬은 스택, 다음 구슬은 큐로 관리한다.
#include<iostream>
#include<queue>
#define BLANK 0
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using namespace std;

int N, M, ans, score[4], T;
int map[50][50],  sy, sx, dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };
int Q[10000], front, rear, S[10000], top;
pair<int, int> spell[100];

int turnLeft(int dir)
{
	switch (dir)
	{
	case UP:
		return LEFT;
	case DOWN:
		return RIGHT;
	case LEFT:
		return DOWN;
	case RIGHT:
		return UP;
	}
}

bool movePos(int* y, int* x, int* dir, int* cnt, int* s, int* dist)
{
	// 다음 칸으로 이동
	*y += dy[*dir];
	*x += dx[*dir];
	++(*s);
	if (*s == *dist)
	{
		*s = 0;
		++(*cnt);
		*dir = turnLeft(*dir);
	}
	if (*cnt == 2)
	{
		*cnt = 0;
		++(*dist);
	}

	if (*x < 0) return false;
}

void cast()
{
	int dir = spell[T].first;
	int range = spell[T].second;

	for (int i = 1; i <= range; ++i)
	{
		int ny = sy + dy[dir] * i;
		int nx = sx + dx[dir] * i;
		map[ny][nx] = BLANK;
	}
}

void explode()
{
	front = rear = -1;
	top = 0;
	int y = sy;
	int x = sx - 1;
	int dir = DOWN, cnt = 1, s = 0, dist = 1;

	while (x >= 0)
	{
		// TODO: 로직 작성
		// 빈칸이면 스킵
		if (map[y][x] == BLANK)
		{
			movePos(&y, &x, &dir, &cnt, &s, &dist);
			continue;
		}
		// 큐에 현재 구슬 삽입.
		Q[++rear] = map[y][x];
		map[y][x] = 0;
		// 큐에 있는 구슬과 숫자가 다르면
		if (Q[front + 1] != Q[rear])
		{
			// 모아논 구슬이 4개 이상이면 구슬 폭발 후 해당 구슬 제거
			// 큐에 이미새로운걸 넣었기 때문에 다른 구슬까지 +1 해주어야함
			if (rear - front > 4)
			{
				score[Q[front + 1]] += (rear - front) - 1;
				front = rear - 1;

				// 스택의 맨 위부터 새로 들어온 구슬과 비교하여 같으면 큐로 옮김.
				while (S[top - 1] == Q[rear])
					Q[++rear] = S[--top];
			}
			else
			{	// 큐에 모아놓은 구슬 스택으로 옮김.
				while (front + 1 != rear)
					S[top++] = Q[++front];
			}
		}
		movePos(&y, &x, &dir, &cnt, &s, &dist);
	}
	// 큐에 남은 구슬 확인.
	if (rear - front > 3)
	{
		score[Q[front + 1]] += (rear - front);
		front = rear;
	}

	y = sy;
	x = sx - 1;
	dir = DOWN, cnt = 1, s = 0, dist = 1;
	for (int i = 0; i < top; ++i)
	{
		map[y][x] = S[i];
		movePos(&y, &x, &dir, &cnt, &s, &dist);
	}
	while (front != rear)
	{
		map[y][x] = Q[++front];
		movePos(&y, &x, &dir, &cnt, &s, &dist);
	}
}
void copyMapA2B(int A[][50], int B[][50])
{
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		B[y][x] = A[y][x];
}
void change()
{
	int tmp[50][50] = {0, };
	front = rear = -1;
	int y = sy, dsty = sy;
	int x = sx - 1, dstx = sx - 1;
	int dir = DOWN, dstdir = DOWN, cnt = 1, dstcnt = 1, s = 0, dsts = 0, dist = 1, dstdist = 1;

	while (map[y][x] && dstx >= 0)
	{
		Q[++rear] = map[y][x];
		if (Q[front + 1] != Q[rear])
		{
			tmp[dsty][dstx] = rear - front - 1;
			if (!movePos(&dsty, &dstx, &dstdir, &dstcnt, &dsts, &dstdist))
			{
				copyMapA2B(tmp, map);
				return;
			}
			tmp[dsty][dstx] = Q[front + 1];
			if (!movePos(&dsty, &dstx, &dstdir, &dstcnt, &dsts, &dstdist))
			{
				copyMapA2B(tmp, map);
				return;
			}
			front = rear - 1;
		}
		movePos(&y, &x, &dir, &cnt, &s, &dist);
	}
	// 큐에 남은 구슬 정리
	if (front != rear)
	{
		tmp[dsty][dstx] = rear - front;
		if (!movePos(&dsty, &dstx, &dstdir, &dstcnt, &dsts, &dstdist))
		{
			copyMapA2B(tmp, map);
			return;
		}
		tmp[dsty][dstx] = Q[front + 1];
		front = rear;
	}

	copyMapA2B(tmp, map);
}

int main()
{
	scanf("%d %d", &N, &M);
	sy = sx = N / 2;
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		scanf("%d", &map[y][x]);
	for (int i = 0; i < M; ++i)
	{
		int dir, range;
		scanf("%d %d", &dir, &range);
		spell[i].first = dir - 1;
		spell[i].second = range;
	}

	for (T = 0; T < M; ++T)
	{
		cast();
		explode();
		change();
	}
	for (int i = 1; i < 4; ++i)
		ans += i * score[i];

	printf("%d\n", ans);

	return 0;
}
#endif
#if 1
#include<iostream>
#include<queue>
#define BLANK 0
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using namespace std;

int N, M, ans, score[4], T;
int map[50][50], sy, sx, dy[4] = { -1, 1, 0, 0 }, dx[4] = { 0, 0, -1, 1 };
int Q[10000], front, rear, S[10000], top;
pair<int, int> spell[100];

int turnLeft(int dir)
{
	switch (dir)
	{
	case UP:
		return LEFT;
	case DOWN:
		return RIGHT;
	case LEFT:
		return DOWN;
	case RIGHT:
		return UP;
	}
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= N || x >= N) return false;
	return true;
}

bool movePos(int* y, int* x, int* dir, int* cnt, int* s, int* dist)
{
	// 다음 칸으로 이동
	*y += dy[*dir];
	*x += dx[*dir];
	++(*s);
	if (*s == *dist)
	{
		*s = 0;
		++(*cnt);
		*dir = turnLeft(*dir);
	}
	if (*cnt == 2)
	{
		*cnt = 0;
		++(*dist);
	}

	return isSafe(*y, *x);
}

void cast()
{
	int dir = spell[T].first;
	int range = spell[T].second;

	for (int i = 1; i <= range; ++i)
	{
		int ny = sy + dy[dir] * i;
		int nx = sx + dx[dir] * i;
		map[ny][nx] = BLANK;
	}
}

bool explode()
{
	bool boom = false;
	front = rear = -1;
	top = 0;
	int y = sy;
	int x = sx - 1;
	int dir = DOWN, cnt = 1, s = 0, dist = 1;

	while (x >= 0)
	{
		// 빈칸이면 스킵
		if (map[y][x] == BLANK)
		{
			movePos(&y, &x, &dir, &cnt, &s, &dist);
			continue;
		}
		// 큐에 있는 구슬과 숫자가 다르면
		if (Q[front + 1] != map[y][x])
		{
			// 모아논 구슬이 4개 이상이면 구슬 폭발 후 해당 구슬 제거
			if (rear - front > 3)
			{
				ans += (Q[front + 1] * (rear - front));
				boom = true;
				front = rear;
			}
			else
			{	// 큐에 모아놓은 구슬 스택으로 옮김.
				while (front != rear)
					S[top++] = Q[++front];
			}
		}
		// 큐에 현재 구슬 삽입.
		Q[++rear] = map[y][x];
		map[y][x] = 0;
		// 커서 이동
		movePos(&y, &x, &dir, &cnt, &s, &dist);
	}
	// 큐에 남은 구슬 확인.
	if (rear - front > 3)
	{
		ans += (Q[front + 1] * (rear - front));
		boom = true;
		front = rear;
	}
	// 4개보다 적으면 모두 스택으로 옮김
	else
		while (front != rear)
			S[top++] = Q[++front];

	y = sy;
	x = sx - 1;
	dir = DOWN, cnt = 1, s = 0, dist = 1;
	for (int i = 0; i < top; ++i)
	{
		map[y][x] = S[i];
		movePos(&y, &x, &dir, &cnt, &s, &dist);
	}

	return boom;
}
void copyMapA2B(int A[][50], int B[][50])
{
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		B[y][x] = A[y][x];
}

void change()
{
	int tmp[50][50] = { 0, };
	front = rear = -1;
	int y = sy, dsty = sy;
	int x = sx - 1, dstx = sx - 1;
	int dir = DOWN, dstdir = DOWN, cnt = 1, dstcnt = 1, s = 0, dsts = 0, dist = 1, dstdist = 1;
	int prev = map[y][x], now = map[y][x], same = 0;
	while (map[y][x] && dstx >= 0)
	{
		if (Q[front + 1] != map[y][x])
		{
			tmp[dsty][dstx] = rear - front;
			movePos(&dsty, &dstx, &dstdir, &dstcnt, &dsts, &dstdist);

			tmp[dsty][dstx] = Q[front + 1];
			if (!movePos(&dsty, &dstx, &dstdir, &dstcnt, &dsts, &dstdist))
			{
				copyMapA2B(tmp, map);
				return;
			}
			front = rear;
		}
		Q[++rear] = map[y][x];
		movePos(&y, &x, &dir, &cnt, &s, &dist);
	}
	// 큐에 남은 구슬 정리
	tmp[dsty][dstx] = rear - front;
	movePos(&dsty, &dstx, &dstdir, &dstcnt, &dsts, &dstdist);

	tmp[dsty][dstx] = Q[front + 1];

	copyMapA2B(tmp, map);
}

int main()
{
	scanf("%d %d", &N, &M);
	sy = sx = N / 2;
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		scanf("%d", &map[y][x]);
	for (int i = 0; i < M; ++i)
	{
		int dir, range;
		scanf("%d %d", &dir, &range);
		spell[i].first = dir - 1;
		spell[i].second = range;
	}

	for (T = 0; T < M; ++T)
	{
		cast();
		while(explode());
		change();
	}

	printf("%d\n", ans);

	return 0;
}
#endif