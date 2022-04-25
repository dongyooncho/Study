#include<iostream>
#define MAX(a, b) a > b ? a : b
int N, DP[1500002], ans;
int T[1500001], P[1500001];

void getSome()
{
	for (int i = N; i > 0; --i)
	{
		// 종료일이 퇴사 이후라면
		if (T[i] > N)
		{
			// 다음날의 최대 수익이 오늘의 최대 수익
			DP[i] = DP[i + 1];
		}
		// 상담이 가능하다면
		else
		{
			// 상담을 했을 때의 최대 수익과 하지 않은 날의 최대 수익 비교
			DP[i] = MAX(DP[T[i] + 1] + P[i], DP[i + 1]);
		}
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d %d", &T[i], &P[i]);
		T[i] = i + T[i] - 1; // 종료일을 기준으로 모두 변경
	}

	getSome();

	printf("%d\n", DP[1]);
	return 0;
}