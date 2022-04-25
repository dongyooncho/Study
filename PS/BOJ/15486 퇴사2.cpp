#include<iostream>
#define MAX(a, b) a > b ? a : b
int N, DP[1500002], ans;
int T[1500001], P[1500001];

void getSome()
{
	for (int i = N; i > 0; --i)
	{
		// �������� ��� ���Ķ��
		if (T[i] > N)
		{
			// �������� �ִ� ������ ������ �ִ� ����
			DP[i] = DP[i + 1];
		}
		// ����� �����ϴٸ�
		else
		{
			// ����� ���� ���� �ִ� ���Ͱ� ���� ���� ���� �ִ� ���� ��
			DP[i] = MAX(DP[T[i] + 1] + P[i], DP[i + 1]);
		}
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i)
	{
		scanf("%d %d", &T[i], &P[i]);
		T[i] = i + T[i] - 1; // �������� �������� ��� ����
	}

	getSome();

	printf("%d\n", DP[1]);
	return 0;
}