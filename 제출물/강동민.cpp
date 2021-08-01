#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#define NUM 50
#define word 101

struct NODE {

    char id[NUM];
    char pw[NUM];    
    char name[NUM];
    struct NODE* next;
};

struct dic {

    char eng[255];
    char kor[255];
    struct dic* next;
};

FILE* fp = NULL;
FILE* fp1 = NULL;
char tmp_id[NUM] = { 0, }; //func2 전역함수

void func1(struct NODE* target) {

    struct NODE* ptr1 = 0;
    struct NODE* node = (struct NODE*)malloc(sizeof(struct NODE));   //  노드 생성
    printf("<회원가입 페이지>\n아이디 : ");
    //중복확인 코드
    while (1)
    {
        int cnt = 0;
        char temp[NUM] = {0,};
        ptr1 = target->next;

        //아이디 입력
        scanf_s("%s", temp, sizeof(temp));
        getchar();       

        while (ptr1 != NULL)
        {
            if (strcmp(ptr1->id, temp) == 0)
            {
                cnt++;
                break;
            }

            else
            {
                ptr1 = (ptr1->next);
            }
        }

        if (cnt == 0)
        {

            strcpy_s(node->id, NUM, temp);
            printf("\n비밀번호 : ");
            scanf_s("%s", temp, sizeof(temp));
            getchar();
            strcpy_s(node->pw, NUM, temp);

            printf("\n이름 : ");
            scanf_s("%s", temp, sizeof(temp));
            getchar();
            strcpy_s(node->name, NUM, temp);

            node->next = target->next;
            target->next = node;

            fp = fopen("info.txt", "a");
            fprintf(fp, "id : %s\npassword : %s\nname : %s\n\n ", node->id, node->pw, node->name);
            fclose(fp);

            return ;
        }

        else
        {
            //system("cls");
            //printf("<회원가입 페이지>\n");
            printf("중복된 아이디입니다.\nID : ");
            continue;
        }
    }
}

int func2(struct NODE* target, int cnt) {
    char id_2[NUM] = { 0, };
    char pw_2[NUM] = { 0, };
    char tmp_pw[NUM] = { 0, };
    struct NODE* ptr2 = (struct NODE*)malloc(sizeof(struct NODE));

    printf("<로그인 페이지>\n");

    while (1)
    {   
        ptr2 = target->next;

        if (cnt == 1)
        {
            system("cls");
            printf("<로그인 페이지>\n");
            printf("이미 로그인상태 입니다.\n");
            printf("(엔터키를 누르세요.)");
            getchar();
            return 1;
        }

        printf("ID : ");
        scanf_s("%s", tmp_id, sizeof(tmp_id));
        printf("비밀번호 : ");
        scanf_s("%s", tmp_pw, sizeof(tmp_pw));


        while ((ptr2 != NULL) && cnt == 0) {

            if ((strcmp(ptr2->id, tmp_id) == 0) && (strcmp(ptr2->pw, tmp_pw) == 0))
            {
                return 1;
            }

            else
            {
                ptr2 = ptr2->next;
            }

            if (ptr2 == NULL)
            {
                system("cls");
                printf("<로그인 페이지>\n");
                printf("아이디/비밀번호를 다시 확인해 주세요.\n");
                continue;
            }
        }
    }
}

int func3(int cnt) {
   
    char tmp_3 ;
    
    printf("<로그아웃 페이지>\n");
    if (cnt == 0)
    {
        printf("로그인상태가 아닙니다.");
        printf("(엔터키를 누르세요.)");
        getchar();
        return 0;
    }
   

    else if (cnt == 1)
    {
        while (1)
        {
            printf("정말 로그아웃 하시겠습니까? [y/n]\n");
            scanf_s("%c", &tmp_3, 1);
            getchar();

            if (tmp_3 == 'y')
            {
                return 0;
            }
            else if (tmp_3 == 'n')
            {
                return 1;
            }
            else
            {
                printf("잘못된 접근입니다.\n");
            }
        }
    }
}

void dic(struct dic* target, char eng[NUM], char kor[NUM]) {

    FILE* fp1 = NULL;
    struct dic* node = (struct dic*)malloc(sizeof(struct dic));
    struct dic* ptr = (struct dic*)malloc(sizeof(struct dic));

    ptr = target->next;
    strcpy(node->eng, eng);
    strcpy(node->kor, kor);
    while (ptr != NULL)
    {

        if (strcmp(ptr->eng, node->eng) == 1)
        {
            node->next = target->next;
            target->next = node;
            return;
        }
        else
        {
            ptr = ptr->next;
            target = target->next;
            continue;
        }
    }
    if (ptr == NULL)
    {
        node->next = target->next;
        target->next = node;
        return;
    }
}

void func4(struct dic* target) {
    int choice = 0;
    int score = 0, cnt = 0;
    FILE* fp2 = NULL;

    char eng[255];
    struct dic* ptr = (struct dic*)malloc(sizeof(struct dic));

    ptr = target->next;

    printf("<영어단어 맞추기 페이지>\n1.영어단어 맞추기 2.페이지 종료\n번호를 선택하세요 : ");
    scanf("%d", &choice);
    if (choice == 1)
    {       
        while (ptr != NULL)
        {
            printf("\n%s ->", ptr->kor);
            scanf("%s", eng);
            getchar();
            if (strcmp(".quit", eng) == 0)
            {
                printf("score : %d / %d", score, cnt);
                getchar();
                return;
            }
            else if (strcmp(eng, ptr->eng) == 0)
            {
                printf("correct!");
                score++;
            }
            else
            {
                printf("incorect!");
            }
            cnt++;
            ptr = ptr->next;
        }
        if (ptr == NULL)
        {
            printf("\nscore : %d / %d", score, cnt);
            getchar();
            return;
        }
    }

    else if (choice == 2)
    {
        return;
    }
}

