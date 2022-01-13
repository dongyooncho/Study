#include<iostream>
#include<string>
#include<queue>
using namespace std;

int score[100], ans = 0, stack;
queue<int> Q;

int main()
{
	int buf[26] = { 3, 2, 1, 2, 3, 3, 3, 3, 1, 1, 3, 1, 3, 3, 1, 2, 2, 2, 1, 2, 1, 1, 2, 2, 2, 1 };
	for (int i = 0; i < 26; i++)
		score['A' + i] = buf[i];

	char w[1000001];
	scanf("%s", w);
	string word = w;

	int len = word.length();

	for (int i = 0; i < len; i++)
		Q.push(score[word[i]]);

	while (Q.size() != 1)
	{
		queue<int> res;

		while (!Q.empty())
		{
			if (!stack)
			{
				stack = Q.front();
				Q.pop();
			}
			else
			{
				res.push(stack + Q.front());
				stack = 0;
				Q.pop();
			}
		}

		if (stack)
		{
			res.push(stack);
			stack = 0;
		}

		Q = res;
	}

	if (Q.front() % 2 == 0) printf("You're the winner?\n");
	else printf("I'm a winner!\n");

	return 0;
}