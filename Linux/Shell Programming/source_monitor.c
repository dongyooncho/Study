/*
지정한 소스파일의 수정 여부를 일정 간격으로 체크하여
수정 발생 시 자동으로 빌드하고 실행하는 프로그램.
파일 이름을 인자로 주지 않으면 오류가 발생한다.

실행 후 최소 1회 무조건 빌드 진행.
실행 예 : 
gcc ./source_monitor.c -o ./source_monitor
./source_monitor ./amuguna.c
 */

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

char cmd[500];
char path[500];
int prev=0;
int main(int argc, char *argv[])
{
	if(argc==1)	printf("ERROR :: no input source file name\n");
	struct stat fileInfo;
	
	strcpy(path, argv[1]);
	system("clear");
	sprintf(cmd, "gcc %s -o run\0", path);
	printf("start\n\n");

	while(1)
	{
		if(stat(path, &fileInfo)==-1)
		{
			printf("ERROR :: Can not read this file\n");
			return 0;
		}
		int now = (int)fileInfo.st_mtime;
		usleep(2000*1000);

		if(prev!=now)
		{
			prev=now;
			system(cmd);
			printf("%s\n", cmd);
			printf("==========================\n");

			system("./run");
			printf("\n");
		}
	}
	return 0;
}