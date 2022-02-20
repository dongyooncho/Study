#if 0
/**
 * btm - up 방식 실패
 */
#include<iostream>
#include<algorithm>
#include<string.h>
#define MAX(a, b) a>b?a:b
using namespace std;

int N, M, A[3000], B[100], arr[3100], s, e;
int poolCnt;
int ans;
int DP[3001][101][101][2]; // A, B[i]의 i, M, 마지막항 체크, 0 패딩, 3천만 약 120M

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
	for (int cnt = 1; cnt <= M; ++cnt) // 다음에 가져갈 B 아이템 인덱스
	{
		//for (int left = M - get; left >= 0; ++left)
			//continue;
		for (int n = 1; n <= N; ++n)
		{
			/**
			 * 과자 선택 상황에서 할 수 있는 선택은 세가지로, 기존의 A에 배치된 과자를 선택하는 방법과
			 * A 앞에 B를 배치하고 B를 선택하는 방법, 과자를 선택하지 않는 방법 총 세가지가 있다.
			 */
			// 1. B[i], n을 미선택하는 경우. 이전 단계에서 과자를 선택했던 값과, 선택하지 않았던 값 중 가장 큰 값,
			DP[n][cnt - 1][M - cnt + 1][0] = MAX(MAX(DP[n - 1][cnt - 1][M - cnt + 1][0], DP[n - 1][cnt - 1][M - cnt + 1][1]), DP[n][cnt - 1][M - cnt + 1][0]);
			if (ans < DP[n][cnt - 1][M - cnt + 1][0]) ans = DP[n][cnt - 1][M - cnt + 1][0];
			// 2. n 선택. 선택 없는 경우에 A를 더한 값과 전 단계에서 A를 선택했던 경우 중 더 큰값 적용.
			DP[n][cnt-1][M + 1 - cnt][1] = MAX((MAX(A[n - 1] + DP[n-1][cnt-1][M-cnt+1][0], DP[n-1][cnt-1][M-cnt+1][1])), DP[n][cnt - 1][M + 1 - cnt][1]);
			if (ans < DP[n][cnt - 1][M + 1 - cnt][1]) ans = DP[n][cnt - 1][M + 1 - cnt][1];
			// 3. B[i] 선택. cnt 위치에 B[cnt]를 더한 값을 저장한다.
			DP[n][cnt][M - cnt][0] = MAX(MAX(B[cnt - 1] + DP[n - 1][cnt - 1][M - cnt + 1][0], DP[n - 1][cnt - 1][M - cnt + 1][1]), DP[n][cnt - 1][M - cnt + 1][0]);
			if (ans < DP[n][cnt][M - cnt][0]) ans = DP[n][cnt][M - cnt][0];
			// 4. B[i] 넣고 A선택
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
* top - down 방식
*/
#include<iostream>
#include<algorithm>
#include<string.h>
#define MAX(a, b) a>b?a:b
using namespace std;

int N, M, A[3000], B[100], arr[3100], s, e;
int poolCnt;
int ans;
int DP[3001][101][101][2]; // A, B[i]의 i, M, 마지막항 체크, 0 패딩, 3천만 약 120M

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

	// 안 고름
	if (take == 0)
	{
		// 아직 배치된 봉지를 고를 수 있다면
		if (n < N)
		{
			// 이번 봉지를 고르거나
			ret = MAX(ret, getSome(n+1, m, aban, 1) + A[n]);
			// 고르지 않는다.
			ret = MAX(ret, getSome(n + 1, m, aban, 0));
		}

		// 아직 끼워넣기 봉지가 남았다면
		if (m + aban < M)
		{
			// m봉지를 고름.
			ret = MAX(ret, getSome(n, m+1, aban, 1) + B[m]);
		}
	}
	// 저번에 골랐다면
	else if (take == 1)
	{
		if (n < N)
			// 그냥 다음번 과자봉지를 보는 방법
			ret = MAX(ret, getSome(n+1, m, aban, 0));
		if (m + aban < M)
			// 이번 봉지 앞에 과자를 끼워넣어 다시 한번 본다.
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
* btm - up 큐 이용, 제출 시 메모리 에러.
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
int DP[3001][101][101][2]; // A, B[i]의 i, M, 마지막항 체크, 0 패딩, 3천만 약 120M

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
		// 안 고름
		if (take == 0)
		{
			// 아직 배치된 봉지를 고를 수 있다면
			if (n < N)
			{
				if (!isSafe(n + 1, m, aban, 1))
					Q.push({ n + 1, m, aban, 1, val + A[n] });
				// 고르지 않는다.
				if (!isSafe(n + 1, m, aban, 0))
					Q.push({n + 1, m, aban, 0, val });
			}

			// 아직 끼워넣기 봉지가 남았다면
			if (m + aban < M)
			{
				// m봉지를 고름.
				if (!isSafe(n, m + 1, aban, 1))
					Q.push({ n, m + 1, aban, 1, val + B[m] });
			}
		}
		// 저번에 골랐다면
		else if (take == 1)
		{
			if (n < N)
				// 그냥 다음번 과자봉지를 보는 방법
				if (!isSafe(n + 1, m, aban, 0))
					Q.push({ n + 1, m, aban, 0, val });
			if (m + aban < M)
				// 이번 봉지 앞에 과자를 끼워넣어 다시 한번 본다.
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