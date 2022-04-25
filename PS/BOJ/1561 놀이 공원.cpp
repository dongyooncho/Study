#include<iostream>
#define ll long long
int N, M;
ll T[10001];

int getSome()
{
	ll max = 0;
	for (int i = 1; i <= M; ++i)
		if (max < T[i]) max = T[i];

	ll s = 1;
	ll e = max * (N), time = e;
	N -= M;
	while (e > s)
	{
		ll m = (s + e) >> 1;
		ll tmp = 0;

		for (int i = 1; i <= M; ++i)
			tmp += (m / T[i]);
		if (tmp < N) s = m + 1;
		else
		{
			if (time > m) time = m;
			e = m;
		}
	}

	ll tmp = 0;
	for (int i = 1; i <= M; ++i)
		tmp += ((time - 1) / T[i]);


	for (int i = 1; i <= M; ++i)
		if (time % T[i] == 0)
		{
			++tmp;
			if (tmp == N)
				return i;
		}
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= M; ++i)
		scanf("%d", &T[i]);
	if (N <= M) printf("%d\n", N);
	else printf("%d\n", getSome());
	return 0;
}