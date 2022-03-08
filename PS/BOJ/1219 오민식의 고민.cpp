/// ���̽�
/// 1. s -> e�� �� �� ���� ���. gg ���
/// 2. s -> e�� �� �� �ִ� ���.
/// 2-1. s->e�� �� �� �ְ�, ����Ŭ�� ���� ��� ans ���
/// 2-2. s -> e�� �� �� �����鼭, ���� ����Ŭ�� �����ϴ� ��� Gee ���
/// 2-3. s -> e�� �� �� �����鼭, ���� ����Ŭ�� �����ϴ� ��� ans ���.
#if 0
#include<iostream>
#include<queue>
using namespace std;

int N; // ������ ��
int S; // ���� ����
int E; // ���� ����
int M; // ���� ������ ��
int city[50]; // ���ú� ����
int map[50][50]; // ���ð� �̵� ���
int memo[50]; // ������ ������ ������ ����

bool checked[50]; // ���� ���� ���� Ȯ���� ���� ����
bool visited[50];
bool visited2[50][50];

int q[1000000], front = -1, rear = -1; // ť
priority_queue<pair<int, int>> PQ; // {val, city} �ڷ������� �ִ� ��뿡 ���� ���� ��带 �����ϴ� �� ����

void getSome()
{
	PQ.push({city[S], S});

	while (!PQ.empty())
	{
		int val = PQ.top().first;
		int city_now = PQ.top().second; PQ.pop();
		// �������� �����ߴٸ�
		if (city_now == E)
		{
			// ���� ����ϰ� ����
			printf("%d\n", val);
			return;
		}
		for (int city_next = 0; city_next < N; ++city_next)
		{
			if (city_now == city_next || !map[city_now][city_next]) continue;

			int res = val - map[city_now][city_next] + city[city_next];
			if (!visited[city_next] || memo[city_next] < res)
			{
				// A->B�� �̹� �̵��� ���� �ִٸ� ����Ŭ �߻��� ����. ?? �ƴҼ���
				if (visited2[city_now][city_next])
				{
					printf("Gee\n");
					return;
				}
				visited[city_next] = true;
				visited2[city_now][city_next] = true;
				PQ.push({res, city_next});
				continue;
			}
		}
	}
}

int main()
{
	scanf("%d %d %d %d", &N, &S, &E, &M);
	for (register int i = 0; i < M; ++i)
	{
		int from, to, val;
		scanf("%d %d %d", &from, &to, &val);
		map[from][to] = val;
	}

	q[++rear] = S;
	checked[S] = true;
	while (front != rear)
	{
		int city_now = q[++front];
		// �湮 ������ ���
		if (city_now == E)
		{
			getSome();
			return 0;
		}
		for (int city_next = 0; city_next < N; ++city_next)
		{
			if (city_now == city_next || !map[city_now][city_next]) continue;
			if (!checked[city_next])
			{
				checked[city_next] = true;
				q[++rear] = city_next;
			}
		}
	}

	// �湮 �Ұ����� ���
	printf("gg\n");
	return 0;
}
#endif
#if 0
#include<iostream>
#include<queue>
#define MAX(a, b) a > b ? a : b
using namespace std;

int N; // ������ ��
int S; // ���� ����
int E; // ���� ����
int M; // ���� ������ ��
int city[50]; // ���ú� ����
int map[50][50]; // ���ð� �̵� ���
bool isConn[50][50];
long long memo[50]; // ���� �׼� �Ѿ�
long long ans = -987654321;

bool visited[50];
bool finished;
bool cycle;

void DFS(int city_now, int val)
{
	if (city_now == E)
	{
		if (isConn[E][E] && map[E][E] < city[E])
			cycle = true;
		ans = (long long)MAX(ans, val);
		finished = true;
		return;
	}
	for (register int city_next = 0; city_next < N; ++city_next)
	{
		if (!isConn[city_now][city_next]) continue;
		int res = val - map[city_now][city_next] + city[city_next];
		if (!visited[city_next])
		{
			memo[city_next] = res;
			visited[city_next] = true;
			DFS(city_next, res);
			visited[city_next] = false;
		}
		// ����Ŭ�� ������, �� �湮�� ���� ����� �����Ѵٸ�, ���� ������ ����.
		else if (memo[city_next] < res)
		{
			cycle = true;
			return;
		}

	}
}

