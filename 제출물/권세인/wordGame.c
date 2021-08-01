#include "wordGame.h"

static void nextLine(char* input)
{
    scanf("%s[^\n]", input);
    getchar();
}

int wordComparer(void* a, void* b)
{
    if (a == NULL) // a < b, a - b < 0
        return -1;
    if (b == NULL)
        return 1;

    WordQuestion* wordA = (WordQuestion*)a;
    WordQuestion* wordB = (WordQuestion*)b;
    return strcmp(wordA->answer, wordB->answer);
}

float wordGameStart()
{
    printf(" >> 영어 단어 맞추기 프로그램 << \n");
    printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");

    int inputNumber;
    char input[8];
    while (true)
    {
        printf("번호를 선택하세요 : ");
        nextLine(input);

        if (strcmp(input, "1") == 0)
        {
            inputNumber = 1;
            break;
        }
        else if (strcmp(input, "2") == 0)
        {
            inputNumber = 2;
            break;
        }
    }

    if (inputNumber != 1)
        return -1;

    ListNode* words = linkedListNewNode(NULL);
    int wordCount   = wordGameLoad(words);

    int corret = 0;
    ListNode *node = linkedListFirstNode(words);
    while (node != NULL)
    {
        if (node->data != NULL)
        {
            WordQuestion *q = (WordQuestion*) node->data;
            int result = wordGameShowQuestion(q);

            if (result == -1)
                return corret;
            else if (result == 1)
                corret++;
        }

        node = node->next;
    }

    linkedListRemoveAll(words);

    return (float)corret / wordCount * 100;
}

int wordGameLoad(ListNode* words)
{
    FILE *fp;
    fp = fopen(WORD_FILE_PATH, "r");
    if (fp == NULL)
    {
        printf(" !!! 경고 : 단어 파일을 열 수 없습니다.");
        return 0;
    }

    int wordCount = 0;
    while (true)
    {
        char question[32];
        char answer[32];
        int r = fscanf(fp, "%s %s", answer, question);
        if (r == EOF)
            break;

        WordQuestion* wordQuestion = (WordQuestion*) malloc(sizeof(WordQuestion));
        strcpy(wordQuestion->question, question);
        strcpy(wordQuestion->answer,   answer);

        linkedListAddData(words, wordQuestion);
        wordCount++;
    }

    fclose(fp);
    linkedListSort(words, wordComparer);
    return wordCount;
}

int wordGameShowQuestion(WordQuestion *q)
{
    char answer[32];

    printf("%s -> ", q->question);
    nextLine(answer);

    if (strcmp(answer, ".quit") == 0)
    {
        return -1;
    }
    else if (strcmp(q->answer, answer) == 0)
    {
        printf("correct!\n");
        return 1;
    }
    else
    {
        printf("incorrect!\n");
        return 0;
    }
}