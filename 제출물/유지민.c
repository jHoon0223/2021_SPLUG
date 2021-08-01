#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Member {
    char id[50];
    char pw[50];
    char name[59];
    struct Member *nxt;
} Member;

typedef struct Dic {
    char eng[16];
    char kor[61];
    struct Dic *nxt;
    struct Dic *prv;
} Dic;

Member *MemHead = NULL;
Dic *DicHead = NULL;
Dic *DicTail = NULL;
int loginCheck, finish;
char loginId[50];

void showMenu();
void Result();
void callMemberData();
void signUp();
void logIn();
void logOut();
int callDicData();
void signOut();
void game();
void bubble(int);

int main(void) {
    MemHead = malloc(sizeof(Member));
    DicHead = malloc(sizeof(Dic));
    DicTail = malloc(sizeof(Dic));
    DicHead -> nxt = DicTail;
    DicTail -> prv = DicHead;
    callMemberData();
    while (1) {
        if (!finish) showMenu();
        else return 0;
    }
}

void showMenu() {
    printf("\
            ==================================\n\
            =========== 2021 SPLUG ===========\n");
    if(!loginCheck) printf("            ==================================\n");
    else if (loginCheck) printf("            ========================== %s\n", loginId); 
printf("            =              메뉴              =\n\
            ==================================\n\
                    1. 회원가입\n\
                    2. 로그인\n\
                    3. 로그아웃\n\
                    4. 영어 단어 맞추기\n\
                    5. 회원 탈퇴\n\
                    6. 프로그램 종료\n\
            ==================================\n:");
    int num; scanf("%d", &num);
    Result(num);
}

void Result(int num) {
        switch (num) {
            case 1:
                signUp();
                break;
            case 2:
                logIn();
                break;
            case 3:
                logOut();
                break;
            case 4:
                game();
                break;
            case 5:
                signOut();
                break;
            case 6:
                system("clear");
                printf("다음에 또 만나요~\n"); 
                finish = 1;
                break;
            default:
                printf("없는 번호입니다. 다시 입력하세요.\n");
                showMenu();
        }
}

void callMemberData() {
    FILE *fp = fopen("member.txt","r");
    int check = 1;
    while (check != EOF) {
        Member *newNode = malloc(sizeof(Member));
        check = fscanf(fp,"%s %s %s",newNode -> id, newNode -> pw, newNode -> name);
        newNode -> nxt = MemHead -> nxt;
        MemHead -> nxt = newNode;
    }
    fclose(fp);
}

void signUp() {
    Member *newNode = malloc(sizeof(Member));
    printf("회원가입 페이지\n");
    while (1) {
        printf("아이디 : "); scanf("%s", newNode -> id);
        Member *cur = MemHead -> nxt;
        int flag = 1;
        while (cur) {
            if (!strcmp(cur -> id, newNode -> id)) flag = 0;
            cur = cur -> nxt;
        }
        if (flag) break;
        else printf("이미 존재하는 아이디 입니다.\n");
    }

    printf("사용 가능한 아이디 입니다\n");
    printf("비밀번호 : "); scanf("%s", newNode -> pw);
    printf("이름 : "); scanf("%s", newNode -> name);

    if (MemHead -> nxt) {
        newNode -> nxt = MemHead -> nxt;
        MemHead -> nxt = newNode;
    } else {
        MemHead -> nxt = newNode;
    }

    FILE *fp = fopen("member.txt", "w");
    Member *cur = MemHead -> nxt;
    while (cur) {
        fprintf(fp, "%s %s %s\n", cur -> id, cur -> pw, cur -> name);
        cur = cur -> nxt;
    }
    fclose(fp);
}

