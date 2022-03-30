#include<iostream>
#include<queue>
using namespace std;

int N, K, ans;
int dx[2] = { 1, 0 }, dy[2] = { 0, 1 };
int arr[100][100], X;
int end_pos[100], next_x[100];
queue<int> Q;

bool isSafe(int y, int x)
{
	if (y < 0 || x < 0 || y> 10 || x >= N) return false;
	return true;
}

void increaseMin()
{
	queue<int> idx_Q;
	int min = 10001;

	for (int i = 0; i < N; ++i)
	{
		if (min > arr[0][i])
		{
			min = arr[0][i];
			idx_Q = {};
			idx_Q.push(i);
		}
		else if (min == arr[0][i])
			idx_Q.push(i);
	}

	while (!idx_Q.empty())
	{
		++arr[0][idx_Q.front()];
		idx_Q.pop();
	}
}

void stackSome()
{
	X = 0;
	while (end_pos[X] < N)
	{
		for (int x = next_x[X] - 1; x >= X; --x)	for (int y = 0; arr[y][X]; ++y)
		{
			Q.push(arr[y][x]);
			arr[y][x] = 0;
		}

		for (int y = 1; !Q.empty(); ++y) for (int x = next_x[X]; x <= end_pos[X]; ++x)
		{
			arr[y][x] = Q.front(); Q.pop();
		}

		X = next_x[X];
	}
}

void controlSome()
{
	int tmp_arr[100][100] = {0,};
	for (int y = 0; arr[y][X]; ++y)	for (int x = X; x < N && arr[y][x]; ++x) for (int dir = 0; dir < 2; ++dir)
	{
		int ny = y + dy[dir];
		int nx = x + dx[dir];

		if (!isSafe(ny, nx) || !arr[y][x] || !arr[ny][nx]) continue;
		int res = (arr[y][x] - arr[ny][nx]) / 5;
		tmp_arr[y][x] -= res;
		tmp_arr[ny][nx] += res;
	}
	
	for (int y = 0; y < 11; ++y) for (int x = X; x < N; ++x)
		if (tmp_arr[y][x])
			arr[y][x] += tmp_arr[y][x];
}

void pressSome()
{
	for (int x = X; x < N && arr[1][x]; ++x) for (int y = 0; arr[y][x]; ++y)
	{
		Q.push(arr[y][x]);
		arr[y][x] = 0;
	}

	for (int x = 0; x < N && !Q.empty(); ++x)
	{
		arr[0][x] = Q.front();
		Q.pop();
	}
	X = 0;
}

void stackHalf()
{
	int half = N >> 1;
	for (int i = 0; i < 2; ++i)
	{
		for (int y = i; y >= 0; --y) for (int x = X + half - 1; x >= X; --x)
		{
			Q.push(arr[y][x]);
			arr[y][x] = 0;
		}

		X += half;
		for (int y = i+1; !Q.empty(); ++y) for (int x = X; x < N; ++x)
		{
			arr[y][x] = Q.front(); Q.pop();
		}

		half >>= 1;
	}
}

bool isEnd()
{
	int min = 10001, max = 0;
	for (int i = 0; i < N; ++i)
	{
		if (min > arr[0][i]) min = arr[0][i];
		if (max < arr[0][i]) max = arr[0][i];
	}

	int res = max - min;
	return res <= K ;
}

int main()
{
	// 다음 쌓는 시작, 끝 위치 선 계산.
	end_pos[X] = 1;
	next_x[X] = 1; X = next_x[X];
	for (int width = 1, height = 2, w_cnt = 1, h_cnt = 0; X < 100;)
	{
		end_pos[X] = X + width - 1 + height;

		next_x[X] = X + width;
		X  = next_x[X];
		++h_cnt; ++w_cnt;

		if (w_cnt == 2)
		{
			w_cnt = 0;
			++width;
		}
		if (h_cnt == 2)
		{
			h_cnt = 0;
			++height;
		}
	}
		
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; ++i)
		scanf("%d", &arr[0][i]);

	while (true)
	{
		// 가장 적은 칸 1 증가
		increaseMin();

		// 말아올리듯 쌓은 후 정리
		stackSome();
		controlSome();
		pressSome();

		// 반씩 접듯 쌓은 후 정리
		stackHalf();
		controlSome();
		pressSome();

		++ans;
		// 종료 조건 확인
		if (isEnd()) break;
	}
	printf("%d\n", ans);
	return 0;
}