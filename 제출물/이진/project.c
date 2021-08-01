#include"header.h"

void Menu(WordStatus *sta_w, UserStatus *sta_u)
{
	while(1){
	int input=0;
	
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

	Menu(sta_w, sta_u);
}
