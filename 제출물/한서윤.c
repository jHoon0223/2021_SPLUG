#define _CRT_SECURE_NO_WARNINGS
#define WORDLIST_MAX 200

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <string.h>

typedef struct MemberInformation { //회원정보 구조체
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	struct MemberInformation* next;
} MemberInformation;

typedef struct WordList { // 영어단어목록 구조체
	char word[20];
	char meaning[10];
} WordList;

// 함수 원형
int menu(void);
void list_init(void);
MemberInformation* makenode(void);
void load_file(void);
void overlap(char input_MemberID[]);
void SignUp(void);
void Login(void);
void Logout(void);
void game(void);
void sort(void);
void DeleteMember(char MemberID[]);
void Unsubscribe(void);
void finish(void);

//전역변수
int LogStatus = 0;
char ID[10];
char Password[20];
char Name[30];
MemberInformation* head;
MemberInformation* tail;


int main(void) {
	FILE* fp = fopen("MemberList.txt", "at");
	if (fp == NULL) {
		printf("파일을 열지 못했습니다.\n");
	}
	fclose(fp);
	int select;
	list_init(); // 연결리스트 초기화
	load_file(); // 파일 불러오기

	while (1) {
		select = menu(); // 메뉴 화면
		switch (select) {
		case 1 : // 회원가입
			SignUp();
			break;
		case 2 : // 로그인
			Login();
			break;
		case 3 : // 로그아웃
			Logout();
			break;
		case 4: // 영어 단어 맞추기
			game();
			getchar();
			break;
		case 5: // 회원 탈퇴
			Unsubscribe();
			break;
		case 6: // 프로그램 종료
			finish();
			if (LogStatus == 0) return 0;
			break;
		default :
			printf("잘못된 번호입니다.\n");
		}
	}
	return 0;
}

int menu(void) {
	int choice;

	printf("==============================\n");
	printf("========= 2021 SPLUG =========\n");		
	printf("==============================");
	if (LogStatus == 1) {
		for (int i = 0; i <= strlen(ID); i++)
			printf("\b");
		printf(" %s\n", ID);
	}
	else printf("\n");
	printf("=            메뉴            =\n");
	printf("==============================\n");
	printf("     1. 회원가입              \n");
	printf("     2. 로그인                \n");
	printf("     3. 로그아웃              \n");
	printf("     4. 영어 단어 맞추기      \n");
	printf("     5. 회원 탈퇴             \n");
	printf("     6. 프로그램 종료         \n");
	printf("==============================\n");
	printf(": ");
	scanf("%d", &choice);

	return choice;
}

void list_init(void) { // 연결리스트 초기화
	head = makenode();
	tail = makenode();
	head->next = tail;
	tail->next = NULL;
}

MemberInformation* makenode(void) { //노드 생성
	MemberInformation* new = (MemberInformation*)malloc(sizeof(MemberInformation));
	strcpy(new->MemberID, "");
	strcpy(new->MemberPassword, "");
	strcpy(new->MemberName, "");
	new->next = NULL;
	return new;
}

void load_file(void) { // 파일 불러오기
	FILE* fp = fopen("MemberList.txt", "rt");
	MemberInformation *newnode;
	MemberInformation* p = head;

	if (fp == NULL) {
		printf("파일을 열지 못했습니다.\n");
	}

	while (!feof(fp)) {
		newnode = makenode();
		fscanf(fp, "%s %s %s\n", newnode->MemberID, newnode->MemberPassword, newnode->MemberName);
		while (p->next != tail) p = p->next;
		newnode->next = tail;
		p->next = newnode;
	}
	fclose(fp);
}

