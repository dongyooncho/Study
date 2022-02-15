#include<iostream>
#define SWAP(a, b) if (a != b) a^=b^=a^=b
#define MOD 20171109

int N, M, minH[200002], minT, maxH[200002], maxT, ans;

bool ASC(int a, int b)
{
	if (a > b) return true;
	else return false;
}

bool DESC(int a, int b)
{
	if (a < b) return true;
	else return false;
}

void pushH(int* heap, int* top, int val, bool (*comp)(int, int))
{
	int* H = heap;
	int* T = top;

	H[++(*T)] = val;

	int child = *T;
	while (child > 1)
	{
		int parent = child >> 1;

		if (!comp(H[parent], H[child]))
			break;

		SWAP(H[parent], H[child]);

		child = parent;
	}
}

int popH(int* heap, int* top, bool(*comp)(int, int))
{
	int* H = heap;
	int* T = top;

	int ret = H[1];
	SWAP(H[1], H[(*top)]); // 매크로 안에 증감연산자를 쓰면 매크로 안에 모든 문장에서 치환되므로 3이 줄어들게 됨.
	--(*top);

	int parent = 1, child = 2;
	while (child <= *T)
	{
		if (child < *T && comp(H[child], H[child + 1]))
			++child;

		if (!comp(H[parent], H[child]))
			break;

		SWAP(H[parent], H[child]);

		parent = child;
		child <<= 1;
	}

	return ret;
}

void init()
{
	minT = maxT = ans = 0;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		init();
		scanf("%d %d", &N, &M);
		pushH(maxH, &maxT, M, DESC);

		for (int i = 0; i < N; ++i)
		{
			int x, y;
			scanf("%d %d", &x, &y);

			pushH(minH, &minT, x, ASC);
			pushH(maxH, &maxT, y, DESC);
			while (minH[1] < maxH[1])
			{
				int minN = popH(minH, &minT, ASC);
				int maxN = popH(maxH, &maxT, DESC);

				pushH(minH, &minT, maxN, ASC);
				pushH(maxH, &maxT, minN, DESC);
			}

			ans = (ans % MOD + maxH[1] % MOD) % MOD;
		}

		printf("#%d %d\n", tc, ans);
	}

	return 0;
}