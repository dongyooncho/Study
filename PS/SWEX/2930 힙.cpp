#include<iostream>
#define MAX_SIZE 100001
#define SWAP(a,b) if(a != b) a^=b^=a^=b
int N, top, heap[MAX_SIZE];

void init()
{
	top = 0;
}

void push(int n)
{
	heap[++top] = n;

	int cur = top;
	while (cur > 1)
	{
		int parent = cur >> 1;

		if (heap[parent] > heap[cur]) break;

		SWAP(heap[parent], heap[cur]);

		cur = parent;
	}
}

void pop()
{
	if (top == 0)
	{
		printf(" %d", -1);
		return;
	}
	printf(" %d", heap[1]);
	heap[1] = heap[top--];

	int cur = 1, child = cur << 1;
	while (child <= top)
	{
		if (child < top)
			child = heap[child] < heap[child + 1] ? child + 1 : child;

		if (heap[cur] > heap[child]) break;

		SWAP(heap[cur], heap[child]);

		cur = child;
		child <<= 1;
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		init();
		printf("#%d", tc);
		scanf("%d", &N);
		for (int i = 0; i < N; ++i)
		{
			int	cmd, num;
			scanf("%d", &cmd);
			if (cmd == 1)
			{
				scanf("%d", &num);
				push(num);
			}
			else
				pop();
		}

		printf("\n");
	}
	return 0;
}