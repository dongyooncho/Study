#include<iostream>
#define MOD 10007
int N, memo[1001];
int main()
{
	scanf("%d", &N);
	
	memo[1] = 1;
	memo[2] = 2;

	for (int i = 3; i <= N; ++i)
		memo[i] = (memo[i - 1] % MOD + memo[i - 2] % MOD) % MOD;

	printf("%d\n", memo[N]);

	return 0;
}