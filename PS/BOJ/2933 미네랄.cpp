#if 0
/** Case 1
 *  한 칸씩 떨어뜨리기
 */
#include <iostream>
#include <queue>
#define MIN(a, b) a < b ? a : b
using namespace std;

int R, C, N, H[100], dx[4] = { 1,0,-1,0 }, dy[4] = { 0, 1, 0, -1 };
char map[102][102];
bool visited[102][102];

queue<pair<int, int>> Q;

void Input()
{
	scanf("%d %d", &R, &C);

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			scanf(" %c", &map[r][c]);

	for (int c = 1; c <= C; c++)
		map[R + 1][c] = 'x'; // 바닥 x 패딩

	for (int r = 1; r <= R; r++)
		map[r][0] = '.';

	scanf(" %d", &N);

	for (int i = 0; i < N; i++)
		scanf(" %d", &H[i]);
}

void Throw(int count)
{
	int height = R - H[count] + 1;

	if (count % 2 == 0)
	{
		for (int i = 1; i <= C; i++)
		{
			if (map[height][i] == 'x')
			{
				map[height][i] = '.';
				return;
			}
		}
	}
	else
	{
		for (int i = C; i >= 1; i--)
		{
			if (map[height][i] == 'x')
			{
				map[height][i] = '.';
				return;
			}
		}
	}
}

void init()
{
	for (int y = 1; y <= R + 1; y++)
		for (int x = 1; x <= C; x++)
			visited[y][x] = false;
}

bool isSafe(int y, int x)
{
	if (y < 1 || x < 1 || y > R + 1 || x > C) return false;
	return true;
}

void Gravity()
{
	init();

	Q.push({ R + 1, 1 });

	while (!Q.empty()) // 떨어진 클러스터 찾기
	{
		int y = Q.front().first;
		int x = Q.front().second;

		Q.pop();
		visited[y][x] = true;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx] && map[ny][nx] == 'x')
			{
				visited[ny][nx] = true;
				Q.push({ ny, nx });
			}
		}
	}

	int min_height = 200;
	for (int x = 1; x <= C; x++)
	{
		int h = 0;
		for (int y = R; y >= 1; y--)
		{
			if (visited[y][x])
			{
				h = 0;
				continue;
			}

			if (map[y][x] == 'x')
			{
				if (h == 0) continue; // 같은 클러스터임.
				min_height = MIN(min_height, h);
			}
			h++;
		}
	}

	if (min_height != 200)
	{
		queue<char> char_Q;
		for (int x = 1; x <= C; x++)
		{
			int sy = R;
			while (isSafe(sy, x) && map[sy][x] == 'x') sy--;

			if (isSafe(sy, x))
			{
				for (int y = sy; y >= 1; y--)
				{
					if (!visited[y][x])
					{
						char_Q.push(map[y][x]);
						map[y][x] = '.';
					}
					else
					{
						for (int i = 0; i < min_height && !char_Q.empty(); i++) char_Q.pop();

						for (int pop_y = sy; !char_Q.empty(); pop_y--)
						{
							map[pop_y][x] = char_Q.front();
							char_Q.pop();
						}

						sy = y - 1;
					}
				}

				for (int i = 0; i < min_height; i++) char_Q.pop();

				for (int pop_y = sy; pop_y >= 1 && !char_Q.empty(); pop_y--)
				{
					map[pop_y][x] = char_Q.front();
					char_Q.pop();
				}
			}
		}
	}
}

void printMap()
{
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
			printf("%c", map[r][c]);

		printf("\n");
	}
}

void Solve()
{
	for (int count = 0; count < N; count++)
	{
		Throw(count);
		Gravity();
	}

	printMap();
}

int main()
{
	Input();
	Solve();

	return 0;
}
#endif
#if 1
/** Case 2
 *  큐를 이용해 한번에 이동
 */
#include <iostream>
#include <queue>
#define MIN(a, b) a < b ? a : b
using namespace std;

int R, C, N, H[100], dx[4] = { 1,0,-1,0 }, dy[4] = { 0, 1, 0, -1 };
char map[102][102];
bool visited[102][102];

queue<pair<int, int>> Q;

void Input()
{
	scanf("%d %d", &R, &C);

	for (int r = 1; r <= R; r++)
		for (int c = 1; c <= C; c++)
			scanf(" %c", &map[r][c]);

	for (int c = 1; c <= C; c++)
		map[R + 1][c] = 'x'; // 바닥 x 패딩

	for (int r = 1; r <= R; r++)
		map[r][0] = '.';

	scanf(" %d", &N);

	for (int i = 0; i < N; i++)
		scanf(" %d", &H[i]);
}

void Throw(int count)
{
	int height = R - H[count] + 1;

	if (count % 2 == 0)
	{
		for (int i = 1; i <= C; i++)
		{
			if (map[height][i] == 'x')
			{
				map[height][i] = '.';
				return;
			}
		}
	}
	else
	{
		for (int i = C; i >= 1; i--)
		{
			if (map[height][i] == 'x')
			{
				map[height][i] = '.';
				return;
			}
		}
	}
}

void init()
{
	for (int y = 1; y <= R + 1; y++)
		for (int x = 1; x <= C; x++)
			visited[y][x] = false;
}

bool isSafe(int y, int x)
{
	if (y < 1 || x < 1 || y > R + 1 || x > C) return false;
	return true;
}

void printMap()
{
	for (int r = 1; r <= R; r++)
	{
		for (int c = 1; c <= C; c++)
			printf("%c", map[r][c]);

		printf("\n");
	}
}

void Gravity()
{
	init();

	Q.push({ R + 1, 1 });

	while (!Q.empty()) // 떨어진 클러스터 찾기
	{
		int y = Q.front().first;
		int x = Q.front().second;

		Q.pop();
		visited[y][x] = true;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx] && map[ny][nx] == 'x')
			{
				visited[ny][nx] = true;
				Q.push({ ny, nx });
			}
		}
	}

	int min_height = 200;
	for (int x = 1; x <= C; x++)
	{
		int h = 0;
		for (int y = R; y >= 1; y--)
		{
			if (visited[y][x])
			{
				h = 0;
				continue;
			}

			if (map[y][x] == 'x')
			{
				if (h == 0) continue; // 같은 클러스터임.
				min_height = MIN(min_height, h);
			}
			h++;
		}
	}

	for (int y = 1; y<= R; y++)
		for (int x = 1; x <= C; x++)
		{
			if (map[y][x] == 'x' && !visited[y][x])
			{
				Q.push({y, x});
				map[y][x] = '.';
			}
		}

	if (min_height != 200)
	{
		while (!Q.empty())
		{
			map[Q.front().first + min_height][Q.front().second] = 'x';
			Q.pop();
		}
	}
}

void Solve()
{
	for (int count = 0; count < N; count++)
	{
		Throw(count);
		Gravity();
	}

	printMap();
}

int main()
{
	Input();
	Solve();

	return 0;
}
#endif