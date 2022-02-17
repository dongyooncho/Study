#include<iostream>
#include <queue>
using namespace std;

priority_queue<pair<int, int>> Q;
int N, A[10], K, mMin;

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		mMin = -1;
		Q = {};
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
			scanf("%d", &A[i]);

		scanf("%d", &K);
		for (int i = 0; i < N; ++i)
		{
			int res = (K%A[i]) + (K / A[i]);
			Q.push({ -K%A[i], K / A[i] });
			if (mMin == -1 || mMin > res)
				mMin = res;
		}
		while (!Q.empty())
		{
			int nK = Q.top().second;
			int val = -Q.top().first;
			Q.pop();

			for (int i = 0; i < N; ++i)
			{
				if (nK%A[i] + val > mMin) continue;
				int res = (nK%A[i] + val) + (nK / A[i]);
				if (nK >= A[i])
				{
					Q.push({ -(nK%A[i] + val), nK / A[i] });
					if (mMin == -1 || mMin > res)
						mMin = res;
				}	
			}
		}

		printf("#%d %d\n", tc, mMin);
	}
	return 0;
}