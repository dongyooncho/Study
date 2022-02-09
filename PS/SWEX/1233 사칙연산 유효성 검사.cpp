#include<iostream>
double half;
int N, TREE[201];
bool ans;

bool isNum(int node)
{
	if ('0' <= node && node <= '9') return true;
	return false;
}

int main()
{
	for (int tc = 1; tc <= 10; ++tc)
	{
		scanf("%d", &N);
		half = N / 2.0;
		ans = true;
		for (int i = 1; i <= N; ++i)
		{
			int id;
			char ch;
			scanf("%d %c ", &id, &ch);
			TREE[id] = ch;

			if (i == half)
				scanf("%d", &id);
			else if (i < half)
				scanf("%d %d", &id, &id);
		}
		
		for (int i = 1; i <= N; ++i)
			if (i <= half && isNum(TREE[i]))
			{
				ans = false;
				break;
			}
			else if (i > half && !isNum(TREE[i]))
			{
				ans = false;
				break;
			}
		printf("#%d %d\n", tc, ans?1:0);
	}
	return 0;
}