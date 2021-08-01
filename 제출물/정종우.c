#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termio.h>
#include<time.h>
#include<unistd.h>
#define Enword 16
#define Koword 31

typedef struct Word{
   char En_word[Enword];
   char Ko_word[Koword];
   struct Word *next;
}Word;

typedef struct WordStatus{
   int num;
   Word *head;
   Word *cur;
   Word *temp;
}WordStatus;

typedef struct User{
   char id[15];
   char password[20];
   char name[10];
   struct User *next;
}User;

typedef struct UserStatus{
   int num;
   User *head;
   User *cur;
   User *temp;
}UserStatus;



//영어 단어 맞추기
Word* makeWordNode();
WordStatus* makeWordStatus();
void Sorting(WordStatus *sta);
void Eng_test(WordStatus *sta);
void menu(WordStatus *sta);
void Eng_test(WordStatus *sta);
WordStatus* InitWord(WordStatus *sta);

//로그인, 회원 가입 구현
User *MakeUserNode(char *id, char *password,char *name);
UserStatus *makeUserStatus();
UserStatus * InitUser(UserStatus *sta);
int GetUserRecordNum(char *filename);
UserStatus * AddUserNode(UserStatus *sta, User *node);
UserStatus * InputUserInfo(UserStatus *sta, int userCount);
User *FindUser(UserStatus *sta, char *id);
void Register(UserStatus *sta);
void LoginUser(UserStatus *sta);
void LogoutUser();
void DeleteUserNode(UserStatus *sta, char *id);
void Withdrawal(UserStatus *sta);
int FindUserIdx(UserStatus *sta, char *id);
//현 로그인 상태 판별
char nowId[15];
int loginStatus;


void Menu(WordStatus *sta_w, UserStatus *sta_u)
{
   while(1){
   int input=0;
   
   //메뉴 출력
   system("clear");
   printf("\n==================================\n");
   printf("============2021 SPLUG============\n");
   printf("==================================\n");

   if(nowId[0]=='\0'){
      printf("==================================\n");
   }else{
      printf("===================%15s\n",nowId);
   }
   printf("==================================\n");
   printf("=               메뉴             =\n");
   printf("==================================\n");
   printf("         1. 회원가입\n");
   printf("         2. 로그인\n");
   printf("         3. 로그아웃\n");
   printf("         4. 영어 단어 맞추기\n");
   printf("         5. 회원 탈퇴\n");
   printf("         6. 프로그램 종료\n");
   printf("==================================\n");
   printf(": ");
   scanf("%d",&input);
   getchar();
      
      switch(input)
      {
         case 1:
            //회원가입
            system("clear");
            Register(sta_u);
            break;
         case 2:
            LoginUser(sta_u);
            printf("로그인 끝\n");
            //로그인
            break;
         case 3:
            LogoutUser();
            //로그아웃
            break;
         case 4:
            //영어 단어 맞추기
            Eng_test(sta_w);
            break;
         case 5:
            Withdrawal(sta_u);
            //회원 탈퇴
            break;
         case 6:
            //종료
            system("clear");
            exit(0);
            break;
         default :
            continue;   
      }
      
   }
}

int main(){
   WordStatus *sta_w = (WordStatus *)makeWordStatus();
   UserStatus *sta_u = (UserStatus *)makeUserStatus();

   sta_w = InitWord(sta_w);
   sta_u = InitUser(sta_u);
   
   loginStatus=0;
   Menu(sta_w, sta_u);
}
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
   while(find->next!=NULL){
      if(!strcmp(find->id, id)) return find;
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

   printf("===== 회원가입 페이지 ====\n");

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
      printf("0\n");
      fseek(fp1, 0, SEEK_SET);
   }else{
      printf("1\n");
      fseek(fp1, sizeof(User)*sta->num, SEEK_SET);
   }
   fwrite(node, sizeof(User), 1, fp1);
   fclose(fp1);

   sta = AddUserNode(sta, node);


   printf("\n회원가입 완료\n\n");
   sleep(3);
   return ;
}

void LoginUser(UserStatus *sta){
   User *user;
   char id[15];
   char password[20];

   memset(id, 0, 15);
   memset(password, 0, 20);

   system("clear");
   printf("=== 로그인 ===\n");
   
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
   loginStatus=1;

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
   if(loginStatus==0){
      printf("\n==로그인 상태가 아닙니다.==\n");
      printf("2초후 메인화면으로 돌아갑니다.\n");
      sleep(2);
      return ;
   }
   
   char input;
   printf("정말 로그아웃 하시겠습니까? [Y/N]: ");
   scanf("%c",&input);
   
   if(input=='y' || input== 'Y'){
      memset(nowId, 0, 15);
      loginStatus=0;
      return ;
   }else{
      return ;
   }
}
void DeleteUserNode(UserStatus *sta, char *id){
   User *delete;

   delete = sta->head;
   while(delete->next!=NULL){
      if(!strcmp(delete->next->id, id)){
         sta->cur = delete;
         delete = delete->next;
         sta->cur->next = delete->next->next;
         sta->num--;
      }
      delete = delete->next;
   }
}

void Withdrawal(UserStatus *sta){
   if(loginStatus==0){
      printf("\n==로그인 상태가 아닙니다.==\n");
      printf("2초후 메인화면으로 돌아갑니다.\n");
      sleep(2);
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

   if(strcmp(check,"y")!=0 && strcmp(check,"Y")!=0){
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
      memset(nowId, 0, 15);
      fclose(fp);
      DeleteUserNode(sta, nowId);

      return ;
   }
}

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
      printf("\n==로그인 상태가 아닙니다.==\n");
      printf("2초후 메인화면으로 돌아갑니다.\n");
      sleep(2);
      return ;
   }

   printf("2초후 영어 단어 시험 화면으로 넘어갑니다.\n");
   sleep(2);
   system("clear");
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

   printf("\n\n");
   if(C_num==0 && F_num==0)
   {
      printf("당신의 점수는 %.2lf 점입니다.",score);
   }else{
      score=(double)100/(C_num + F_num)*C_num;
      printf("당신의 점수는 %.2lf 점입니다.",score);
   }
   while(getchar()!='\n');
   printf("3초 후 점수 화면이 지워집니다.\n");
   sleep(3);
   system("clear");
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


   

