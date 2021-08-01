#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"

#define ACCOUNT_FILE_PATH "account.txt"

typedef struct Player {
    char  id[16];
    char  name[16];
    char  pw[16];
    float score;
} Player;

ListNode* accountLoadAll();
void      accountSaveAll(ListNode* accounts);

Player*   accountNewAccount(char* id, char* name, char* pw, float score);
void      accountRegister(ListNode* accounts, Player *player);
Player*   accountLogin(ListNode* accounts, char *id, char *pw);
void      accountDelete(ListNode* accounts, char *id);

// 유효성 검사 반환값 규칙
// 0: 가능, 1: 중복, 2: 짧은 길이, 3: 길이 초과, 4: 금지 문자 포함
int accountCheckIdValidation(ListNode* accounts, char* id);
int accountCheckPasswordValidation(char* pw);
int accountCheckNameValidation(char *name);
