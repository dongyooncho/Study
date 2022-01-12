#include <iostream>
int N, memo[5001];

int main()
{
	scanf("%d", &N);
	memo[3] = memo[5] = 1;

	for (int i = 6; i <= N; i++)
	{
		if (memo[i - 3]) memo[i] = memo[i - 3] + 1;
		if (memo[i - 5] && !memo[i-3]) memo[i] = memo[i - 5] + 1;
		if (memo[i - 5] && memo[i - 5] < memo[i - 3]) memo[i] = memo[i - 5] + 1;
	}

	printf("%d\n", memo[N] ? memo[N] : -1);
	return 0;
}