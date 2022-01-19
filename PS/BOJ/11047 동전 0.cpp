#include<iostream>
int N, K, coin[10], i, count;


int main()
{
	scanf("%d %d", &N, &K);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &coin[i]);
	}
	while (K)
	{
		if (K >= coin[i - 1])
		{
			K -= coin[i - 1];
			count++;
		}
		else i--;
	}

	printf("%d\n", count);
	return 0;
}