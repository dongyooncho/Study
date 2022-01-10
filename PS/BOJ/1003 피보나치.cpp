#include <iostream>
int N, memo[41][2];
int main()
{
	int T;
	scanf("%d", &T);

	memo[0][0] = 1;
	memo[1][1] = 1;

	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d", &N);

		for (int i = 2; i <= N; i++)
		{
			if (!memo[i][0])
				memo[i][0] = memo[i - 2][0] + memo[i - 1][0];
			if (!memo[i][1])
				memo[i][1] = memo[i - 2][1] + memo[i - 1][1];
		}

		printf("%d %d\n", memo[N][0], memo[N][1]);
	}

	return 0;
}