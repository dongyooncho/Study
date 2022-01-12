#include <iostream>
int N, a[11]; 
// a[1] 1, a[2] 2, a[3] 4, a[4] 7, a[5] 13, a[6] 24

int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		int N;
		a[1] = 1, a[2] = 2, a[3] = 4, a[4] = 7;
		scanf("%d", &N);

		for (int i = 5; i <= N; i++)
		{
			if (!a[i])
			//a[i] = a[i - 3] + a[i - 2] + a[i - 1];
			a[i] = a[i - 1] * 2 - a[i - 4]; // 슬라이딩 윈도우, 
		}
		printf("%d\n", a[N]);
	}
	
	return 0;
}