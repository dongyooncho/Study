#include<iostream>
#include<string.h>
#define ll long long
#define KEY1 3
#define KEY2 5

int cpy_hash, origin_hash[2000][2000];
int H, W, N, M, ans;
int memo[2000][2000], mul[2][2000]; // ������ idx ~ idx+W������ �ؽð��� �����ϴ� �޸�, �ߺ� ����� �ּ�ȭ�ϱ� ���� x�� ����Ʈ ���� ���
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
	for (int y = 0; y < N; ++y) // 0~N ���� �� �ؾ���. �̴� ���߿� hash���� ���� �� ����� �����Ͱ� ��.
	{
		memo[y][0] = (0 << KEY1) + getData(origin[y][0]) ;
		
		for (int x = 1; x < W; ++x) // i ~ I+W���� �ؾ���.
		{
			memo[y][0] = (memo[y][0] << KEY1) + memo[y][0] + getData(origin[y][x]);
		}

		for (int x = 1; x < M - W + 1; ++x)
		{
			memo[y][x] = memo[y][x - 1] - (getData(origin[y][x - 1]) ? getPrevXData(W) : 0); // o�� 0�̱� ������ ����, x �� �ڸ��� ��ŭ�� �ش��ϴ� �ؽð��� ��
			memo[y][x] = (memo[y][x] << KEY1) + memo[y][x] + getData(origin[y][x + W - 1]); // i + W ��° �ؽð� ���ϱ�
		}
	}

	for (int x = 0; x < M - W + 1; ++x)
	{
		origin_hash[0][x] = memo[0][x];
		for (int y = 1; y < H; ++y)  // i ~ i + H������ �ؽð��� ����ؾ���
			origin_hash[0][x] = (origin_hash[0][x] << KEY2) + origin_hash[0][x] + memo[y][x];

		for (int y = 1; y < N - H + 1; ++y)
		{
			origin_hash[y][x] = origin_hash[y - 1][x] - memo[y-1][x] * getPrevYData(H); // i-1���� �ؽð� ��� �� ����
			origin_hash[y][x] = (origin_hash[y][x]<<KEY2) + origin_hash[y][x] + memo[y + H - 1][x]; // i + H ��° �ؽð� ���� ���ϱ�
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