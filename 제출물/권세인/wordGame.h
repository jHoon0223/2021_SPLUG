#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"

#define WORD_FILE_PATH "dic.txt"

typedef struct WordQuestion
{
    char question[32];
    char answer[32];
} WordQuestion;

float     wordGameStart();
int       wordGameLoad(ListNode* list);
int       wordGameShowQuestion(WordQuestion *q);
