#include<iostream>
int N, M, ans;
bool visited[101], com[101][101];

void getSome(int here)
{
	visited[here] = true;
	ans++;

	for (int next = 1; next <= N; next++)
	{
		if (!visited[next] && com[here][next])
			getSome(next);
	}
}

int main()
{
	scanf("%d", &N);
	scanf("%d", &M);

	for (int i = 1; i <= M; i++)
	{
		int from, to;
		scanf("%d %d", &from, &to);

		com[from][to] = 1;
		com[to][from] = 1;
	}

	getSome(1);
	
	printf("%d\n", ans - 1);

	return 0;
}