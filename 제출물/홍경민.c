#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE* info;
	int  log = 0, size, idlog, invalid;
	long int len;
    char menu;
	float cor, incor, score;
	char *id, *pw, *name;
	char temp[100], tp1[100], tp2[100], tp3[100];
	int num = 101;
	char logout, withdraw;
	char lgst[29] = "============================";
main_menu: //메인메뉴 #완료
	while (1)
	{
		printf("============================\n");
		printf("=========2021 SPLUG=========\n");
		if (log == 0)
		{
			char lgst[29] = "============================";
			printf("%s\n", lgst);
		}
		if (log == 1)
		{
			char lgst[29] = "============================";	
			size = strlen(id);
			int N = 29;
			while (size > 0)
			{
				lgst[N-2] = id[size -1];
				N--;
				size--;
			}
			printf("%s\n", lgst);
		}
		printf("============================\n");
		printf("=           메뉴           =\n");
		printf("============================\n");
		printf("      1. 회원가입           \n");
		printf("      2. 로그인             \n");
		printf("      3. 로그아웃           \n");
		printf("      4. 영어 단어 맞추기   \n");
		printf("      5. 회원 탈퇴          \n");
		printf("      6. 프로그램 종료      \n");
		printf("============================\n");
		scanf(" %c", &menu);
		getchar();
		if (menu == '1') //회원가입
			goto regist;
		if (menu == '2') //로그인
			goto log_in;
		if (menu == '3') //로그아웃
			goto log_out;
		if (menu == '4') //단어 맞추기
			goto quiz;
		if (menu == '5') //탈퇴
			goto withdr;
		if (menu == '6') //종료
			goto end;
		printf("다시 입력하세요.\n\n");
	}
regist: //회원가입 #완료
    printf("회원가입 페이지\n");
	info = fopen("clinf.txt", "a+");
	while (1)
	{
		invalid = 0;
		printf("아이디(15글자 내) : ");
		scanf("%s", temp);
		getchar();
		if (strlen(temp) > 15)
		{
			printf("아이디는 15글자 이내로 해주시기 바랍니다.\n");
			invalid = 1;
		}
		fseek(info, 0, SEEK_SET);
		while (feof(info) == 0)
		{
			fscanf(info, "%s%s%s", tp1, tp2, tp3);
			if (strcmp(temp, tp1) == 0)
			{
				printf("사용할 수 없는 아이디입니다.\n");
				invalid = 1;
				break;
			}
		}
		if (invalid == 0)
			break;
	}
	fprintf(info, "%s ", temp);
	printf("비밀번호 : ");
	scanf(" %s", temp);
	fprintf(info, "%s ", temp);
	printf("이름 : ");
	scanf(" %s", temp);
	fprintf(info, "%s\n", temp);
	fclose(info);
	printf("회원가입이 완료되었습니다.\n\n");
	goto main_menu;

log_in:  //로그인
	if (log == 1)
		printf("이미 로그인 상태입니다.\n\n");
	if (log == 0)
	{
		info = fopen("clinf.txt", "r");
		printf("로그인\n");
		printf("아이디 : ");
		scanf(" %s", temp);
		while (feof(info) == 0)
		{
			fscanf(info, "%s%s%s", tp1, tp2, tp3);
			if (strcmp(temp, tp1) == 0)
			{
				idlog = 0;
				break;
			}
			idlog = 1;
		}
		if (idlog == 1)
			printf("유효하지 않은 아이디입니다.\n");
		if (idlog == 0)
		{
			id = (char *) calloc(strlen(tp1), sizeof(char));
			strcpy(id, tp1);
			printf("비밀번호 : ");
			scanf(" %s", temp);
			if (strcmp(temp, tp2) != 0)
				printf("유효하지 않은 비밀번호입니다.\n");
			if (strcmp(temp, tp2) == 0)
			{
				pw = (char *) calloc(strlen(tp2), sizeof(char));
				strcpy(pw, tp2);
				name = (char*) calloc(strlen(tp3), sizeof(char));
				strcpy(name, tp3);
				log = 1;
				printf("로그인 되셨습니다,  %s님\n\n", name);
			}
			fclose(info);
		}
	}
	goto main_menu;
log_out: //로그아웃#완료
	if (log == 0)
		printf("로그인 상태에서만 가능합니다.\n\n");
	if (log == 1)
	{
		while (1)
		{
			printf("정말 로그아웃 하시겠습니까? [y/n] : ");
			scanf(" %c", &logout);
			if (logout == 'y')
			{
				log = 0;
				printf("로그아웃 되셨습니다.\n\n");
				free(id);
				free(pw);
				free(name);
				break;
			}
			if (logout == 'n')
			{
				printf("로그아웃 하지 않으셨습니다.\n\n");
				break;
			}
			else	
				printf("다시 입력하세요.\n");
		}
	}
	goto main_menu;
quiz:   //단어 맞추기 #순서만 하면 완료
	if (log == 0)
		printf("로그인 상태에서만 가능합니다.\n\n");
	if (log == 1)
	{
		cor = 0;
		incor = 0;
		FILE* dic = fopen("dic.txt", "r");
		while (num > 0)
		{
			fscanf(dic, "%s%s", tp1, tp2);
			printf("%s -> ", tp2);
			scanf(" %s", temp);
			if (strcmp(temp, ".quit") == 0)
				break;
			if (strcmp(temp, tp1) == 0)
			{
				printf("correct!\n");
				cor += 1;
			}
			else
			{
				printf("incorrect!\n");
				incor += 1;
			}
			num--;
		}
		fclose(dic);
		score = 100 * (cor / (cor + incor));
		printf("당신의 점수는 %.2f점입니다.\n\n", score);
	}
	goto main_menu;
withdr:  //탈퇴
	if (log == 0)
		printf("로그인 상태에서만 가능합니다.\n\n");
	if (log == 1)
	{	
		while (1)
		{
			printf("아이디 : %s\n", id);
			printf("비밀번호 : %s\n", pw);
			printf("이름 : %s\n", name);
			printf("정말 회원을 탈퇴하시겠습니까? [y/n]");
			scanf(" %c", &withdraw);
			if (withdraw == 'y')
			{
				info = fopen("clinf.txt", "r+");
				while (1)
				{
					fscanf(info, "%s %s %s", tp1, tp2, tp3);
					if (strcmp(tp1, id) == 0)
						break;
				}
				len = strlen(tp1) + strlen(tp2) + strlen(tp3);
				fseek(info, -(len + 2), SEEK_CUR);
				while (len + 2 >0)
				{
					fputs(" ", info);
					len--;
				}
				fclose(info);
				log = 0;
				printf("회원 탈퇴하셨습니다.\n\n");
				free(id);
				free(pw);
				free(name);
				break;
			}
			if (withdraw == 'n')
			{
				printf("회원 탈퇴하지 않으셨습니다.\n\n");
				break;
			}
			else
				printf("다시 입력하세요.\n");
		}
	}
	goto main_menu;
end:    //종료 #완료
	printf("\e[0m\ec\e[H\e[3J");
	printf("다음에 또 만나요!!\n");
	return 0;
}
