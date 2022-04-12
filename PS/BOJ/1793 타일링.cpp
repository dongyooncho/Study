#include<iostream>
#define ll long long
#define MAX(a,b) a > b ? a : b
struct BigInteger {
	int arr[1000];
	int top;
} DP[251];
int N;

int main()
{
	DP[0].arr[0] = 1; DP[1].arr[0] = 1;	DP[2].arr[0] = 3;
	for (int tc = 0; scanf("%d", &N) != EOF; ++tc)
	{
		for (int i = 3; i <= N; ++i)
		{
			if (DP[i].top || DP[i].arr[0]) continue;
			DP[i].top = MAX(DP[i - 1].top, DP[i - 2].top);
			for (int x = 0; x <= DP[i - 1].top; ++x)
				DP[i].arr[x] += DP[i - 1].arr[x];
			for (int x = 0; x <= DP[i - 2].top; ++x)
				DP[i].arr[x] += DP[i - 2].arr[x] * 2;
			for (int x = 0; x < DP[i].top; ++x)
				while (DP[i].arr[x] > 9)
				{
					DP[i].arr[x] -= 10;
					++DP[i].arr[x + 1];
				}

			while (DP[i].arr[DP[i].top] > 9)
			{
				int val = DP[i].arr[DP[i].top] / 10;
				DP[i].arr[DP[i].top] -= (10 * val);
				++DP[i].top;
				DP[i].arr[DP[i].top] += val;
			}
		}
		for (int i = DP[N].top; i >= 0; --i)
			printf("%d", DP[N].arr[i]);
		printf("\n");
	}
	
	return 0;
}

#if 0
#include<iostream>
#define ll long long
#define MAX(a,b) a > b ? a : b

class BigInteger {
public:
	int arr[1000] = { 0, };
	int top = 0;

	void add(BigInteger* b)
	{
		top = MAX(top, b->top);
		for (int x = 0; x <= b->top; ++x)
			arr[x] += b->arr[x];
	}

	void organize()
	{
		for (int x = 0; x < top; ++x)
			if (arr[x] > 9)
			{
				int val = arr[x] / 10;
				arr[x] -= 10 * val;
				arr[x + 1] += val;
			}

		while (arr[top] > 9)
		{
			int val = arr[top] / 10;
			arr[top] -= 10 * val;
			arr[++top] += val;
		}
	}
};
int N;


int main()
{
	scanf("%d", &N);
	BigInteger DP[251];
	DP[1].arr[0] = 1;	DP[2].arr[0] = 3;
	for (int i = 3; i <= N; ++i)
	{
		DP[i].add(&DP[i - 1]);
		DP[i].add(&DP[i - 2]);
		DP[i].add(&DP[i - 2]);
		DP[i].organize();
	}
	for (int i = DP[N].top; i >= 0; --i)
		printf("%d", DP[N].arr[i]);
	printf("\n");
	return 0;
}

#endif