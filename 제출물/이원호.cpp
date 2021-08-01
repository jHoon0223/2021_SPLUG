#include<stdio.h>
#include<windows.h> //화면 초기화 , Sleep 
void menu(void);
void join_membership(void);
void login(void);
void logout(void);
void guess_words(void);
void membership_wishdrawal(void);
void end_program(void);
int i=0,account=0,n1,n2,z;
typedef struct data
{
	char id[100];
	char password[100];
	char name[100];
}Data;
Data member[100];
int main(void)
{
	menu();
	return 0;
}
void menu(void)
{
	system("cls");
	printf("====================================\n");
	printf("============ 2021 SPLUG ============\n");
	printf("====================================\n");
	printf("====================================\n");
	printf("=               메뉴               =\n");
	printf("\t1. 회원가입\n");
	printf("\t2. 로그인\n");
	printf("\t3. 로그아웃\n");
	printf("\t4. 영어 단어 맞추기\n");
	printf("\t5. 회원 탈퇴\n");
	printf("\t6. 프로그램 종료\n");
	if(account==0)
		printf("로그인X\n");
	else
		printf("로그인중\n");
	int n;
	scanf("%d", &n);
	switch(n)
	{
		case 1 :
			Sleep(1000);
			join_membership();
			break;
		case 2 :
			Sleep(1000);
			login();
			break;
		case 3 :
			Sleep(1000);
			logout();
			break;
		case 4 : 
			Sleep(1000);
			guess_words();
			break;
		case 5 :
			Sleep(1000);
			membership_wishdrawal();
			break;
		case 6 :
			Sleep(1000);
			end_program();
			break;
		default :
			printf("번호를 다시 입력하여주세요.");
			Sleep(1000);
			menu();
	}
}
void join_membership(void)
{
	printf("회원가입 페이지\n");
	printf("아이디 : ");
	scanf("%s", &member[i].id);
	printf("비밀번호 : ");
	scanf("%s", &member[i].password);
	printf("이름 :");
	scanf("%s", &member[i].name);
	FILE *fp=fopen("member.txt", "w");
	for(int z=0; z<=i; z++)
	{	
	    fputs(member[i].id, fp);
   		fputs("\n", fp);
   		fputs(member[i].password, fp);
   		fputs("\n", fp);
   		fputs(member[i].name, fp);
   		fputs("\n", fp);
   		fputs("\n", fp);	
	}
	fclose(fp);
	i++;
	menu();
}
void login(void)
{
	printf("로그인\n");
	printf("아이디 : ");
	scanf("%s", &n1);
	printf("비밀번호 : ");
	scanf("%s", &n2);
	account=1;
	menu();
}
void logout(void)
{
	printf("정말 로그아웃 하시겠습니까? [y/n]: ");
	getchar();
	scanf("%c", &z);
	if(z=='y')
	{
		account=0; 
		menu();
	}
	else if(z=='n')		
		menu();
	else
	{
		printf("잘못 입력하셨습니다.다시 입력해주세요.\n");
		logout();
	}
}
void guess_words(void)
{
	printf(">> 영어 단어 맞추기 프로그램 <<\n");
	printf("1. 영어 단어 맞추기 2. 프로그램 종료\n");
	printf("번호를 선택하세요.");
	getchar();
	scanf("%c", &z);
	if(z=='1')
	{
		
	}
	else if(z=='2')
	{
		menu();
	}
	else
	{
		printf("잘못입력하셨습니다. 다시 입력하여 주세요.\n");
		guess_words();
	}
}
void membership_wishdrawal(void)
{
	printf("정말 회원을 탈퇴하시겠습니까? [y/n]: \n");
	getchar();
	scanf("%c", &z);
	if(z=='y')
	{
		if(account==0)
		{
			printf("로그인 중이 아닙니다.");
			Sleep(1000);
			menu();
		} 
		if(account==1)
		{
			printf("탈퇴 완료되었습니다.");
			Sleep(1000);
			i--;
			account=0;
			menu();
		} 
	}
	else if(z=='n')
		menu();
	else
	{
		printf("잘못입력하셨습니다. 다시 입력하여 주세요.");
		membership_wishdrawal();
	}
}
void end_program(void)
{
	printf("다음에 또 만나요!!!");
}
