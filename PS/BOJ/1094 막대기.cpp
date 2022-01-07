#include<iostream>
int N, num[9];

int getSome()
{
	int ans = 0;

	for (int j = 8; j >= 0; j--)
		if (N / (1 << j))
		{
			num[j] = 1;
			N %= (1 << j);
		}
				

	for (int i = 0; i < 9; i++)
		if (num[i])
			ans++;

	return ans;
}

int main()
{
	scanf("%d", &N);

	printf("%d\n", getSome());
	return 0;
}