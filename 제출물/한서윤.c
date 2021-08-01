#define _CRT_SECURE_NO_WARNINGS
#define WORDLIST_MAX 200

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <string.h>

typedef struct MemberInformation { //ȸ������ ����ü
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	struct MemberInformation* next;
} MemberInformation;

typedef struct WordList { // ����ܾ��� ����ü
	char word[20];
	char meaning[10];
} WordList;

// �Լ� ����
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

//��������
int LogStatus = 0;
char ID[10];
char Password[20];
char Name[30];
MemberInformation* head;
MemberInformation* tail;


int main(void) {
	FILE* fp = fopen("MemberList.txt", "at");
	if (fp == NULL) {
		printf("������ ���� ���߽��ϴ�.\n");
	}
	fclose(fp);
	int select;
	list_init(); // ���Ḯ��Ʈ �ʱ�ȭ
	load_file(); // ���� �ҷ�����

	while (1) {
		select = menu(); // �޴� ȭ��
		switch (select) {
		case 1 : // ȸ������
			SignUp();
			break;
		case 2 : // �α���
			Login();
			break;
		case 3 : // �α׾ƿ�
			Logout();
			break;
		case 4: // ���� �ܾ� ���߱�
			game();
			getchar();
			break;
		case 5: // ȸ�� Ż��
			Unsubscribe();
			break;
		case 6: // ���α׷� ����
			finish();
			if (LogStatus == 0) return 0;
			break;
		default :
			printf("�߸��� ��ȣ�Դϴ�.\n");
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
	printf("=            �޴�            =\n");
	printf("==============================\n");
	printf("     1. ȸ������              \n");
	printf("     2. �α���                \n");
	printf("     3. �α׾ƿ�              \n");
	printf("     4. ���� �ܾ� ���߱�      \n");
	printf("     5. ȸ�� Ż��             \n");
	printf("     6. ���α׷� ����         \n");
	printf("==============================\n");
	printf(": ");
	scanf("%d", &choice);

	return choice;
}

void list_init(void) { // ���Ḯ��Ʈ �ʱ�ȭ
	head = makenode();
	tail = makenode();
	head->next = tail;
	tail->next = NULL;
}

MemberInformation* makenode(void) { //��� ����
	MemberInformation* new = (MemberInformation*)malloc(sizeof(MemberInformation));
	strcpy(new->MemberID, "");
	strcpy(new->MemberPassword, "");
	strcpy(new->MemberName, "");
	new->next = NULL;
	return new;
}

void load_file(void) { // ���� �ҷ�����
	FILE* fp = fopen("MemberList.txt", "rt");
	MemberInformation *newnode;
	MemberInformation* p = head;

	if (fp == NULL) {
		printf("������ ���� ���߽��ϴ�.\n");
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

void overlap(char input_MemberID[]) { // ���̵� �ߺ��˻�
	int res, cmp = 1;
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	FILE* fp;

	fp = fopen("MemberList.txt", "r"); // ���� �ε�
	if (fp == NULL) {
		printf("������ ���� ���߽��ϴ�.\n");
	}

	while (1) { // �ߺ��˻�
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
			printf("�̹� �����ϴ� ���̵��Դϴ�.\n\n");
			printf("���̵� : ");
			gets(input_MemberID);
			rewind(fp);
		}

		else {
			printf("��� ������ ���̵��Դϴ�.\n");
			break;
		}

	}
	fclose(fp);
}

void SignUp(void) { // ȸ������
	MemberInformation* newnode = makenode();
	FILE* fp;

	printf("ȸ������ ������\n");
	printf("���̵� : ");
	getchar();
	gets(newnode->MemberID); // ���̵� �Է�
	overlap(newnode->MemberID); // �ߺ��˻�
	printf("��й�ȣ : "); // ��й�ȣ �Է�
	gets(newnode->MemberPassword);
	printf("�̸� : "); // �̸� �Է�
	gets(newnode->MemberName);
	tail->next = newnode;
	tail = newnode;
	fp = fopen("MemberList.txt", "at"); // ���� �ε�
	if (fp == NULL) {
		printf("������ ���� ���߽��ϴ�.\n");
	}
	fprintf(fp, "%s %s %s\n", newnode->MemberID, newnode->MemberPassword, newnode->MemberName);
	fclose(fp);
	printf("ȸ������ �Ǿ����ϴ�.\n");
}

void Login(void) { // �α���
	char Login_ID[10];
	char Login_Password[20];
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	int login = 0;
	FILE* fp;

	fp = fopen("MemberList.txt", "r"); // ���� �ε�
	if (fp == NULL) {
		printf("������ ���� ���߽��ϴ�.\n");
	}
	if (LogStatus == 0) {
		printf("�α���\n");
		printf("���̵� : ");
		getchar();
		gets(Login_ID);
		printf("��й�ȣ : ");
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
				printf("�α��� ����\n\n");
				strcpy(ID, Login_ID);
				strcpy(Password, Login_Password);
				LogStatus = 1;
				break;
			}
			else {
				printf("�α��� ����\n\n");
				printf("���̵� : ");
				gets(Login_ID);
				printf("��й�ȣ : ");
				gets(Login_Password);
				rewind(fp);
			}
		}
	}
	else
		printf("�α��� �����Դϴ�.\n");
		
}

void Logout(void) { // �α׾ƿ�
	char logout_check;
	if (LogStatus == 0) {
		printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.\n");
	}
	else {
		printf("���� �α׾ƿ� �Ͻðڽ��ϱ�? [y/n] :  ");
		getchar();
		scanf("%c", &logout_check);
		if (logout_check == 'y') {
			printf("�α׾ƿ� �Ǿ����ϴ�.\n\n");
			LogStatus = 0;
		}
		else if (logout_check == 'n');
		else
			printf("�߸��� �Է��Դϴ�.\n");
	}
}

void game (void) { // ���� �ܾ� ���߱�
	int GameStart;

	if (LogStatus == 0) {
		printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.\n");
	}
	else {
		
		printf(">> ���� �ܾ� ���߱� ���α׷� <<\n");
		printf("1. ���� ����  2. ���α׷� ����\n\n");
		printf("��ȣ�� �����ϼ���: ");
		scanf("%d", &GameStart);
		if (GameStart == 1) {
			printf("\n�١ڡ١� Game Start ! �١ڡ١�\n\n");
			printf("�����Ϸ��� \'.quit\'�� �Է��ϼ���.\n");
			sort();
			getchar();
		}
		else if (GameStart == 2);
		else
			printf("�߸��� �Է��Դϴ�.\n");

	}
}

void sort (void) { // ���� �ܾ� ����
	int i, j, line, score=100;
	int min;
	char answer[20];

	WordList temp, ary[WORDLIST_MAX];
	FILE* fp;

	fp = fopen("dic.txt", "r"); // ���� �ε�
	if (fp == NULL) {
		printf("������ ���� ���߽��ϴ�.\n");
	}
	for (i = 0; i < WORDLIST_MAX; i++) { // ���� ���� �迭�� ����
		if (feof(fp)) break;
		fscanf(fp, "%s %s", ary[i].word, ary[i].meaning);
		line = i+1;
	}

	for (i = 0; i < WORDLIST_MAX; i++) { // ����
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

	for (i = 0; i <= line; i++) { // ���� ���� ���
		if (i == line) {
			printf("����� ������ %d�� �Դϴ�.\n", score);
			break;
		}
		printf("%s -> ", ary[i].meaning);
		scanf("%s", &answer);
		if (strcmp(answer, ".quit") ==0) {
			printf("����� ������ %d�� �Դϴ�.\n\n", score);
			break;
		}

		else if (strcmp(ary[i].word, answer) == 0) {
			printf("correct! (+1)\n\n");
			score += 1;
			if (score > 100) score = 100;
		}
		else {
			printf("incorrect! (-5) ���� : %s\n\n", ary[i].word);
			score -= 5;
			if (score < 0) score = 0;
		}
	}
}

void DeleteMember(char ID[]) { // ȸ������
	MemberInformation* temp = head->next;
	MemberInformation* p = head->next; // ������ ���
	MemberInformation* pre = head; // ������ ����� �� ���
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
		printf("������ ���� ���߽��ϴ�.\n");
	}
	if (t != NULL) {
		while (t->next != NULL) {
			fprintf(fp, "%s %s %s\n", t->next->MemberID, t->next->MemberPassword, t->next->MemberName);
			t = t->next;
		}
	}
	fclose(fp);
}

void Unsubscribe(void) { // ȸ��Ż��
	char MemberID[10];
	char MemberPassword[20];
	char MemberName[30];
	char unsubscribe_check;

	if (LogStatus == 0) {
		printf("�α��� ���°� �ƴմϴ�.\n");
	}
	else {
		printf("���� ȸ���� Ż���Ͻðڽ��ϱ�? [y/n] :  ");
		getchar();
		scanf("%c", &unsubscribe_check);
		if (unsubscribe_check == 'y') {
			DeleteMember(ID);
			printf("ȸ��Ż�� �Ǿ����ϴ�. �����մϴ�.\n");
			LogStatus = 0;
		}
		else if (unsubscribe_check == 'n');
		else
			printf("�߸��� �Է��Դϴ�.\n");
	}
}

void finish(void) { // ���α׷� ����
	MemberInformation *temp;

	while (head->next) {
		temp = head->next;
		head = head->next;
	}
	free(head);

	if (LogStatus == 0) {
		system("cls");
		printf("������ �� ������~!\n\n");
	}
	else {
		printf("�α׾ƿ��� �ʿ��մϴ�.\n");
	}
}