/**
 * Case 1. Merge Sort 과정에서 거꾸로 된 숫자 개수를 셈.
 */
#include<iostream>
int N, arr[100000];
long long ans;

void init()
{
	ans = 0;
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
		scanf("%d", &arr[i]);
}

void merge(int l, int m, int r)
{
	int s[100000];
	int i = l, j = m + 1, k = l;
	while (i <= m && j <= r)
		if (arr[i] < arr[j])
			s[k++] = arr[i++];
		else
		{
			// 거꾸로 된 숫자가 있다면, Inversion Counting 이므로 1 추가
			s[k++] = arr[j++];
			ans+= m + 1 - i;
		}

	while (i <= m)
		s[k++] = arr[i++];
	while (j <= r)
		s[k++] = arr[j++];

	for (i = l; i <= r; ++i)
		arr[i] = s[i];
}

void merge_sort(int l, int r)
{
	if (l >= r) return;
	int m = (l + r) / 2;

	merge_sort(l, m);
	merge_sort(m+1, r);
	merge(l, m, r);
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		init();
		merge_sort(0, N-1);
		printf("#%d %lld\n", tc, ans);
	}
	return 0;
}