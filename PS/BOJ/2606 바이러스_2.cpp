/** Case 2
 *  유니온파인드
 */
#include<iostream>
int N, M, ans, parent[101];

int find(int x)
{
	if (x == parent[x]) return x;

	return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
	x = find(x);
	y = find(y);

	if (x != y)
	{
		if (x < y)
			parent[y] = x;
		else
			parent[x] = y;
	}
}

bool isUnion(int x, int y)
{
	return find(x) == find(y);
}

int main()
{
	scanf("%d", &N);
	scanf("%d", &M);

	for (int i = 1; i <= N; i++)
		parent[i] = i;

	for (int i = 1; i <= M; i++)
	{
		int from, to;
		scanf("%d %d", &from, &to);

		if (!isUnion(from, to))
			merge(from, to);
	}

	for (int i = 2; i <= N; i++)
	{
		if (find(i) == 1)
			ans++;
	}
		

	printf("%d\n", ans);

	return 0;
}
