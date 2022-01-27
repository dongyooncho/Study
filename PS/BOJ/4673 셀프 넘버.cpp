#include<iostream>
bool era[10001];

int main()
{
	for (int i = 1; i < 10000; ++i)
	{
		int buf = i;
		int di = buf;

		while (buf)
		{
			di += buf % 10;
			buf /= 10;
		}

		era[di] = true;
	}

	for (int i = 1; i < 10001; ++i)
		if (!era[i])
			printf("%d\n", i);
	return 0;
}