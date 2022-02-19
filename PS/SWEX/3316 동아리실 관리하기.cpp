#if 0
#include<iostream>
#define MOD 1000000007
int ans;
char key[10001];
int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%s", key);
		int mCase[1 << 4][10000] = { 0, }, ans = 0;
		int day = 0;
		for (int i = 0; i < 16; i++)
			if(i & (1 << (key[day] - 'A'))) mCase[i][day] = 1;
		
		while (key[++day])
			for (int i = 0; i < 16; i++) // prev
				if (mCase[i][day - 1])
					for (int j = 0; j < 16; j++) // now
						if ((j & (1 << (key[day] - 'A'))) != 0 && (i & j ) != 0) mCase[j][day] += mCase[i][day-1];

		for (int i = 0; i < 16; i++)
			ans += mCase[i][day - 1];
		printf("#%d %d\n", tc, ans);
	}
	return 0;
}
#endif
#if 1
/**
 * ����.
 * ù������ 'A'�� ���Ƹ����� Ű�� ����ִٴ� ������ ���ư�, ans�� DP �迭�� int�� �����ؼ� ū ���� ������ �� ������.
 */
#include<iostream>
#include<string.h>
#define MOD 1000000007
long long ans; // ����
long long mCase[1 << 4][10001]; // DP
char key[10001]; // ���
int main()
{
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%s", key);
		
		memset(mCase, 0, sizeof(mCase));
		ans = 0;
		int day = 0;

		for (int i = 1; i < 16; i++)
			if ((i & (1 << (key[day] - 'A'))) && (i & 1)) // �����ڰ� �ְ�, A�� �ִ� ���� ��쿡�� +
				mCase[i][day] = 1;

		while (key[++day])
			for (int i = 1; i < 16; i++) // prev
				if (mCase[i][day - 1])
					for (int j = 1; j < 16; j++) // now
						if ((j & (1 << (key[day] - 'A'))) != 0 && (i & j) != 0)
						{
							mCase[j][day] += mCase[i][day - 1];
							mCase[j][day] %= MOD;
						}

		for (int i = 1; i < 16; i++)
		{
			ans += mCase[i][day - 1];
			ans %= MOD;
		}
		printf("#%d %lld\n", tc, ans);
	}
	return 0;
}
#endif