#include<iostream>
#include<queue>
#include<vector>
#define INF 987654321
using namespace std;
int N, M, S, E, dist[1001];
vector<pair<int, int>> nodes[1001];

struct comp {
	bool operator()(pair<int,int> I, pair<int,int> C)
	{
		if(I.first != C.first)
			return I.first > C.first;
		return I.second > C.second;
	}
};

void getSome()
{
	for (int i = 1; i <= N; i++) dist[i] = INF;

	priority_queue<pair<int, int>, vector<pair<int, int>>, comp> PQ;
	PQ.push({0, S});
	dist[S] = 0;

	while (!PQ.empty())
	{
		int v = PQ.top().second;
		PQ.pop();

		int leng = nodes[v].size();
		for (int i = 0; i < leng; i++)
		{
			int w = nodes[v][i].first;
			int val = dist[v] + nodes[v][i].second;

			if (dist[w] > val)
			{
				dist[w] = val;
				PQ.push({val,w});
			}
		}
	}
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 0; i < M; i++)
	{
		int from, to, val;
		scanf("%d %d %d", &from, &to, &val);
		nodes[from].push_back({to, val});
	}
	scanf("%d %d", &S, &E);

	getSome();

	printf("%d\n", dist[E]);

	return 0;
}