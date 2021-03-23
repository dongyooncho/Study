/*
argc는 리눅스 명령체계에서 실행 파일 뒤에 준 인자의 개수,
argv[0]은 실행파일이름,
argv[n]은 n번째 인자값
*/
#include<stdio.h>

int main(int argc, char *argv[])
{
	printf("argc: %d\n",argc);
	for(int i=0; i<argc; i++) printf("argv[%d]: %s\n", i, argv[i]);

	return 0;
}