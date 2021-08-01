#include <stdio.h>
#include <stdlib.h>

void join();
void english();

int main(void)
{
	int option;
	printf("================================\n");
	printf("========== 2021 SPLUG ==========\n");
	printf("================================\n");
	printf("================================\n");
	printf("=             메뉴             =\n");
	printf("================================\n");
	printf("         1. 회원 가입\n");
	printf("         2. 로그인\n");
	printf("         3. 로그아웃\n");
	printf("         4. 영어 단어 맞추기\n");
	printf("         5. 회원 탈퇴\n");
	printf("         6. 프로그램 종료\n");
	printf("================================\n");
	printf(":");
	scanf_s("%d", &option);
	if (option == 1)
	{
		join();
	}
}

void join()
{

	FILE* fp = NULL;
	fp = fopen("join.txt", "w");
	printf("회원가입 페이지");
	fprintf("아이디: ");
	fscanf_s("%s", &)
}

void english();
{
	int eng;
	printf("<영어 단어 맞추기 프로그램>\n");
	printf("1. 영어 단어 맞추기 2. 프로그램 종료\n");
	
	printf("번호를 선택하세요: ");
	scanf("%d", &eng);
	if (eng == 1)
	{
	    
	}

}