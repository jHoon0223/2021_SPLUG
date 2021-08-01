#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct member {//연결리스트의 노드 구조체
	char id[10];
	char password[10];
	char name[10];
	struct member* next;//다음 노드의 주소를 저장할 포인터
}member;

member* info = NULL; //첫번째 노드. 현재 입력받는 노드.
member* now = NULL; //현재 로그인한 member 노드. 로그인 여부 확인 가능.

member* makenode() {
	member* tmp = (member*)malloc(sizeof(member));//알맞는 공간 생성
	tmp->next = NULL;
	return tmp;
}

void menu_init() {
	printf("==============================\n");
	printf("==========2021 SPLUG==========\n");
	if (now != NULL) { //로그인 여부 확인. true일시 오른쪽에 아이디 호출.
		printf("======================%s\n", now->id);
	}
	else {
		printf("==============================\n");
	}
	printf("==============================\n");
	printf("=             메뉴           =\n");
	printf("==============================\n");
	printf("\t1. 회원가입\n");
	printf("\t2. 로그인\n");
	printf("\t3. 로그아웃\n");
	printf("\t4. 영어 단어 맞추기\n");
	printf("\t5. 회원 탈퇴\n");
	printf("\t6. 프로그램 종료\n");
	printf("==============================\n");
	printf(":");
}
void saveMemberinfo() {//프로그램 종료시 Member_list_test.txt에 새로운 값들을 저장해주는 함수.
	FILE* save = fopen("Member_list_test.txt", "wt");
	if (info != NULL) {
		while (info->next != NULL) {
			member* al = info;
			fprintf(save, "%s %s %s\n", al->id, al->password, al->name);
			info = info->next;
		}
		fprintf(save, "%s %s %s", info->id, info->password, info->name);
		free(info);
	}
}
void saveMemberinfo_test(member * head) {//Member_list_test.txt에 새로운 값들을 저장해주는 함수.
	FILE* save = fopen("Member_list_test.txt", "a");
	fprintf(save, "%s %s %s\n", head->id, head->password, head->name);
	free(head);
}
void AddMember_test(char Memberid[], char Memberpassword[], char Membername[]) {
	member * head = makenode();
	strcpy(head->id, Memberid);
	strcpy(head->password, Memberpassword);
	strcpy(head->name, Membername);
	
	if(info == NULL){
		info = head;
	}else{
		member * temp =info;
		while(temp->next != NULL){
			temp=temp->next;
		}
		temp->next = head;
	}
	saveMemberinfo_test(head);
}
bool idoverlap(char id[10]) { //중복하는 아이디가 있는지 확인.
	member* test = info;
	if (test == NULL)
		return false;
	while (test->next != NULL) { 
		if (!strcmp(id, test->id)) {
			return true;
		}
		else {
			test = test->next;
		}
	}
	return false;
}
void join() { //회원가입
	printf("# 회원가입 페이지 #\n");
	while (1) {
		member* tmp = NULL;
		char id[10];
		char password[10];
		char name[10];
		while (1) {
			//아이디 입력
			printf("아이디 : ");
			scanf("%s", id);
			if (idoverlap(id)) {
				printf("이미 존재하는 아이디입니다.\n");
			}
			else {
				printf("사용 가능한 아이디 입니다.\n");
				break;
			}
		}
		//비밀번호 입력
		printf("비밀번호 : ");
		scanf("%s", password);
		//이름 입력
		printf("이름 : ");
		scanf("%s", name);

		//회원정보 확인.
		printf("\n=========입력 정보확인========\n");
		printf("아이디 : %s\n", id);
		printf("비밀번호 : %s\n", password);
		printf("이름 : %s\n:", name);
		printf("입력하신정보가 맞습니까? (Y/N)\n");

		char inputIsCorrect[10];
		scanf("%s", inputIsCorrect);
		if (!strcmp(inputIsCorrect, "Y") || !strcmp(inputIsCorrect, "y")) {//입력한 정보 맞을시.
			AddMember_test(id, password, name);
			break;
		}
		printf("\n=============재입력============\n");
	}
}

