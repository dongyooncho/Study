#include<iostream>
int N;
char TREE[101];
void inOrder(int idx)
{
	if (idx > N) return;
	inOrder(idx*2);
	printf("%c", TREE[idx]);
	inOrder(idx * 2 + 1);
}
int main()
{
	for (int tc = 1; tc <= 10; ++tc)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; ++i)
		{
			int res = i * 2, id;
			char ch;

			scanf("%d %c ", &id, &ch);
			TREE[id] = ch;

			if (res > N)
				continue;
			else if (res == N)
				scanf("%d", &id);
			else
				scanf("%d %d", &id, &id);
		}
		printf("#%d ", tc);
		inOrder(1);
		printf("\n");
	}
	return 0;
}