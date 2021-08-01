#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<Windows.h>

/*파일에서 ID, PW, name 받아오는 배열은 save_ID, save_PW, save_name로 통일*/

typedef struct member
{
	char ID[20];
	char PW[30];
	char name[30];
	struct member* next;
}member;
//파일에서 회원정보 연결리스트에 저장
void loadmember(member* target)
{
	FILE* load = fopen("C:\\test\\IDPW.txt", "r");
	if (load == NULL)
	{
		return;
	}
	else
	{
		while (1)
		{
			if (feof(load)) break;
			char load_ID[10];
			char load_PW[20];
			char load_name[20];

			fscanf(load, "%s %s %s\n", load_ID, load_PW, load_name);
			member* newmember = (member*)malloc(sizeof(member));

			load_ID[strlen(load_ID) + 1] = '\0';
			load_PW[strlen(load_PW) + 1] = '\0';
			load_name[strlen(load_name) + 1] = '\0';

			newmember->next = target->next;
			strcpy(newmember->ID, load_ID);
			strcpy(newmember->PW, load_PW);
			strcpy(newmember->name, load_name);

			target->next = newmember;
		}
		fclose(load);
	}
}
//새로운 회원가입 정보 연결리스트에 저장, 파일에 저장
void addmember(member* target, char ID[], char PW[], char name[])
{
	FILE* save = fopen("C:\\test\\IDPW.txt", "at");
	member* newmember = (member*)malloc(sizeof(member));
	newmember->next = target->next;
	strcpy(newmember->ID, ID);
	strcpy(newmember->PW, PW);
	strcpy(newmember->name, name);
	fprintf(save, "%s %s %s\n", newmember->ID, newmember->PW, newmember->name);
	target->next = newmember;
	fclose(save);
	system("cls");
}
//아이디중복체크
bool IDcheck(char check_ID[])//아이디 중복 확인
{
	FILE* check = fopen("C:\\test\\IDPW.txt", "r");

	char save_ID[10];
	char save_PW[20];
	char save_name[20];

	if (check == NULL)
	{
		printf("사용가능한 아이디 입니다.\n");
		return true;
	}

	while (1)
	{
		if (feof(check)) break;

		fscanf(check, "%s %s %s\n", save_ID, save_PW, save_name);
		save_ID[strlen(save_ID) + 1] = '\0';

		if (strcmp(save_ID, check_ID) == 0)
		{
			printf("이미 존재하는 아이디 입니다.\n");
			return false;
		}
	}

	printf("사용가능한 아이디입니다.\n");
	fclose(check);
	return true;
}
//비밀번호 중복체크
bool namecheck(char check_name[])//이름 중복 확인
{
	FILE* check = fopen("C:\\test\\IDPW.txt", "r");
	char save_ID[40];
	char save_PW[40];
	char save_name[40];

	if (check == NULL)
		return true;

	while (1)
	{
		if (feof(check)) break;

		fscanf(check, "%s %s %s\n", save_ID, save_PW, save_name);
		save_name[strlen(save_name) + 1] = '\0';

		if (strcmp(save_name, check_name) == 0)
		{
			printf("이미 가입한 회원입니다.\n");
			printf("메뉴로 돌아갑니다.\n");
			Sleep(10000);
			system("cls");
			return false;
		}
	}
	fclose(check);
	return true;
}
//로그인
bool logincheck = 0; // 0 : 비로그인, 1 : 로그인
void login(char login_ID[], char login_PW[]) // 로그인
{
	FILE* check = fopen("C:\\test\\IDPW.txt", "r");

	char save_ID[20];
	char save_PW[30];
	char save_name[30];

	if (logincheck == true)
	{
		printf("이미 로그인 되어있습니다.\n");
		return;
	}

	if (check == NULL)
	{
		printf("파일이 비어있어 회원정보가 존재하지 않습니다.\n");
		return;
	}
	else
	{
		while (1)
		{
			if (feof(check)) break;

			fscanf(check, "%s %s %s", save_ID, save_PW, save_name);
			save_ID[strlen(save_ID) + 1] = '\0';
			save_PW[strlen(save_PW) + 1] = '\0';

			if ((strcmp(save_ID, login_ID) == 0) && (strcmp(save_PW, login_PW) == 0))
			{
				logincheck = true;
				fclose(check);
				return;
			}
		}
	}
	printf("잘못된 아이디이거나 틀린 비밀번호입니다.\n");
	printf("처음화면으로 돌아갑니다.\n");
	Sleep(500);
	system("cls");
	return;
}
//로그아웃
void logout()// 로그아웃
{
	if (logincheck == false)
	{
		printf("로그인 되지 않았습니다. 다시 시도하세요.\n");
		Sleep(500);
		system("cls");
	}
	else
	{
		printf("정말 로그아웃 하시겠습니끼? [y/n]: ");
		char logoutcheck;
		scanf(" %c", &logoutcheck);

		if (logoutcheck == 'y')
		{
			logincheck = false;
			system("cls");
		}
		else if (logoutcheck == 'n')
			return;
	}
}
//퀴즈프로그램
void quiz_start(char* word_eng[], char* word_mean[])
{
	double score = 0; //점수
	int count = 0;//문제 개수
	int correct = 0;//맞은 문제 개수

	for (int i = 0; i < 101; i++)
	{
		char andswer[20] = " ";
		printf("%s -> ", word_mean[i]);
		scanf("%s", andswer);

		if (strcmp(andswer, ".quit") == 0)
			break;

		count++;
		if (strcmp(andswer, word_eng[i]) == 0)
		{
			correct++;
			printf("correct!\n");
		}
		else
			printf("intcorrect!\n");
	}
	score = 100 * ((double)correct / count);
	printf("당신의 점수는 %.1f점입니다.\n", score);
	Sleep(1000);
	system("cls");
}
void quiz_setting()
{
	char* word_eng[101] = {0};
	char* word_mean[101] = {0};


	FILE* word = fopen("C:\\test\\dic.txt", "r");
	//단어 저장
	while (1)
	{
		static int cnt = 0;
		char buffer_eng[40]; //파일에 있는 단어를 불러와 저장할 배열, 단어퀴즈니까 40자가 넘지는 않는다.
		char buffer_mean[40];

		if (feof(word))
		{
			break; //파일 끝이면 종료
			cnt = 0;
		}
		fscanf(word, "%s %s\n", buffer_eng, buffer_mean); //파일에 있는 단어 저장

		char* input_eng = (char*)malloc((sizeof(char)) * (strlen(buffer_eng) + 1)); //단어의 길이만큼 공간 할당
		strcpy(input_eng, buffer_eng);//단어 복사
		word_eng[cnt] = input_eng; //단어저장

		char* input_mean = (char*)malloc((sizeof(char)) * (strlen(buffer_mean) + 1));
		strcpy(input_mean, buffer_mean);
		word_mean[cnt] = input_mean;
		cnt++;
	}
	fclose(word);

	char* key_eng;
	char* key_mean;
	int i, j;
	// 삽입정렬로 단어 정렬
	for (i = 1; i < 101; i++)
	{
		key_eng = word_eng[i];
		key_mean = word_mean[i];
		for (j = i - 1; j >= 0; j--) 
		{
			if (strcmp(word_eng[j], key_eng) > 0)
			{
				word_eng[j + 1] = word_eng[j];
				word_mean[j + 1] = word_mean[j];
			}
			else
				break;
		}
		word_eng[j + 1] = key_eng;
		word_mean[j + 1] = key_mean;
	}
	i = 0;
	j = 0;
	char option = ' ';
	printf(">> 영어 단어 맞추기 프로그램 <<\n");
	printf("1. 영어 단어 맞추기 2. 프로그램 종료\n");
	printf("번호를 선택하세요: ");
	scanf(" %c", &option);
	if (option == '1')
		quiz_start(word_eng, word_mean);
	else if (option == '2')
		return;
}

