#include<iostream>
#define MAX(a, b) a > b ? a : b
int N, H[100000], stack[100001], top = 0;
long long max;

int main()
{
	for (;;)
	{
		max = 0;
		scanf("%d", &N);

		if (!N) break;

		for (int i = 0; i < N; i++)
			scanf("%d", &H[i]);

		for (int i = 0; i < N; i++)
		{
			while (top && H[stack[top - 1]] > H[i])
			{
				long long height = H[stack[--top]];
				long long width = i;

				if (top) width = i - stack[top - 1] - 1;
				max = MAX(max, height * width);
			}

			stack[top++] = i;
		}

		while (top > 0)
		{
			long long height = H[stack[--top]];
			long long width = N;

			if (top) width = N - stack[top - 1] - 1;

			max = MAX(max, width * height);
		}

		printf("%lld\n", max);
	}

	return 0;
}