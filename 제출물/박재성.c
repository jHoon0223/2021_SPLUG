#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>



void menu_display(char a[])
{
	int i;
	printf("=======================================\n");
	printf("===============2021 SPLUG==============\n");
	if(a[0]!="\0")
	{	
		int c=strlen(a); 
		for(i=1;i<39-c;i++)
			printf("=");
		printf("%s",a); 
	}
	else
		printf("=======================================\n");
		
	printf("=======================================\n");
	printf("=                메뉴                 =\n");
	printf("=======================================\n");	
	printf("          1. 회원가입                  \n");
	printf("          2. 로그인                    \n");
	printf("          3. 로그아웃                  \n");
	printf("          4. 영어 단어 맞추기          \n");
	printf("          5. 회원 탈퇴                 \n");
   	printf("          6. 프로그램 종료             \n");		
	printf("=======================================\n");
	
}


void signup()
{
	FILE *m_list;
	int flag;
	char temp[20],tmp[20];
	int check=0,j=1;
		
	m_list=fopen("m_list.txt","r");
/*	if(m_list==NULL)
	{
		fclose(m_list);
		m_list=fopen("m_list.txt","w");
		fclose(m_list);
	}
*/	do
	{
		printf("회원가입 페이지\n");
		printf("아이디: ");
		scanf("%s",temp);		
		while(1)
		{
			fscanf(m_list,"%s",tmp);
			if(0==strcmp(temp,tmp))
			{
				printf("이미 존재하는 아이디 입니다.\n"); 
				Sleep(3000);
				break;
			}
			else
			{
				check=1;
			}
		}
	}while(check==0);
	printf("사용가능한 아이디입니다\n.");
	fclose(m_list);
	m_list=fopen("m_list.txt","a");
	fprintf(m_list,"%s ",temp);
	
	printf("비밀번호: ");
	scanf("%s",temp);
	fprintf(m_list,"%s ",temp);
	
	printf("이름: ");
	scanf("%s",temp);
	fprintf(m_list,"%s\n",temp);
	
	fclose(m_list);
	printf("가입 완료");
	
}


	


typedef struct eng_word
{
	char eng[20];
	char kor[20];
	struct eng_word *next;
} word;

void test()
{	
	char temp[20];
	FILE *dic;
	struct eng_word *head,*node,*last; 
	dic= fopen("dic","r");
	fseek(dic,0,0);
	int cnt,cor,flag=1;
	head=NULL;
	last=NULL;
	
	
	while(flag)
	{	
		node=(word *)malloc(sizeof(word));	
		fscanf(dic,"%s",temp);
		strcpy(head->eng,temp);
		fscanf(dic,"%s",temp);
		strcpy(head->eng,temp);
		if(EOF==temp)
		{	
			last=node;
			break;
		}
		
		
		fscanf("%[^ \n]",head->kor);
		node->next=NULL;
		if(head==NULL)
			head=node;
		else
		{
			last->next=node;	
		}
		last=node;
	}
	fclose(dic);
	
	
	
}

typedef struct membership
{
	char id[20];
	char pw[20];
	char name[20];
	struct membership *next;
}member;

int withdrawal(char a[])
{	
	int flag=1;
	char temp1[20],temp2[20],temp3[20];
	FILE *m_list;
	struct membership *h,*n,*l;
	m_list= fopen("m_list.txt","r");
	fseek(m_list,0,0);
	
	while(flag)
	{		
		fscanf(m_list,"%s",temp1);
		fscanf(m_list,"%s",temp2);
		fscanf(m_list,"%s",temp3);
		
		if(feof(m_list))
			break;
			
		n=(member *)malloc(sizeof(member));
		strcpy(h->id, temp1);
		strcpy(h->pw, temp2);
		strcpy(h->name, temp3);	
		n->next=NULL;
		if(h==NULL)
			h=n;
		else
		{
			l->next=n;	
		}
		l=n;
	
	}
	fclose(m_list);
	m_list=fopen("m_list.txt","w");
	while(h!=NULL)
	{	
		if(0!=strcmp(a,h->id))
		{
			fprintf(m_list,"%s ",h->id);
			fprintf(m_list,"%s ",h->pw);
			fprintf(m_list,"%s\n",h->name);
		}
		h=h->next;
	}
	fclose(m_list);
	
	
  	return 0;
}


int main()
{   
	char id[20]="\0",temp[20];
    int check=0;
    do
	{ 
		menu_display(id);
		
		scanf("%d",&check);
		if(check==1)
		{
			system("cls");
			signup();
			system("cls");
		}
		
		else if(check==2)
		{
			system("cls");
			struct log
{	
	char id[20];
	char pw[20];
};
			
				int k=1,flag=1;
				FILE *m_list;
				struct log usr;
				m_list=fopen("m_list.txt","r");
				while(flag==1)
				{	
					printf("로그인\n");
					printf("아이디: ");
					scanf("%s",usr.id);
					getchar(); 
					printf("비밀번호: ");
					scanf("%s",usr.pw);
					getchar();
					
					while(k)
					{
						int i=strcmp(usr.id,fscanf(m_list,"%s"));
						int j=strcmp(usr.pw,fscanf(m_list,"%s"));
						if(i==0)
							if(j==0)
							{
								flag=0;
								break;
							}
						break;
					}	
				}
					
		strcpy(id,usr.id);
			system("cls");
		}	
		
		else if(check==3)
		{   
			if(id[0]!="\0")
			{
				char ok;
				printf("정말 로그아웃 하시겠습니까? [y/n]: ");
				scanf("%c",ok);
				if(ok=='y'||ok=='Y')
					id[0]="\0";
			else
			{
				printf("로그인 되지 않았습니다. 다시 시도하세요.");
				Sleep(3000);
			}
			system("cls");
		}
		
		else if(check==4)
		{	
			char flag;
			system("cls"); 
			printf(">> 영어 단어 맞추기 프로그램 <<\n");
			printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");
			printf("번호를 선택하세요: ");
			scanf("%c",&flag);
			getchar();
			if(flag=="1")
			
				test();
				system("cls");
			}
			else
			system("cls");
		}
		
		else if(check==5)
		{
			if(id[0]!="\0")
			{
				withdrawal(id[20]);
				id[0]="\0";
				system("cls");
			}	
			else
			{
				printf("로그인 상태가 아닙니다.");
				Sleep(3000);
			}
				system("cls"); 
		}	
		else
		system("cls");
		

	} while(check != 6);
	
	printf("다음에 또 만나요!!");
	return 0;
} 
