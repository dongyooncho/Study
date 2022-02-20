#if 0
/**
 * btm - up ��� ����
 */
#include<iostream>
#include<algorithm>
#include<string.h>
#define MAX(a, b) a>b?a:b
using namespace std;

int N, M, A[3000], B[100], arr[3100], s, e;
int poolCnt;
int ans;
int DP[3001][101][101][2]; // A, B[i]�� i, M, �������� üũ, 0 �е�, 3õ�� �� 120M

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);

	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
		scanf("%d", &B[i]);
}

void init()
{
	memset(DP, 0, sizeof(DP));
	sort(B, B + M, [](int a, int b) {
		return a > b;
	});
	s = poolCnt = 0;
	e = M - 1;
}

void getSome()
{
	for (int cnt = 1; cnt <= M; ++cnt) // ������ ������ B ������ �ε���
	{
		//for (int left = M - get; left >= 0; ++left)
			//continue;
		for (int n = 1; n <= N; ++n)
		{
			/**
			 * ���� ���� ��Ȳ���� �� �� �ִ� ������ ��������, ������ A�� ��ġ�� ���ڸ� �����ϴ� �����
			 * A �տ� B�� ��ġ�ϰ� B�� �����ϴ� ���, ���ڸ� �������� �ʴ� ��� �� �������� �ִ�.
			 */
			// 1. B[i], n�� �̼����ϴ� ���. ���� �ܰ迡�� ���ڸ� �����ߴ� ����, �������� �ʾҴ� �� �� ���� ū ��,
			DP[n][cnt - 1][M - cnt + 1][0] = MAX(MAX(DP[n - 1][cnt - 1][M - cnt + 1][0], DP[n - 1][cnt - 1][M - cnt + 1][1]), DP[n][cnt - 1][M - cnt + 1][0]);
			if (ans < DP[n][cnt - 1][M - cnt + 1][0]) ans = DP[n][cnt - 1][M - cnt + 1][0];
			// 2. n ����. ���� ���� ��쿡 A�� ���� ���� �� �ܰ迡�� A�� �����ߴ� ��� �� �� ū�� ����.
			DP[n][cnt-1][M + 1 - cnt][1] = MAX((MAX(A[n - 1] + DP[n-1][cnt-1][M-cnt+1][0], DP[n-1][cnt-1][M-cnt+1][1])), DP[n][cnt - 1][M + 1 - cnt][1]);
			if (ans < DP[n][cnt - 1][M + 1 - cnt][1]) ans = DP[n][cnt - 1][M + 1 - cnt][1];
			// 3. B[i] ����. cnt ��ġ�� B[cnt]�� ���� ���� �����Ѵ�.
			DP[n][cnt][M - cnt][0] = MAX(MAX(B[cnt - 1] + DP[n - 1][cnt - 1][M - cnt + 1][0], DP[n - 1][cnt - 1][M - cnt + 1][1]), DP[n][cnt - 1][M - cnt + 1][0]);
			if (ans < DP[n][cnt][M - cnt][0]) ans = DP[n][cnt][M - cnt][0];
			// 4. B[i] �ְ� A����
			DP[n][cnt][M - cnt][1] = MAX(MAX(A[n - 1] + DP[n - 1][cnt - 1][M - cnt + 1][1], A[n-1] + DP[n - 1][cnt - 1][M - cnt + 1][0]), DP[n][cnt - 1][M - cnt + 1][0]);
			if (ans < DP[n][cnt][M - cnt][1]) ans = DP[n][cnt][M - cnt][1];
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
		getSome();
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
#endif
#if 0
/**
* top - down ���
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#define MAX(a, b) a>b?a:b
using namespace std;

int N, M, A[3000], B[100], arr[3100], s, e;
int poolCnt;
int ans;
int DP[3001][101][101][2]; // A, B[i]�� i, M, �������� üũ, 0 �е�, 3õ�� �� 120M

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);

	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
		scanf("%d", &B[i]);
}

void init()
{
	memset(DP, -1, sizeof(DP));
	sort(B, B + M, [](int a, int b) {
		return a > b;
	});
	s = poolCnt = 0;
	e = M - 1;
}

int getSome(int n, int m, int aban, int take)
{
	if (n == N && m + aban == M) return 0;
	if (DP[n][m][aban][take] != -1) return DP[n][m][aban][take];

	int ret = DP[n][m][aban][take];

	ret = 0;

	// �� ��
	if (take == 0)
	{
		// ���� ��ġ�� ������ �� �� �ִٸ�
		if (n < N)
		{
			// �̹� ������ ���ų�
			ret = MAX(ret, getSome(n+1, m, aban, 1) + A[n]);
			// ���� �ʴ´�.
			ret = MAX(ret, getSome(n + 1, m, aban, 0));
		}

		// ���� �����ֱ� ������ ���Ҵٸ�
		if (m + aban < M)
		{
			// m������ ��.
			ret = MAX(ret, getSome(n, m+1, aban, 1) + B[m]);
		}
	}
	// ������ ����ٸ�
	else if (take == 1)
	{
		if (n < N)
			// �׳� ������ ���ں����� ���� ���
			ret = MAX(ret, getSome(n+1, m, aban, 0));
		if (m + aban < M)
			// �̹� ���� �տ� ���ڸ� �����־� �ٽ� �ѹ� ����.
			ret = MAX(ret, getSome(n, m, aban+1, 0));
	}

	return DP[n][m][aban][take] = ret;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		input();
		init();
		ans = getSome(0, 0, 0, 0);
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
#endif
#if 1
/**
* btm - up ť �̿�, ���� �� �޸� ����.
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#include<queue>
#define MAX(a, b) a>b?a:b
using namespace std;

struct Req {
	int n;
	int m;
	int aban;
	bool take;
	int val;
};

queue<Req> Q;
int N, M, A[3000], B[100], s, e;
int ans;
int DP[3001][101][101][2]; // A, B[i]�� i, M, �������� üũ, 0 �е�, 3õ�� �� 120M

bool isSafe(int n, int m, int aban, int take)
{
	if (n == N && m + aban == M) return false;
	if (DP[n][m][aban][take] != -1) return false;
	return true;
}

void input()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &A[i]);

	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
		scanf("%d", &B[i]);
}

void init()
{
	memset(DP, 0, sizeof(DP));
	sort(B, B + M, [](int a, int b) {
		return a > b;
	});
	ans = 0;
}

void getSome()
{
	Q.push({0, 0, 0, 0, 0});
	while (!Q.empty())
	{
		Req* r = &Q.front(); Q.pop();
		int n = r->n;
		int m = r->m;
		int aban = r->aban;
		bool take = r->take;
		int val = r->val;

		DP[n][m][aban][take] = val;
		ans = MAX(ans, val);
		// �� ��
		if (take == 0)
		{
			// ���� ��ġ�� ������ �� �� �ִٸ�
			if (n < N)
			{
				if (!isSafe(n + 1, m, aban, 1))
					Q.push({ n + 1, m, aban, 1, val + A[n] });
				// ���� �ʴ´�.
				if (!isSafe(n + 1, m, aban, 0))
					Q.push({n + 1, m, aban, 0, val });
			}

			// ���� �����ֱ� ������ ���Ҵٸ�
			if (m + aban < M)
			{
				// m������ ��.
				if (!isSafe(n, m + 1, aban, 1))
					Q.push({ n, m + 1, aban, 1, val + B[m] });
			}
		}
		// ������ ����ٸ�
		else if (take == 1)
		{
			if (n < N)
				// �׳� ������ ���ں����� ���� ���
				if (!isSafe(n + 1, m, aban, 0))
					Q.push({ n + 1, m, aban, 0, val });
			if (m + aban < M)
				// �̹� ���� �տ� ���ڸ� �����־� �ٽ� �ѹ� ����.
				if (!isSafe(n, m, aban + 1, 0))
					Q.push({ n, m, aban + 1, 0, val });
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
		getSome();
		printf("#%d %d\n", tc, ans);
	}

	return 0;
}
#endif