void overlap(char input_MemberID[]) { // 아이디 중복검사
	int res, cmp = 1;
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	FILE* fp;

	fp = fopen("MemberList.txt", "r"); // 파일 로드
	if (fp == NULL) {
		printf("파일을 열지 못했습니다.\n");
	}

	while (1) { // 중복검사
		res = fscanf(fp, "%s %s %s\n", MemberID, MemberPassword, MemberName);
		while (1) {
			if (res == EOF) break;

			if (strcmp(MemberID, input_MemberID) == 0) {
				cmp = 0;
				fflush(fp);
				break;
			}
			else {
				cmp = 1;
				res = fscanf(fp, "%s %s %s\n", MemberID, MemberPassword, MemberName);

			}
		}

		if (cmp == 0) {
			printf("이미 존재하는 아이디입니다.\n\n");
			printf("아이디 : ");
			gets(input_MemberID);
			rewind(fp);
		}

		else {
			printf("사용 가능한 아이디입니다.\n");
			break;
		}

	}
	fclose(fp);
}

void SignUp(void) { // 회원가입
	MemberInformation* newnode = makenode();
	FILE* fp;

	printf("회원가입 페이지\n");
	printf("아이디 : ");
	getchar();
	gets(newnode->MemberID); // 아이디 입력
	overlap(newnode->MemberID); // 중복검사
	printf("비밀번호 : "); // 비밀번호 입력
	gets(newnode->MemberPassword);
	printf("이름 : "); // 이름 입력
	gets(newnode->MemberName);
	tail->next = newnode;
	tail = newnode;
	fp = fopen("MemberList.txt", "at"); // 파일 로드
	if (fp == NULL) {
		printf("파일을 열지 못했습니다.\n");
	}
	fprintf(fp, "%s %s %s\n", newnode->MemberID, newnode->MemberPassword, newnode->MemberName);
	fclose(fp);
	printf("회원가입 되었습니다.\n");
}

void Login(void) { // 로그인
	char Login_ID[10];
	char Login_Password[20];
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	int login = 0;
	FILE* fp;

	fp = fopen("MemberList.txt", "r"); // 파일 로드
	if (fp == NULL) {
		printf("파일을 열지 못했습니다.\n");
	}
	if (LogStatus == 0) {
		printf("로그인\n");
		printf("아이디 : ");
		getchar();
		gets(Login_ID);
		printf("비밀번호 : ");
		gets(Login_Password);

		while (1) {

			while (!feof(fp)) {
				fscanf(fp, "%s %s %s\n", MemberID, MemberPassword, MemberName);
				if ((strcmp(Login_ID, MemberID) == 0) && (strcmp(Login_Password, MemberPassword) == 0)) {
					login = 1;
					break;
				}
				else login = 0;
			}
			if (login == 1) {
				printf("로그인 성공\n\n");
				strcpy(ID, Login_ID);
				strcpy(Password, Login_Password);
				LogStatus = 1;
				break;
			}
			else {
				printf("로그인 실패\n\n");
				printf("아이디 : ");
				gets(Login_ID);
				printf("비밀번호 : ");
				gets(Login_Password);
				rewind(fp);
			}
		}
	}
	else
		printf("로그인 상태입니다.\n");
		
}

void Logout(void) { // 로그아웃
	char logout_check;
	if (LogStatus == 0) {
		printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
	}
	else {
		printf("정말 로그아웃 하시겠습니까? [y/n] :  ");
		getchar();
		scanf("%c", &logout_check);
		if (logout_check == 'y') {
			printf("로그아웃 되었습니다.\n\n");
			LogStatus = 0;
		}
		else if (logout_check == 'n');
		else
			printf("잘못된 입력입니다.\n");
	}
}

void game (void) { // 영어 단어 맞추기
	int GameStart;

	if (LogStatus == 0) {
		printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
	}
	else {
		
		printf(">> 영어 단어 맞추기 프로그램 <<\n");
		printf("1. 게임 시작  2. 프로그램 종료\n\n");
		printf("번호를 선택하세요: ");
		scanf("%d", &GameStart);
		if (GameStart == 1) {
			printf("\n☆★☆★ Game Start ! ☆★☆★\n\n");
			printf("종료하려면 \'.quit\'를 입력하세요.\n");
			sort();
			getchar();
		}
		else if (GameStart == 2);
		else
			printf("잘못된 입력입니다.\n");

	}
}

