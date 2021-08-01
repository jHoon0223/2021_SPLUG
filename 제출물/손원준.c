#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MN 105

char eng[MN][30],kor[MN][30],lgn[MN]={0};
int i,n,t,lgcon=0,cnt=0;

typedef struct node{
    struct node *next;
    char id[MN], psw[MN], name[MN];
};

void prt(){
    printf("============================\n");
    if(lgcon) printf("=================== %s\n", lgn);
    else printf("============================\n");
    printf("============MENU============\n");
    printf("============================\n");
    printf("%5d. ȸ������\n",1);
    printf("%5d. �α���\n",2);
    printf("%5d. �α׾ƿ�\n",3);
    printf("%5d. ���� �ܾ� ���߱�\n",4);
    printf("%5d. ȸ�� Ż��\n",5);
    printf("%5d. ���α׷� ����\n",6);
    printf("============================\n");
}
void first();
void second();
void third();
void fourth();
void fifth();
void addf(struct node *target, int a[], int b[], int c[]);
void addFirst(struct node *target, int arr[]);

int main(){
    FILE* dic = fopen("dic.txt", "r");
    FILE* user = fopen("user.txt", "r");

    for(i=1;i<=101;i++){
        fscanf(dic, "%s\n", eng[i]);
        fscanf(dic, "%s\n", kor[i]);
    }
    fclose(dic);

    struct node *head = malloc(sizeof(struct node));
    struct node *node1 = malloc(sizeof(struct node));
    head->next = node1;
    node1->next = NULL;

    fscanf(user, "%d", &n);
    for(i=1;i<=n;i++){
        int a[MN]={0},b[MN]={0},c[MN]={0};
        fscanf(user, "%s\n", a);
        fscanf(user, "%s\n", b);
        fscanf(user, "%s\n", c);
        addf(head, a, b, c);
    }
    fclose(user);
    FILE* us = fopen("user.txt", "w");

    srand(time(NULL));
    while(1){
        prt();
        int num;
        scanf("%d", &num);
        system("cls");
        if(num==1) first(head);
        else if(num==2) second(head);
        else if(num==3) third();
        else if(num==4) fourth();
        else if(num==5) fifth(head);
        else if(num==6){
            printf("�ȳ�~\n");
            fprintf(us, "%d\n", cnt);
            struct node *curr = head->next;
            while(curr->next!=NULL){
                fprintf(us, "%s %s %s\n", curr->id, curr->psw, curr->name);
                curr = curr->next;
            }
            fclose(us);
            break;
        }
        else printf("1~6������ ���� �Է�\n");
        system("pause");
        system("cls");
    }

    return 0;
}

void first(struct node* head){
    printf("ȸ������ ������\n");
    while(1){
        char str[MN]={0};
        printf("���̵� : ");
        scanf("%s", &str);
        int con = 0;
        struct node *curr = head->next;
        while(curr!=NULL){
            if(!strcmp(str,curr->id)) con = 1;
            curr = curr->next;
        }

        if(!con){
            addFirst(head, str);
            break;
        }
        else
            printf("�̹� �ִ� ���̵��Դϴ�\n");
    }
}

void second(struct node *head){
    char str[MN]={0},arr[MN]={0};
    printf("�α���\n");
    printf("���̵� : ");
    scanf("%s", str);
    printf("��й�ȣ : ");
    scanf("%s", arr);

    struct node *curr = head->next;
    while(curr!=NULL){
        if(!strcmp(curr->id,str)&&!strcmp(curr->psw,arr)) break;
        curr = curr->next;
    }
    if(curr==NULL) printf("�α��� ����!");
    else{
        lgcon = 1;
        strcpy(lgn, str);
    }
}

void third(){
    if(!lgcon) printf("�α׾ƿ��� �α��� �� ���¿����� �����մϴ�\n");
    else{
        lgcon = 0;
        for(int i=0;i<MN;i++) lgn[i] = 0;
    }
}

void fourth(){
    printf(">> ���� �ܾ� ���߱� ���α׷� <<\n");
    printf("1. ���� �ܾ� ���߱� 2. ���α׷� ����\n");
    printf("��ȣ�� �����ϼ��� : ");
    int con,cnt=0;
    scanf("%d", &con);
    if(con==1){
        while(1){
            char str[MN]={0};
            int pt = rand()%101;
            printf("%s -> ", kor[pt+1]);
            scanf("%s",str);
            if(!strcmp(".quit",str)) break;
            else if(!strcmp(eng[pt+1],str)){
                printf("correct!\n");
                cnt++;
            }
            else printf("incorrect!\n");
        }
        printf("����� ������ %d���Դϴ�.\n", cnt);
    }
}

void fifth(struct node* head){
    if(!lgcon) printf("�α��� ���°� �ƴմϴ�\n");
    else{
        char s;
        printf("���� ȸ�� Ż�� �Ͻðڽ��ϱ�? (y/n)\n");
        scanf("\n%c", &s);
        if(s=='y'){
            struct node *curr = head->next;
            struct node *ps = head;
            while(curr->next!=NULL){
                if(!strcmp(curr->id,lgn)) break;
                ps = curr;
                curr = curr->next;
            }
            removeFirst(ps);
            third();
        }
    }
}

void addf(struct node *target, int a[], int b[], int c[]){
    struct node *newNode = malloc(sizeof(struct node));

    newNode->next = target->next;
    strcpy(newNode->id, a);
    target->next = newNode;
    strcpy(newNode->psw, b);
    strcpy(newNode->name, c);
    cnt++;
}

void addFirst(struct node *target, int arr[]){
    struct node *newNode = malloc(sizeof(struct node));
    int ctr[MN]={0},dtr[MN]={0};

    newNode->next = target->next;
    strcpy(newNode->id, arr);
    target->next = newNode;
    printf("��й�ȣ : ");
    scanf("%s", ctr);
    strcpy(newNode->psw, ctr);
    printf("�̸� : ");
    scanf("%s", dtr);
    strcpy(newNode->name, dtr);
    cnt++;
}
void removeFirst(struct node *target){
    struct node *removeNode = target->next;
    target->next = removeNode->next;
    free(removeNode);
    cnt--;
}