void login() {//로그인
	bool loginSuccess = false;
	if(now != NULL){
		printf("이미 로그인 상태입니다.\n");
	}else{
		char inputID[10];
		char inputPW[10];
		printf("id : ");
		scanf("%s",inputID);
		printf("PW : ");
		scanf("%s", inputPW);
		
		member * temp = info;
		while(temp->next != NULL){
			if(strcmp(inputID,temp->id)==0){
				if(strcmp(inputPW,temp->password)==0){
					loginSuccess=true;
				}
				break;
			}
			temp=temp->next;
		}
		if(loginSuccess){
			now = temp;
			printf("로그인에 성공했습니다.\n");
		}else{
			printf("아이디 또는 비밀번호를 다시 입력하세요.\n");
		}
	}
}
void logout() {//로그아웃
	if (now != NULL) {//로그인된 상태
		now = NULL;
		printf("로그아웃 되었습니다.\n");
	}
	else {	//로그인 되지 않은 상태
		printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
	}
}
void saveMemberinfo_delete_test() {//회원탈퇴시 필요한 파일 수정.
	FILE* save = fopen("Member_list_test.txt", "wt");
	if (info != NULL) {
		member * delete = info;
		while (delete->next != NULL) {
			member* al = delete;
			fprintf(save, "%s %s %s\n", al->id, al->password, al->name);
			delete = delete->next;
		}
		fprintf(save, "%s %s %s", delete->id, delete->password, delete->name);
		free(delete);
	}
}
void deleteMember(){	//회원탈퇴.
	int i;
	member * temp;
	member * prev;
	temp = info;
	if(strcmp(temp->id,now->id)==0){
		info = temp->next;
		free(temp);
	}
	else{
		for(i=0;strcmp(temp->id, now->id)!=0;++i){
			temp = temp->next;
			if(i != 0){
				prev = prev->next;
			}if(i==1){
				prev=info;
			}
		}
		prev->next=temp->next;
		free(temp);
	}
	saveMemberinfo_delete_test();//한줄 사라진 파일로 바꿔치기.
	now=NULL;
}
void memberListLoad() {//Member_list_test.txt 파일에서 정보를 불러오는 함수
	FILE* load = fopen("Member_list_test.txt", "rt");
	if (load != NULL) {
		member* MidNode = NULL;
		int loadfp;
		while (feof(load) == 0) {
			MidNode = (member*)malloc(sizeof(member));
			MidNode->next = NULL;
			fscanf(load, "%s %s %s\n", MidNode->id, MidNode->password, MidNode->name);
			if (info == NULL) {
				info = MidNode;
			}
			else {
				member* temp = info;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = MidNode;
			}
		}
	}
}

void EnglishTest(){//영어맞추기 프로그램
	char inputTxt [20];
	printf("공사중.");
}

int main() {
	memberListLoad();	//회원정보 불러오기.
	while (1) {
		//struct member info[100];
		int menu;

		menu_init();
		scanf("%d", &menu);

		if (menu == 1) {//회원가입
			join();
		}
		else if (menu == 2) {//로그인
			login();
		}
		else if (menu == 3) {//로그아웃
			logout();
		}
		else if (menu == 4) {//영어 단어 맞추기
			if (now != NULL) {//로그인한 상태
				int num;
				printf(">>영어 단어 맞추기 프로그램<<\n");
				printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");
				printf("번호를 선택하세요 : ");
				scanf("%d", &num);
				if(num==1){
					EnglishTest();
				}else if(num==2){
					printf("영어 단어 맞추기 프로그램을 종료합니다.\n");
					continue;
				}
			}
			else {	//로그인 되지 않은 상태
				printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
			}
		}
		else if (menu == 5) {//회원 탈퇴
			printf("정말 회원을 탈퇴하시겠습니까? [y/n] : ");
			char memberDelete[10];
			scanf("%s", memberDelete);
			if (!strcmp(memberDelete, "Y") || !strcmp(memberDelete, "y")) {
				if(now != NULL){
					deleteMember();
					printf("회원탈퇴되었습니다.\n");
				}else{
					printf("로그인 상태가 아닙니다.\n");
				}
			}
		}
		else if (menu == 6) {//프로그램 종료
			saveMemberinfo();
			break;
		}
		else {
			printf("입력이 잘못되었습니다.\n");
		}
		printf("\n");
	}
	return 0;
}
