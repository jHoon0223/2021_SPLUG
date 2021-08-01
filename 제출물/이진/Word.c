#include "header.h"

Word *makeWordNode(){
	Word *node = (Word *)malloc(sizeof(Word));
	node->next = NULL;
	node->En_word[Enword] = 0;
	node->Ko_word[Koword] = 0;
	return node;
}

WordStatus * makeWordStatus(){
	WordStatus * sta = (WordStatus *)malloc(sizeof(WordStatus));
	sta->num=0;
	sta->head=sta->cur=sta->temp=NULL;

	return sta;
}



void Sorting(WordStatus *sta)
{
	sta->cur = sta->temp = sta->head;
	for(int i=0;i<sta->num;i++)
	{
		for(int j=0;j<sta->num-i;j++)
		{
			if(strcmp(sta->temp->En_word, sta->cur->En_word)>0)
			{
				char tem_E[Enword]={0};
				char tem_K[Koword]={0};
				strcpy(tem_E,sta->cur->En_word);
				strcpy(sta->cur->En_word, sta->temp->En_word);
				strcpy(sta->temp->En_word , tem_E);

				strcpy(tem_K,sta->cur->Ko_word);
				strcpy(sta->cur->Ko_word, sta->temp->Ko_word);
				strcpy(sta->temp->Ko_word, tem_K);
			}
			sta->cur = sta->cur->next;

		}
		sta->temp =sta->cur = sta->temp->next;
	}
}




void Eng_test(WordStatus *sta)
{

	if(loginStatus==0){
		printf("로그인 상태가 아닙니다.\n");
		sleep(1);
		return ;
	}
	int C_num=0,F_num=0;
	sta->cur = sta->head;
	while(sta->num--)
	{
		printf("%s ->",sta->cur->Ko_word);
		char input[Koword]={0}; scanf("%s",input);
		if(!strcmp(input,".quit")) break;

		if(!strcmp(sta->cur->En_word,input))
		{
			printf("correct!\n");
			C_num++;
		}else{
			printf("incorrect!\n");
			F_num++;
		}
		sta->cur=sta->cur->next;
	}

	double score = 0.0;
	if(C_num==0 && F_num==0)
	{
		printf("당신의 점수는 %.2lf 점입니다.",score);
	}else{
		score=(double)100/(C_num + F_num)*C_num;
		printf("당신의 점수는 %.2lf 점입니다.",score);
	}
	while(getchar()!='\n');
}




WordStatus * InitWord(WordStatus *sta)
{
	//영어 단어 끌어오기
	FILE *fp = fopen("dic.txt","r");  
	rewind(fp); 
	char tmp_eng[Enword];
	sta = makeWordStatus();

	while(fscanf(fp,"%s",tmp_eng)==1)
	{
		Word * node = makeWordNode();
		strcpy(node->En_word,tmp_eng);

		fscanf(fp,"%[^\n]s",node->Ko_word);
		fgetc(fp);

		if(!sta->num)
		{
			sta->head=sta->cur=node;
			node->next=NULL;
		}else{
			node->next=NULL;
			sta->cur->next=node;
			sta->cur = sta->cur->next;
		}
		sta->num++;
	}
	return sta;

}

