// 백준에서는 두 풀이가 별 차이가 없는데, 컴퓨터 상에서는 26회 반복 TC에서 15초와 5초로 큐보다 벡터가 3배이상 빨랐음. 이유는 모르겠음
#if 0
/// 큐를 이용한 풀이
///  80ms
#include<iostream>
#include<queue>
using namespace std;
struct F {
	int y;
	int x;
	int dir;
};
int M, S, ans, dx[8] = { -1,-1,0,1,1,1,0,-1 }, dy[8] = { 0,-1,-1,-1,0,1,1,1 }, sdx[4] = { 0, -1, 0, 1 }, sdy[4] = {-1, 0, 1, 0};
int visited[4][4], mMax, s_dir; // 맵과 잡아먹힌 시간 기록. 이동 시 잡아먹는 최대 물고기 수, 상어가 다음으로 갈 방향
int next_shark_direction[3];
bool checked[4][4]; // 물고기를 잡아먹었는지 확인하는 배열
queue<F> map[4][4];
queue<F> Q;
int sx, sy;

int turnLeft(int dir)
{
	return (dir + 7) % 8;
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y > 3 || x > 3) return false;
	return true;
}

void getSome(int y, int x, int val, int cnt)
{
	if (val > 100)
	{
		if (mMax < cnt)
		{
			mMax = cnt;
//			s_dir = val;
			int buf = 100;
			for (int i = 0; i < 3;)
			{
				int dir = (val / buf) - 1;
				val %= buf; buf /= 10;

				next_shark_direction[i++] = dir;
			}
		}
		return;
	}
	val *= 10;
	for (int dir = 0; dir < 4; ++dir)
	{
		int ny = y + sdy[dir];
		int nx = x + sdx[dir];

		if (isSafe(ny, nx))
		{
			bool buf = checked[ny][nx];
			checked[ny][nx] = true;
			getSome(ny, nx, val + dir + 1, cnt + (buf ? 0 : map[ny][nx].size()));
			checked[ny][nx] = buf;
		}
	}
}

int main()
{
	scanf("%d %d", &M, &S);

	for (int i = 0; i < M; ++i)
	{
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		Q.push({ y - 1,x - 1, dir - 1 });
//		map[y - 1][x - 1].push( { y - 1,x - 1,dir - 1 } );
	}
	scanf("%d %d", &sy, &sx);
	--sx; --sy;

	for (int T = 0; T < S; ++T)
	{
		queue<F> bQ; // 다음 T의 물고기들을 담고 있는 벡터

		while (!Q.empty())
		{
			int y = Q.front().y;
			int x = Q.front().x;
			int dir = Q.front().dir; Q.pop();

			// 1. 복제 시작
			bQ.push({y, x, dir});
			
			// 2. 이동
			for (int cnt = 0; cnt < 8; ++cnt)
			{
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				// 해당 칸이 맵 안에 있고, 상어나 물고기의 냄새가 존재하지 않으면 이동 후 종료.
				if (isSafe(ny, nx) && !visited[ny][nx] && (ny != sy || nx != sx))
				{
					y = ny;
					x = nx;
					break;
				}

				// 이동 불가 시 45도 반시계 회전 후 재탐색
				dir = turnLeft(dir);
			}

			map[y][x].push({y,x,dir});
		}

		// 3. 상어 출격
		mMax = -1;
		// 최적 경로 계산
		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = sy + sdy[dir];
			int nx = sx + sdx[dir];
			int val = dir + 1;
			
			if (isSafe(ny, nx))
			{
				checked[ny][nx] = true;
				getSome(ny, nx, val, map[ny][nx].size());
				checked[ny][nx] = false;
			}
		}
		// 최적 경로 진행
		//int val = 100;
		//while (val)
		for (int i = 0; i < 3; ++i)
		{
			/*int dir = (s_dir / val) - 1;
			s_dir %= val; val /= 10;
*/
			int dir = next_shark_direction[i];
			int ny = sy + sdy[dir];
			int nx = sx + sdx[dir];

			while (!map[ny][nx].empty())
			{
				visited[ny][nx] = T + 2;
				map[ny][nx].pop();
			}

			sy = ny;
			sx = nx;
		}
		
		// 4. 2시간 전 냄새 지우기
		for (int y = 0; y < 4; ++y)	for (int x = 0; x < 4; ++x)
		{
			if (visited[y][x] == T)
				visited[y][x] = 0;
			// 맵에 남은 물고기를 큐에 집어넣음
			while (!map[y][x].empty())
			{
				Q.push({ y, x, map[y][x].front().dir });
				map[y][x].pop();
			}
		}
		// 5. 복사 완료
		// 1번에서 복사한 물고기들을 큐에 집어넣음
		while (!bQ.empty())
		{
			Q.push({ bQ.front().y, bQ.front().x, bQ.front().dir });
			bQ.pop();
		}
	}

	printf("%d\n", Q.size());
	return 0;
}
#endif
#if 1
/// 벡터를 사용, 연산 횟수를 조금 줄임
/// 64ms
#include<iostream>
#include<queue>
using namespace std;
struct F {
	int y;
	int x;
	int dir;
};
int M, S, ans, dx[8] = { -1,-1,0,1,1,1,0,-1 }, dy[8] = { 0,-1,-1,-1,0,1,1,1 }, sdx[4] = { 0, -1, 0, 1 }, sdy[4] = { -1, 0, 1, 0 };
int visited[4][4], mMax, s_dir; // 맵과 잡아먹힌 시간 기록. 이동 시 잡아먹는 최대 물고기 수, 상어가 다음으로 갈 방향
int next_shark_direction[3], DP[4][4][8];
bool checked[4][4]; // 물고기를 잡아먹었는지 확인하는 배열
vector<F> map[4][4], egg[4][4];
queue<F> Q;
int sx, sy;

