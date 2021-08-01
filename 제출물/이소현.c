#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

void menu();
void signup();
void memlogin();
void memlogout();
void quiz();
void memdel(char playerid);
void appendmem();
int overlap(char memid);
int overlapp(char tmppasswd);
void fileload();
void addword(struct quizdata **fward, char* str1, char* str2);
void sort();
void swap(struct quizdata* a, struct quizdata* b);

int login = 0;
int logout = 0;
char playerid[20] = { 0, };
char tmppasswd2[20] = { 0, };
FILE* fp;

typedef struct quizdata {
	char eng[20];
	char kor[20];
	struct quizdata* follow;
}quizdata;
quizdata* fward = NULL;

typedef struct meminfo {
	char id[20];
	char passwd[20];
	struct meminfo* next;
}meminfo;
meminfo* first = NULL;

meminfo* init() {
	meminfo* tmp = (meminfo*)malloc(sizeof(meminfo));
	tmp->next = NULL;
	return tmp;
}

int main(void) {

	int val = 0;
	fileload();

	while (1) {
		menu();

		val = _getch();

		if (val == '1' || val == '2' || val == '3' || val == '4' || val == '5' || val == '6')
			;
		else
			continue;

		if (val == '1')
			signup(); // 완료

		else if (val == '2')
			memlogin(); // 완료

		else if (val == '3')
			memlogout(); // 완료
			
		else if (val == '4')
			quiz();
			
		else if (val == '5')
			memdel(playerid); // 완료
		
		else if (val == '6'){
			system("clear");
			printf("감사합니다!!");
			free(first);
			return 0;
		}
	}

	return 0;
}
void menu() {
	system("clear");
	printf("==================================\n");
	printf("=========== 2021 SPLUG ===========\n");
	if (login == 1) {
		for (int i = 0; i < 34 - (strlen(playerid) + 3); i++)
			printf("=");
		printf(" <%s>\n", playerid);
	}
	else
		printf("==================================\n");
	printf("==================================\n");
	printf("=              메뉴              =\n");
	printf("==================================\n");
	printf("        1. 회원가입\n");
	printf("        2. 로그인\n");
	printf("        3. 로그아웃\n");
	printf("        4. 영어 단어 맞추기\n");
	printf("        5. 회원 탈퇴\n");
	printf("        6. 프로그램 종료\n");
	printf("==================================\n");
	printf("> ");
}

void signup() {
	char memid[20], mempasswd[20];
	int x;
	system("clear");
	printf("<회원가입 페이지>\n");
	printf("아이디 : ");
	scanf("%10s", memid);
	fopen_s(&fp, "member.txt", "wt");
	while (1) {
		x = overlap(memid);
		if (x == 2) {
			printf("이미 존재하는 아이디입니다. 다시 입력해주세요.\n");
			printf("아이디 : ");
			scanf("%10s", memid);
		}
		else if (x == 1)
			break;
	}
	printf("비밀번호 : ");
	scanf("%10s", mempasswd);
	appendmem(&first, memid, mempasswd);
	struct meminfo* q = first;
	while (q != NULL) {
		fprintf(fp, "%s %s\n", q->id, q->passwd);
		q = q->next;
	}
	fclose(fp);
}

void memlogin() {
	char tmpid[20] = { 0, }, tmppasswd[20] = { 0, };
	int x;
	system("clear");
	printf("<로그인>\n");
	while (1) {
		printf("아이디 : ");
		scanf("%s", tmpid);
		x = overlap2(tmpid);
		if (x == 2) {
			while (1) {
				printf("비밀번호 : ");
				scanf("%s", tmppasswd);
				x = overlapp(tmppasswd);
				if (x == 2) {
					login = 1;
					strcpy(playerid, tmpid);
					return;
				}
				else
					printf("잘못된 비밀번호입니다. 다시 입력해주세요.\n");
			}
		}
		else
			printf("잘못된 아이디입니다. 다시 입력해주세요.\n");
	}

}

void memlogout() {
	if (login == 1) {
		printf("로그아웃 하시겠습니까? [Y/N] : ");
		logout = _getch();
		if (logout == 'Y')
			login = 0;
		else if (logout == 'N')
			;
		else
			printf("\n잘못된 입력입니다.");
	}
	else {
		printf("로그인이 되어 있지 않습니다.");
	}
}