//회원탈퇴
void removemember(member* target, char ID[])
{
	char check;
	printf("정말 회원을 탈퇴하시겠습니까? [y/n]: ");
	scanf(" %c", &check);
	if (check == 'n')
		return;

	member* deletemember = target->next; // 기준 노드의 다음 노드 주소를 저장 - 파일삭제용
	while (deletemember != NULL)
	{
		if (strcmp(deletemember->ID, ID) == 0)
		{
			target->next = deletemember->next; // 기준 노드의 다음 노드에 삭제할 노드의 다음 노드를 지정
			free(deletemember);
			logincheck = false;
			return;
		}
		target = target->next;
		deletemember = deletemember->next;
	}
	//로그인상태에서 진행되기 때문에 아이디가 존재하지 않는 경우는 고려하지 않음
	
}
//탈퇴후 정보 다시 저장
void save(member* target)
{
	member* temp = target->next;// 기준 노드의 다음 노드 주소를 저장
	FILE* file = fopen("C:\\test\\IDPW.txt", "w");
	while (temp != NULL)
	{
		printf("%s %s %s\n", temp->ID, temp->PW, temp->name);
		fprintf(file, "%s %s %s\n", temp->ID, temp->PW, temp->name);
		temp = temp->next;
	}
	fclose(file);
}

