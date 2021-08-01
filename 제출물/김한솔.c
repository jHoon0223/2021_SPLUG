#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//문자열 입력받아 동적할당 받는 문자열 생성
const char *newstring(const char *source) 
{
    if(!source)
    {
        return NULL;
    }

    int length = strlen(source);

    if(!length)
    {
        return NULL;
    }

    char *str = (char*)calloc(length + 1, sizeof(char));
    strcpy(str, source);
    return str;
}


//문자열 가르키는 두 개의 포인터를 입력 받아서 두 문자열 스왑
void swapstring(const char **ptr1, const char **ptr2)
{
    const char *str1 = *ptr1;
    const char *str2 = *ptr2;

    *ptr1 = str2;
    *ptr2 = str1;
}


//링크드 리스트를 구성하는 노드 생성
typedef struct _Node 
{
    const char *data1; //단어와 아이디
    const char *data2; //뜻과 비밀번호
    const char *data3; //이름

    struct _Node *next;
} Node; //node 라고 명칭


//데이터를 가지는 노드 동적할당해주기
Node *createnode(const char *data1, const char *data2, const char *data3) 
{
    Node *node = (Node*)malloc(sizeof(Node)); //동적메모리 할당

    node -> data1 = newstring(data1);
    node -> data2 = newstring(data2);
    node -> data3 = newstring(data3);

    node -> next = NULL;

    return node;
}


//prev 노드 다음에 targer 노드 만들기
void insertnode(Node *prev, Node *target)
{
    target -> next = prev -> next;
    prev -> next = target;
}


// 파일의 데이터를 읽어와 링크드리스트로 변환
// isword 의 값이 0일 때와 1일 때 구분
// isword 가 0 이면 단어 파일(dic.txt) 
// isword 가 1 이면 계정 파일(accoint.txt)
// 계정 파일이면 이름까지 입력 받음.
Node *readlistfromfile(const char* filename, int isword)
{
    Node *head = createnode(NULL, NULL, NULL);

    FILE *fp = fopen(filename, "rt");

    if(fp)
    {
        Node *last = head;

        char data1[100];
        char data2[100];
        char data3[100] = "";
        
        while(fscanf(fp, "%s %s", data1, data2) == 2)
        {
            if(!isword)
            {
                fscanf(fp, "%s", data3);
            }

            Node *node = createnode(data1, data2, data3);
            insertnode(last, node);
            last = node;
        }
        
        fclose(fp);
    }

    if(isword)
    {
        int swapped;
        Node *node;
        Node *last = NULL;

        do
        {
            swapped = 0;
            node = head -> next;

            while(node -> next != last)
            {
                if(strcmp(node -> data1, node -> next -> data1) > 0)
                {
                    swapstring(&node -> data1, &node -> next -> data1);
                    swapstring(&node -> data2, &node -> next -> data2);

                    swapped = 1;
                }

                node = node -> next;
            }

            last = node;

        }while(swapped);
    }

    return head;
}

//파일명과 헤드를 받아 링크드리스트의 내용을 파일에 저장
void savelisttofile(const char *filename, const Node *head)
{
    FILE *fp = fopen(filename, "wt");

    const Node *n = head -> next;

    while(n)
    {
        if(n -> data3)
        {
            fprintf(fp, "%s %s %s\n", n -> data1, n -> data2, n -> data3);
        }
        else
        {
            fprintf(fp, "%s %s\n", n -> data1, n-> data2);
        }

        n = n -> next;
    }

    fclose(fp);
}

int prompt(const char *question)
{
    char answer[10];

    while(1)
    {
        printf("%s [y/n] : ", question);
        scanf("%s",answer);

        if(!strcmp(answer, "y") || !strcmp(answer, "Y"))
        {
            return 1;
        }
        if(!strcmp(answer, "n") || !strcmp(answer, "N"))
        {
            return 0;
        }
    }
}

//메뉴를 구성하는 배열 생성
const char *MENU[] = {"회원가입" , "로그인" , "로그아웃" , "영어 단어 맞추기" , "회원 탈퇴" , "프로그램 종료"};


//로그인 했을 떄와 로그인 하지 않았을 떄를 구분
//로그인 하면 우측 상단에 아이디 문자열 길이만큼 = 뺴고 아이디 출력
//로그인 하지 않았을 시 우측 상단에 =====출력
int menu(const char *id)
{

    printf("==============================\n");
    printf("========= 2021 SPLUG =========\n");

    if(id)
    {
        int len = strlen(id);

        for(int i = 0; i < 29 - len; i++)
        {
            printf("=");
        }
        printf(" %s\n", id);
    }
    else
    {
        printf("==============================\n");
    }

    printf("==============================\n");
    printf("=            메뉴            =\n");
    printf("==============================\n");

    for(int i = 0; i < 6; i++)
    {
        printf("%9d. %s\n", i+1, MENU[i]);
    }
    printf("==============================\n");

    int input;

    do
    {
        printf("number : ");
        scanf("%d", &input);
    }while(input < 1 || input > 6);

    return (input - 1);
}

