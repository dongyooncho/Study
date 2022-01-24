#include<iostream>
int N, ans;

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		char a = 0;
		scanf(" %c", &a);
		ans += a - '0';
	}
		
	printf("%d\n", ans);
	return 0;
}