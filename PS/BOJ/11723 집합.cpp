#include <iostream>
#include <string>
int M, X[21], front = -1, rear = -1;
char queue[100001][11];

int strlen(char str[])
{
	int len = 0;
	for (char* ch = str; *ch; ch++)
		len++;

	return len;
}

int atoi(char num[])
{
	int ans = 0;

	for (int i = 0; i < strlen(num); i++)
	{
		ans *= 10;
		ans += num[i] - '0';
	}

	return ans;
}

void doQueue()
{
	char cmd = queue[++front][0];

	if (cmd == 'a')
		X[atoi(&queue[front][4])] = 1;
	else if (cmd == 'r')
		X[atoi(&queue[front][7])] = 0;
	else if (cmd == 't')
	{
		int next = atoi(&queue[front][7]);
		X[next] = !X[next];
	}
}

void doSome(int idx)
{
	if (queue[idx][0] == 'a' && queue[idx][1] == 'l')
	{
		for (int i = 1; i <= 20; i++)
			X[i] = 1;
	}
	else if (queue[idx][0] == 'c')
	{
		while (front + 1< idx)
		{
			doQueue();
		}

		int num = atoi(&queue[idx][6]);
		printf("%d\n", X[num]);
	}
	else if (queue[idx][0] == 'e')
	{
		for (int i = 1; i <= 20; i++)
			X[i] = 0;
	}
	else
		return;

	front = rear = -1;
}

int main()
{
	scanf("%d", &M);

	for (int i = 0; i < M; i++)
	{
		scanf(" %[^\n]s", queue[++rear]);
		doSome(rear);

		if (rear == 100000)
		{
			while (front <= rear)
				doQueue();
			front = rear = -1;
		}
	}

	return 0;
}