//아이디와 비밀번호가 일치하는지 확인
int matchaccount(const Node *accounts, const char *id, const char *pw)
{
    const Node *n = accounts -> next;

    while(n)
    {
        if(!strcmp(n -> data1, id))
        {
            if(!pw || !strcmp(n -> data2, pw))
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
        n = n -> next;
    }
    return 0;
}

//회원가입
//아이디가 이미 존재할 시 이미 존재한다는 메세지 출력
//사용 가능하면 사용 가능하다는 메세지 출력 후 비밀번호와 이름까지 입력받아 accounts.txt 파일에 저장
void signup(Node *accounts)
{
    char id[100] = ""; 

    printf("회원가입 페이지\n");

    do
    {
        if (strlen(id) > 0)
        {
            printf("이미 존재하는 아이디입니다.\n");
        }
        printf("아이디 : ");
        scanf("%s", id);
    }while(matchaccount(accounts, id, NULL));
    printf("사용가능한 아이디입니다.\n");

    char pw[100];
    char name[100];

    printf("비밀번호 : ");
    scanf("%s", pw);

    printf("이름 : ");
    scanf("%s", name);

    insertnode(accounts, createnode(id, pw, name));
    savelisttofile("accounts.txt", accounts);
}

//로그인
const char *login(const Node *accounts)
{
    char id[100] = "";
    char pw[100];
    printf("로그인\n");

    do
    {
        if(strlen(id) > 0)
        {
            printf("아이디나 비밀번호를 잘못 입력하였습니다. 다시 시도하세요. \n");
        }

        printf("아이디 : ");
        scanf("%s",id);
        printf("비밀번호 : ");
        scanf("%s",pw);

    }while(!matchaccount(accounts, id, pw));

    return newstring(id);
}

//영어단어 맞추기 기능
void wordtest(const Node *words)
{
    printf(">> 영어 단어 맞추기 프로그램 <<\n");
    printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");

    int menu;
    do
    {
        printf("번호를 입력하세요 : ");
        scanf("%d", &menu);
    }while(menu < 1 || menu > 2);

    if(menu == 2)
    {
        return;
    }

    double o = 0;
    double x = 0;
    char input[100];
    Node *n = words -> next;

    while(n)
    {
        printf("%s -> ", n -> data2);
        scanf("%s", input);

        if(!strcmp(input, ".quit"))
        {
            break;
        }

        if(!strcmp(n -> data1, input))
        {
            printf("correct!\n");
            o += 1;
        }
        else
        {
            printf("incorrect!\n");
            x += 1;
        }

        n = n -> next;
    }

    printf("당신의 점수는 %.2f점 입니다.\n", (o/(o+x)*100));
}


//계정 삭제
void removeaccount(const char *id, Node *accounts)
{
    Node *p = accounts;
    Node *n = accounts -> next;

    while(n)
    {
        if(!strcmp(n -> data1, id))
        {
            p -> next = n -> next;
            free(n);
            break;
        }

        p = n;
        n = n -> next;
    }

    savelisttofile("accounts.txt", accounts);
}

int main()
{
    const Node *words = readlistfromfile("dic.txt", 1);

    const char *id = NULL;

    Node *accounts = readlistfromfile("accounts.txt", 0);

    int loop = 1;

    while (loop)
    {
        switch(menu(id))
        {
            case 0: //1번 선택시 회원가입(id,pw,이름 입력받아 txt저장)
                signup(accounts);
                break;
            case 1: //2번 선택시 로그인(txt확인)
                if(id)
                {
                    printf("로그아웃을 먼저 해주세요.\n");
                }
                else
                {
                    id = login(accounts);
                }
                break;
            case 2: //3번 선택시 로그아웃(로그인 된 상태에서만 가능)
                if(!id)
                {
                    printf("로그인 되지 않았습니다. 다시 시도해주세요.\n");
                }
                else if(prompt("정말 로그아웃 하시겠습니까?"))
                {
                    free(id);
                    id = NULL;
                }
                break;
            case 3: //4번 선택시 영어단어 맞추기 프로그램(dic.txt)
                wordtest(words);
                break;
            case 4: //5번 선택시 회원 탈퇴(로그인 된 상태에서만 가능)
                if(!id)
                {
                    printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
                }
                else if(prompt("정말 탈퇴하시겠습니까?"))
                {
                    removeaccount(id, accounts);
                    free(id);
                    id = NULL;
                }
                break;
            case 5: //6번 선택시 프로그램 종료           
                loop = 0;
                break;
        }
    }

    printf("다음에 또 만나요!!\n\n");

    return 0;
}