void logIn() {
    Member *tmp = MemHead -> nxt;
    printf("로그인\n");
    while (1) {
        char iptId[50];
        char iptPw[50];
        printf("아이디 : "); scanf("%s", iptId);
        printf("비밀번호 : "); scanf("%s", iptPw);
        Member *cur = MemHead -> nxt;
        
        int pwCorret = 0, idFind = 0;
        while (cur) {
            if (!strcmp(iptId, cur -> id)) {
                if (!strcmp(iptPw, cur -> pw)) pwCorret = 1;
                idFind = 1;
                break;
            }
            cur = cur -> nxt;
        }
        if (idFind && pwCorret) {
            loginCheck = 1;
            strcpy(loginId, iptId);
            break;
        } else {
            printf("아이디나 비밀번호가 틀렸습니다. 다시 시도하세요\n");
        } 
    }
}

void logOut() {
    char ipt[50];
    printf("정말 로그아웃을 하시겠습니까? [y/n] : "); scanf("%s", ipt);
    if (!strcmp(ipt, "y")) loginCheck = 0;
}

void signOut() {
    if (!loginCheck) {
        printf("로그인 상태가 아닙니다.\n");
    } else {
        FILE *fp = fopen("member.txt", "w");
        printf("정말 회원을 탈퇴하시겠습니까? [y/n] : ");
        char ipt[50]; scanf("%s", ipt);
        if (!strcmp(ipt, "y")) {
            Member *cur = MemHead;
            while (cur -> nxt) {
                if (!strcmp(loginId, cur -> nxt -> id)) break;
                cur = cur -> nxt;
            }
            Member *tmp = cur -> nxt;
            cur -> nxt = tmp -> nxt;
            free(tmp);
            loginCheck = 0;
        } 

        Member *cur = MemHead -> nxt;
        while (cur) {
            fprintf(fp, "%s %s %s\n", cur -> id, cur -> pw, cur -> name);
            cur = cur -> nxt;
        }
        fclose(fp);
    }
}

int callDicData() {
    FILE *fp = fopen("dic.txt","r");
    int check = 1, size = 0;
    while(check != EOF){
        Dic *newNode = malloc(sizeof(Dic));
        check = fscanf(fp, "%s %s", newNode -> eng, newNode -> kor);
        newNode -> nxt = DicHead -> nxt;
        DicHead -> nxt -> prv = newNode;
        newNode -> prv = DicHead;
        DicHead -> nxt = newNode;
        size++;
    }
    fclose(fp);
    return size - 1;
}

void game() {
    printf("(1) 영어 단어 맞추기\n(2) 프로그램종료\n");
    printf("번호를 선택하세요 : "); 
    int ipt; scanf("%d", &ipt);
    if (ipt == 1) {
        int sz = callDicData();
        bubble(sz);

        Dic *cur = DicHead -> nxt -> nxt;
        int score = 0;
        while (cur) {
            printf("%s : ", cur -> kor);
            char ans[50]; scanf("%s", ans);
            if (!strcmp(ans, ".quit")) {
                printf("점수 : %d\n", score);
                break;
            } else if (!strcmp(ans, cur -> eng)) {
                printf("correct!\n");
                score++;
            } else {
                printf("incorrect!\n");
            }
            if (!cur){
                printf("점수 : %d\n", score);
                break;
            }
            cur = cur -> nxt;
        }
    } else {
        system("clear");
        return;
    }
}

void bubble(int size) {
    for(int i = size - 1; i > 0; i--){
        Dic *cur = DicHead;
        if (cur -> nxt  == DicTail) return;
        for (int j = 0; j < i; j++){
            cur = DicHead -> nxt;
            for (int k = 0; k < j; k++)
                cur = cur -> nxt;
            if (strcmp(cur -> eng,cur -> nxt -> eng) > 0){
                cur -> nxt -> prv = cur -> prv;
                cur -> prv -> nxt = cur -> nxt;
                cur -> nxt = cur -> nxt -> nxt;
                cur -> prv = cur -> nxt -> prv;
                cur -> prv -> nxt = cur;
                cur -> nxt -> prv = cur;
            }
        }
    }
}
