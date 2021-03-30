/*
 * 리눅스 상에서 동작하는 커스텀 쉘 제작
 * system함수를 이용해 실제 리눅스 명령어를 호출해보고
 * 명령어 수행 기록을 history 배열에 저장한다.
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char history[1000][100];
int top=1;

void getSome(int num)
{
	if(num)
	{
		if(strcmp(history[num],"date")==0) system("date");
		else if(strcmp(history[num],"uptime")==0) system("uptime");
		else if(strcmp(history[num],"ls")==0) system("ls -al");
		else if(strcmp(history[num],"log")==0) system("dmesg");
		else if(strcmp(history[num],"history")==0)
			for(int prev=1; prev<top; prev++) 
				printf("%d\t%s\n",prev,history[prev]);
		else printf("ERROR\n");
	}
	else
	{
		if(strcmp(history[top-1],"date")==0) system("date");
		else if(strcmp(history[top-1],"uptime")==0) system("uptime");
		else if(strcmp(history[top-1],"ls")==0) system("ls -al");
		else if(strcmp(history[top-1],"log")==0) system("dmesg");
		else if(strcmp(history[top-1],"history")==0)
			for(int prev=1; prev<top; prev++) 
				printf("%d\t%s\n",prev,history[prev]);
		else if(strcmp(history[top-1],"hclear")==0) top=1;
		else 
		{
			top--;
			printf("ERROR(No Such File exist.)\n");
		}
	}
}

int main()
{
	while(1)
	{
		printf("SSAFY > ");
		scanf("%s", history[top++]);
		if(strcmp(history[top-1], "exit")==0) break;

		int len=0, num=0;
		while(history[top-1][len++]);

		if(history[top-1][0]=='!')
		{
			char tmp[100];
			strcpy(tmp,&history[top-1][1]);
			num = atoi(tmp);
			top--;
			if(num>0&&num<top)	getSome(num);
			else printf("ERROR(History Out of Bounds)\n");
		}
		else getSome(top-1);

	}
	return 0;
}