#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert();
void registration();
void login();
void logout();
void engword();
void wordsort();
void accountout();
void update();

int logining = 0;
int wordnum = 0;
char onID[100];

typedef struct user 
{
    struct user* next1;
    char userid[100];
    char userpw[100];
    char username[100];
} user;

typedef struct word 
{
    struct word* next2;
    char kor[100];
    char eng[100];
} word;

int main()
{
    user* head1 = malloc(sizeof(user));
    head1->next1 = NULL;
    word* head2 = malloc(sizeof(word));
    head2->next2 = NULL;
    FILE *fp;
    if (!(fp = fopen("id.txt", "rb")))//파일이 없을시 생성
    {
        fp = fopen("id.txt", "wb");
        fclose(fp);
    }
    fp = fopen("id.txt", "rb");//id 목록 연결 리스트에 담기
    while(!feof(fp))
    {
        char id[100], pw[100], name[100];
        user* _user = malloc(sizeof(user));
        _user->next1 = head1->next1;
        fscanf(fp, "%s %s %s", id, pw, name);
        strcpy(_user -> userid, id);
        strcpy(_user -> userpw, pw);
        strcpy(_user -> username, name);
        head1->next1 = _user;
    }
    fclose(fp);
    
    fp = fopen("dic.txt", "rb"); //영단어 목록 연결 리스트에 담기
    while(!feof(fp))
    {
        char ko[100], en[100];
        word* _word = malloc(sizeof(word));
        _word->next2 = head2->next2;
        fscanf(fp, "%s %s", en, ko);
        strcpy(_word -> eng, en);
        strcpy(_word -> kor, ko);
        head2->next2 = _word;
        wordnum++;
    }
    fclose(fp);
    while(1)
    {
        int menu=0;

        if(logining==1)
        {
            printf("안녕하세요! %s님!\n", onID);
        }
        printf("==메뉴==\n1. 회원가입\n2. 로그인\n3. 로그아웃\n4.영어 단어 맞추기\n5. 회원 탈퇴\n6. 프로그램 종료\n:");
        scanf("%d",&menu);
        getchar();
        if(menu==1)
        {
            if(logining==1)
            {
                printf("이미 로그인 중 입니다. 초기 화면으로 돌아갑니다.\n");
            }
            else
            {
                registration(head1);
                update(head1);
            }
        }
        else if(menu==2)
        {
            if(logining==1)
            {
                printf("이미 로그인 중 입니다. 초기 화면으로 돌아갑니다.\n");
            }
            else
                login(head1);
        }
        else if(menu==3)
        {
            if(logining==0)
            {
                printf("로그인 상태가 아닙니다. 초기 화면으로 돌아갑니다.\n");
            }
            else
                logout();
        }
        else if(menu==4)
        {
            wordsort(head2);//정렬
            engword(head2);//단어 맞추기
        }
        else if(menu==5)
        {
            if(logining==0)
            {
                printf("로그인 상태가 아닙니다. 초기 화면으로 돌아갑니다.\n");
            }
            else
            {
                accountout(head1);
                update(head1);
            }
        }
        else if(menu==6)
        {
            system("clear");
            printf("다음에 또 만나요!!\n");
            break;
        }
        else
        {
            printf("메뉴는 1~6까지 숫자로 입력해주세요.\n");
        }
    }
    return 0;
}

void registration(user* target)
{
    char r_id[100], r_pw[100], r_name[100];
    printf("<회원가입>\n");
    while(1)
    {
        int reset=0;
        printf("아아디 : ");
        scanf("%s", r_id);
        user* temp = target->next1;
        while(temp != NULL)
        {
            if(strcmp(temp->userid, r_id)==0)
            {
                printf("중복된 아이디입니다. 다시 입력하세요.\n");
                reset=1;
                break;
            }
            temp = temp->next1;
        }
        if (reset==0)
        {
            break;
        }
    }
        printf("사용 가능한 아이디입니다.\n비밀번호 : ");
        scanf("%s",r_pw);
        printf("이름: ");
        scanf("%s",r_name);

        FILE *fp;
        fp=fopen("id.txt", "ab");
        fprintf(fp, "%s %s %s\n", r_id, r_pw, r_name);
        fclose(fp);
    
    printf("회원가입이 완료되었습니다.\n");
}

void login(user* target)
{
    int conform=0;
    char loginid[100], loginpw[100];
    while(1)
    {
        printf("<로그인>\n아이디: ");
        scanf("%s",loginid);
        printf("비밀번호: ");
        scanf("%s",loginpw);
        user* temp = target->next1;
        while(temp != NULL)
        {
            if(strcmp(temp->userid, loginid)==0)
            {
                if(strcmp(temp->userpw, loginpw)==0)
                {
                    conform=1;
                    break;
                }
            }
            temp = temp->next1;
        }
        if (conform==0)
            printf("잘못된 아이디 혹은 비밀번호 입니다. 다시 입력해주세요.\n");
        else if (conform==1)
        {
            printf("로그인 성공!\n");
            logining=1;
            strcpy(onID,loginid);
            break;
        }
    }
}

void logout()
{
    char yesorno;
        
    printf("정말 로그아웃 하시겠습니까? [y/n]: ");
    
    scanf("%c", &yesorno);
    
    if (yesorno == 'y')
    {
        logining=0;
    }
    else if (yesorno == 'n')
        printf("로그아웃이 취소되었습니다. 초기화면으로 돌아갑니다.\n");
}

void wordsort(word* target)
{
    for (int i = 0; i < wordnum; i++)
    {
        char set[100];
        word* head = target->next2;
        word* temp = head->next2;
        while(temp != NULL)
        {
            if(strcmp(head->eng, temp->eng)>0)
            {
                strcpy(set, head->eng);
                strcpy(head->eng, temp->eng);
                strcpy(temp->eng, set);
                strcpy(set, head->kor);
                strcpy(head->kor, temp->kor);
                strcpy(temp->kor, set);
            }
            head = head->next2;
            temp = temp->next2;
        }
    }
}

void engword(word* target)
{
    char answer[100];
    int point = 0, count = 0;
    word* temp = target->next2;
    while(temp != NULL)
    {
        printf("%s -> ", temp->kor);
        scanf("%s", answer);
        getchar();
        if (strcmp(answer,".quit") == 0)
        {
            break;
        }
        else if (strcmp(temp->eng, answer)==0)
        {
            printf("correct!\n");
            point++;
        }
        else
            printf("incorrect!\n");
        count++;    
        temp = temp->next2;
    }
    printf("맞춘 개수는 총 %d개 중, %d개 입니다.\n", count, point);
}

void accountout(user* target)
{
    char yesorno;
        
    printf("정말 회원을 탈퇴 하시겠습니까? [y/n]: ");
    
    scanf("%c", &yesorno);
    
    if (yesorno == 'y')
    {
        user* head = NULL;
        user* temp = target;
        while(temp != NULL)
        {
            if(strcmp(temp->userid, onID)==0)
            {
                head->next1 = temp->next1;
                free(temp);
                logining = 0;
                break;
            }
            head = temp;
            temp = temp->next1;
        }
    }
    else if (yesorno == 'n')
        printf("회원 탈퇴가 취소되었습니다. 초기화면으로 돌아갑니다.\n");
}

void update(user* target)
{
    FILE *fp;
    fp=fopen("id.txt", "wb");
    user* temp = target->next1;
    while(temp != NULL)
    {
        fprintf(fp, "%s %s %s\n", temp->userid, temp->userpw, temp->username);
        temp = temp->next1;
    }
    fclose(fp);
}