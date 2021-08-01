#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

typedef struct Node {
    char *data1;
    char *data2;
    char *data3;
    struct Node *link;
} Node;

Node *list1=(struct Node*)malloc(sizeof(Node));




int login_status=0;//�α��� ���� 
int Basic_status(char *loginID);//�⺻���� 
void join_membership(); //ȸ������ 
void out_membership(char *loginID,int chch); //ȸ��Ż�� 
char* login(); //�α��� 
void logout(char *loginID); //�α׾ƿ� 
void game(); //���� ����  
void ascend_insertion_sort(char *word1[],char *word2[],int a);  //�������� 
void append(Node *ptr, char *newData,char *newData1,char *newData2);

int main(){
	int usr=0,chch=0;
	char * loginID=NULL;
	FILE * fp=fopen("usr.txt","at");
	fclose(fp);
	while(usr!=6){
		usr=Basic_status(loginID);
		
		if(usr==1)
			join_membership();
		
		if(usr==2)
			loginID=login();	
				
		if(usr==3)
			logout(loginID);
			
		if(usr==4)
			game();
		
		if(usr==5){
			out_membership(loginID,chch);
			chch=1;
		}
	}	
	system("cls");
	printf("������ �� ������~~");
	return 0;	
	
}
void join_membership(){
	system("cls");
	int ret;
	int pass=1;
	char ID[30];
	char password[30];
	char name[30]; 
	char overlap[30];
	char overlap2[30];
	char overlap3[30];
	printf("ȸ������ ������       �ڷΰ���: 9\n");
	while(pass==1){
		pass=0;
		printf("���̵� : ");
		scanf("%s",ID);
		if(strcmp("9",ID)==0)
			return ;
		FILE * fp=fopen("usr.txt","rt");
		while((ret=fscanf(fp,"%s %s %s",overlap,overlap2,overlap3))!=EOF){
			if(strcmp(overlap,ID)==0){
				printf("�̹� �����ϴ� ���̵� �Դϴ�.\n");
				pass=1;
				break;
			}
		}
		fclose(fp);
	}
		printf("��밡���� ���̵� �Դϴ�.\n");
		printf("��й�ȣ : ");
		scanf("%s",password);
		printf("�̸� : ");
		scanf("%s",name);
		FILE * fp=fopen("usr.txt","at");
		fprintf(fp,"%s %s %s\n",ID,password,name);
		fclose(fp);	
}




char* login(){
	system("cls");
	char ID[30];
	char password[30];
	int pass=1,ret,pass2=1; 
	char overlap[30];
	char overlap2[30];
	char overlap3[30];	
	printf("�α���       �ڷΰ���: 9\n"); 
	while(pass==1){
		pass=0;
		pass2=1;
		printf("���̵� : ");
		scanf("%s",ID);
		if(strcmp("9",ID)==0)
			return NULL;
		printf("��й�ȣ : ");
		scanf("%s",password);
		FILE * fp=fopen("usr.txt","rt");
		while((ret=fscanf(fp,"%s %s %s",overlap,overlap2,overlap3))!=EOF){
			if(strcmp(overlap,ID)==0){
				pass2=0;
				if(strcmp(overlap2,password)==0){
				char * loginID = (char*)malloc(sizeof(ID));
				login_status=1;
				strcpy(loginID,ID);
				return loginID;
				}
				else{
					printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n");
					pass=1;
					break;
				}
			}
		}
		fclose(fp);
		if(pass2==1){
			printf("���̵� �������� �ʽ��ϴ�.\n");
			pass=1; 
			}
	}
}

int Basic_status(char * loginID){
	system("cls");
	int usr;
	if(login_status==0){
		printf("=====================\n");
		printf("======2021SPULG======\n");
		printf("=====================\n");
		printf("=        �޴�       =\n");
		printf("=====================\n");
		printf("  1.ȸ������         \n");
		printf("  2.�α���           \n");
		printf("  3.�α׾ƿ�         \n");
		printf("  4.���� �ܾ� ���߱� \n");
		printf("  5.ȸ��Ż��         \n");
		printf("  6.���α׷� ����    \n");
		printf("=====================\n");	
	}
	else{
		printf("=====================\n");
		printf("======2021SPULG======\n");
		printf("ID : %s\n",loginID);
		printf("=        �޴�       =\n");
		printf("=====================\n");
		printf("  1.ȸ������         \n");
		printf("  2.�α���           \n");
		printf("  3.�α׾ƿ�         \n");
		printf("  4.���� �ܾ� ���߱� \n");
		printf("  5.ȸ��Ż��         \n");
		printf("  6.���α׷� ����    \n");
		printf("=====================\n");			
	}
	while(1){
		printf(":");
		scanf("%d",&usr);
		if((usr==1||usr==2)&&login_status==1){
			printf("�̹� �α����� �Ǿ��ֽ��ϴ�. �ٽ� �õ��� �ּ���.\n");
			continue;		
		}
		if((usr==3||usr==5||usr==4)&&login_status==0){
			printf("�α����� �����ʾҽ��ϴ�. �ٽ� �õ��� �ּ���.\n");	
			continue;
		}
		if(usr>6||usr<1){
			printf("�߸��Է��ϼ̽��ϴ�.\n");
			continue;
		}
		break;
	}
	if(usr==1)
		return 1;
	if(usr==2)
		return 2;
	if(usr==3)
		return 3;
	if(usr==4)
		return 4;		
	if(usr==5)
		return 5;
	if(usr==6)
		return 6;			
}

