/**
 *  9471 피사노 주기를 이해하면 더 쉽게 풀수 있는 문제
 */
#include<iostream>
using namespace std;
long long N;
long fibo[1500001];

long Fibo(long long N)
{
	fibo[0] = 0, fibo[1] = 1;

	for (int i = 0; i < N - 1; i++)
	{
		fibo[i + 2] = (fibo[i] % 1000000 + fibo[i + 1] % 1000000)%1000000;
	}

	return fibo[N];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> N;

	cout << Fibo(N%(15*100000)) << endl;

	return 0;
}