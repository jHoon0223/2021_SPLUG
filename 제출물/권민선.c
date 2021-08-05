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

	printf("아이디:");
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
	printf("삭제가 완료되었습니다.");
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
	printf("\n\n=\t\t\t메뉴\t\t\t=\n\n");
	if (n = 0) {
		printf("아이디");
	}
	else if (n = 1) { printf(""); }
	printf("\t1. 회원가입\n\t2. 로그인\n\t3. 로그아웃\n\t4. 영어 단어 맞추기\n\t5. 회원탈퇴\n\t6. 프로그램 종료\n");

	int i = 0;
	scanf("%d", &i);
	if (i == 1) {
		int j = 0;
		system("cls");
		FILE* load = NULL;
		char mID[MAX];
		char mName[12];
		char mPW[ID];
		printf("회원가입 페이지\n");
	again:
		printf("아이디 : ");
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
				printf("이미 존재하는 아이디 입니다\n");
				goto again;
			}
			else if (strcmp(members[i].memID, mID) != 0) {

				printf("사용가능한 아이디 입니다.\n");
				fopen_s(&load, "col.txt", "wt");
				fputs(mID, load);
				fclose(load);
				printf("비밀번호 : ");
				scanf("%s", mPW);
				printf("이름 : ");
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
		printf("로그인\n");
		printf("아이디 : ");
		scanf("%s", ch1);
		getchar();
		printf("비밀번호 : ");
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
				printf("틀렸습니다.");
			}

		}

	}
	else if (i == 3) {
		char x[MAX];
		printf("정말 로그아웃하시겠습니까? [y/n]: ");
		scanf("%s", x);
		if (x == "y") { goto login; }
		else if (x == "n") { n = 0; }

	}
	 else if (i == 4) {
		system("cls");

		int k = 0, i = 0, j = 0, count = 0;
		char* ans;
		char quiz[MAX];

		printf(">>영어 단어 맞추기 프로그램<<\n");
		printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");
		printf("번호를 선택하세요: ");
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
		printf("정말 회원을 탈퇴하시겠습니까? [y/n]: ");
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


