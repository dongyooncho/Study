/// 케이스
/// 1. s -> e로 갈 수 없는 경우. gg 출력
/// 2. s -> e로 갈 수 있는 경우.
/// 2-1. s->e로 갈 수 있고, 사이클이 없는 경우 ans 출력
/// 2-2. s -> e로 갈 수 있으면서, 양의 사이클이 존재하는 경우 Gee 출력
/// 2-3. s -> e로 갈 수 있으면서, 음의 사이클이 존재하는 경우 ans 출력.
#if 0
#include<iostream>
#include<queue>
using namespace std;

int N; // 도시의 수
int S; // 시작 도시
int E; // 도착 도시
int M; // 교통 수단의 수
int city[50]; // 도시별 수입
int map[50][50]; // 도시간 이동 비용
int memo[50]; // 목적지 까지의 누적값 저장

bool checked[50]; // 도착 가능 여부 확인을 위한 변수
bool visited[50];
bool visited2[50][50];

int q[1000000], front = -1, rear = -1; // 큐
priority_queue<pair<int, int>> PQ; // {val, city} 자료형으로 최대 비용에 따라 다음 노드를 선택하는 힙 생성

void getSome()
{
	PQ.push({city[S], S});

	while (!PQ.empty())
	{
		int val = PQ.top().first;
		int city_now = PQ.top().second; PQ.pop();
		// 목적지에 도착했다면
		if (city_now == E)
		{
			// 돈을 출력하고 종료
			printf("%d\n", val);
			return;
		}
		for (int city_next = 0; city_next < N; ++city_next)
		{
			if (city_now == city_next || !map[city_now][city_next]) continue;

			int res = val - map[city_now][city_next] + city[city_next];
			if (!visited[city_next] || memo[city_next] < res)
			{
				// A->B로 이미 이동한 적이 있다면 사이클 발생한 것임. ?? 아닐수도
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
		// 방문 가능한 경우
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

	// 방문 불가능한 경우
	printf("gg\n");
	return 0;
}
#endif
#if 0
#include<iostream>
#include<queue>
#define MAX(a, b) a > b ? a : b
using namespace std;

int N; // 도시의 수
int S; // 시작 도시
int E; // 도착 도시
int M; // 교통 수단의 수
int city[50]; // 도시별 수입
int map[50][50]; // 도시간 이동 비용
bool isConn[50][50];
long long memo[50]; // 도착 액수 총액
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
		// 사이클이 있으며, 재 방문시 점점 비용이 증가한다면, 무한 루프에 빠짐.
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

	// 방문 불가능한 경우
	if (!finished)
		printf("gg\n");
	// 사이클이 있는 경우
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

int N; // 도시의 수
int S; // 시작 도시
int E; // 도착 도시
int M; // 교통 수단의 수
int profit[50]; // 도시별 수입
int map[50][50]; // 도시간 이동 비용
bool isConn[50][50]; // 비용 0의 이동수단도 있어서 판단하기 위함.
long long memo[50]; // 도착 액수 총액

queue<pair<int, int>> Q; // {출발지, 도착지} 정보를 담는 큐 생성
queue<int> QQ; // 넓이 탐색에 쓸 큐 생성
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

// 사이클이 도착 금액에 영향을 주는지 확인하는 함수.
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

	// N - 1번의 엣지 릴렉션을 수행할 예정.
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

	// 추가로 더 진행하고, 변화가 있다면 사이클이 있는것으로 판단한다.
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
	// 갈 수 없음
	if (memo[E] == INF && !fin)
		printf("gg\n");
	// 갈 수 있음
	else
	{
		// 사이클 존재.
		if (cycle)
			printf("Gee\n");
		// 사이클이 없거나 결과에 영향을 주지 않을 때
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

int N; // 도시의 수
int S; // 시작 도시
int E; // 도착 도시
int M; // 교통 수단의 수
int profit[50]; // 도시별 수입
int map[50][50]; // 도시간 이동 비용
bool isConn[50][50]; // 비용 0의 이동수단도 있어서 판단하기 위함.
long long memo[50]; // 도착 액수 총액

queue<pair<int, int>> Q; // {출발지, 도착지} 정보를 담는 큐 생성
queue<int> QQ; // 넓이 탐색에 쓸 큐 생성
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

// 사이클이 도착 금액에 영향을 주는지 확인하는 함수.
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

	// N - 1번의 엣지 릴렉션을 수행할 예정.
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

	// 추가로 더 진행하고, 변화가 있다면 사이클이 있는것으로 판단한다.
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
	// 갈 수 없음
	if (memo[E] == INF && !fin)
		printf("gg\n");
	// 갈 수 있음
	else
	{
		// 사이클 존재.
		if (cycle)
			printf("Gee\n");
		// 사이클이 없거나 결과에 영향을 주지 않을 때
		else
			printf("%lld\n", -memo[E]);
	}

	return 0;
}
#endif