int main()
{
	member* firstmember = (member*)malloc(sizeof(member)); // head노드
	firstmember->next = NULL;
	
	loadmember(firstmember);

	char input_ID[10]; //회원가입시 ID 입력
	char input_PW[20]; //회원가입시 PW 입력
	char input_name[10]; //회원가입시 이름 입력

	char login_ID[10];
	char login_PW[20];

	char option = ' '; //옵션선택 변수
	while (1)
	{
		if (logincheck == true)
		{
			system("cls");
			printf("====20211402 컴퓨터학부 김민욱====\n");
			printf("==================================\n");
			printf("=========== 2021 SPLUG ===========\n");
			printf("======================== %-10s\n", login_ID);
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
			printf("-\n");
			printf("-");
		}
		else
		{
			printf("====20211402 컴퓨터학부 김민욱====\n");
			printf("==================================\n");
			printf("=========== 2021 SPLUG ===========\n");
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
			printf("-\n");
			printf("-");
		}
		scanf(" %c", &option);

		switch (option)
		{
		case '1':
			system("cls");
			printf("회원가입 페이지\n");
			while (1)
			{
				bool result_IDcheck = true; // 중복 : fasle, 미중복 : true
				printf("ID : ");
				scanf(" %s", input_ID);//버퍼 때문에 한칸 띄움

				result_IDcheck = IDcheck(input_ID);
				if (result_IDcheck == true)
					break;
			}
			printf("PW : ");
			scanf("%s", input_PW);

			printf("이름 : ");
			scanf("%s", input_name);
			{
				bool result_namecheck = true;
				result_namecheck = namecheck(input_name);
				if (result_namecheck == false)
					continue;
				else
					addmember(firstmember, input_ID, input_PW, input_name); // 회원가입 정보 저장
			}
			break;
		case '2':
			system("cls");

			if (logincheck == true)
			{
				printf("이미 로그인하셨습니다.\n");
				Sleep(700);
				continue;
			}

			printf("로그인\n");
			printf("ID : ");
			scanf("%s", login_ID);

			printf("PW : ");
			scanf("%s", login_PW);

			login(login_ID, login_PW);

			break;
		case '3':
			logout();
			break;
		case '4':			
			if (logincheck == false)
			{
				printf("로그인 상태가 아닙니다.\n");
				Sleep(500);
				system("cls");
				continue;
			}
			system("cls");
			quiz_setting();
			break;
		case '5':
			if (logincheck == false)
			{
				printf("로그인 상태가 아닙니다.\n");
				Sleep(700);
				system("cls");
				continue;
			}
			removemember(firstmember, login_ID);
			save(firstmember);
			system("cls");
			break;
		case '6':
			system("cls");
			printf("수고하셨습니당!\n");
			exit(0);
			break;
		default:
			{
				printf("메뉴에 없습니다악!!!!!!!\n");
				Sleep(700);
				system("cls");
			}
			break;
		}	
	}

	return 0;
}