#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct member
{
    char id[20];
    char pw[20];
    char nm[20];
    struct member *next;
}member;

typedef struct dict{
    char en[20];
    char kr[20];
    struct dict *link;
}dict;

void join(void);
member *member_update(member *head);
int login(char *ID);
void member_delete(char *ID);
void problem(void);
dict *dic_update_sort(dict *head);
dict *sort(dict *head, int n);
void swap(dict *addr);


int main(void)
{
    member *list;
    int num = 0, status = 0;
    char check, ID[20];
    list = NULL;
    list = member_update(list);
    
    while(1)
    {
        printf("==================================\n=========== 2021 SPLUG ===========\n");
        if (status == 1)
        {
            
            for (int i = 0; i < 33 - strlen(ID); i++)
                printf("=");
            printf(" %s\n", ID);
        }
        
        else printf("==================================\n");

        printf("==================================\n=              메뉴              =\n==================================\n        1. 회원가입\n        2. 로그인\n        3. 로그아웃\n        4. 영어 단어 맞추기\n        5. 회원 탈퇴\n        6. 프로그램 종료\n==================================\n");
        
        scanf("%d", &num);
        getchar();

        if (num == 1)//회원가입
        {
            join();
            continue;
        }
        
        if (num == 2)//로그인
        {
            status = login(ID);
            continue;
        }
        
        if (num == 3)//로그아웃
        {
            if (status != 1)
            {
                printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
                continue;
            }
            else 
            {
                printf("정말 로그아웃 하시겠습니까? [y/n]: ");
                scanf("%c", &check);
                if (check == 'y')
                {
                    status = 0;
                    continue;
                }
                else continue;
            }
        }
        
        if (num == 4)//영단어
        {
            problem();
            continue;
        }
        
        if (num == 5)//회원탈퇴
        {
            if (status != 1)
            {
                printf("로그인 상태가 아닙니다.\n");
                continue;
            }
            else 
            {
                printf("정말 회원을 탈퇴하시겠습니까? [y/n]: ");
                scanf("%c", &check);
                if (check == 'y')
                {
                    member_delete(ID);
                    status = 0;
                    continue;
                }
            }
        }
        
        if (num == 6)//종료
        {
            printf("다음에 또 만나요!!");
            break;
        }
    
    }
    return 0;
}


void join(void)
{
    member *list_head, *cur;
    char Id[20], Pw[20], Nm[20];
    int c, n, m=0;

    list_head = member_update(list_head);
    if (list_head == NULL)
    {
        FILE *list_w = fopen("list.txt", "w");
        fprintf(list_w, "%s %s %s", "아이디", "비밀번호", "이름");
        fclose(list_w);
        list_head = member_update(list_head);
    }
    
    FILE *list_a = fopen("list.txt", "a");

    printf("회원가입 페이지\n"); 
    while(1)
    {    
        printf("아이디 : ");
        scanf("%[^\n]", Id);
        getchar();

        cur = list_head;
        
        while(1)
        {
            
            n = strcmp(cur->id, Id);
            if (n == 0)
                break;
                
            cur = cur->next;
            if (cur == NULL)
                break;
        }
        
        if (n == 0)
        {
            printf("이미 존재하는 아이디 입니다.\n");
            continue;
        }
        else 
        {
            printf("사용가능한 아이디 입니다.\n");
            break;
        }
        return;
    }
    
    printf("비밀번호 : ");
    scanf("%[^\n]", Pw);
    getchar();

    
    printf("이름 : ");
    scanf("%[^\n]", Nm);
    getchar();
    fprintf(list_a, "\n%s %s %s", Id, Pw, Nm);
    fclose(list_a);

    return;
}

member *member_update(member *head)
{
    member *list;
    int c;
    char Id[20], Pw[20], Nm[20];

    FILE *list_fp = fopen("list.txt", "r");
    head = NULL;
    

    while (1)
    {
        c = fscanf(list_fp, "%s %s %s", Id, Pw, Nm);
        if(c != 3)
            break;
        list = (member *)malloc(sizeof(member));
        strcpy(list->id, Id);
        strcpy(list->pw, Pw);
        strcpy(list->nm, Nm);
        if (head == NULL)
        {
            head = list;
            list->next = NULL;
        }
        else 
        {   
            list->next = head;
            head = list;
        }
    }
    return head;
}

