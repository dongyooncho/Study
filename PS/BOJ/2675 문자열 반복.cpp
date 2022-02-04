#include<iostream>
int N, len;
char word[162];

void init()
{
	len = 0;
}
int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; ++tc)
	{
		init();
		scanf("%d ", &N);
		
		for (;;)
		{
			char ch;
			scanf("%c", &ch);
			if (ch == EOF || ch == '\n')
				break;
			for (int i = 0; i < N; ++i)
				word[len++] = ch;
		}
		word[len] = '\0';
		printf("%s\n", word);
	}
	return 0;
}