void quiz() {
	int i = 0;
	char buffer[25];
	char* str1 = malloc(sizeof(char));
	char* str2 = malloc(sizeof(char));;
	fopen_s(&fp, "dic.txt", "rt");
	quizdata* pres;
	pres = (quizdata*)malloc(sizeof(quizdata));
	while (!feof(fp)) {
		fgets(buffer, sizeof(buffer), fp);
		char* ptr = strtok(buffer, " ");
		while (ptr != NULL) {
			if (i == 0) {
				strcpy(str1, ptr);
				i++;
			}
			else if (i == 1) {
				strcpy(str2, ptr);
				addword(&fward, str1, str2);
				i = 0;
			}
			ptr = strtok(NULL, " ");
		}
	}
	sort(fward);
	int l, score = 0;
	char word[15];
	system("clear");
	printf(">> 영어 단어 맞추기 프로그램 <<\n");
	printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");
	while (1) {
		printf("번호를 선택하세요 : \n");
		l = _getch();
		if (l != '1' && l != '2')
			printf("잘못된 입력입니다.\n");		
		else
			break;
	}
	if (l == '1') {
		pres = fward;
		while (pres != NULL) {

			printf("%s -> ", pres->kor);
			scanf("%s", word);
			if (strcmp(word, pres->eng) == 0) {
				printf("correct!\n");
				score++;
			}
			else if (strcmp(word, ".quit") == 0) {
				printf("당신의 점수는 %d점 입니다.", score);
				clock_t start = clock();
				while (clock() - start < 500)
					;
				return;
			}
			else
				printf("incorrect!\n");
			pres = pres->follow;

		}
		printf("당신의 점수는 %d점 입니다.", score);
		clock_t start = clock();
		while (clock() - start < 500)
			;
		return;
	}
	else if (l == '2')
		return;
	free(str1);
	free(str2);
	free(fward);
}

void memdel(char playerid[]) {
	int i = 0, j = 0;
	meminfo* tmpr, *bef;
	if (login == 1) {
		printf("정말 탈퇴하시겠습니까? [Y/N] : ");
		i = _getch();
		if (i == 'Y') {
			tmpr = first;
			if (strcmp(tmpr->id, playerid) == 0) {
				first = tmpr->next;
				free(tmpr);
			}
			else {
				for (; strcmp(tmpr->id, playerid) != 0; j++) {
					tmpr = tmpr->next;
					if (j == 1)
						bef = bef->next;
					if (j != 0)
						bef = first;
				}
				bef->next = tmpr->next;
				free(tmpr);
			}
			fopen_s(&fp, "member.txt", "wt");
			while (first != NULL) {
				fprintf(fp, "%s %s\n", first->id, first->passwd);
				first = first->next;
			}
			login = 0;
			fclose(fp);
			
		}
		else if (i == 'N')
			return;
		else {
			printf("\n잘못된 입력입니다.");
			return;
		}
	}
	else
		printf("로그인이 되어 있지 않습니다.");
}

void appendmem(meminfo** head, char id[20], char passwd[20]) {
	if (!*head) {
		*head = init();
		strcpy((*head)->id, id);
		strcpy((*head)->passwd, passwd);
		return;
	}
	appendmem(&(*head)->next, id, passwd);
}

void addword(struct quizdata** fward, char* str1, char* str2) {
	quizdata* addlist = (quizdata*)malloc(sizeof(quizdata));
	strcpy(addlist->eng, str1);

	for (int i = 0; i < strlen(str2); i++) {
		if (str2[i] == '\n')
			str2[i] = '\0';
	}
	strcpy(addlist->kor, str2);

	if (*fward == NULL)
		*fward = addlist;
	else {
		struct quizdata* fin = *fward;
		while (fin->follow != NULL) {
			fin = fin->follow;
		}
		fin->follow = addlist;
	}
	addlist->follow = NULL;
}

int overlap(char memid[]) {
	struct meminfo* curr = first;
	while (curr != NULL) {
		if (strcmp(memid, curr->id) != 0)
			curr = curr->next;
		else
			return 2;
	}
	return 1;
}

int overlap2(char tmpid[]) {
	struct meminfo* curr = first;
	while (curr != NULL) {
		if (strcmp(tmpid, curr->id) != 0)
			curr = curr->next;
		else {
			strcpy(tmppasswd2, curr->passwd);
			return 2;
		}
	}
	return 1;
}

int overlapp(char tmppasswd[]) {
	if (strcmp(tmppasswd2, tmppasswd) == 0)
		return 2;
	else
		return 1;
}

void fileload() {
	fopen_s(&fp, "member.txt", "rt");
	if (fp == NULL)
		return;
	else {
		meminfo* load = NULL;
		while (feof(fp) == 0) {
			load = (meminfo*)malloc(sizeof(meminfo));
			load->next = NULL;
			fscanf(fp, "%s %s\n", &load->id, &load->passwd);
			if (first == NULL)
				first = load;
			else {
				meminfo* tmpr = first;
				while (tmpr->next != NULL)
					tmpr = tmpr->next;
				tmpr->next = load;
			}
		}
	}
	fclose(fp);
}

void sort(struct quizdata *fward) {
	int i;
	struct quizdata* a;
	struct quizdata* b = NULL;
	
	do {
		i = 0;
		a = fward;

		while (a->follow != b) {
			if (strcmp(a->eng, a->follow->eng) > 0) {
				swap(a, a->follow);
				i = 1;
			}
			a = a->follow;
		}
		b = a;
	} 	while (i);
}

void swap(struct quizdata* a, struct quizdata* b) {
	char tmpeng[20], tmpkor[20];
	strcpy(tmpeng, a->eng);
	strcpy(tmpkor, a->kor);
	strcpy(a->eng, b->eng);
	strcpy(a->kor, b->kor);
	strcpy(b->eng, tmpeng);
	strcpy(b->kor, tmpkor);
}