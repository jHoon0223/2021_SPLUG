#include "linkedList.h"

// 새로운 노드 생성
ListNode* linkedListNewNode(void* data)
{
    ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
    newNode->next     = NULL;
    newNode->previous = NULL;
    newNode->data     = data;
    return newNode;
}

// 리스트의 첫번째 노드 가져오기
ListNode* linkedListFirstNode(ListNode* node)
{
    if (node == NULL)
        return NULL;

    if (node->previous == NULL)
        return node;
    
    linkedListFirstNode(node->previous);
}

// 리스트의 마지막 노드 가져오기
ListNode* linkedListLastNode(ListNode* node)
{
    if (node == NULL)
        return NULL;

    if (node->next == NULL)
        return node;

    linkedListLastNode(node->next);
}

// TODO : 나중에 하기
// 리스트 끝에 새로운 데이터 추가
void linkedListAddData(ListNode* node, void* data)
{
    if (node == NULL)
        return;

    ListNode* lastNode = linkedListLastNode(node);
    ListNode* newNode  = linkedListNewNode(data);

    lastNode->next = newNode;
    newNode->previous = lastNode;
}

// node 바로 다음에 데이터 삽입
void linkedListInsertAfter(ListNode* node, void* data)
{
    if (node == NULL)
        return;

    ListNode *nextNode = node->next;
    ListNode *newNode  = linkedListNewNode(data);

    node->next        = newNode;
    newNode->previous = node;
    newNode->next     = nextNode;
    if (nextNode != NULL)
        nextNode->previous = newNode;
}

void linkedListInsertBefore(ListNode* node, void* data)
{
    if (node == NULL)
        return;
    
    ListNode* previousNode = node->previous;
    ListNode* newNode      = linkedListNewNode(data);

    node->previous    = newNode;
    newNode->next     = node;
    newNode->previous = previousNode;
    if (previousNode != NULL)
        previousNode->next = newNode;
}

// a와 b를 swap
void linkedListSwapNode(ListNode* a, ListNode* b)
{
    if (a == NULL || b == NULL)
        return;
    if (a->data == b->data)
        return;
    
    void* temp = a->data;
    a->data = b->data;
    b->data = temp;
}

// node 를 리스트에서 삭제
void linkedListRemoveNode(ListNode* node)
{
    if (node == NULL)
        return;

    // preNode -> node -> nextNode
    ListNode *preNode  = node->previous;
    ListNode *nextNode = node->next;

    if (nextNode != NULL)
        nextNode->previous = preNode;
    if (preNode != NULL)
        preNode->next = nextNode;

    free(node);
}

// node 부터 마지막 노드까지 제거
void linkedListRemoveAfter(ListNode* node)
{
    if (node == NULL)
        return;

    if (node->next != NULL)
        linkedListRemoveAfter(node->next);
    
    linkedListRemoveNode(node);
}

// 리스트 전체 삭제
void linkedListRemoveAll(ListNode* node)
{
    if (node == NULL)
        return;

    ListNode *first = linkedListFirstNode(node);
    linkedListRemoveAfter(first);
}

// for test
static void printStringList(ListNode* node)
{
    if (node == NULL)
        return;

    if (node->data != NULL)
    {
        char* str = (char*)node->data;
        printf("%s\n", str);
    }

    if (node->next != NULL)
        printStringList(node->next);
}

// insertion sort
void linkedListSort(ListNode* node, int (*comparer)(void*, void*))
{
    if (node == NULL)
        return;

    ListNode *target = linkedListFirstNode(node)->next;
    ListNode *next   = target->next;
    while (target != NULL)
    {
        next = target->next;

        //printf("target : %s \n", ((char*)target->data));
        ListNode *cp = target;
        while (true)
        {
            if (cp->previous == NULL)
                break;
            if (comparer(target->data, cp->previous->data) > 0)
                break;

            cp = cp->previous;
        }

        //printf("insert before : %s \n", (char*)cp->data);
        if (target != cp)
        {
            linkedListInsertBefore(cp, target->data);
            linkedListRemoveNode(target);
        }

        target = next;
        //printStringList(linkedListFirstNode(cp));
    }
}

int test_comparer(void *a, void *b)
{
    char *astr = (char*) a;
    char *bstr = (char*) b;
    return strcmp(astr, bstr);
}

// for test
void _test_linkedlist()
{
    char *test[10] = {
        "k", "b", "c", "x", "e", "f", "q", "i", "j", "a"
    };

    ListNode* list = linkedListNewNode(test[0]);
    for (int i = 1; i < 10; i++)
    {
        linkedListAddData(list, test[i]);
    }
    //printStringList(list);

    //ListNode* last = linkedListLastNode(list);
    //linkedListRemoveNode(last->previous);
    
    linkedListSort(list, test_comparer);

    // c f
    //linkedListSwapNode(list->next->next, list->next->next->next->next->next);

    // k b
    //linkedListSwapNode(list, list->next);

    //linkedListInsertBefore(list, "asdf");
    //linkedListRemoveNode(list->next);

    printStringList(linkedListFirstNode(list));
}