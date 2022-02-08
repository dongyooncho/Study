#include<iostream>
#include<queue>
#include<vector>
#define ll long long
#define SWAP(a,b) if (a!=b) a^=b^=a^=b
using namespace std;

int N, M, parent[50001];
ll ans;
vector<vector<pair<int, int>>> E; // E[start_node] = {end_node, cost};

void init()
{
	ans = 0;
	E.clear();

	scanf("%d", &N);
	scanf("%d", &M);
	E.resize(M);
	for (int i = 0; i < M; ++i)
	{
		int s, e, c;
		scanf("%d %d %d", &s, &e, &c);
		E[s].push_back({ e, (ll)c });
		E[e].push_back({ s, (ll)c });
	}

	for (int i = 1; i <= N; ++i)
		parent[i] = i;
}

int findS(int x)
{
	if (x == parent[x])
		return x;
	return parent[x] = findS(parent[x]);
}

void unionS(int x, int y)
{
	x = findS(x);
	y = findS(y);

	if (x != y)
	{
		if (x > y) SWAP(x, y);
		parent[y] = x;
	}
}

void getSome()
{
	priority_queue<pair<ll, int>> PQ;
	PQ.push({0, 1});

	int cnt = 0;
	while (cnt != N && !PQ.empty())
	{
		int node = PQ.top().second;
		int val = PQ.top().first;
		PQ.pop();
		if (node != 1 && findS(node) == 1) continue;
		unionS(1, node);
		ans -= val;
		++cnt;

		for (int i = 0; i < E[node].size(); ++i)
		{
			int next = E[node][i].first;
			ll cost = E[node][i].second;

			if (findS(next) != 1)
				PQ.push({ -cost, next });
		}
		
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		init();
		
		getSome();
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}