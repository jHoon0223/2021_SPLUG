#include "header.h"

User *makeUserNode(char *id, char *password, char *name){
	User *node = (User *)malloc(sizeof(User));
	strcpy(node->id, id);
	strcpy(node->password, password);
	strcpy(node->name, name);
	node->next = NULL;
	
	return node;
}


UserStatus * makeUserStatus(){
	UserStatus * sta = (UserStatus *)malloc(sizeof(UserStatus));
	sta->num=0;
	sta->head = sta->cur = sta->temp = NULL;

	return sta;
}

UserStatus*  InitUser(UserStatus *sta){
	int recordNum = GetUserRecordNum("user.txt");
	sta = InputUserInfo(sta, recordNum);

	return sta;
}

int GetUserRecordNum(char *filename){
	FILE *fp;
	int count=0;
	int filesize=0;

	if((fp=fopen(filename, "r+"))==NULL) return 0;


	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	count = filesize/sizeof(User);
	fclose(fp);
	return count;
}

UserStatus* AddUserNode(UserStatus *sta, User *node){

	
	if(!sta->num){
		sta->head = sta->cur = node;
		node->next = NULL;
	}else{
		node->next = NULL;
		sta->cur->next = node;
		sta->cur = sta->cur->next;
	}
	sta->num++;

	sleep(3);
	
	return sta;
}

UserStatus* InputUserInfo(UserStatus *sta, int userCount){
	FILE *fp;
	User *node;
	User tmp;
	int i;

	memset(&tmp, 0, sizeof(User));
	if(userCount == 0){
		return NULL;
	}else{
		fp = fopen("user.txt","r+");
		for(i=0; i<userCount; i++){
			fread(&tmp, sizeof(User), 1, fp);
			if(tmp.id[0]==0){
				continue;
			}
			node = makeUserNode(tmp.id, tmp.password, tmp.name);
			AddUserNode(sta, node);			
		}
	}
	fclose(fp);

	return sta;
}

User* FindUser(UserStatus *sta, char *id){
	User *find;

	if(sta->head==NULL) return NULL;


	find = sta->head;
	while(find!=NULL){
		if(!strcmp(find->id, id)){
			 return find;
		}
		find = find->next;
	}

	return NULL;
}

int FindUserIdx(UserStatus *sta, char *id){
	if(sta->num==0) return -1;

	User *find;
	find = sta->head;
	int num=0;

	if(!strcmp(find->id, id)) return num;
	
	while(find->next != NULL){
		if(!strcmp(find->id, id)) return num;
		num++;
		find = find->next;
	}

	return -2;
}



void Register(UserStatus *sta){
	User *tmp = (User *)malloc(sizeof(User));
	char tmp_id[15];
	char tmp_password[20];
	char tmp_name[10];

	memset(tmp_id, 0, 15);
	memset(tmp_password, 0, 20);
	memset(tmp_name, 0, 10);

	printf("회원가입 페이지\n");

	while(1){
		printf("아이디 : ");
		scanf("%s",tmp_id);

		if(sta==NULL) break;
		getchar();

		int idx = FindUserIdx(sta, tmp_id);
		
		if(idx==-1){
			break;
		}else if(idx>=0){
			printf("이미 존재하는 아이디 입니다.\n");
			memset(tmp_id, 0, 15);
			continue;
		}else if(idx==-2){
			break;
		}
		
	}
	
	printf("비밀번호 : ");
	scanf("%s",tmp_password);
	getchar();

	printf("이름 : ");
	scanf("%s", tmp_name);
	getchar();

	User *node = makeUserNode(tmp_id, tmp_password, tmp_name);
	FILE* fp1 = fopen("user.txt", "r+");
	int a=0;
	
	if(!GetUserRecordNum("user.txt")){
		fseek(fp1, 0, SEEK_SET);
	}else{
		fseek(fp1, sizeof(User)*sta->num, SEEK_SET);
	}
	fwrite(node, sizeof(User), 1, fp1);
	fclose(fp1);

	sta = AddUserNode(sta, node);


	printf("\n회원가입 완료\n\n");
	return ;
}

void LoginUser(UserStatus *sta){
	User *user;
	char id[15];
	char password[20];

	memset(id, 0, 15);
	memset(password, 0, 20);

	system("clear");
	printf("로그인\n");

	loginStatus=1;
	
	while(1){
		printf("아이디 : ");
		scanf("%s",id);
		if(sta->num!=0){
			user = FindUser(sta, id);
			if(user != NULL){
				break;
			}
			memset(id, 0, 20);
			printf("잘못된 아이디!\n");
		}else{
			break;
		}
	}
	strcpy(nowId, id);

	while(1){
		printf("비밀번호 : ");
		scanf("%s", password);
		if(!strcmp(password, user->password)){
			break;
		}
		memset(password, 0, 20);
		printf("잘못된 비밀번호!\n\n");
	}

	return ;
}

void LogoutUser(){
	char input;
	if(loginStatus==0){
		printf("로그인 상태가 아닙니다\n");
		sleep(2);
	}	
	printf("정말 로그아웃 하시겠습니까? [Y/N]: ");
	scanf("%c",&input);
	
	if(input=='y' || input== 'Y'){
		memset(nowId, 0, 15);
		return ;
	}else{
		return ;
	}
}
void DeleteUserNode(UserStatus *sta, char *id){
	User *cur = sta->head;
	while(cur->next){
		if(!strcmp(nowId, cur->next->id)) break;
		cur = cur->next;
	}
	User *tmp = cur->next;
	cur->next = tmp->next;
	free(tmp);
	loginStatus = 0;

}

void Withdrawal(UserStatus *sta){
	if(loginStatus==0){
		printf("로그인 되어있지 않습니다!\n\n");
		sleep(1);
		return ;
	}

	FILE *fp;
	char check[10];
	User tmp;
	memset(check, 0, 10);

	int i, idx;
	printf("정말 회원을 탈퇴하시겠습니까? [y/n] : ");
	scanf("%s",check);
	getchar();

	if(strcmp(check,"y")!=0){
		printf("취소\n");
	}else{
		fp = fopen("user.txt","r+");
		for(i=0; i<sta->num; i++){
			memset(&tmp, 0, sizeof(User));
			fread(&tmp, sizeof(User), 1, fp);
			if(!strcmp(tmp.id,nowId)){
				break;
			}
		}
		
		
		idx = i;
		memset(&tmp, 0, sizeof(User));
		fseek(fp, sizeof(User)*idx, SEEK_SET);
		
		for(i=idx; i<sta->num; i++){
			fwrite(&tmp, sizeof(User), 1, fp);
			fread(&tmp, sizeof(User), 1, fp);
			fseek(fp, sizeof(User)*i, SEEK_SET);
			fwrite(&tmp, sizeof(User), 1, fp);
			memset(&tmp, 0, sizeof(User));
		}

		fseek(fp, sizeof(User)*sta->num, SEEK_SET);
		fwrite(&tmp, sizeof(User), 1, fp);
		printf("%s는 탈퇴처리 되었습니다\n",nowId);
		fclose(fp);
		DeleteUserNode(sta, nowId);
		memset(nowId, 0, 15);

		return ;
	}
}


	


