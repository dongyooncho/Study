#include<iostream>
#include<vector>
using namespace std;

struct Stone {
	int mass;
	int speed;
	int dir;
};
int N, M, K, ans;
int dy[8] = { -1, -1, 0, 1, 1, 1, 0, -1 }, dx[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
vector<Stone> map[50][50];

void copyMapA2B(vector<Stone> A[][50], vector<Stone> B[][50])
{
	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
		B[y][x] = A[y][x];
}

void moveFireball()
{
	vector<Stone> tmp[50][50] = {};

	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x) for (int i = 0; i < map[y][x].size(); ++i)
	{
		int ny = y + dy[map[y][x][i].dir] * map[y][x][i].speed;
		int nx = x + dx[map[y][x][i].dir] * map[y][x][i].speed;
		ny = (ny + 1000 * N) % N;
		nx = (nx + 1000 * N) % N;

		tmp[ny][nx].push_back({ map[y][x][i] });
	}

	copyMapA2B(tmp, map);
}

void sumFireball()
{
	vector<Stone> tmp[50][50] = {};

	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		if (map[y][x].size() > 1)
		{
			int mass = 0, spd = 0;
			bool odd = map[y][x][0].dir % 2, allSame = true;
			for (int i = 0; i < map[y][x].size(); ++i)
			{
				mass += map[y][x][i].mass;
				spd += map[y][x][i].speed;
				if (odd != map[y][x][i].dir % 2) allSame = false;
			}
			mass /= 5;
			if (!mass) continue;

			spd /= map[y][x].size();
			if (allSame)
			{
				for (int dir = 0; dir < 8; dir += 2)
					tmp[y][x].push_back( { mass, spd, dir } );
			}
			else
			{
				for (int dir = 1; dir < 8; dir += 2)
					tmp[y][x].push_back({ mass, spd, dir });
			}
		}
	}

	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x)
	{
		// 2개 이상 있던 곳은 사라지던 쪼개지던 일이 일어나는게 포인트. 복사해야한다.
		if (map[y][x].size() > 1)
			map[y][x] = tmp[y][x];
	}
}

int main()
{
	scanf("%d %d %d", &N, &M, &K);
	for (register int i = 0; i < M; ++i)
	{
		// y, x, 질량, 속력, 방향
		int y, x, m, spd, dir;
		scanf("%d %d %d %d %d", &y, &x, &m, &spd, &dir);
		map[y - 1][x - 1].push_back({ m, spd, dir });
	}

	for (int T = 0; T < K; ++T)
	{
		// 이동
		moveFireball();
		// 파이어볼 진화
		sumFireball();
	}

	for (int y = 0; y < N; ++y) for (int x = 0; x < N; ++x) for (int i = 0; i < map[y][x].size(); ++i)
		ans += map[y][x][i].mass;
	printf("%d\n", ans);
		
	return 0;
}