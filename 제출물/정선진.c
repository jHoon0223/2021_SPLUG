#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int count;
char log_detect[16];
int source;

struct Person{
    char ID[16];
    char NAME[10];
    char PASSWORD[11];
};

void enrollment(struct Person *num){

    printf("회원가입 페이지\n");
    FILE *USER_INFO = fopen("user.txt", "a");
    fputs("", USER_INFO);
    fclose(USER_INFO);
    
    char str[100],ans[100];
    int num_ = 0,pass=0;
    ONE:
        printf("아이디: ");
        scanf("%s", num[count+1].ID);
        strcpy(ans, num[count+1].ID);

        num_ = 0;
        pass = 0;

        //파일열기
        USER_INFO = fopen("user.txt", "r");
        if (USER_INFO == NULL) {
            printf("==ERROR==");
        }
        
        while (!feof(USER_INFO)) {
            num_++;
            fgets(str, 100, USER_INFO);

            if (strstr(str, ans) != NULL) {
                printf("중복된 아이디입니다.\n");
                pass++;
            }
            if(pass != 0){
                goto ONE;
            }
        }

        if (pass == 0) printf("사용가능한 아이디입니다.\n");
        fclose(USER_INFO);
    
    USER_INFO = fopen("user.txt", "a");
    fputs(num[count+1].ID, USER_INFO);
    fputs("\n",USER_INFO);
    fclose(USER_INFO);
    printf("\n비밀번호: ");
    scanf("%s", num[count+1].PASSWORD);
    printf("\n이름: ");
    scanf("%s", num[count+1].NAME);
    count++;
}

void log_in(struct Person *num){
    char *user_tmp;
    printf("ID: ");
    scanf("%s", user_tmp);
    for(int i = 0; i<100; i++){
        if(strcmp(user_tmp, num[i].ID)==0){
            char *hello = malloc(sizeof(char) * 10);
            while(1){
                printf("PASSWORD: ");
                scanf("%s", hello);
                if(strcmp(num[i].PASSWORD, hello)==0){
                    printf("로그인 성공! 메인화면으로 이동합니다.(3초 뒤이동)\n");
                    strcpy(log_detect, num[i].ID);
                    source = 1;
                    Sleep(3000);
                    break;
                }
                else{
                    printf("잘못된 입력입니다. 다시 입력하세요.\n");
                }
            }
            break;
        }
    }

}
void drop_out(struct Person *num){
    printf("아직 구현되지 않은 기능입니다. 메인화면으로 돌아갑니다.(3초뒤 이동)\n");
    Sleep(3000);
}

void match_words(struct Person *num){
    printf("아직 구현되지 않은 기능입니다. 메인화면으로 돌아갑니다.(3초뒤 이동)\n");
    Sleep(3000);
}

int main(void){
    while(1){
        struct Person num[10];
        int sys = 0;
        //초기화면 세팅
        if(source == 0){
            printf("==================================\n");
            printf("=========== 2021 SPLUG ===========\n");
            printf("==================================\n");
            printf("==================================\n");
            printf("=              메뉴              =\n");
            printf("==================================\n");
            printf("        1. 회원가입\n");
            printf("        2. 로그인\n");
            printf("        3. 로그아웃\n");
            printf("        4. 영어 단어 맞추기\n");
            printf("        5. 회원 탈퇴\n");
            printf("        6. 프로그램 종료\n");
            printf("==================================\n");
            printf(": ");
            scanf("%d", &sys);
        }
        if(source == 1){
            int a = strlen(log_detect);
            printf("==================================\n");
            printf("=========== 2021 SPLUG ===========\n");
            for(int i = 1; i < 30-strlen(log_detect); i++){
                printf("=");
            }
            printf("%s", log_detect);
            printf("\n");
            printf("==================================\n");
            printf("=              메뉴              =\n");
            printf("==================================\n");
            printf("        1. 회원가입\n");
            printf("        2. 로그인\n");
            printf("        3. 로그아웃\n");
            printf("        4. 영어 단어 맞추기\n");
            printf("        5. 회원 탈퇴\n");
            printf("        6. 프로그램 종료\n");
            printf("==================================\n");
            printf(": ");
            scanf("%d", &sys);
        }

        if(sys==1){
            enrollment(num);
        }
        else if(sys==2){
            log_in(num);
        }
        else if(sys==3){
            if(source == 0){
                printf("로그인 되지 않았습니다. 다시 시도하세요.(3초 뒤 메인화면으로 이동)\n");
                Sleep(3000);
            }
            else{
                getchar();
                printf("정말 로그아웃 하시겠습니까? [y/n]: ");
                char a;
                scanf("%c", &a);
                
                if(a == 'y'){
                    printf("로그아웃 되었습니다.(3초 뒤 메인화면으로 이동)\n");
                    Sleep(3000);
                    source = 0;
                }
                else{
                    printf("로그아웃에 실패했습니다.(3초 뒤 메인화면으로 이동)\n");
                    Sleep(3000);
                }
            }
        }
        else if(sys==5){
            drop_out(num);
        }
        else if(sys==4){
            match_words(num);
        }
        else if(sys==6){
            printf("프로그램이 종료됩니다.\n");
            Sleep(2000);
            return 0;
        }
        else{
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
        }
    }
}


/* 중복확인 절차

1. 입력한 아이디열이 기존 입력되었는 지 검색.
2-1. 없다면 그대로 사용(끝)
2-2. 있다면 3으로 넘어감
3. 중복처리된 문자열을 선택. 해당 문자열 삭제 후 사용자가 입력한 문자열 파일 내에 배치.
4-1. 삭제한 문자열을 가지고 중복검사 다시 시행. 없다면 파일에 다시 입력(끝).
4-2. 있다면 중복일 가능성 존재.

==>> 중복 검사 실패. 너무 경우의 수가 많이 갈림.
*/

/*중복확인 절차 Ver.2

1. txt파일에서 문자열을 한 줄씩 읽어, 그 문자열을 포인터 문자열에 저장.
2. 첫번째 문자열부터 차례로 비교.
3-1 strcmp로 비교해 0값이 나오는 순간, 4로 이동.
3-2 strcmp로 비교해 문제 없으면 사용.
4. "중복입니다."를 출력하며, 아이디를 다시 입력받는다.

==>> 문제없음. 오히려 첫 번째 방법보다 예외도 없고 안전하다.
*/