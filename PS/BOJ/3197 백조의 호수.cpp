#if 0
/** Case 1
 *  중복된 BFS 탐색
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, time, map[1500][1500], dy[4] = { 0,1,0,-1 }, dx[4] = {1,0,-1,0};
bool visited[1500][1500]; // 백조 간 탐색 확인 배열
bool checked[1500][1500]; // 물 주변의 얼음이 녹았는지 확인하는 배열
bool melted[1500][1500]; // 녹은 얼음을 체크하는 배열
bool is_end; // 백조끼리 맞닿았는지 확인하는 변수.
vector<pair<int, int>> swan;
queue<pair<int, int>> q;

void init()
{
	for (int i = 0; i < 1500; i++)
		for (int j = 0; j < 1500; j++)
			visited[i][j] = checked[i][j] = melted[i][j] = 0;
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= R || x >= C) return false;
	return true;
}

void checkMeet()
{
	pair<int, int> s1 = swan.front();
	visited[s1.first][s1.second] = true;
	q.push(s1);

	while (q.size())
	{
		pair<int, int> point = q.front();
		int y = point.first, x = point.second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx] && map[ny][nx] != 1)
			{
				if (map[ny][nx] == 2)
				{
					is_end = true;
					return;
				}
				else
				{
					visited[ny][nx] = true;
					q.push({ny, nx});
				}
			}
		}
	}
}

void melting()
{
	while (q.size())
	{
		pair<int, int> point = q.front();
		int y = point.first;
		int x = point.second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !checked[ny][nx])
			{
				if (map[ny][nx] == 1)
				{
					melted[ny][nx] = true;
				}
				else
				{
					checked[ny][nx] = true;
					q.push({ ny, nx });
				}
			}
		}
	}
}

void doSome()
{
	for (int y = 0; y < R; y++)
		for (int x = 0; x < C; x++)
			if (melted[y][x])
				map[y][x] = 0;
}

int main()
{
	scanf("%d %d", &R, &C);

	// 맵 입력: 물 0, 얼음 1, 백조 2
	for(int r = 0 ; r < R; r++)
		for (int c = 0; c < C; c++)
		{
			char ch;
			scanf(" %c", &ch);
			if (ch == 'L')
			{
				swan.push_back({ r, c });
				map[r][c] = 2;
			}
			else map[r][c] = ch == 'X' ? 1 : 0;
		}

	for (time = 0; ;time++)
	{
		init();

		checkMeet();
		if (is_end) break;

		for (int y = 0; y<R; y++)
			for (int x = 0; x < C; x++)
			{
				if (!checked[y][x] && map[y][x] == 0)
				{
					checked[y][x] = true;
					q.push({y, x});
					melting();
				}
			}

		doSome();
	}

	printf("%d\n", time);

	return 0;
}
#endif
#if 0
/** Case 2
 *  BFS 중복 최소화
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, time, map[1500][1500], dy[4] = { 0,1,0,-1 }, dx[4] = { 1,0,-1,0 };
bool visited[1500][1500]; // 탐색 확인 배열
bool melted[1500][1500]; // 녹은 얼음을 체크하는 배열
bool is_end; // 백조끼리 맞닿았는지 확인하는 변수.
vector<pair<int, int>> swan;
queue<pair<int, int>> q;

void init()
{
	for (int i = 0; i < 1500; i++)
		for (int j = 0; j < 1500; j++)
			visited[i][j] = melted[i][j] = 0;
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= R || x >= C) return false;
	return true;
}

void checkMeet()
{
	pair<int, int> s1 = swan.front();
	visited[s1.first][s1.second] = true;
	q.push(s1);

	while (q.size())
	{
		pair<int, int> point = q.front();
		int y = point.first, x = point.second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx])
			{
				if (map[ny][nx] == 2)
				{
					is_end = true;
					return;
				}
				else if(map[ny][nx] == 0)
				{
					visited[ny][nx] = true;
					q.push({ ny, nx });
				}
				else
				{
					visited[ny][nx] = true;
					melted[ny][nx] = true;
				}
			}
		}
	}
}

void melting()
{
	while (q.size())
	{
		pair<int, int> point = q.front();
		int y = point.first;
		int x = point.second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx])
			{
				if (map[ny][nx] == 1)
				{
					melted[ny][nx] = true;
				}
				else
				{
					visited[ny][nx] = true;
					q.push({ ny, nx });
				}
			}
		}
	}
}

void doSome()
{
	for (int y = 0; y < R; y++)
		for (int x = 0; x < C; x++)
			if (melted[y][x])
				map[y][x] = 0;
}

int main()
{
	scanf("%d %d", &R, &C);

	// 맵 입력: 물 0, 얼음 1, 백조 2
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
		{
			char ch;
			scanf(" %c", &ch);
			if (ch == 'L')
			{
				swan.push_back({ r, c });
				map[r][c] = 2;
			}
			else map[r][c] = ch == 'X' ? 1 : 0;
		}

	for (time = 0; ; time++)
	{
		init();

		checkMeet();
		if (is_end) break;

		for (int y = 0; y<R; y++)
			for (int x = 0; x < C; x++)
			{
				if (!visited[y][x] && map[y][x] == 0)
				{
					visited[y][x] = true;
					q.push({ y, x });
					melting();
				}
			}

		doSome();
	}

	printf("%d\n", time);

	return 0;
}
#endif
#if 0
/** Case 3
 *  물이 아닌 얼음 탐색
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, time, map[1500][1500], dy[4] = { 0,1,0,-1 }, dx[4] = { 1,0,-1,0 };
bool visited[1500][1500]; // 탐색 확인 배열
bool melted[1500][1500]; // 녹은 얼음을 체크하는 배열
bool is_end; // 백조끼리 맞닿았는지 확인하는 변수.
vector<pair<int, int>> swan;
queue<pair<int, int>> q;

void init()
{
	for (int i = 0; i < 1500; i++)
		for (int j = 0; j < 1500; j++)
			visited[i][j] = melted[i][j] = 0;
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= R || x >= C) return false;
	return true;
}

void checkMeet()
{
	pair<int, int> s1 = swan.front();
	visited[s1.first][s1.second] = true;
	q.push(s1);

	while (q.size())
	{
		pair<int, int> point = q.front();
		int y = point.first, x = point.second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx])
			{
				if (map[ny][nx] == 2)
				{
					is_end = true;
					return;
				}
				else if (map[ny][nx] == 0)
				{
					visited[ny][nx] = true;
					q.push({ ny, nx });
				}
				else
				{
					visited[ny][nx] = true;
					melted[ny][nx] = true;
				}
			}
		}
	}
}

void melting()
{
	while (q.size())
	{
		pair<int, int> point = q.front();
		int y = point.first;
		int x = point.second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx])
			{
				if (map[ny][nx] == 1)
				{
					visited[ny][nx] = true;
					q.push({ny, nx});
				}
				else
				{
					melted[y][x] = true;
				}
			}
		}
	}
}

void doSome()
{
	for (int y = 0; y < R; y++)
		for (int x = 0; x < C; x++)
			if (melted[y][x])
				map[y][x] = 0;
}

int main()
{
	scanf("%d %d", &R, &C);

	// 맵 입력: 물 0, 얼음 1, 백조 2
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
		{
			char ch;
			scanf(" %c", &ch);
			if (ch == 'L')
			{
				swan.push_back({ r, c });
				map[r][c] = 2;
			}
			else map[r][c] = ch == 'X' ? 1 : 0;
		}

	for (time = 0; ; time++)
	{
		init();

		checkMeet();
		if (is_end) break;

		for (int y = 0; y<R; y++)
			for (int x = 0; x < C; x++)
			{
				if (!visited[y][x] && map[y][x] == 1)
				{
					visited[y][x] = true;
					q.push({ y, x });
					melting();
				}
			}

		doSome();
	}

	printf("%d\n", time);

	return 0;
}
#endif
#if 1
/** Case 4
 *  큐에 다음 탐색 지점 저장
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C, time, map[1500][1500], dy[4] = { 0,1,0,-1 }, dx[4] = { 1,0,-1,0 };
bool visited[1500][1500]; // 탐색 확인 배열
bool is_end; // 백조끼리 맞닿았는지 확인하는 변수.
vector<pair<int, int>> swan;
queue<pair<int, int>> q, wq;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y >= R || x >= C) return false;
	return true;
}

void checkMeet()
{
	queue<pair<int, int>> nq;
	while (q.size())
	{
		pair<int, int> point = q.front();
		int y = point.first, x = point.second;
		q.pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx) && !visited[ny][nx])
			{
				if (map[ny][nx] == 2)
				{
					is_end = true;
					return;
				}
				else if (map[ny][nx] == 0)
				{
					visited[ny][nx] = true;
					q.push({ ny, nx });
				}
				else
				{
					visited[ny][nx] = true;
					nq.push({ny, nx}); // 다음 큐에 집어넣기
				}
			}
		}
	}

	q = nq;
}

void melting()
{
	queue<pair<int, int>> wnq;
	while (!wq.empty())
	{
		pair<int, int> point = wq.front();
		wq.pop();

		int y = point.first;
		int x = point.second;

		for (int dir = 0; dir < 4; dir++)
		{
			int ny = y + dy[dir];
			int nx = x + dx[dir];

			if (isSafe(ny, nx))
			{
				if (map[ny][nx] == 1)
				{
					wnq.push({ ny, nx });
					map[ny][nx] = 0;
				}
			}
		}
	}
	wq = wnq;
}

int main()
{
	scanf("%d %d", &R, &C);

	// 맵 입력: 물 0, 얼음 1, 백조 2
	for (int r = 0; r < R; r++)
		for (int c = 0; c < C; c++)
		{
			char ch;
			scanf(" %c", &ch);
			if (ch == 'L')
			{
				swan.push_back({ r, c });
				map[r][c] = 2;
				wq.push({r, c});
			}
			else if (ch == '.')
			{
				map[r][c] = 0;
				wq.push({r, c});
			}
			else map[r][c] = 1;
		}

	q.push({swan.front()});
	visited[swan[0].first][swan[0].second] = true;

	for (time = 0; ; time++)
	{
		checkMeet();
		if (is_end) break;

		melting();
	}

	printf("%d\n", time);

	return 0;
}
#endif