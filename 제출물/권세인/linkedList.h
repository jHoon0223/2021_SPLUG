#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>

typedef struct ListNode
{
    struct ListNode *previous;
    struct ListNode *next;
    void *data;
} ListNode;

ListNode* linkedListNewNode(void* data);
ListNode* linkedListFirstNode(ListNode* node);
ListNode* linkedListLastNode(ListNode* node);
void      linkedListAddData(ListNode* node, void* data);
void      linkedListInsertBefore(ListNode* node, void* data);
void      linkedListInsertAfter(ListNode* node, void* data);
void      linkedListRemoveNode(ListNode* node);
void      linkedListRemoveAfter(ListNode* node);
void      linkedListRemoveAll(ListNode* node);
void      linkedListSort(ListNode* node, int (*comparer)(void*, void*));

void _test_linkedlist();