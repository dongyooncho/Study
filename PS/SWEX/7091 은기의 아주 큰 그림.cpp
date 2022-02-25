#include<iostream>
#include<string.h>
#define ll long long
#define KEY1 3
#define KEY2 5

int cpy_hash, origin_hash[2000][2000];
int H, W, N, M, ans;
int memo[2000][2000], mul[2][2000]; // 원본의 idx ~ idx+W까지의 해시값을 저장하는 메모리, 중복 계산을 최소화하기 위해 x축 시프트 연산 기억
char origin[2001][2001], cpy[2001][2001];

void input()
{
	scanf("%d %d %d %d", &H, &W, &N, &M);
	for (int i = 0; i < H; ++i)
		scanf("%s", cpy[i]);

	for (int i = 0; i < N; ++i)
		scanf("%s", origin[i]);
}

void init()
{
	ans = memo[0][0] = 0;
}

int getData(char ch)
{
	if (ch == 'o') return 0;
	else return 1;
}

int getPrevXData(int cnt)
{
	if (mul[0][cnt]) return mul[0][cnt];
	int ret = 1;
	for (int i = 1; i < cnt; ++i) ret = (ret << KEY1) + ret;
	return mul[0][cnt] = ret;
}

int getPrevYData(int cnt)
{
	if (mul[1][cnt]) return mul[1][cnt];
	int ret = 1;
	for (int i = 1; i < cnt; ++i) ret = (ret << KEY2) + ret;
	return mul[1][cnt] = ret;
}

void getCpyKey()
{
	int y_key = 0;
	for (int y = 0; y < H; ++y)
	{
		int x_key = 0;
		for (int x = 0; x < W; ++x)
		{
			x_key = ((x_key << KEY1) + x_key) + getData(cpy[y][x]);
		}
		y_key = (y_key << KEY2) + y_key + x_key;
	}

	cpy_hash = y_key;
}

void getOriginKey()
{
	for (int y = 0; y < N; ++y) // 0~N 까지 다 해야함. 이는 나중에 hash값을 구할 때 사용할 데이터가 됨.
	{
		memo[y][0] = (0 << KEY1) + getData(origin[y][0]) ;
		
		for (int x = 1; x < W; ++x) // i ~ I+W까지 해야함.
		{
			memo[y][0] = (memo[y][0] << KEY1) + memo[y][0] + getData(origin[y][x]);
		}

		for (int x = 1; x < M - W + 1; ++x)
		{
			memo[y][x] = memo[y][x - 1] - (getData(origin[y][x - 1]) ? getPrevXData(W) : 0); // o는 0이기 때문에 생략, x 면 자릿수 만큼에 해당하는 해시값을 뺌
			memo[y][x] = (memo[y][x] << KEY1) + memo[y][x] + getData(origin[y][x + W - 1]); // i + W 번째 해시값 더하기
		}
	}

	for (int x = 0; x < M - W + 1; ++x)
	{
		origin_hash[0][x] = memo[0][x];
		for (int y = 1; y < H; ++y)  // i ~ i + H까지의 해시값을 계싼해야함
			origin_hash[0][x] = (origin_hash[0][x] << KEY2) + origin_hash[0][x] + memo[y][x];

		for (int y = 1; y < N - H + 1; ++y)
		{
			origin_hash[y][x] = origin_hash[y - 1][x] - memo[y-1][x] * getPrevYData(H); // i-1번쨰 해시값 계산 후 뺴기
			origin_hash[y][x] = (origin_hash[y][x]<<KEY2) + origin_hash[y][x] + memo[y + H - 1][x]; // i + H 번째 해시값 새로 더하기
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	for (int tc = 1; tc <= T; ++tc)
	{
		input();
		init();
		getCpyKey();
		getOriginKey();

		for (int y = 0; y < N - H + 1; ++y)
			for (int x = 0; x < M - W + 1; ++x)
				if (origin_hash[y][x] == cpy_hash)
					++ans;

		printf("#%d %d\n", tc, ans);
	}
	return 0;
}