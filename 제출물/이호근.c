#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define max_eng 200

struct member {
	struct member* next;
	char id[100];
	char pw[100];
	char name[100];
};

void addmember(struct member* target, char id[100], char pw[100], char name[100])
{
	struct member* newmember = malloc(sizeof(struct member));
	newmember->next = target->next;
	strcpy(newmember->id , id);
	strcpy(newmember->pw , pw);
	strcpy(newmember->name , name);

	target->next = newmember;
}

void removemember(struct member* target)
{
	struct member* removemem = target->next;
	target->next = removemem->next;
	free(removemem);
}

int main()
{
	int option=0, list=0, login=0, eng_option=0;
	int i=0, line_count=0, line_tmp=0, eng_num=0, question=0, correct=0, incorrect=0;
	int wrong_answer[max_eng] = { 0, };
	char buffer[100] = { 0, };
	char buf[300] = { 0, };
	char eng_buf[100] = { 0, };
	char eng_tmp[100] = { 0, };
	char kor_tmp[100] = { 0, };
	char answer[100] = { 0, };
	char dic[2][max_eng][100] = { 0, };
	char login_id[100] = { 0, };
	char c = '\0',join_after = '\0',test = '\0',wrong_check ='\0';
	char logout = '\0';
	char memout = '\0';
	char idp[100] = { 0, };
	char pwp[100] = { 0, };
	char namep[100] = { 0, };

	FILE* fp = fopen("member.txt", "a");
	fclose(fp);

	struct member *head = malloc(sizeof(struct member));
	head->next = NULL;

	struct member* curr;

	FILE* mfp = fopen("member.txt", "r");
	rewind(mfp);
	
	i = 0;
	while (feof(mfp)==0)
	{
		c = getc(mfp);
		if (c != ' ' && c != '\n'&& i>=0)
			buffer[i] = c;
		else if (c == '\n')
			c = '\0';
		else if (c == ' ')
		{
			if (list == 0)
			{
				strcpy(idp, buffer);
				list++;
				i = -1;
			}
			else if (list == 1)
			{
				strcpy(pwp, buffer);
				list++;
				i = -1;
			}
			else if (list == 2)
			{
				strcpy(namep, buffer);
				list = 0;
				i = -2;
				addmember(head, idp, pwp, namep);
				memset(idp, 0, sizeof(idp));
				memset(pwp, 0, sizeof(pwp));
				memset(namep, 0, sizeof(namep));
			}
			memset(buffer, 0, sizeof(buffer));
			c = '\0';
		}
		i++;
	}
	fclose(mfp);
	
start:
	system("cls");
	if (login == 0)
	{
		printf("========================================\n");
		Sleep(100);
		printf("============== 2021 SPLUG ==============\n");
		Sleep(100);
		printf("=============???????? ??????============\n");
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf("=============??????????????.============\n");
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf("=		  ????		       =\n");
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf("	  1. ????????\n");
		Sleep(100);
		printf("	  2. ??????\n");
		Sleep(100);
		printf("	  3. ????????\n");
		Sleep(100);
		printf("	  4. ???? ???? ??????\n");
		Sleep(100);
		printf("	  5. ???? ????\n");
		Sleep(100);
		printf("	  6. ???????? ????\n");
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf(":");
		scanf("%d", &option);
	}
	else if (login == 1)
	{
		printf("========================================\n");
		Sleep(100);
		printf("============== 2021 SPLUG ==============\n");
		Sleep(100);
		printf("=============???????? ??????============\n");
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf("=      %s?? ??????????~	       =\n",login_id);
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf("=		  ????		       =\n");
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf("	  1. ????????\n");
		Sleep(100);
		printf("	  2. ??????\n");
		Sleep(100);
		printf("	  3. ????????\n");
		Sleep(100);
		printf("	  4. ???? ???? ??????\n");
		Sleep(100);
		printf("	  5. ???? ????\n");
		Sleep(100);
		printf("	  6. ???????? ????\n");
		Sleep(100);
		printf("========================================\n");
		Sleep(100);
		printf(":");
		scanf("%d", &option);
	}
	switch (option){
	/*
	case 0: //linked list test
		i = 1;
		curr = head->next;
		while (curr != NULL)
		{
			printf("%d???? ?????? id: %s, pw: %s, name: %s\n",i,curr->id,curr->pw,curr->name);
			Sleep(1500);
			i++;
			curr = curr->next;
		}
		i = 0;
		Sleep(5000);

		break;
	*/
	case 1: //???????? O
		if (login == 1)
		{
			Sleep(200);
			printf("???????? ????????????.\n");
			Sleep(1000);
			printf("?????????? ?? ?????????? ??????????.\n");
			Sleep(1000);
			printf("???????????? ??????????.\n");
			Sleep(1000);
			system("cls");
			goto start;
		}

		system("cls");
		printf("<<???????? ??????>>\n");
		Sleep(200);
		printf("\n???????? ???????? ??????????\n\n");
		printf("??????: ");
		scanf("%s", idp);

		curr = head->next;
		while (curr != NULL)
		{
			if (strcmp(curr->id, idp)==0)
			{
				Sleep(200);
				printf("\n???? ???????? ????????????. ???? ???????? ??????????????.\n\n");
				curr = head->next;
				Sleep(1000);
				memset(idp, 0, sizeof(idp));
				system("cls");
				printf("<<???????? ??????>>\n");
				Sleep(200);
				printf("\n???????? ???????? ??????????\n\n");
				printf("??????: ");
				scanf("%s", idp);
			}
			else 
				curr = curr -> next;
		}
		Sleep(200);
		printf("\n?????????? ?????? ??????.\n\n");

		Sleep(200);
		printf("????????: ");
		scanf("%s", pwp);

		Sleep(200);
		printf("????: ");
		scanf("%s", namep);

		addmember(head, idp, pwp, namep);

		FILE* mfp = fopen("member.txt", "a");
		fprintf(mfp, "%s ", idp);
		fprintf(mfp, "%s ", pwp);
		fprintf(mfp, "%s \n", namep);
		fclose(mfp);

		memset(namep, 0, sizeof(namep));

		Sleep(200);
		printf("\n?????????? ??????????????.\n");
		Sleep(1000);

		getchar();
		printf("\n???? ??????????????????? [y/n]: ");
		scanf("%c", &join_after);

		if (join_after == 'y')
		{
			Sleep(200);
			goto login;
		}
		else if (join_after == 'n')
		{
			Sleep(200);
		}
		else if (join_after != 'y' && join_after != 'n')
		{
			Sleep(200);
			printf("y?? n?? ???????? ????????.\n");
			Sleep(1000);
		}
		join_after = '\0';

		memset(idp, 0, sizeof(idp));
		memset(pwp, 0, sizeof(pwp));

		break;
	  
   case 2: //?????? O
		if(login==1)
		{
			Sleep(200);
			printf("???? ???????? ????????????.\n");
			Sleep(1000);
			printf("???????????? ??????????.\n");
			Sleep(1000);
			system("cls");
			goto start;
		}

		system("cls");
		printf("<<??????>>\n");
		Sleep(200);

		printf("??????: ");
		scanf("%s", idp);

		printf("????????: ");
		scanf("%s", pwp);

		login:
		curr = head->next;
		while (curr != NULL)
		{
			if (strcmp(idp, curr->id) == 0 && strcmp(pwp, curr->pw) == 0)
			{
				Sleep(200);
				printf("\n????????????????.\n");
				login=1;
				strcpy(login_id, idp);
				Sleep(1000);
			}
			curr = curr->next;
		}
		if (login == 0)
		{
			Sleep(200);
			printf("\n???????? ???? ????????????, ?????? ??????????????.\n");
			Sleep(1000);
			system("cls");
		}

		memset(idp, 0, sizeof(idp));
		memset(pwp, 0, sizeof(pwp));

		break;

   case 3: //????????
		if (login == 0)
		{
			Sleep(200);
			printf("?????? ?????? ????????.\n"); 
			Sleep(1000);
			system("cls");
			goto start;
		}
		getchar();
		printf("???????? ????????????? [y/n]: ");
		scanf("%c", &logout);

		if (logout == 'y')
		{
			Sleep(200);
			login = 0;
			memset(login_id, 0, sizeof(login_id));
		}
		else if (logout == 'n')
		{
			Sleep(200);
		}
		else if(logout != 'y' && logout != 'n')
		{
			Sleep(200);
			printf("y?? n?? ???????? ????????.\n");
			Sleep(1000);
		}
		logout = '\0';

		break;

   case 4: //???????? ??????
	   if (login == 0)
	   {
		   Sleep(200);
		   printf("?????? ?? ??????????????. ???????? ????????.\n");
		   Sleep(1000);
		   system("cls");
		   goto start;
	   }

		system("cls");
		Sleep(1000);
		printf(">> ???? ???? ?????? <<\n");
		Sleep(1000);
		printf("1.???? ???? ?????? 2.???????????? ????\n\n");
		Sleep(1000);
		printf("?????? ??????????: ");
		scanf("%d", &eng_option);

		if (eng_option == 1)
		{
			FILE* fp = fopen("dic.txt", "r");
			rewind(fp);
			eng_num = 0;
			c = '\0';
			i = 0;
			while (feof(fp) == 0)
			{
				c = getc(fp);
				if (c != ' ' && c != '\n' && i >= 0)
					eng_buf[i] = c;
				else if (c == ' ')
				{
					strcpy(dic[0][eng_num], eng_buf);
					memset(eng_buf, 0, sizeof(eng_buf));
					i = -1;
				}
				else if (c == '\n')
				{
					strcpy(dic[1][eng_num], eng_buf);
					memset(eng_buf, 0, sizeof(eng_buf));
					i = -1;
					eng_num++;
				}
				i++;
			}
			fclose(fp);

			for (int step = 0; step < eng_num - 2; step++)
			{
				i = step;
				while (strcmp(dic[0][i], dic[0][i + 1]) > 0)
				{
					strcpy(eng_tmp,dic[0][i]);
					strcpy(dic[0][i], dic[0][i + 1]);
					strcpy(dic[0][i + 1], eng_tmp);
					strcpy(kor_tmp, dic[1][i]);
					strcpy(dic[1][i], dic[1][i + 1]);
					strcpy(dic[1][i + 1], kor_tmp);
					i--;
					if (i < 0)
						break;
				}
			}
	
			Sleep(500);
			printf("\n???????? ???????? ??????????\n");
			Sleep(1500);
			printf("???????? 100???????? ???? ??????/???? ???????? ??????????.??\n");
			Sleep(1500);
			printf("??'.quit'?? ???????? ?????? ?????? ???????? ??????????.??\n");
			Sleep(1500);
			printf("\nstart!\n\n");
			correct = 0;
			incorrect = 0;
			question = 0;
			for (i = 0; i < eng_num; i++)
			{
				Sleep(500);
				printf("%d. %s -> ", i+1, dic[1][i]);
				scanf("%s", answer);
				if (strcmp(answer, ".quit") == 0)
				{
					if (i == 0)
					{
						Sleep(200);
						printf("\n???????????? ??????????.\n");
						Sleep(1000);
						goto start;
					}
					Sleep(500);
					if (correct == question)
					{
						printf("\n100??! ?????????? ???? ?????????? ????????????!\n");
						goto start;
					}
					else
					{
						printf("\n?????? ?????? %.2f????????.\n\n", (float)100 * correct / question);
						Sleep(2000);
						goto check_wrong_answer;
					}
				}
				else if (strcmp(answer, dic[0][i]) == 0)
				{
					printf("correct! ????!\n");
					correct++;
				}
				else
				{
					printf("incorrect! ????!\n");
					wrong_answer[incorrect] = i;
					incorrect++;
				}
				question++;
			}
			Sleep(500);
			if (correct == question)
			{
				printf("\n100??! ????????????! ?????? ???? ?????????? ????????????!\n");
				Sleep(2000);
				goto start;
			}
			else
			{
				Sleep(200);
				printf("\n?????? ?????? %.2f????????.\n\n", (float)100 * correct / question);
				Sleep(2000);
			}
		check_wrong_answer:
			getchar();
			printf("?????? ????????????????? [y/n]: ");
			scanf("%c", &wrong_check);

			if (wrong_check == 'y')
			{
				Sleep(200);
				for (i = 0; i < incorrect; i++)
				{
					if (i == incorrect - 1)
					{
						printf("???? %d. ??: %s -> %s\n",wrong_answer[i] + 1,dic[1][wrong_answer[i]], dic[0][wrong_answer[i]]);
						Sleep(2000);
						printf("\n???? ?????????? ??????????????. ??????????????!\n");
						Sleep(5000);
					}
					else
					{
						printf("???? %d. ??: %s -> %s\n", wrong_answer[i] + 1, dic[1][wrong_answer[i]], dic[0][wrong_answer[i]]);
						Sleep(2000);
					}
				}
			}
			else if (wrong_check == 'n')
			{
				Sleep(200);
			}
			else if (wrong_check != 'y' && wrong_check != 'n')
			{
				Sleep(200);
				printf("y?? n?? ???????? ????????.\n");
				Sleep(1000);
			}
			wrong_check = '\0';

		}
		else if (eng_option == 2)
		{
			Sleep(200);
			printf("\n???????????? ??????????.\n");
			Sleep(1000);
		}
		else
		{
			Sleep(200);
			printf("1~2?? ?????? ????????????.\n");
			Sleep(1000);
		}

		break;

   case 5: //????????
		if (login == 0)
		{
			Sleep(200);
			printf("?????? ?????? ????????.\n");
			Sleep(1000);
			system("cls");
			goto start;
		}

		getchar();
		printf("???? ?????? ????????????????? [y/n]: ");
		scanf("%c", &memout);

		if (memout == 'y')
		{
			struct member* next = head;
			curr = head->next;
			i = 1;
			line_count = 0;

			FILE* mfp = fopen("member.txt", "r");
			rewind(mfp);
			while (fgets(buf, 300, mfp) != NULL)
			{
				line_count++;
			}
			line_tmp = line_count;
			fclose(mfp);

			line_count = 0;
			while (curr != NULL)
			{
				if (strcmp(login_id, curr->id) == 0)
				{
					FILE* mfp = fopen("member.txt", "r");
					FILE* mfptmp = fopen("membertmp.txt", "w");
					rewind(mfp);
					rewind(mfptmp);
					while (fgets(buf, 300, mfp) != NULL)
					{
						line_count++;
						if (line_count == line_tmp+1-i)
						{
							continue;
						}
						else
						{
							fprintf(mfptmp, buf);
						}
					}
					fclose(mfp);
					fclose(mfptmp);

					mfp = fopen("member.txt", "w");
					mfptmp = fopen("membertmp.txt", "r");
					rewind(mfp);
					rewind(mfptmp);
					for (int j = 0; j < line_count-1; j++)
					{
						fgets(buf, 300, mfptmp);
						fprintf(mfp, buf);
					}
					fclose(mfp);
					fclose(mfptmp);
			
					removemember(next);
					break;
				}
				next = curr;
				curr = curr->next;
				i++;
			}
			login = 0;
			memset(login_id, 0, sizeof(login_id));
			Sleep(200);
			printf("?????????? ??????????????.");
			Sleep(1000);
		}
		else if (memout == 'n')
		{
			Sleep(200);
		}
		else if (memout != 'y' && memout != 'n')
		{
			Sleep(200);
			printf("y?? n?? ???????? ????????.\n");
			Sleep(1000);
		}
		memout = '\0';

		break;

   case 6: //???????? ???? O
	    system("cls");
		printf("?????? ???? ??????~~\n");
		Sleep(1000);
		goto end;

   default:
	    Sleep(200);
		printf("1~6?? ?????? ????????????.\n");
		Sleep(1000);
	}
	system("cls");
	goto start;

end: 
	curr = head->next;
	while (curr != NULL)
	{
		struct member* next = curr->next;
		free(curr);
		curr = next;
	}
	free(head);
	printf("??????????.\n");
	return 0;
}