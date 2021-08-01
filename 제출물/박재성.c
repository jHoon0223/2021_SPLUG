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
	printf("=                �޴�                 =\n");
	printf("=======================================\n");	
	printf("          1. ȸ������                  \n");
	printf("          2. �α���                    \n");
	printf("          3. �α׾ƿ�                  \n");
	printf("          4. ���� �ܾ� ���߱�          \n");
	printf("          5. ȸ�� Ż��                 \n");
   	printf("          6. ���α׷� ����             \n");		
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
		printf("ȸ������ ������\n");
		printf("���̵�: ");
		scanf("%s",temp);		
		while(1)
		{
			fscanf(m_list,"%s",tmp);
			if(0==strcmp(temp,tmp))
			{
				printf("�̹� �����ϴ� ���̵� �Դϴ�.\n"); 
				Sleep(3000);
				break;
			}
			else
			{
				check=1;
			}
		}
	}while(check==0);
	printf("��밡���� ���̵��Դϴ�\n.");
	fclose(m_list);
	m_list=fopen("m_list.txt","a");
	fprintf(m_list,"%s ",temp);
	
	printf("��й�ȣ: ");
	scanf("%s",temp);
	fprintf(m_list,"%s ",temp);
	
	printf("�̸�: ");
	scanf("%s",temp);
	fprintf(m_list,"%s\n",temp);
	
	fclose(m_list);
	printf("���� �Ϸ�");
	
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
					printf("�α���\n");
					printf("���̵�: ");
					scanf("%s",usr.id);
					getchar(); 
					printf("��й�ȣ: ");
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
				printf("���� �α׾ƿ� �Ͻðڽ��ϱ�? [y/n]: ");
				scanf("%c",ok);
				if(ok=='y'||ok=='Y')
					id[0]="\0";
			else
			{
				printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.");
				Sleep(3000);
			}
			system("cls");
		}
		
		else if(check==4)
		{	
			char flag;
			system("cls"); 
			printf(">> ���� �ܾ� ���߱� ���α׷� <<\n");
			printf("1. ���� �ܾ� ���߱� 2. ���α׷� ����\n\n");
			printf("��ȣ�� �����ϼ���: ");
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
				printf("�α��� ���°� �ƴմϴ�.");
				Sleep(3000);
			}
				system("cls"); 
		}	
		else
		system("cls");
		

	} while(check != 6);
	
	printf("������ �� ������!!");
	return 0;
} 