void sort (void) { // 영어 단어 정렬
	int i, j, line, score=100;
	int min;
	char answer[20];

	WordList temp, ary[WORDLIST_MAX];
	FILE* fp;

	fp = fopen("dic.txt", "r"); // 파일 로드
	if (fp == NULL) {
		printf("파일을 열지 못했습니다.\n");
	}
	for (i = 0; i < WORDLIST_MAX; i++) { // 파일 내용 배열에 저장
		if (feof(fp)) break;
		fscanf(fp, "%s %s", ary[i].word, ary[i].meaning);
		line = i+1;
	}

	for (i = 0; i < WORDLIST_MAX; i++) { // 정렬
		min = i;
		for (j = i + 1; j < WORDLIST_MAX; j++) {
			if (strcmp(ary[min].word, ary[j].word) > 0) min = j;
		}
		if (min != i) {
			temp = ary[min];
			ary[min] = ary[i];
			ary[i] = temp;
		}
	}

	for (i = 0; i <= line; i++) { // 정렬 내용 출력
		if (i == line) {
			printf("당신의 점수는 %d점 입니다.\n", score);
			break;
		}
		printf("%s -> ", ary[i].meaning);
		scanf("%s", &answer);
		if (strcmp(answer, ".quit") ==0) {
			printf("당신의 점수는 %d점 입니다.\n\n", score);
			break;
		}

		else if (strcmp(ary[i].word, answer) == 0) {
			printf("correct! (+1)\n\n");
			score += 1;
			if (score > 100) score = 100;
		}
		else {
			printf("incorrect! (-5) 정답 : %s\n\n", ary[i].word);
			score -= 5;
			if (score < 0) score = 0;
		}
	}
}

void DeleteMember(char ID[]) { // 회원삭제
	MemberInformation* temp = head->next;
	MemberInformation* p = head->next; // 삭제할 노드
	MemberInformation* pre = head; // 삭제할 노드의 앞 노드
	MemberInformation* t = head;

	FILE* fp;

	while (p != tail) {
		if (strcmp(p->MemberID, ID) == 0) break;
		p = p->next;
	}
	while (strcmp(pre->next->MemberID, p->MemberID) != 0) {
		pre = temp;
		temp = temp->next;
	}
	pre->next = p->next;
	free(p);

	fp = fopen("MemberList.txt", "wt");
	if (fp == NULL) {
		printf("파일을 열지 못했습니다.\n");
	}
	if (t != NULL) {
		while (t->next != NULL) {
			fprintf(fp, "%s %s %s\n", t->next->MemberID, t->next->MemberPassword, t->next->MemberName);
			t = t->next;
		}
	}
	fclose(fp);
}

void Unsubscribe(void) { // 회원탈퇴
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	char unsubscribe_check;

	if (LogStatus == 0) {
		printf("로그인 상태가 아닙니다.\n");
	}
	else {
		printf("정말 회원을 탈퇴하시겠습니까? [y/n] :  ");
		getchar();
		scanf("%c", &unsubscribe_check);
		if (unsubscribe_check == 'y') {
			DeleteMember(ID);
			printf("회원탈퇴 되었습니다. 감사합니다.\n");
			LogStatus = 0;
		}
		else if (unsubscribe_check == 'n');
		else
			printf("잘못된 입력입니다.\n");
	}
}

void finish(void) { // 프로그램 종료
	MemberInformation *temp;

	while (head->next) {
		temp = head->next;
		head = head->next;
	}
	free(head);

	if (LogStatus == 0) {
		system("cls");
		printf("다음에 또 만나요~!\n\n");
	}
	else {
		printf("로그아웃이 필요합니다.\n");
	}
}