int main()
{
	scanf("%d %d %d %d", &N, &S, &E, &M);
	for (register int i = 0; i < M; ++i)
	{
		int from, to, val;
		scanf("%d %d %d", &from, &to, &val);
		if (!isConn[from][to] || map[from][to] > val)
		{
			map[from][to] = val;
			isConn[from][to] = true;
		}
	}
	for (register int i = 0; i < N; ++i)
		scanf("%d", &city[i]);

	visited[S] = true;
	memo[S] = city[S];
	DFS(S, city[S]);

	// �湮 �Ұ����� ���
	if (!finished)
		printf("gg\n");
	// ����Ŭ�� �ִ� ���
	else if (cycle)
		printf("Gee\n");
	else
		printf("%lld\n", ans);

	return 0;
}
#endif
#if 0
#include<iostream>
#include<queue>
#define MAX(a, b) a > b ? a : b
#define INF 98765432198798
using namespace std;

int N; // ������ ��
int S; // ���� ����
int E; // ���� ����
int M; // ���� ������ ��
int profit[50]; // ���ú� ����
int map[50][50]; // ���ð� �̵� ���
bool isConn[50][50]; // ��� 0�� �̵����ܵ� �־ �Ǵ��ϱ� ����.
long long memo[50]; // ���� �׼� �Ѿ�

queue<pair<int, int>> Q; // {�����, ������} ������ ��� ť ����
queue<int> QQ; // ���� Ž���� �� ť ����
bool fin;
bool cycle;
bool visited[50];

void addRelaxation(int cnt)
{
	for (register int i = 0; i < cnt; ++i)
		for (int city_now = 0; city_now < N; ++city_now)
			for (int city_next = 0; city_next < N; ++city_next)
				if (isConn[city_now][city_next])
					Q.push({ city_now, city_next });
}

// ����Ŭ�� ���� �ݾ׿� ������ �ִ��� Ȯ���ϴ� �Լ�.
bool BFS()
{
	while (!QQ.empty())
	{
		int city_now = QQ.front(); QQ.pop();

		for (int city_next = 0; city_next < N; ++city_next)
		{
			if (isConn[city_now][city_next] && !visited[city_next])
			{
				QQ.push(city_next);
				visited[city_next] = true;
			}
		}
	}

	if (visited[E])
		return true;
	return false;
}

int main()
{
	scanf("%d %d %d %d", &N, &S, &E, &M);
	for (register int i = 0; i < M; ++i)
	{
		int from, to, val;
		scanf("%d %d %d", &from, &to, &val);
		if (!isConn[from][to] || map[from][to] > val)
		{
			map[from][to] = val;
			isConn[from][to] = true;
		}
	}
	for (register int i = 0; i < N; ++i)
		memo[i] = INF;

	for (register int i = 0; i < N; ++i)
		scanf("%d", &profit[i]);

	memo[S] = -profit[S];

	// N - 1���� ���� �������� ������ ����.
	addRelaxation(N-1);

	while (!Q.empty())
	{
		int city_now = Q.front().first;
		int city_next = Q.front().second; Q.pop();

		if (memo[city_now] == INF) continue;
		int res = memo[city_now] + map[city_now][city_next] - profit[city_next];
		if (memo[city_next] > res)
		{
			memo[city_next] = res;
			if (city_next == E)
				fin = true;
		}
	}

	// �߰��� �� �����ϰ�, ��ȭ�� �ִٸ� ����Ŭ�� �ִ°����� �Ǵ��Ѵ�.
	addRelaxation(1);

	while (!Q.empty())
	{

		int city_now = Q.front().first;
		int city_next = Q.front().second; Q.pop();

		if (memo[city_now] == INF) continue;
		int res = memo[city_now] + map[city_now][city_next] - profit[city_next];
		if (memo[city_next] > res)
		{
			memo[city_next] = res;

			QQ.push(city_next);
			visited[city_next] = true;
		}
	}

	if (BFS())
		cycle = true;
	// �� �� ����
	if (memo[E] == INF && !fin)
		printf("gg\n");
	// �� �� ����
	else
	{
		// ����Ŭ ����.
		if (cycle)
			printf("Gee\n");
		// ����Ŭ�� ���ų� ����� ������ ���� ���� ��
		else
			printf("%lld\n", -memo[E]);
	}

	return 0;
}
#endif
#if 1
#include<iostream>
#include<queue>
#define MAX(a, b) a > b ? a : b
#define INF 98765432198798
using namespace std;

