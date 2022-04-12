#include<iostream>
#include<algorithm>
#include<vector>
#define MAX(a, b) a>b?a:b
using namespace std;

int N, DP[101], lis;
vector<pair<int, int>> line;

void getSome()
{
	// ±‚¡ÿ
	for (int i = 0; i < N; ++i)
	{
		DP[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (line[j].second < line[i].second) DP[i] = MAX(DP[i], DP[j] + 1);
		}
		lis = MAX(lis, DP[i]);
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		int s, e;
		scanf("%d %d", &s, &e);
		line.push_back({s, e});
	}
	sort(line.begin(), line.end());

	getSome();
	printf("%d\n", N - lis);

	return 0;
}