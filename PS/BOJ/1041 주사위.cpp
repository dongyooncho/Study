#include <iostream>
long long num[6], min[6], max, N;
bool visited[6];

void getSome(int data, int x, int depth, int last_index)
{
	if (depth == x)
	{
		if (min[x] > data) min[x] = data;
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		if (visited[i] || num[i]+data>min[3]) continue;
	
		visited[i] = 1;
		visited[5 - i] = 1;
		getSome(num[i]+data, x, depth+1, i);
		visited[i] = 0;
		visited[5 - i] = 0;
	}
}

int main()
{
	for (int i = 0; i < 6; i++) min[i] = 987654321;
	scanf("%lld", &N);
	for (int i = 0; i < 6; i++)
	{
		scanf("%d", &num[i]);
		if (num[i] < min[0]) min[0] = num[i];
		if (num[i] > max) max = num[i];
	}

	if (N == 1)
	{
		long long result = 0;
		for (int i = 0; i < 6; i++)
		{
			result += num[i];
		}
		printf("%lld\n", result-max);
		return 0;
	}

	for (int i = 0; i < 6; i++)
	{
		visited[i] = 1;
		visited[5 - i] = 1;
		getSome(num[i], 2, 1, 0);
		visited[i] = 0;
		visited[5 - i] = 0;
	}

	for (int i = 0; i < 6; i++)
	{
		visited[i] = 1;
		visited[5 - i]=1;
		getSome(num[i], 3, 1, 0);
		visited[i] = 0;
		visited[5 - i] = 0;
	}

	long long result = ((N - 2) *(N-2) * min[0] * 5 + (N - 2) * 4 * min[0]) + (min[2] * (N - 1) * 4 + (N - 2)*min[2] * 4) + (min[3] * 4);
	printf("%lld\n", result);
	return 0;
}