#include<iostream>
int N, C, ans;
int main()
{
	scanf("%d ",&N);
	for (int tc = 1; tc<=N;++tc)
	{
		ans = C = 0;
		char ch = 0;
		scanf("%c", &ch);
		while (ch != '\n')
		{
			if (ch == 'O')
			{
				ans += ++C;
			}
			else
				C = 0;

			scanf("%c", &ch);
		}
		printf("%d\n", ans);
	}
	return 0;
}