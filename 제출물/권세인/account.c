#include "account.h"

ListNode* accountLoadAll()
{
    FILE *fp = fopen(ACCOUNT_FILE_PATH, "r");

    if (fp == NULL)
        return linkedListNewNode(NULL);
    
    ListNode *accounts = linkedListNewNode(NULL);
    while (true)
    {
        char  id[16];
        char  pw[16];
        char  name[16];
        float score;

        int r = fscanf(fp, "%s %s %s %f", id, pw, name, &score);

        if (r == EOF)
            break;

        Player* player = accountNewAccount(id, pw, name, score);
        linkedListAddData(accounts, player);
    }

    return accounts;
}

void accountSaveAll(ListNode* accounts)
{
    FILE *fp = fopen(ACCOUNT_FILE_PATH, "w");

    ListNode *node = linkedListFirstNode(accounts);
    while (node != NULL)
    {
        if (node->data != NULL)
        {
            Player* player = (Player*) node->data;

            fprintf(fp, "%s %s %s %f\n", 
                player->id,
                player->pw,
                player->name,
                player->score);
        }

        node = node->next;
    }

    fclose(fp);
}

// 새로운 Player 구조체 생성
Player* accountNewAccount(char* id, char* pw, char* name, float score)
{
    Player* newPlayer = (Player*) malloc(sizeof(Player));
    strcpy(newPlayer->id,   id);
    strcpy(newPlayer->name, name);
    strcpy(newPlayer->pw,   pw);
    newPlayer->score = score;

    return newPlayer;
}

// 유효성 검사 반환값 규칙
// 0: 가능, 1: 중복, 2: 짧은 길이, 3: 길이 초과, 4: 금지 문자 포함

// id 유효성 검사
int accountCheckIdValidation(ListNode* accounts, char* id)
{
    // 길이 검사
    if (strlen(id) < 1)
        return 2;
    if (strlen(id) > 16)
        return 3;

    // 금지 문자 검사
    if (strchr(id, ' '))
        return 4;

    // 중복 검사
    ListNode* node = linkedListFirstNode(accounts);
    while (node != NULL)
    {
        if (node->data != NULL)
        {
            Player* player = (Player*)node->data;
            if (strcmp(player->id, id) == 0)
                return 1;
        }

        node = node->next;
    }

    return 0;
}

// pw 유효성 검사
int accountCheckPasswordValidation(char* pw)
{
    if (strlen(pw) < 1)
        return 2;
    if (strlen(pw) > 16)
        return 3;
    
    if (strchr(pw, ' '))
        return 4;
    
    return 0;
}

// name 유효성 검사
int accountCheckNameValidation(char* name)
{
    if (strlen(name) < 1)
        return 2;
    if (strlen(name) > 16)
        return 3;
    
    if (strchr(name, ' '))
        return 4;
    
    return 0;
}

// 회원가입
void accountRegister(ListNode* accounts, Player *player)
{
    linkedListAddData(accounts, player);
    accountSaveAll(accounts);
}

// 로그인
Player* accountLogin(ListNode* accounts, char *id, char *pw)
{
    ListNode *node = linkedListFirstNode(accounts);
    while (node != NULL)
    {
        if (node->data != NULL)
        {
            Player *player = (Player*) node->data;
            if (strcmp(player->id, id) == 0 && strcmp(player->pw, pw) == 0)
                return player;
        }
        node = node->next;
    }

    return NULL;
}

// 회원탈퇴
void accountDelete(ListNode* accounts, char *id)
{
    ListNode *node = linkedListFirstNode(accounts);
    while (node != NULL)
    {
        if (node->data != NULL)
        {
            Player *player = (Player*) node->data;
            if (strcmp(player->id, id) == 0)
            {
                linkedListRemoveNode(node);
                free(player);
                return;
            }
        }
        node = node->next;
    }
    
    accountSaveAll(accounts);
}