int func5(struct NODE* target, int cnt) {

    char tmp;
    char tmp_id1[NUM] = { 0, };
    char tmp_pw[NUM] = {0,};
    struct NODE* ptr5 = (struct NODE*)malloc(sizeof(struct NODE));
    ptr5 = target->next;

    if (cnt == 0)
    {
        printf("<회원탈퇴 페이지>\n");
        printf("로그인상태가 아닙니다.\n");
        printf("(엔터키를 누르세요.)");
        getchar();
        return 0;
    }
    else if (cnt == 1)
    {
        printf("<회원탈퇴 페이지>\n");
        printf("회원탈퇴를 위해 회원정보를 다시한번 입력해주세요.\n");
        printf("아이디 : ");
        scanf_s("%s", tmp_id1, sizeof(tmp_id1));
        printf("비밀번호 : ");
        scanf_s("%s", tmp_pw, sizeof(tmp_pw));
        getchar();

        while (ptr5 != NULL)
        {
            if ((strcmp(tmp_id,tmp_id1) == 0) && (strcmp(ptr5->id, tmp_id1) == 0) && (strcmp(ptr5->pw, tmp_pw) == 0))
                //현재 로그인된 아이디, 검증 아이디, 비밀번호가 일치하는지 검사(현재로그인된 아이디와의 검사가 없으면 현재 로그인되지 않은 링크드리스트 속 아무 아이디가 탈퇴 가능해진다)
            {
                printf("정말 회원을 탈퇴하시겠습니까? [y/n]\n");
                scanf_s("%c", &tmp, 1);
                if (tmp == 'y')
                {
                    target->next = ptr5->next; //노드 삭제
                    free(ptr5); //메모리 해제

                    ptr5 = target->next;
                    fp = fopen("info.txt", "w");

                    while (ptr5 != NULL)
                    {
                        fprintf(fp, "id : %s\npassword : %s\nname : %s\n\n ", ptr5->id, ptr5->pw, ptr5->name);
                        ptr5 = ptr5->next;
                    }
                    fclose(fp);
                    return 0;
                }
                else if (tmp == 'n')
                {
                    return 1;
                }
                else
                {
                    printf("잘못된 접근입니다.\n");
                    getchar();
                    continue;
                }
            }
            else
            {
                ptr5 = ptr5->next;
                target = target->next;
            }
        }
        if (ptr5 == NULL)
        {
            //system("cls");
            //printf("<회원탈퇴 페이지>\n");
            printf("아이디/비밀번호를 다시 확인해 주세요.\n");
            getchar();
            return 1;
        }
    }
}

int main(void){

    struct NODE* head = (struct NODE*)malloc(sizeof(struct NODE));
    struct dic* head1 = (struct dic*)malloc(sizeof(struct dic));

    char eng[NUM];
    char kor[NUM];

    head->next = NULL;
    head1->next = NULL;
    int cnt = 0;

    while (1)
    {
        int select = 0;
         //로그인 X 화면
        system("cls");
        printf("================================================\n");
        printf("===================2021 SPLUG===================\n");
        printf("================================================\n");
        
        if (cnt == 0)
        {
        printf("================================================\n");
        }
        
        else if (cnt == 1)
        {
            for (int i = 1; i <= (47 - (signed)strlen(tmp_id)); i++)
            {
                printf("=");
            }
            printf(" %s\n", tmp_id);
        }
        
        printf("=                    메 뉴                     =\n");
        printf("================================================\n");
        printf("                %d. 회원가입\n", 1);
        printf("                %d. 로그인\n", 2);
        printf("                %d. 로그아웃\n", 3);
        printf("                %d. 영어 단어 맞추기\n", 4);
        printf("                %d. 회원 탈퇴\n", 5);
        printf("                %d. 프로그램 종료\n", 6);
        printf("================================================\n");

        scanf_s("%d", &select);
        getchar();

        if (select == 1)
        {
            system("cls");
            func1(head);
        }
        else if (select == 2)
        {
            system("cls");
            cnt = func2(head, cnt);
        }
        else if (select == 3)
        {
            system("cls");
            cnt = func3(cnt);
        }
        else if (select == 4)
        {
            system("cls");
            fp1 = fopen("dic.txt", "r");

            if (fp1 == NULL)
            {
                printf("파일열기 실패\n");
                exit(1);
            }

            while (!feof(fp1))
            {
                fscanf(fp1, "%s %s", eng, kor);
                dic(head1, eng, kor);
            }
            fclose(fp1);

            func4(head1);

        }
        else if (select == 5)
        {
            system("cls");
            cnt = func5(head, cnt);
        }
        else if (select == 6)
        {
            system("cls");
            printf("다음에 또 만나요!!\n");
            break;
        }
    }
    free(head);
    free(head1);
    return 0;
}