#include<stdio.h>
#include<windows.h> //ȭ�� �ʱ�ȭ , Sleep 
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
	printf("=               �޴�               =\n");
	printf("\t1. ȸ������\n");
	printf("\t2. �α���\n");
	printf("\t3. �α׾ƿ�\n");
	printf("\t4. ���� �ܾ� ���߱�\n");
	printf("\t5. ȸ�� Ż��\n");
	printf("\t6. ���α׷� ����\n");
	if(account==0)
		printf("�α���X\n");
	else
		printf("�α�����\n");
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
			printf("��ȣ�� �ٽ� �Է��Ͽ��ּ���.");
			Sleep(1000);
			menu();
	}
}
void join_membership(void)
{
	printf("ȸ������ ������\n");
	printf("���̵� : ");
	scanf("%s", &member[i].id);
	printf("��й�ȣ : ");
	scanf("%s", &member[i].password);
	printf("�̸� :");
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
	printf("�α���\n");
	printf("���̵� : ");
	scanf("%s", &n1);
	printf("��й�ȣ : ");
	scanf("%s", &n2);
	account=1;
	menu();
}
void logout(void)
{
	printf("���� �α׾ƿ� �Ͻðڽ��ϱ�? [y/n]: ");
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
		printf("�߸� �Է��ϼ̽��ϴ�.�ٽ� �Է����ּ���.\n");
		logout();
	}
}
void guess_words(void)
{
	printf(">> ���� �ܾ� ���߱� ���α׷� <<\n");
	printf("1. ���� �ܾ� ���߱� 2. ���α׷� ����\n");
	printf("��ȣ�� �����ϼ���.");
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
		printf("�߸��Է��ϼ̽��ϴ�. �ٽ� �Է��Ͽ� �ּ���.\n");
		guess_words();
	}
}
void membership_wishdrawal(void)
{
	printf("���� ȸ���� Ż���Ͻðڽ��ϱ�? [y/n]: \n");
	getchar();
	scanf("%c", &z);
	if(z=='y')
	{
		if(account==0)
		{
			printf("�α��� ���� �ƴմϴ�.");
			Sleep(1000);
			menu();
		} 
		if(account==1)
		{
			printf("Ż�� �Ϸ�Ǿ����ϴ�.");
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
		printf("�߸��Է��ϼ̽��ϴ�. �ٽ� �Է��Ͽ� �ּ���.");
		membership_wishdrawal();
	}
}
void end_program(void)
{
	printf("������ �� ������!!!");
}
