#include<iostream>
int N, S[10001], top = 0;

int atoi(char* word)
{
	int num = 0;
	for (int i = 0; word[i]; i++)
	{
		num *= 10;
		num += word[i] - '0';
	}
	return num;
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		char word[10];
		scanf(" %[^\n]s", word);

		if (word[0] == 'p')
		{
			if (word[1] == 'u') S[top++] = atoi(&word[5]);
			else
			{
				if (top) printf("%d\n", S[--top]);
				else printf("%d\n", -1);
			}
				
		}
		else if (word[0] == 't')
		{
			if (top) printf("%d\n", S[top - 1]);
			else printf("%d\n", -1);
		}
		else if (word[0] == 's') printf("%d\n", top);
		else
		{
			if (top) printf("%d\n", 0);
			else printf("%d\n", 1);
		}
	}
	return 0;
}