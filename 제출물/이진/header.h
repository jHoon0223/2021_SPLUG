#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termio.h>
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
