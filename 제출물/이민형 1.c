#include <stdio.h>
#include <stdlib.h>
#include <string.h>

_Bool logInState=0;
char currentID[100];

void UI();
void createAccount();
void logIn();
void logOut();
void engQuizUI();
void deleteAccount();
void engWordQuiz();
void saveUser();

struct User
{
    struct User *next;
    char ID[100];
    char PW[100];
    char Name[100];
};


int main()
{
    int input;
    _Bool run=1;

    struct User *head=malloc(sizeof(struct User));
    head->next=NULL;

    system("clear");
    printf("============================\n");
    while(run)
    {
        FILE *fp=fopen("user.txt", "rb");

        head->next=NULL;
        while(!feof(fp))
        {
            char a[20], b[20], c[20];
            struct User *users=malloc(sizeof(struct User));
            users->next=head->next;
            fscanf(fp, "%s %s %s\n", a, b, c);
            strcpy(users->ID, a);
            strcpy(users->PW, b);
            strcpy(users->Name, c);
            head->next=users;
        }
        fclose(fp);

        if(logInState)
        {
            for(int i=0; i<28-(strlen(currentID)+1); i++)
                printf("=");
            printf(" %s\n", currentID);
        }
        else
            printf("============================\n");
        printf("=           메뉴           =\n");
        printf("============================\n");
        printf("      1. 회원가입\n");
        printf("      2. 로그인\n");
        printf("      3. 로그아웃\n");
        printf("      4. 영어 단어 맞추기\n");
        printf("      5. 회원 탈퇴\n");
        printf("      6. 프로그램 종료\n");
        printf("============================\n:");
        scanf("%d", &input);
        getchar();
        switch(input)
        {
            case 1:
                createAccount(head);
                break;
            case 2:
                logIn(head);
                break;
            case 3:
                logOut();
                break;
            case 4:
                engQuizUI();
                break;
            case 5:
                deleteAccount(head);
                break;
            case 6:
                system("clear");
                printf("[system] 다음에 또 만나요. :)\n");
                run=0;
                break;
            default:
                system("clear");
                printf("[system] 다시 입력하세요.\n");
                break;
        }
    }
}

void createAccount(struct User *node)
{
    char inputID[100], inputPW[100], inputName[100];

    system("clear");
    if(logInState)
        printf("[system] 로그아웃 후 다시 시도해 주세요.\n");
    else
    {
        printf("============================\n");
        printf("============================\n");
        printf("=         회원가입         =\n");
        printf("============================\n");
        while(1)
        {
            _Bool notUnique=0;
            printf("ID : "); 
            scanf("%s", inputID);
            struct User *curr=node->next;
            while(curr!=NULL)
            {
                if(strcmp(curr->ID, inputID)==0)
                {
                    notUnique=1;
                    break;
                }
                curr=curr->next;
            }
            if(notUnique)
                printf("[system] 이미 사용중인 ID입니다.\n");
            else
            {
                printf("[system] 사용 가능한 ID입니다.\n");
                break;
            }
        }
        printf("PW : ");
        scanf("%s", inputPW);
        printf("이름 : ");
        scanf("%s", inputName);

        struct User *curr = malloc(sizeof(struct User));
        curr->next=node->next;
        strcpy(curr->ID, inputID);
        strcpy(curr->PW, inputPW);
        strcpy(curr->Name, inputName);
        node->next=curr;

        FILE *fp=fopen("user.txt", "wb");
        curr=node->next;
        while(curr!=NULL)
        {
            fprintf(fp, "%s %s %s\n", curr->ID, curr->PW, curr->Name);
            curr=curr->next;
        }
        fclose(fp);
        
        system("clear");
        printf("[system] 회원가입이 완료되었습니다.\n");
    }
}

void logIn(struct User *node)
{
    char inputID[100], inputPW[100];

    system("clear");
    if(logInState)
        printf("[system] 이미 로그인되어 있습니다.\n"); 
    else
    {
        printf("============================\n");
        printf("============================\n");
        printf("=          로그인          =\n");
        printf("============================\n");  
        printf("ID : ");
        scanf("%s", inputID);
        printf("PW : ");
        scanf("%s", inputPW);
        struct User *curr=node->next;
        while(curr!=NULL)
        {
            if(strcmp(curr->ID, inputID)==0&&strcmp(curr->PW, inputPW)==0)
            {
                logInState=1;
                break;
            }
            curr=curr->next;
        }
        if(logInState)
        {
            strcpy(currentID, inputID);
            system("clear");
            printf("[system] %s님 환영합니다.\n", curr->Name);
        }
        else
        {
            system("clear");
            printf("[system] ID나 비밀번호가 일치하지 않습니다. 다시 시도하세요.\n");
        }
    }
}

void logOut()
{
    if(logInState)
    {
        char answer;
        printf("[system] 정말 로그아웃 하시겠습니까? [y/n] : ");
        scanf("%c", &answer);
        getchar();
        system("clear");
        if(answer=='y'||answer=='Y')
        {
            printf("[system] 정상적으로 로그아웃 되었습니다.\n");
            logInState=0;
        }
        else
            printf("============================\n");
    }
    else
    {
        system("clear");
        printf("[system] 로그인 되지 않았습니다. 다시 시도하세요.\n");
    }
}

void engQuizUI()
{
    int input;
    _Bool run=1;
    system("clear");
    if(logInState)
    {
        printf("============================\n");
        for(int i=0; i<28-(strlen(currentID)+1); i++)
                printf("=");
        printf(" %s\n", currentID);
        printf("=     영어 단어 맞추기     =\n");
        printf("============================\n");
        printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");
        while(run)
        {
            printf("번호를 선택하세요 : ");
            scanf("%d", &input);
            getchar();
            switch(input)
            {
                case 1:
                    engWordQuiz();
                    run=0;
                    break;
                case 2:
                    run=0;
                    system("clear");
                    printf("============================\n");
                    break;
                default:
                    printf("다시 입력하세요.\n");
                    break;
            }   
        }
    }
    else
        printf("[system] 로그인 후 이용해 주세요.\n");
}

void deleteAccount(struct User *node)
{
    if(logInState)
    {
        char answer;
        printf("[system] 정말 회원 탈퇴하시겠습니까? [y/n] : ");
        scanf("%c", &answer);
        getchar();
        system("clear");
        if(answer=='y'||answer=='Y')
        {
            struct User *curr=node;
            struct User *prev=NULL;
            while(curr!=NULL)
            {
                if(strcmp(curr->ID, currentID)==0)
                {
                    prev->next=curr->next;
                    free(curr);
                    break;;
                }
                prev=curr;
                curr=curr->next;
            }
            FILE *fp=fopen("user.txt", "wb");
            curr=node->next;
            while(curr!=NULL)
            {
                fprintf(fp, "%s %s %s\n", curr->ID, curr->PW, curr->Name);
                curr=curr->next;
            }
            fclose(fp);
            printf("[system] 정상적으로 회원 탈퇴 되었습니다.\n");
            logInState=0;
        }
        else
            printf("============================\n");
    }
    else
    {
        system("clear");
        printf("[system] 로그인 상태가 아닙니다.\n");
    }
}
