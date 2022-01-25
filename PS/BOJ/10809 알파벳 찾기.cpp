#include<iostream>
int c['z' + 1];
int main()
{
	for (int i = 'a'; i <= 'z'; ++i)
		c[i] = -1;
	char w[101];
	scanf("%s", w);
	for (int i = 0; w[i]; ++i)
		c[w[i]] = c[w[i]] == -1 ? i : c[w[i]];
	for (int i = 'a'; i <= 'z'; i++)
		printf("%d ", c[i]);
	printf("\n");
	return 0;
}