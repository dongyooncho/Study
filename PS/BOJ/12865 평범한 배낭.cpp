#if 0
/** Case 1
 *  완전탐색
 */
#include <iostream>
int N, W[100], V[100], K, max;
bool visited[100];

void getSome(int total_weight, int total_value, int weight, int value)
{
	if (total_weight + weight > K)
	{
		if (max < total_value)
			max = total_value;

		return;
	}

	total_weight += weight;
	total_value += value;

	for (int i = 0; i < N; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			getSome(total_weight, total_value, W[i], V[i]);
			visited[i] = false;
		}
	}
}

int main()
{
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &W[i], &V[i]);
	}

	for (int i = 0; i < N; i++)
	{
		visited[i] = true;
		getSome(0, 0, W[i], V[i]);
		visited[i] = false;
	}

	printf("%d\n", max);

	return 0;
}
#endif

#if 0
/** Case 2
 *  조합
 */
#include<iostream>
int N, K, W[100], V[100], max;

void getSome(int idx, int w, int v)
{
	w += W[idx];
	v += V[idx];

	if (w > K) return;

	max = max < v ? v : max;

	for (int i = idx + 1; i < K; i++)
		getSome(idx + 1, w, v);
}

int main()
{
	scanf("%d %d", &N, &K);

	for (int i = 0; i < N; i++)
		scanf("%d %d", &W[i], &V[i]);

	for (int i = 0; i < N; i++)
		getSome(i, 0, 0);

	printf("%d\n", max);

	return 0;
}
#endif

#if 1
/** Case 3
 *  DP
 */
#include<iostream>
#define MAX(a, b) a>b?a:b;
int N, K, W[101], V[101], max, DP[100001][101];

void getSome()
{
	for (int idx = 1; idx <= N; ++idx)
	{
		int weight = W[idx], value = V[idx];

		for (int total_weight = 1; total_weight <= K; ++total_weight) // 가방의 제한 무게
		{
			// 물건을 넣지 않았을 때
			if (total_weight < weight)
				// 이전 단계의 최적값을 넣음
				DP[total_weight][idx] = DP[total_weight][idx - 1];
			// 물건을 넣었을 때
			else
				// 물건을 넣은 값과 이전 단계의 최적값을 비교
				DP[total_weight][idx] = MAX(DP[total_weight][idx - 1], DP[total_weight - weight][idx - 1] + value);
		}
	}
}

int main()
{
	scanf("%d %d", &N, &K);

	for (int i = 1; i <= N; i++)
		scanf("%d %d", &W[i], &V[i]);

	getSome();

	printf("%d\n", DP[K][N]);

	return 0;
}
#endif