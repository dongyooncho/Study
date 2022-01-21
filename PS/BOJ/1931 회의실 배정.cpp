#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct timetable {
	unsigned int start;
	unsigned int end;
};
bool comp(timetable a, timetable b)
{
	if (a.end != b.end)
		return a.end < b.end;
	else
		return a.start < b.start;
}
vector<timetable> V;
int N, memo[100000];
bool visited[100000];

void getSome()
{
	memo[0] = 1;
	int s = V[0].start, e = V[0].end;
	for (int i = 1; i < N; i++)
	{
		if (V[i].start >= e) // 선택 가능
		{
			memo[i] = memo[i - 1] + 1;
			e = V[i].end;
		}
		else
			memo[i] = memo[i - 1];
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		unsigned int s, e;
		scanf("%u %u", &s, &e);
		V.push_back({s, e});
	}
	sort(V.begin(), V.end(), comp);
	getSome();

	printf("%d\n", memo[N-1]);
	return 0;
}