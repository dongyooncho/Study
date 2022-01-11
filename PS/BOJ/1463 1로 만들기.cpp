#if 0
/** Case 1
 *  top-down
 *  stack overflow
 */
#include<iostream>
#define MIN(a, b) a < b ? a : b
int memo[1000001], N;

int getSome(int num)
{
	if (num == 1) return 0;
	if (memo[num]) return memo[num];

	int a = 987654321, b = 987654321, c = 987654321;

	if (num % 3 == 0) a = getSome(num / 3);
	if (num % 2 == 0) b = getSome(num / 2);
	c = getSome(num - 1);
	int min = MIN(MIN(a, b), c);

	memo[num] = min + 1;

	return memo[num];
}

int main()
{
	scanf("%d", &N);
	printf("%d\n", getSome(N));

	return 0;
}
#endif
#if 1
/** Case 2
 *  btm-up
 */
#include<iostream>
#define INF 987654321
#define MIN(a, b) a < b ? a : b
int memo[1000001], N;

int getSome()
{
	for (int i = 2; i <= N; i++)
		memo[i] = INF;
	for (int i = 1; i < N; i++)
	{
		int next = i * 3;
		if (next <= N && memo[next] > memo[i] + 1)
			memo[next] = memo[i] + 1;

		next = i * 2;
		if (next <= N && memo[next] > memo[i] + 1)
			memo[next] = memo[i] + 1;

		next = i + 1;
		if (next <= N && memo[next] > memo[i] + 1)
			memo[next] = memo[i] + 1;
	}

	return memo[N];
}

int main()
{
	scanf("%d", &N);
	printf("%d\n", getSome());

	return 0;
}
#endif