int login(char *ID)
{
    char cur_ID[20], cur_PW[20];
    member *list;
    int c;
    
    list = member_update(list);
    if (list == NULL)
    {
        printf("등록된 회원이 없습니다.\n");
        return 0;
    }    
    
    printf("로그인\n");

    while (1)
    {
        list = member_update(list);
        c = 0;
        printf("아이디 : ");
        scanf("%[^\n]", cur_ID);
        getchar();

        printf("비밀번호 : ");
        scanf("%[^\n]", cur_PW);
        getchar();

        while(1)
        {
            if(strcmp(cur_ID, list->id) == 0)
            {
                if(strcmp(cur_PW, list->pw) == 0)
                c++;
                break;
            }
            list = list->next;
            if (list == NULL)
                break;
        }
        
        if(c != 1)
        {
            printf("아이디나 비밀번호가 틀렸습니다. 다시 시도하세요.\n");
            continue;
        }
        if(c == 1)
        {
            strcpy(ID, cur_ID);
            break;
        }
    }
    return 1;
}

void member_delete(char *ID)
{
    member *list, *cur, *head, *prev;

    list = member_update(list);
    head = list;
    while(1)
    {
        if(strcmp(ID, list->id) == 0)
            break;
        prev = list;
        list = list->next;
        if (list == NULL)
            break;
    }
    
    if (list == head)
        head = list->next;
    else
        prev->next=prev->next->next;

    FILE *list_w = fopen("list.txt", "w");
    
    cur = head;

    while(1)
    {
        fprintf(list_w, "%s %s %s\n", cur->id, cur->pw, cur->nm);
        cur = cur->next;
        if(cur == NULL)
            break;
    }
    fclose(list_w);
    
    return;
}

void problem(void)
{
    dict *dic_head, *cur;
    int n;
    char answer[20];
    dic_head = dic_update_sort(dic_head);

    printf(">> 영어 단어 맞추기 프로그램 <<\n");
    printf("1. 영어 단어 맞추기 2. 프로그램 종료\n");
    printf("\n번호를 선택하세요: ");
    scanf("%d", &n);
    getchar();

    if(n == 2)
        return;

    else if(n == 1)
    {
        int count = 0, O = 0;
        double score = 0.0;
        cur = dic_head;
        while(1)
        {
            
            printf("%s -> ", cur->kr);
            scanf("%[^\n]", answer);
            getchar();

            if (strcmp(answer,".quit") == 0)
            {   
                score = (double)O/count*100;
                printf("당신의 점수는 %.2f점입니다.\n", score);    
                break;
            }
            else if (strcmp(answer, cur->en) == 0)
            {
                O++;
                printf("correct!\n");
            }
            else printf("incorrect!\n");
            count++;
            cur = cur->link;
            if(cur == NULL)
            {
                score = (double)O/count*100;
                printf("당신의 점수는 %.2f점입니다.\n", score);    
                break;
            }
        }
    }
    return;
}

dict *dic_update_sort(dict *head)
{
    dict *node, *cur;
    char t_en[20], t_kr[20];
    int c, n = 0;
    FILE *dic = fopen("dic.txt", "r");
    head = NULL;
    
    while (1)
    {
        c = fscanf(dic, "%s %s", t_en, t_kr); 
        
        if (c != 2)
            break;
        n++;
        node = (dict *)malloc(sizeof(dict));
        
        strcpy(node->en, t_en);
        strcpy(node->kr, t_kr);
        
        if (head == NULL)
        {
            head = node;
            node->link = NULL;
        }
        else 
        {
            node->link = head;
            head = node;
        }
    }
    fclose(dic);

    head = sort(head, n);

    return head;
}

dict *sort(dict *head, int n)
{
    dict *cur, *tmp1, *tmp2;
    for(int i = 0; i < n; i++)
    {
        cur = head;
        tmp1 = head;
        while(cur->link != NULL)
        {
            if(strcmp(cur->en, cur->link->en) > 0)
            {
                if(cur == head)
                {
                    tmp2 = head->link;
                    head->link = head->link->link;
                    tmp2->link = head;
                    head = tmp2;
                    tmp1 = tmp2;    
                }
                else
                {
                    swap(tmp1);
                    tmp1=tmp1->link;
                }
                cur = tmp1->link;       
            }
            else if (cur == head)
                cur = tmp1->link;
            else
            {
                tmp1 = tmp1->link;
                cur = tmp1->link;
            }
        }
    }
    
    return head;
}

void swap(dict *addr)//주소의 다음 두 노드의 자리 바꾸기
{
    dict *node1, *node2, *node3;
    
    node1 = addr;
    node2 = node1->link;
    node3 = node1->link->link;

    node2->link = node3->link;
    node3->link = node2;
    node1->link = node3;

    return;
}