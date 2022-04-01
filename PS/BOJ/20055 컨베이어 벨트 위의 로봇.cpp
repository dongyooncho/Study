#include<iostream>
int N, K, cnt, ans;
int front, rear; // ��Ʈ�� ������
int next[200], prev[200];
int belt[200]; // ��Ʈ�� ������
bool used_belt[200]; // ������� ��Ʈ

// ���� ť ������� �������� �ٲ�.
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
	// ������ ��ġ �� ĭ���� �ø��� ��ġ���� ���ʷ� Ž��
	while (prev[front] != pos)
	{
		// �κ��� �ְ�, ����ĭ�� �̵� ������ ���¶�� �̵��Ѵ�.
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
		// ����ĭ, ����ĭ�� �����.
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