void copyA2B(vector<F> A[4][4], vector<F> B[4][4])
{
	for (int y = 0; y < 4; ++y) for (int x = 0; x < 4; ++x)
		B[y][x] = A[y][x];
}

int turnLeft(int dir)
{
	switch (dir)
	{
	case 0:
		return 7;
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return 2;
	case 4:
		return 3;
	case 5:
		return 4;
	case 6:
		return 5;
	case 7:
		return 6;
	}
}

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y > 3 || x > 3) return false;
	return true;
}

void getSome(int y, int x, int top, int tmp_route[], int cnt)
{
	if (top == 3)
	{
		if (mMax < cnt)
		{
			mMax = cnt;
			for (int i = 0; i < 3; ++i)
				next_shark_direction[i] = tmp_route[i];
		}
		return;
	}

	for (int dir = 0; dir < 4; ++dir)
	{
		tmp_route[top] = dir;
		int ny = y + sdy[dir];
		int nx = x + sdx[dir];

		if (isSafe(ny, nx))
		{
			bool buf = checked[ny][nx];
			checked[ny][nx] = true;
			getSome(ny, nx, top + 1, tmp_route, cnt + (buf ? 0 : map[ny][nx].size()));
			checked[ny][nx] = buf;
		}
	}
}

int main()
{
	scanf("%d %d", &M, &S);

	for (int y = 0 ; y < 4; ++y)
		for (int x = 0; x < 4; ++x)
			for (int i = 0; i < 8; ++i)
			{
				int dir = i;
				int ny = y + dy[dir];
				int nx = x + dx[dir];
				while (!isSafe(ny, nx))
				{
					dir = turnLeft(dir);
					ny = y + dy[dir];
					nx = x + dx[dir];
				}
				DP[y][x][i] = dir;
			}

	for (int i = 0; i < M; ++i)
	{
		int y, x, dir;
		scanf("%d %d %d", &y, &x, &dir);
		map[y-1][x-1].push_back({ y - 1,x - 1, dir - 1 });
	}
	scanf("%d %d", &sy, &sx);
	--sx; --sy;

	for (int T = 0; T < S; ++T)
	{
		// 1. 복제
		copyA2B(map, egg);
		vector<F> temp_map[4][4] = {};
		for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) for (int z = 0; z < map[i][j].size(); ++z)
		{
			int y = map[i][j][z].y;
			int x = map[i][j][z].x;
			int dir = map[i][j][z].dir;
			dir = DP[y][x][dir];
			
			// 2. 이동
			for (int cnt = 0; cnt < 8; ++cnt)
			{
				int ny = y + dy[dir];
				int nx = x + dx[dir];

				// 해당 칸이 맵 안에 있고, 상어나 물고기의 냄새가 존재하지 않으면 이동 후 종료.
				if (isSafe(ny, nx) && !visited[ny][nx] && (ny != sy || nx != sx))
				{
					y = ny;
					x = nx;
					break;
				}

				// 이동 불가 시 45도 반시계 회전 후 재탐색
				dir = turnLeft(dir);
			}

			temp_map[y][x].push_back({ y,x,dir });
		}
		copyA2B(temp_map, map);

		// 3. 상어 출격
		mMax = -1;
		// 최적 경로 계산
		for (int dir = 0; dir < 4; ++dir)
		{
			int ny = sy + sdy[dir];
			int nx = sx + sdx[dir];
			int val = dir + 1;

			if (isSafe(ny, nx))
			{
				int tmp_route[3] = {dir,0,0};
				checked[ny][nx] = true;
				getSome(ny, nx, 1, tmp_route, map[ny][nx].size());
				checked[ny][nx] = false;
			}
		}

		for (int i = 0; i < 3; ++i)
		{

			int dir = next_shark_direction[i];
			int ny = sy + sdy[dir];
			int nx = sx + sdx[dir];

			if (!map[ny][nx].empty())
			{
				visited[ny][nx] = T + 2;
				map[ny][nx] = {};
			}

			sy = ny;
			sx = nx;
		}

		// 4. 2시간 전 냄새 지우기
		for (int y = 0; y < 4; ++y)	for (int x = 0; x < 4; ++x)
		{
			if (visited[y][x] == T)
				visited[y][x] = 0;
			// 5. 복사 완료
			for (int z = 0; z < egg[y][x].size(); ++z)
				map[y][x].push_back({y, x, egg[y][x][z].dir});
		}
	}
	for (int y = 0; y < 4; ++y)	for (int x = 0; x < 4; ++x)
		ans += map[y][x].size();

	printf("%d\n", ans);
	return 0;
}
#endif