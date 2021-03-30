/*
 * 사용자의 입력을 되풀이하는 프로그램.
 * 1~100 사이의 숫자 N을 입력 시 1~N까지 출력한다.
 * quit, exit로 프로그램을 종료할 수 있다.
 */

#include <stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	while(1)
	{
		char a[1000];
		printf("SSAFY_ECHOBOT >> ");
		scanf("%s", a);
		if(strcmp(a,"exit") == 0|| strcmp(a, "bye")==0) break;

		int number = atoi(a);

		if(number>0 && number<=100)
			for(int i = 1; i<=number; i++) printf("%d",i);

		else printf("%s", a);

		printf("\n");
	}

	return 0;
}
