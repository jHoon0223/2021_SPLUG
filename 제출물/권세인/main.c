#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#include "wordGame.h"
#include "display.h"
#include "account.h"
#include "linkedList.h"

ListNode *accounts;
Player   *currentAccount;

static void nextLine(char *input)
{
    scanf("%s[^\n]", input);
    getchar();
}

void printValidationResult(int value)
{
    switch (value)
    {
        case 0:
            return;
        case 1:
            printf("이미 사용중입니다. \n");
            break;
        case 2:
            printf("길이가 너무 짧습니다.\n");
            break;
        case 3:
            printf("최대 15자리까지만 입력 가능합니다. \n");
            break;
        case 4:
            printf("공백 문자는 입력 불가능합니다. \n");
            break;
        default:
            printf("사용 불가능한 값입니다. \n");
            break;
    }
}

void startRegister()
{
    displayClear();
    printf("회원가입 페이지\n");

    char id[32];
    char pw[32];
    char name[32];

    while (true)
    {
        printf("아이디 : ");
        nextLine(id);

        int result = accountCheckIdValidation(accounts, id);
        printValidationResult(result);
        if (result == 0)
        {
            printf("사용가능한 아이디입니다.\n");
            break;
        }
    }

    while (true)
    {
        printf("비밀번호 : ");
        nextLine(pw);

        int result = accountCheckPasswordValidation(pw);
        printValidationResult(result);
        if (result == 0)
        {
            printf("사용가능한 비밀번호입니다.\n");
            break;
        }
    }

    while (true)
    {
        printf("이름 : ");
        nextLine(name);

        int result = accountCheckNameValidation(name);
        printValidationResult(result);
        if (result == 0)
        {
            printf("사용가능한 이름입니다.\n");
            break;
        }
    }

    Player *newPlayer = accountNewAccount(id, pw, name, 0);
    accountRegister(accounts, newPlayer);

    printf("회원가입 성공\n");
    getchar();
}

void startLogin()
{
    while (true)
    {
        displayClear();
        printf("로그인\n");
        printf("아이디 : ");

        char id[16];
        nextLine(id);

        printf("비밀번호 : ");

        char pw[16];
        nextLine(pw);

        Player *player = accountLogin(accounts, id, pw);
        if (player == NULL)
        {
            printf("로그인 실패\n");
            continue;
        }
        else
        {
            currentAccount = player;
            return;
        }
    }
}

void startLogout()
{
    if (currentAccount == NULL)
    {
        printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
        getchar();
        return;
    }

    bool result = displayPrompt(L"정말 로그아웃 하시겠습니까?");
    if (result)
        currentAccount = NULL;
}

void startDelete()
{
    if (currentAccount == NULL)
    {
        printf("로그인 상태가 아닙니다.\n");
        getchar();
        return;
    }

    bool result = displayPrompt(L"정말 회원을 탈퇴하시겠습니까?");
    if (result)
    {
        accountDelete(accounts, currentAccount->id);
        currentAccount = NULL;
    }
}

void startWordGame()
{
    displayClear();
    float score = wordGameStart();

    if (score < 0) // 게임 안했을 때
        return; 

    printf("당신의 점수는 %.2f점 입니다.\n", score);
    if (currentAccount != NULL)
    {
        if (score > currentAccount->score)
            currentAccount->score = score;
        printf("%s의 최고점수는 %.2f 입니다.\n", currentAccount->id, currentAccount->score);
    }

    getchar();
}

void end()
{
    accountSaveAll(accounts);
    displayClear(); // 종료
    printf("다음에 또 만나용!\n");
}

int main(void)
{   
    // wchar 한글출력
    setlocale(LC_ALL, "");

    accounts = accountLoadAll();

    char *contents[6] = 
    {
        "회원가입",
        "로그인",
        "로그아웃",
        "영어 단어 맞추기",
        "회원 탈퇴",
        "프로그램 종료"
    };

    while (true)
    {
        displayClear();

        // 로그인된 계정의 id 가져오기
        char currentId[16];
        if (currentAccount != NULL)
            strcpy(currentId, currentAccount->id);
        else
            currentId[0] = '\0';

        // 메뉴 표시
        displayPrintMenu(currentId, contents, 6);

        // 입력
        char input[4];
        displayPrintInput();
        nextLine(input);

        if (strlen(input) != 1)
            continue;
        
        int inputNumber = atoi(input);
        switch (inputNumber)
        {
            case 1:
                startRegister(); // 회원가입
                break;
            case 2:
                startLogin(); // 로그인
                break;
            case 3:
                startLogout(); // 로그아웃
                break;
            case 4:
                startWordGame(); // 영어단어
                break;
            case 5:
                startDelete(); // 회원탈퇴
                break;
            case 6:
                end(); // 종료
                return 0;
            default:
                continue;
        }
    }
    return 0;
}