#include<iostream>
#include<string.h>
int ans, N;


int main()
{
	scanf("%d", &N);
	ans = 0;
	for (int i = 0; i < N; ++i)
	{
		char word[101];
		scanf("%s", word);
		bool use['z' + 1] = {false,};

		char prev = word[0];
		for (int j = 0; word[j]; ++j)
		{
			// �پ��ִ� ���ڰ� �ƴѵ� �ٽ� ���´ٸ�
			if (prev != word[j] && use[word[j]])
			{
				--ans;
				break;
			}
			prev = word[j];
			use[word[j]] = true;
		}
		++ans;
	}
	printf("%d\n", ans);
	return 0;
}