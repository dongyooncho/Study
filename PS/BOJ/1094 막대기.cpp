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
			/// 비트 삭제
			/// N ^= (1<<j); // XOR, 토글이기 때문에 원소 추가에도 사용 가능
			/// N &= ~(1<<j); // 틸트 + AND 연산
		}
				
	for (int i = 0; i < 9; i++)
		if (num[i])
			ans++;

	return ans;
}

int bitCount(int x)
{
	if (x == 0) return 0;
	return (x % 2) + bitCount(x / 2);
}

int main()
{
	scanf("%d", &N);

	// printf("%d\n", getSome());
	printf("%d\n", bitCount(N));
	return 0;
}