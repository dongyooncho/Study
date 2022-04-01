#include<iostream>
int N, K, cnt, ans;
int front, rear; // 벨트의 시작점
int next[200], prev[200];
int belt[200]; // 벨트의 내구성
bool used_belt[200]; // 사용중인 벨트

// 원형 큐 방식으로 시작점을 바꿈.
void turnBelt()
{
	front = prev[front];
	rear = prev[rear];
}

void downRobot(int pos)
{
	used_belt[pos] = false;
}

void upRobot(int pos)
{
	if (belt[pos])
	{
		--belt[pos];
		used_belt[pos] = true;
		if (!belt[pos]) ++cnt;
	}
}

void moveRobot()
{
	int pos = prev[rear];
	// 내리는 위치 전 칸부터 올리는 위치까지 차례로 탐색
	while (prev[front] != pos)
	{
		// 로봇이 있고, 다음칸이 이동 가능한 상태라면 이동한다.
		if (used_belt[pos] && !used_belt[next[pos]] && belt[next[pos]])
		{
			downRobot(pos);
			upRobot(next[pos]);
		}

		pos = prev[pos];
	}
}

int main()
{
	scanf("%d %d", &N, &K);
	for (int i = 0; i < 2 * N; ++i)
	{
		scanf("%d", &belt[i]);
		// 다음칸, 이전칸을 선계산.
		next[i] = (i + 1) % (2 * N);
		prev[i] = (i - 1 + 2 * N) % (2 * N);
	}

	rear = N - 1;

	while (cnt < K)
	{
		turnBelt();
		downRobot(rear);

		moveRobot();
		downRobot(rear);

		upRobot(front);
		++ans;
	}

	printf("%d\n", ans);
	return 0;
}