#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 100
#define ID 20

extern int index = 0;

typedef struct Word {
	char source[MAX];
	char target[MAX];
}Word;
Word words[MAX];

typedef struct Member {
	char memName[12];
	char memID[ID];
	char memPW[ID];
	struct member* next;
}Member;
Member members[MAX];

Member* First = NULL;

void Infodel()
{
	
	char mID[20];
	char comparename[20];
	FILE* fp = fopen("col.txt", "a+");

	printf("���̵�:");
	scanf("%s", mID);

	while (1)
	{
		fscanf(fp, "%s" , comparename);

		if (feof(fp))
			break;
		if (!strcmp(comparename, mID))
		{
			fputs(" ", fp);
		}
	}
	printf("������ �Ϸ�Ǿ����ϴ�.");
}


int n = 0;

void memberdelete(char MemberID[]) {}



int main(void) {
	char* ans;
	char membername[12];
	char memberid[20];
	char memberpw[20];

start:
	//system("mode con:cols=50lines=20");
	printf("\n===================2021SPLUG======================\n");
	printf("\n\n=\t\t\t�޴�\t\t\t=\n\n");
	if (n = 0) {
		printf("���̵�");
	}
	else if (n = 1) { printf(""); }
	printf("\t1. ȸ������\n\t2. �α���\n\t3. �α׾ƿ�\n\t4. ���� �ܾ� ���߱�\n\t5. ȸ��Ż��\n\t6. ���α׷� ����\n");

	int i = 0;
	scanf("%d", &i);
	if (i == 1) {
		int j = 0;
		system("cls");
		FILE* load = NULL;
		char mID[MAX];
		char mName[12];
		char mPW[ID];
		printf("ȸ������ ������\n");
	again:
		printf("���̵� : ");
		scanf("%s", mID);
		getchar();

		char s1[MAX];
		fopen_s(&load, "col.txt", "r");
		while (fgets(s1, MAX - 1, load)) {
			Member member;
			char* ans = strtok(s1, "\n");
			strcpy(member.memID, ans);
			ans = strtok(NULL, "\n");
			members[j++] = member;
		}
		fclose(load);
		for (int i = 0; i < j;i++) {
			if (strcmp(members[i].memID, mID) == 0) {
				printf("�̹� �����ϴ� ���̵� �Դϴ�\n");
				goto again;
			}
			else if (strcmp(members[i].memID, mID) != 0) {

				printf("��밡���� ���̵� �Դϴ�.\n");
				fopen_s(&load, "col.txt", "wt");
				fputs(mID, load);
				fclose(load);
				printf("��й�ȣ : ");
				scanf("%s", mPW);
				printf("�̸� : ");
				scanf("%s", mName);
				goto start;

			}


		}
	}


	else if (i == 2) {

		FILE* load = NULL;
		int j = 0;
		char mID[MAX];
		char ch1[MAX];
		char ch2[MAX];
		system("cls");
	login:
		printf("�α���\n");
		printf("���̵� : ");
		scanf("%s", ch1);
		getchar();
		printf("��й�ȣ : ");
		scanf("%s", ch2);
		fopen_s(&load, "col.txt", "r");
		while (fgets(ch1, MAX - 1, load)) {
			Member member;
			char* ans = strtok(ch1, "\n");
			strcpy(member.memID, ans);
			ans = strtok(NULL, "\n");
			members[j++] = member;
		}
		fclose(load);
		for (int i = 0; i < j;i++) {
			if (strcmp(members[i].memID, mID) == 0) {
				goto start;

			}
			else {
				printf("Ʋ�Ƚ��ϴ�.");
			}

		}

	}
	else if (i == 3) {
		char x[MAX];
		printf("���� �α׾ƿ��Ͻðڽ��ϱ�? [y/n]: ");
		scanf("%s", x);
		if (x == "y") { goto login; }
		else if (x == "n") { n = 0; }

	}
	 else if (i == 4) {
		system("cls");

		int k = 0, i = 0, j = 0, count = 0;
		char* ans;
		char quiz[MAX];

		printf(">>���� �ܾ� ���߱� ���α׷�<<\n");
		printf("1. ���� �ܾ� ���߱� 2. ���α׷� ����\n\n");
		printf("��ȣ�� �����ϼ���: ");
		scanf("%d", &k);
		if (k == 1) {
			FILE* fp = fopen("dic.txt", "r");
			char s1[MAX];
			while (fgets(s1, MAX - 1, fp)) {
				Word word;
				char* ans = strtok(s1, " ");
				strcpy(word.source, ans);
				ans = strtok(NULL, "\n");
				strcpy(word.target, ans);
				words[j++] = word;
			}
			for (i = 0; i < j;i++) {
				printf("%s->", words[i].target);
				scanf("%s", quiz);
				if (strcmp(words[i].source, quiz) == 0) {
					printf("correct\n");
				}
				else if (strcmp(quiz, ":quit") == 0) { break; }
				else { printf("wrong\n"); }
			}
		}
		else if (k == 2) { goto start; }
	}
		
		else if (i == 5) {
			char x = {0};
		printf("���� ȸ���� Ż���Ͻðڽ��ϱ�? [y/n]: ");
		scanf("%s", x);
		if (x == "y") {  }
		else if (x == "n") { n = 0; }
		goto start;
		}
		else if (i == 6) {
		system("cls");
		Infodel();
		
		}

	return 0;
}