void logout(char *loginID){
	char yn='y';
	while((yn!='y')||(yn!='n')){
		while(getchar()!='\n');
		printf("���� �α׾ƿ� �ϱ�ڽ��ϱ�? [y/n]:");	
		scanf("%c",&yn);
		if(yn=='y'){
			login_status=0;
			free(loginID);
			break;
		}
		
		if(yn=='n')
			break;
		
	printf("�߸��Է��ϼ̽��ϴ�.\n");	
		
	}
}


void game()	{
	system("cls");
	int ret,num,i=0,j=0;
	char *word1[160];
	char *word2[160];
	char simple1[30];
	char simple2[30];
	printf(">>���� �ܾ� ���߱� ���α׷�<<\n");
	printf("1. ���� �ܾ� ���߱� 2.���α׷� ����\n\n");
	printf("��ȣ�� �����ϼ���.\n");
	scanf("%d",&num);
	if(num==2)
		return ; 
	FILE * fp=fopen("dic.txt","rt");
	while((ret=fscanf(fp,"%s %s",simple1,simple2))!=EOF){
		word1[i] = (char*)malloc(sizeof(simple1));
		word2[i] = (char*)malloc(sizeof(simple2));
		strcpy(word1[i],simple1);
		strcpy(word2[i],simple2);
		i=i+1;
	}
	fclose(fp);
	num=0;
	for(j=0;j<i-1;j++)
		ascend_insertion_sort(word1,word2,j);

	
		
	i=0;	
	while((strcmp(simple1,".quit")!=0)&&i!=101){
		printf("%s > ",word2[i]);
		scanf("%s",simple1);
		if(strcmp(simple1,word1[i])==0)
			num++;
		i++;
	}
	printf("%d��ŭ �����ƽ��ϴ�",num);
	Sleep(5000);
}

void out_membership(char *loginID,int chch){
	char yn='y';
	while(getchar()!='\n');
	printf("���� ȸ��Ż�� �Ͻðڽ��ϱ� ? [y/n]:");
	scanf("%c",&yn);
	if(yn=='n')
		return ;	 
	if(chch==0){
		int ret;
		char overlap[30];
		char overlap2[30];
		char overlap3[30];
		FILE * fp=fopen("usr.txt","rt");
		list1->link=NULL;
		while((ret=fscanf(fp,"%s %s %s",overlap,overlap2,overlap3))!=EOF){
			char * o1 = (char*)malloc(sizeof(overlap));
			char * o2 = (char*)malloc(sizeof(overlap2));
			char * o3 = (char*)malloc(sizeof(overlap3));
			strcpy(o1,overlap);
			strcpy(o2,overlap2);
			strcpy(o3,overlap3);
			append(list1,o1,o2,o3);
		}
		fclose(fp);
	}
	
	Node *cur = list1;
    Node *next;
    while(cur != NULL)
    {
    	next = cur->link;
        if((strcmp(next->data1,loginID))==0){
        	free(next->data1);
        	free(next->data2);
        	free(next->data3);
        	cur->link=next->link;
        	free(next);
        	login_status=0;
			free(loginID);
			break;
		}
        cur = next;
    }
	FILE * fp=fopen("usr.txt","wt");

    Node *cur1 = list1->link;
    while(cur1 != NULL)
    {
    	fprintf(fp,"%s %s %s\n",cur1->data1,cur1->data2,cur1->data3);
        cur1 = cur1->link;
    }
	fclose(fp);
}

void ascend_insertion_sort(char *word1[],char *word2[],int a){
	int j=a;
	char *temp_word;
	while(strcmp(word1[j],word1[j+1])>0){
		temp_word=word1[j];
		word1[j]=word1[j+1];
		word1[j+1]=temp_word;
		temp_word=word2[j];
		word2[j]=word2[j+1];
		word2[j+1]=temp_word;
		j--;
		if(j==-1){
			break ;
		}
	}
}

void append(Node *list, char *newData,char *newData1,char *newData2){
    if(list->link == NULL){
        Node *newNode = (struct Node*)malloc(sizeof(Node));
        newNode->data1 = newData;
        newNode->data2 = newData1;
        newNode->data3 = newData2;
        newNode->link = NULL;
 
        list->link = newNode;
    }
    else
    {
        Node *cur = list;
        while(cur->link != NULL)
        {
            cur = cur->link;
        }
        Node *newNode = (struct Node*)malloc(sizeof(Node));
        newNode->data1 = newData;
        newNode->data2 = newData1;
        newNode->data3 = newData2;
        newNode->link = NULL;
 
        cur->link = newNode;
    }
}




	 
	
