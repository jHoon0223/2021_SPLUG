/*
2021. 07. 09
SPLUG 정회원 심사 프로젝트
20212895 컴퓨터학부 김황조
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h> // sleep 

typedef struct user{
	char user_id[30];
	char user_pw[30];
	char user_name[10];
	struct user *ac_next;
	struct user *ac_prev;
}user;


typedef struct word{
	char eng_word[20];
	char kor_word[20];
	struct word *wd_next;
	struct word *wd_prev;
}word;

user *ac_head, *ac_tail;
word *wd_head, *wd_tail;


void linked_preset(void);    //연결리스트 기초 세팅 로딩
void load_info(void);        //ID정보 있는 파일 읽고, 연결리스트에 저장
void viewmain(int,char *);   //메인화면 뷰어
int input_valid(int);        //입력값의 유효성 판단
void user_register(void);    //회원가입
int overlap_chk(char *);     //ID 중복체크기
int user_login(int,char *);  //로그인
int user_logout(int);        //로그아웃
void user_edit(int, char *); //회원 정보 변경
void user_del(int *,char *); //회원 탈퇴
void info_rewrite(void);     //탈퇴&정보변경시 파일에도 기록
void game_load(void);        //단어게임 로드
void word_game(void);        // 게임 셋업 
void word_sorting(void);     //파일에서 단어 읽고, 정렬하여 연결리스트에 저장
int node_counter(void);      // 노드의 갯수(단어의 수) 카운터
void swap_nodes(word *node1,word *node2); //노드 자리바꾸기 
void game_run(void);         //게임 진행
void end(void);              //종료

int main (void){
	int loginchk = 0;
	int select= -1;
	char myid[30];
	linked_preset();
	load_info();
	while (1){
		viewmain(loginchk,myid);
		scanf("%d", &select);
		if (input_valid(select)) continue;
		switch (select)
		{
			case 1:
				user_register();
				break;
			case 2:
				loginchk = user_login(loginchk,myid);
				break;
			case 3:
				loginchk = user_logout(loginchk);
				break;
			case 4:
				user_edit(loginchk,myid);
				break;
			case 5:
				word_game();
				break;
			case 6:
				user_del(&loginchk,myid);
				break;
			case 7:
				end();
				break;
		}
	}
	return 0;
}

void linked_preset(void){
	ac_head= (user *)malloc(sizeof(user));
	ac_tail= (user *)malloc(sizeof(user));
	wd_head= (word *)malloc(sizeof(word));
	wd_tail= (word *)malloc(sizeof(word));
	ac_head->ac_next = ac_tail;
	ac_tail->ac_prev = ac_head;
	ac_head->ac_prev = ac_tail->ac_next = NULL;
	wd_head->wd_next = wd_tail;
	wd_tail->wd_prev = wd_head;
	wd_head->wd_prev = wd_tail->wd_next = NULL;
	return ;
}

void load_info(void){

	FILE* fp = fopen("account.txt", "a+");
	while (1){
		user *player = 0;
		player= (user *)malloc(sizeof(user));
		fscanf(fp, "%s %s %s",  player->user_id, player->user_pw,player->user_name);
		if (feof(fp) != 0) break;
		player->ac_next = ac_tail;
		player->ac_prev = ac_tail->ac_prev;
		ac_tail->ac_prev->ac_next = player;
		ac_tail->ac_prev = player;
	}
	fclose(fp);
	return ;
}

void viewmain(int loginchk,char myid[30]){
	system("clear");
	printf("==============================\n");
	printf("========== 2021 SPLUG ========\n");
	if (loginchk==0)
		printf("==============================\n");
	else {
		for(int i=0;i<(30-strlen(myid));i++)
			printf("=");
		printf("%s\n",myid);
	}	
	printf("==============================\n");
	printf("=            메뉴            =\n");
	printf("==============================\n");
	printf("        1.회원가입           \n");
	printf("        2.로그인          \n");
	printf("        3.로그아웃          \n");
	printf("        4.회원 정보 변경          \n");
	printf("        5.영어 단어 맞추기           \n");
	printf("        6.회원탈퇴          \n");
	printf("        7.프로그램 종료           \n");
	printf("==============================\n");
	printf(" 입력 : ");
	return ;
}

int input_valid(int select){
	if (select < 1 || select > 7){
		printf("잘못된 입력입니다. \n");
		while(getchar() != '\n');
		sleep(2);
		return 1;
	}
	return 0;
}

void user_register(void){
	char tmp_id[30];
	user *player = 0;
	player= (user *)malloc(sizeof(user));
	printf("사용할 아이디를 입력하세요 : ");
	scanf("%s",tmp_id);
	if (overlap_chk(tmp_id)){
		printf("중복된 아이디입니다!\n");
		sleep(2);
		return ;
	}
	strcpy(player->user_id,tmp_id);
	printf("사용할 비밀번호를 입력하세요 : ");
	scanf("%s",player->user_pw);
	printf("사용자의 이름을 입력하세요 : ");
	scanf("%s",player->user_name);
	player->ac_next = ac_tail;
	player->ac_prev = ac_tail->ac_prev;
	ac_tail->ac_prev->ac_next = player;
	ac_tail->ac_prev = player;
	FILE* fp = fopen("account.txt", "a");
	fprintf(fp, "%s %s %s\n", player->user_id, player->user_pw,player->user_name);
	fclose(fp);
	printf("정상적으로 가입되었습니다.\n");
	sleep(2);
	return ;
}

int overlap_chk(char tmp_id[30]){
	user *find = 0;
	for (find=ac_head->ac_next;find!=ac_tail;find=find->ac_next){
		if (strcmp(find->user_id,tmp_id) == 0)
			return 1;
	}
	return 0;
}
int user_login(int loginchk,char myid[30]){
	char temp_id[30];
	char temp_pw[30];
	int wrong_pw;
	user *find = 0;
	if (loginchk == 1){
		printf("이미 로그인되어있습니다.\n");
		sleep(2);
		return 1;
	}
	printf("아이디를 입력하세요 : ");
	scanf("%s", temp_id);
	printf("비밀번호를 입력하세요 : ");
	scanf("%s", temp_pw);
	for (find=ac_head->ac_next;find!=ac_tail;find=find->ac_next){
		if (strcmp(find->user_id,temp_id) == 0 && strcmp(find->user_pw,temp_pw) == 0){
			strcpy(myid,temp_id);
			printf("%s님, 환영합니다.\n",find->user_name);
			sleep(2);
			return 1;
		}
		else if (strcmp(find->user_id,temp_id) == 0 && strcmp(find->user_pw,temp_pw) != 0) {
			printf("비밀번호가 틀립니다. \n");
			sleep(2);
			return 0;
		}
	}
	printf("해당하는 아이디가 없습니다 ! \n");
	sleep(2);
	return 0;
}


int user_logout(int loginchk){
	char select;
	while(getchar() != '\n');
	if (loginchk == 0){
		printf("로그인하지 않았습니다.\n");
		sleep(2);
		return 0;
	}
	else{
		printf("정말 로그아웃 하시겠습니까? [y/n]: ");
		scanf("%c", &select);
		while(getchar() != '\n'); 
		if (select==121 || select == 89)
			return 0;
		else
			return 1;
	}
}

void user_edit(int loginchk, char myid[30]){
	char temp_pw[20];
	char temp_pocket[20];
	while(getchar() != '\n');
	if (loginchk == 0){
		printf("로그인하지 않았습니다!\n");
		sleep(2);
		return ;
	}
	system("clear");
	printf("보안을 위해 현재 비밀번호를 다시 입력해주세요. : ");
	scanf("%s",temp_pw);
	user *find =0;
	for (find=ac_head->ac_next;find!=ac_tail;find=find->ac_next){
		if (strcmp(find->user_id,myid) == 0){
			if(strcmp(find->user_pw,temp_pw)==0){
				system("clear");
				printf("===변경할 정보를 선택해주세요===\n");
				printf(" 1.아이디 2.비밀번호 3.이름\n입력 : ");
				int select;
				scanf("%d", &select);
				switch (select){
					case 1:
						while(getchar() != '\n');
						printf("현재 아이디 : %s\n",find->user_id);
						printf("변경할 아이디를 입력해주세요 : ");
						scanf("%s",temp_pocket);
						strcpy(find->user_id,temp_pocket);
						strcpy(myid,temp_pocket);
						printf("성공적으로 변경되었습니다.\n");
						info_rewrite();
						sleep(2);
						break;
					case 2:
						while(getchar() != '\n');
						printf("현재 비밀번호 : %s\n",find->user_pw);
						printf("변경할 비밀번호를 입력해주세요 : ");
						scanf("%s",temp_pocket);
						strcpy(find->user_pw,temp_pocket);
						printf("성공적으로 변경되었습니다.\n");
						info_rewrite();
						sleep(2);
						break;
					case 3:
						while(getchar() != '\n');
						printf("현재 이름 : %s\n",find->user_name);
						printf("변경할 이름을 입력해주세요 : ");
						scanf("%s",temp_pocket);
						strcpy(find->user_name,temp_pocket);
						printf("성공적으로 변경되었습니다.\n");
						info_rewrite();
						sleep(2);
						break;
				}
			}
			else{
				printf("비밀번호가 틀렸습니다! \n");
				sleep(2);
				return ;
			}
		}
	}
}

void user_del(int *loginchk,char myid[30]){
	user *find = 0;
	char select;
	while(getchar() != '\n');
	if (*loginchk ==0){
		printf("로그인 상태가 아닙니다.\n");
		sleep(2);
		return ;
	}
	else {
		printf("정말 회원탈퇴 하시겠습니까? [y/n] : ");
		scanf("%c", &select);

		if (select==121 || select == 89)
		{
			for (find=ac_head->ac_next;find!=ac_tail;find=find->ac_next){
				if (strcmp(find->user_id,myid) == 0){
					find->ac_prev->ac_next = find->ac_next;
					find->ac_next->ac_prev = find->ac_prev;
					info_rewrite();
					*loginchk = 0;
					printf("정상적으로 탈퇴되었습니다.\n");
					sleep(2);
					return ;
				}
			}
		}
	}
}

void info_rewrite(void){
	user *rewrite = 0;
	while(getchar() != '\n'); 
	FILE* fp = fopen("account.txt", "w");
	for (rewrite=ac_head->ac_next;rewrite!=ac_tail;rewrite=rewrite->ac_next)
	{

		fprintf(fp, "%s %s %s\n", rewrite->user_id, rewrite->user_pw,rewrite->user_name);
	}
	fclose(fp);
	return ;

}
void game_load(void){
	FILE* fp = fopen("dic.txt", "r");
	while (1){
		word *finder = 0;
		finder= (word *)malloc(sizeof(word));
		fscanf(fp, "%s %s",  finder->eng_word, finder->kor_word);
		if (feof(fp) != 0) 
			break;
		finder->wd_next = wd_tail;
		finder->wd_prev = wd_tail->wd_prev;
		wd_tail->wd_prev->wd_next = finder;
		wd_tail->wd_prev = finder;
	}
	fclose(fp);
	return ;
}
void word_game(void){
	int select = 1;
	system("clear");
	while(getchar() != '\n');
	printf(">>>영어 단어 맞추기 프로그램<<<\n");
	printf("1. 영어 단어 맞추기 / 2. 프로그램 종료\n\n");
	printf("입력 : ");
	scanf("%d", &select);
	if (select == 2)
		end();
	game_load();
	word_sorting();
	game_run();
	return ;
}

void word_sorting(void){
	word *sort = 0;
	sort = (word *)malloc(sizeof(word));
	int count = node_counter();
	//버블소트 사용
	sort = wd_head->wd_next;
	for(int i=0; i<count; i++){
		for(int j=0; j < count- 1 -i ; j++){
			if (strcmp(sort->eng_word,sort->wd_next->eng_word)>0){
				swap_nodes(sort,sort->wd_next);
			}
			sort = sort->wd_next;
		}
		sort = wd_head->wd_next;
	}
	return ;
}

void game_run(void){
	char answer[20];
	int score=0;
	word *game = 0;
	for (game=wd_head->wd_next;game!=wd_tail;game=game->wd_next){
		printf("%s ---> ",game->eng_word);
		scanf("%s", answer);
		getchar();
		if(strcmp(answer,".quit")==0){
			printf("당신의 점수는 %d점 입니다.\n",score);
			printf("종료합니다.\n");
			sleep(3);
			return ;
		}

		if (strcmp(game->kor_word,answer) == 0){
			printf("correct!\n");
			score+=5;
		}
		else
			printf("incorrect!\n");
	}
	printf("당신의 점수는 %d점 입니다.\n",score);
	sleep(3);
	return ;
}

void swap_nodes(word *node1,word *node2){
	char temp[20];
	strcpy(temp,node2->eng_word);
	strcpy(node2->eng_word,node1->eng_word);
	strcpy(node1->eng_word,temp);
	strcpy(temp,node2->kor_word);
	strcpy(node2->kor_word,node1->kor_word);
	strcpy(node1->kor_word,temp);
}

int node_counter(void){
	word *counter = 0;
	int tmp = 0;
	for(counter=wd_head->wd_next;counter!=wd_tail;counter=counter->wd_next) tmp++;
	return tmp;
}

void end(void){
	system("clear");
	printf("다음에 또 만나요.\n");
	free(ac_head);
	free(ac_tail);
	free(wd_head);
	free(wd_tail);
	exit(0);
}
