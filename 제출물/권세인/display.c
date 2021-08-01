#include "display.h"

// 화면 지우기
void displayClear()
{
    // https://stackoverflow.com/questions/2347770/how-do-you-clear-the-console-screen-in-c
    printf("\e[1;1H\e[2J");
}

// m을 times만큼 출력
void displayPrints(char m, int times)
{
    while(times-- > 0)
    {
        putchar(m);
    }
}

// msg를 가운데 정렬로 출력
void displayPrintMid(wchar_t *msg, char space, int width)
{
    int margin = width - wcslen(msg);
    int sideMargin = margin / 2;

    displayPrints(space, sideMargin);
    printf("%ls", msg);
    displayPrints(space, sideMargin);

    if (margin % 2 != 0)
        putchar(space);
}

// 줄 출력
void displayPrintLine()
{
    displayPrints(DISPLAY_LINE_CHAR, DISPLAY_WIDTH);
    putchar('\n');
}

// 메뉴 화면 출력
void displayPrintMenu(char* id, char* contents[], int count)
{
    displayPrintMenuHeader(id);
    displayPrintMenuContent(contents, count);
    displayPrintMenuFooter();
}

// 메뉴 윗부분 출력
void displayPrintMenuHeader(char* id)
{
    displayPrintLine();
    displayPrintMid(DISPLAY_TITLE, DISPLAY_LINE_CHAR, DISPLAY_WIDTH);
    putchar('\n');

    int idLength = strlen(id);
    int idMargin = DISPLAY_WIDTH - idLength;
    displayPrints(DISPLAY_LINE_CHAR, idMargin);
    if (id != NULL && idLength > 0)
        printf("\b %s", id);
    putchar('\n');

    displayPrintLine();

    putchar(DISPLAY_LINE_CHAR);
    displayPrintMid(L"메뉴", ' ', DISPLAY_WIDTH - 4);
    putchar(DISPLAY_LINE_CHAR);
    putchar('\n');

    displayPrintLine();
}

// 메뉴 내용 출력
void displayPrintMenuContent(char* contents[], int count)
{
    for (int i = 0; i < count; i++)
    {
        displayPrints(' ', MENU_CONTENT_MARGIN);
        printf("%d. %s\n", i+1, contents[i]);
    }
}

// 메뉴 아랫부분 출력
void displayPrintMenuFooter()
{
    displayPrintLine();
}

// 메뉴 입력받는부분 출력
void displayPrintInput()
{
    printf(": ");
}

// 유저에게 [y/n] 물어보기
bool displayPrompt(wchar_t *msg)
{
    while (true)
    {
        printf("%ls [y/n]:", msg);

        char res[16];
        scanf("%s[^\n]", res);

        if (strcmp(res, "y") == 0)
            return true;
        if (strcmp(res, "n") == 0)
            return false;
    }
}