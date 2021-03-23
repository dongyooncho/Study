/*
stat 함수는 파일의 상태를 체크하는 함수로
내부의 st_mtime으로 마지막 수정 시간을 체크할 수 있음.
stat(경로(파일이름), &stat구조체)로 사용하여 구조체로 정보를 넘겨줌.
반환값이 -1이면 파일 읽기 실패.
*/
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>


char path[500];

int main(int argc, char *argv[])
{
	if(argc==1)
	{
		printf("ERROR :: no input source file name\n");
	}

	strcpy(path, argv[1]);

	struct stat fileInfo;

	if(stat(path, &fileInfo)==-1)
	{
		printf("ERROR :: Can not read this file\n");
		return 0;
	}

	printf("%d\n", (int)fileInfo.st_mtime);
	return 0;
}
