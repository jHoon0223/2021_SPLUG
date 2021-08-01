#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Eng
{
    struct Eng *next;
    char word[20];
    char meaning[20];
};

void engWordQuiz()
{
    FILE *fp=fopen("dic.txt", "rb");

    struct Eng *head=malloc(sizeof(struct Eng));
    head->next=NULL;

    while(!feof(fp))
    {
        char a[20], b[20];
        struct Eng *words=malloc(sizeof(struct Eng));
        words->next=head->next;
        fscanf(fp, "%s %s\n", a, b);
        strcpy(words->word, a);
        strcpy(words->meaning, b);
        head->next=words;
    }
    while(1)
    {
        char temp[20];
        struct Eng *curr=head->next;
        int count=0;
        while(curr->next!=NULL)
        {
            if(strcmp(curr->word, curr->next->word)>0)
            {
                strcpy(temp, curr->word);
                strcpy(curr->word, curr->next->word);
                strcpy(curr->next->word, temp);
                strcpy(temp, curr->meaning);
                strcpy(curr->meaning, curr->next->meaning);
                strcpy(curr->next->meaning, temp);
                count++;
            }
            curr=curr->next;
        }
        if(count==0)
            break;
    }
    struct Eng *curr=head->next;
    float count=0, try=0;
    while(curr!=NULL)
    {
        char input[20];
        printf("%s : ", curr->word);
        scanf("%s", input);
        if(strcmp(curr->meaning, input)==0)
        {
            printf("correct :)\n");
            count++;
            try++;
        }
        else if(strcmp(input,".quit")==0)
        {
            system("clear");
            printf("[system] 영어 단어 맞추기 결과 : %.0f점\n", count/(try==0?1:try)*100);
            break;
        }
        else
        {
            printf("incorrect :(\n");
            try++;
        }
        curr=curr->next;
    }
    fclose(fp);
}