int N; // ������ ��
int S; // ���� ����
int E; // ���� ����
int M; // ���� ������ ��
int profit[50]; // ���ú� ����
int map[50][50]; // ���ð� �̵� ���
bool isConn[50][50]; // ��� 0�� �̵����ܵ� �־ �Ǵ��ϱ� ����.
long long memo[50]; // ���� �׼� �Ѿ�

queue<pair<int, int>> Q; // {�����, ������} ������ ��� ť ����
queue<int> QQ; // ���� Ž���� �� ť ����
bool fin;
bool cycle;
bool visited[50];

void addRelaxation(int cnt)
{
	for (register int i = 0; i < cnt; ++i)
		for (int city_now = 0; city_now < N; ++city_now)
			for (int city_next = 0; city_next < N; ++city_next)
				if (isConn[city_now][city_next])
					Q.push({ city_now, city_next });
}

// ����Ŭ�� ���� �ݾ׿� ������ �ִ��� Ȯ���ϴ� �Լ�.
bool BFS()
{
	while (!QQ.empty())
	{
		int city_now = QQ.front(); QQ.pop();

		for (int city_next = 0; city_next < N; ++city_next)
		{
			if (isConn[city_now][city_next] && !visited[city_next])
			{
				QQ.push(city_next);
				visited[city_next] = true;
			}
		}
	}

	if (visited[E])
		return true;
	return false;
}

int main()
{
	scanf("%d %d %d %d", &N, &S, &E, &M);
	for (register int i = 0; i < M; ++i)
	{
		int from, to, val;
		scanf("%d %d %d", &from, &to, &val);
		if (!isConn[from][to] || map[from][to] > val)
		{
			map[from][to] = val;
			isConn[from][to] = true;
		}
	}
	for (register int i = 0; i < N; ++i)
		memo[i] = INF;

	for (register int i = 0; i < N; ++i)
		scanf("%d", &profit[i]);

	memo[S] = -profit[S];

	// N - 1���� ���� �������� ������ ����.
	addRelaxation(N - 1);

	while (!Q.empty())
	{
		int city_now = Q.front().first;
		int city_next = Q.front().second; Q.pop();

		if (memo[city_now] == INF) continue;
		long long res = memo[city_now] + map[city_now][city_next] - profit[city_next];
		if (memo[city_next] > res)
		{
			memo[city_next] = res;
			if (city_next == E)
				fin = true;
		}
	}

	// �߰��� �� �����ϰ�, ��ȭ�� �ִٸ� ����Ŭ�� �ִ°����� �Ǵ��Ѵ�.
	addRelaxation(1);

	while (!Q.empty())
	{

		int city_now = Q.front().first;
		int city_next = Q.front().second; Q.pop();

		if (memo[city_now] == INF) continue;
		long long res = memo[city_now] + map[city_now][city_next] - profit[city_next];
		if (memo[city_next] > res)
		{
			memo[city_next] = res;

			QQ.push(city_next);
			visited[city_next] = true;
		}
	}

	if (BFS())
		cycle = true;
	// �� �� ����
	if (memo[E] == INF && !fin)
		printf("gg\n");
	// �� �� ����
	else
	{
		// ����Ŭ ����.
		if (cycle)
			printf("Gee\n");
		// ����Ŭ�� ���ų� ����� ������ ���� ���� ��
		else
			printf("%lld\n", -memo[E]);
	}

	return 0;
}
#endif