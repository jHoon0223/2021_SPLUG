#pragma warning(disable : 4996)

#include	<stdio.h>
#include	<stdlib.h>
#include	<malloc.h>
#include	<string.h>
#include	<conio.h>
#include	<windows.h>
#include	<io.h>

#define A				25
#define USERDATASIZE	50

typedef struct node //영단어를 저장할 linked list를 위한 구조체
{
	char word[A]; //정보를 저장할 공간
	struct node* ptr_next; //다음 노드를 가리키는 포인터
} NODE;

typedef struct node_user //사용자 정보를 저장할 linked list를 위한 구조체
{
	char userdata[USERDATASIZE]; //사용자 정보를 저장할 공간
	struct node_user* ptr_next; //다음 노드를 가리키는 포인터
} NODE_USER;

int FileSave(void);
void StringRefine(NODE* ptr, char array[12]);
void AlpArray(NODE* ptr_head);
void RunGame_Print(NODE* ptr_head, NODE_USER* ptr_user_head);
void RunGame(NODE* ptr_head, NODE_USER* ptr_user_head);
void EnglishGame(NODE_USER* ptr_user_head);
void GameInterface(void);
void UserRegister(NODE_USER* ptr_user_head);
int MakeUserList();
void LinkFree_User(NODE_USER* ptr_user_head);
void LinkFree(NODE* ptr_head);
void Userlogin(NODE_USER* ptr_user_head);
void UserLogout(void);
void UserWithdraw(NODE_USER* ptr_user_head);
void UserWithdraw_delete(NODE_USER* ptr_user_head);

int login; //로그인 여부
char username[20]; //로그인 중인 사용자의 이름
char username_id[15]; //로그인 중인 사용자의 ID

/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// main 함수

int main(void)
{
	if (_access("loginfile.txt", 0) == (-1)) //userfile.txt 파일이 존재하지 않을 경우
	{
		FILE* fp_tmp;
		fp_tmp = fopen("loginfile.txt", "w");
		fclose(fp_tmp);
	}

	while (1)
	{
		//사용자 정보가 저장되어 있는 linked list 생성
		NODE_USER* ptr_user_head = (NODE_USER*)MakeUserList();

		//옵션 입력받기
		GameInterface();

		int option = (getch() - 48);

		switch (option) //----------------------------------각 케이스에 해당하는 함수를 하나씩 만들면 된다.
		{
		case 1:
			//회원가입 함수 (완료)
			UserRegister(ptr_user_head);
			break;
		case 2:
			//로그인 함수 (완료)
			Userlogin(ptr_user_head);
			break;
		case 3:
			//로그아웃 함수 (완료)
			UserLogout();
			break;
		case 4:
			//영단어 맞추기 함수 (완료)
			EnglishGame(ptr_user_head);
			break;
		case 5:
			//회원 탈퇴 함수 (완료)
			UserWithdraw(ptr_user_head);
			break;
		case 6:
			//종료 (완료)
			LinkFree_User(ptr_user_head);
			system("cls");
			printf("프로그램을 종료합니다. 다음에 또 만나요!!\n");
			exit(0);
			break;
		default:
			break;
		}
		system("cls"); //옵션에 없는 값을 입력한 경우, 화면을 지우고 다시 출력한다.

		//사용자 정보를 저장한 linked list 반납
		LinkFree_User(ptr_user_head);

	}

	return 0;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 사용자 정보 관리를 위한 linked list 관련 함수

/*
* 이름: 사용자 liked list 생성 함수
* 기능: 파일을 읽어 사용자 정보를 linked list로 저장
*		-> 파일에 내용이 있을 경우 정상적으로 linked list에 저장된다.
*		-> 파일에 내용이 없을 경우 헤드 포인터에 NULL값이 들어 있는 채로 아무 데이터도 저장되지 않는다.
* 받는값: X
* 리턴값: 사용자 정보를 저장한 linked list의 헤드 포인터 값
*/
int MakeUserList()
{
	FILE* fp;
	fp = fopen("loginfile.txt", "r");
	NODE_USER* ptr_user_head = NULL;
	NODE_USER* ptr_user_tail = NULL;

	while (1)
	{
		//tmp에 문자열 저장
		char tmp[USERDATASIZE] = { 0 };
		fgets(tmp, sizeof(tmp), fp);

		if (tmp[0] == 0)
		{
			break;
		}

		//tmp를 linked list에 추가
		if (ptr_user_head == NULL) //노드가 추가되어 있지 않았던 경우
		{
			ptr_user_head = (NODE_USER*)malloc(sizeof(NODE_USER)); //헤드 포인터에 노드 연결
			for (int j = 0; j < USERDATASIZE; j++)
			{
				ptr_user_head->userdata[j] = tmp[j];
			}
			ptr_user_head->ptr_next = NULL;
			ptr_user_tail = ptr_user_head;
		}
		else //노드가 추가되어 있는 경우
		{
			ptr_user_tail->ptr_next = (NODE_USER*)malloc(sizeof(NODE_USER));
			ptr_user_tail = ptr_user_tail->ptr_next;
			for (int j = 0; j < USERDATASIZE; j++)
			{
				ptr_user_tail->userdata[j] = tmp[j];
			}
			ptr_user_tail->ptr_next = NULL;
		}
	}

	fclose(fp);

	return (int)ptr_user_head;
}

/*
* 이름: linked list free 함수 (LinkFree_User, LinkFree 이렇게 두 가지 종류가 있다.)
* 기능: 매개변수로 받은 헤드 포인터의 linked list를 free() 처리한다.
* 받는값; 헤드 포인터
* 리턴값: X
*/
void LinkFree_User(NODE_USER* ptr_user_head)
{
	NODE_USER* p = ptr_user_head;
	NODE_USER* tmp;

	if (ptr_user_head == NULL) //노드가 추가되어 있지 않은 경우
	{
		free(ptr_user_head);
	}
	else //노드가 추가되어 있는 경우
	{
		while (p != NULL)
		{
			tmp = p->ptr_next;
			free(p);
			p = tmp;
		}
	}

	return;
}
void LinkFree(NODE* ptr_user_head)
{
	NODE* p = ptr_user_head;
	NODE* tmp;

	if (ptr_user_head == NULL) //노드가 추가되어 있지 않은 경우
	{
		free(ptr_user_head);
	}
	else //노드가 추가되어 있는 경우
	{
		while (p != NULL)
		{
			tmp = p->ptr_next;
			free(p);
			p = tmp;
		}
	}

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 인터페이스 함수

/*
* 이름: 인터페이스 함수
* 기능: 옵션 입력 화면을 조건에 맞춰 출력한다.
* 받는값: X
* 리턴값: X
*/
void GameInterface(void)
{
	printf("========================================\n");
	printf("============== 2021 splug ==============\n");
	printf("========================================\n");
	if (login == 0)
	{
		printf("\n");
	}
	else
	{
		printf("%40s\n", username);
	}
	printf("========================================\n");
	printf("=                 메뉴                 =\n");
	printf("========================================\n");

	printf("            1. 회원 가입\n");
	printf("            2. 로그인\n");
	printf("            3. 로그아웃\n");
	printf("            4. 영어 단어 맞추기\n");
	printf("            5. 회원 탈퇴\n");
	printf("            6. 프로그램 종료\n");

	printf("========================================\n: ");

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 1번 옵션 관련 함수들

/*
* 이름: 회원가입 함수
* 기능: 회원가입을 진행한다.
* 받는값; loginfile에 들어 있던 정보를 저장한 linked list의 헤드 포인터
* 리턴값: X
*/
void UserRegister(NODE_USER* ptr_user_head)
{
	//회원가입 인터페이스 출력
	system("cls");
	printf("회원가입 페이지\n");

	//아이디, 비번, 이름 입력받기
	char tmp_id[15] = { 0 }; //아이디를 저장할 임시공간
	char tmp_pw[15] = { 0 }; //비밀번호를 저장할 임시공간
	char tmp_username[15] = { 0 }; //사용자 이름을 저장할 임시공간

	while (1)
	{
		//아이디 입력받기
		printf("아이디 : ");
		scanf("%s", tmp_id);

		//아이디 중복 여부 확인을 위한 변수
		int joogbok = 0; //0이면 중복 X, 1이면 중복 O

		//linked list에서 아이디 하나씩 불러와서 비교하기
		if (ptr_user_head == NULL) //파일에 내용이 없는 경우 -> 비교 진행 X
		{
			;
		}
		else //파일에 내용이 있는 경우 -> 비교 진행
		{
			NODE_USER* p = ptr_user_head;
			while (1)
			{
				//linked list에서 정보 꺼내오기
				char tmp_data_id[15] = { 0 }; //linked list의 정보를 저장할 임시공간
				int i = 0;
				while (p->userdata[i] != ' ')
				{
					tmp_data_id[i] = p->userdata[i];
					i++;
				}

				//입력값과 비교하기
				if (strcmp(tmp_data_id, tmp_id) == 0) //동일한 문자열인 경우
				{
					joogbok++;
					break;
				}
				else //동일한 문자열이 아닌 경우 -> 다음 노드로 이동
				{
					p = p->ptr_next;
					if (p == NULL)
					{
						break;
					}
				}
			}

			if (joogbok == 1)
			{
				printf("이미 존재하는 아이디입니다.\n");
				continue;
			}
		}
		printf("사용 가능한 아이디 입니다.\n");

		//비번, 이름 입력받기
		printf("비밀번호 : ");
		scanf("%s", tmp_pw);
		printf("이름 : ");
		scanf("%s", tmp_username);

		//아이디, 비번, 이름 파일에 저장하기 -> 파일의 맨 마지막 줄에 저장된다.
		char result[USERDATASIZE] = { 0 };
		strcat(result, tmp_id);
		strcat(result, " ");
		strcat(result, tmp_pw);
		strcat(result, " ");
		strcat(result, tmp_username);

		FILE* fp = fopen("loginfile.txt", "a");

		fprintf(fp, "%s", result);
		fprintf(fp, "\n");

		fclose(fp);

		break;
	}

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 2번 옵션 관련 함수들

/*
* 이름: 로그인 함수
* 기능: 로그인을 진행한다.
* 받는값; loginfile에 들어 있던 정보를 저장한 linked list의 헤드 포인터
* 리턴값: X
*/
void Userlogin(NODE_USER* ptr_user_head)
{
	if (login == 1)
	{
		system("cls");
		printf("이미 로그인되어 있습니다.");
		char trash = getch();
		return;
	}

	//로그인 인터페이스
	system("cls");
	printf("로그인\n");

	while (1)
	{
		//아이디, 비번 입력받기
		char userid[15] = { 0 }; //로그인하려는 아이디
		char userpw[15] = { 0 }; //로그인하려는 아이디의 비밀번호
		char userdata[35] = { 0 }; //아이디와 비밀번호를 하나의 문자열로 묶어서 저장할 배열

		printf("아이디 : ");
		scanf("%s", userid);
		printf("비밀번호 : ");
		scanf("%s", userpw);

		strcat(userdata, userid);
		strcat(userdata, " ");
		strcat(userdata, userpw);
		

		//입력한 값이 맞는지 확인
		NODE_USER* p = ptr_user_head;
		if (p == NULL) //파일에 정보가 없는 경우
		{
			printf("회원 목록에 정보가 저장되어 있지 않습니다. 회원가입한 후에 다시 시도하세요.\n\n아무 키나 누르면 메인 화면으로 이동합니다.\n");
			char trash = getch();
			break;
		}
		else //파일에 정보가 있는 경우
		{
			//userdata 배열에 저장된 문자열을 ptr_user_head의 linked list 속 정보들과 비교
			while (1)
			{
				char nameupload[15] = { 0 }; //이름을 저장해둘 배열

				//linked list의 값 가공
				char listdata[35] = { 0 }; //가공한 값을 저장할 배열
				int i = 0, blank = 0;
				while (blank != 2)
				{
					listdata[i] = p->userdata[i];
					if (p->userdata[i] == ' ')
					{
						blank++;
					}
					i++;
				}
				listdata[i - 1] = 0;

				int j = 0;
				while (p->userdata[i] != '\n')
				{
					nameupload[j] = p->userdata[i];
					i++;
					j++;
				}
				nameupload[j] = 0;


				//비교
				if (strcmp(listdata, userdata) == 0) //해당 노드의 정보와 입력 정보가 같은 경우
				{
					login++;
					strcpy(username, nameupload);
					strcpy(username_id ,userid);
					break;
				}
				else //해당 노드의 정보와 입력 정보가 다른 경우
				{
					if (p->ptr_next == NULL)
					{
						break;
					}
					else
					{
						p = p->ptr_next;
					}
				}
			}
		}

		if (login == 1)
		{
			break;
		}
		printf("아이디 또는 비밀번호가 등록되지 않았거나 틀렸습니다. 다시 입력하세요.\n");
	}

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 3번 옵션 관련 함수들

/*
* 이름: 로그아웃 함수
* 기능: 로그아웃을 진행한다.
* 받는값; X
* 리턴값: X
*/
void UserLogout(void)
{
	system("cls");

	if (login == 1) //로그인 되어있는 경우
	{
		printf("정말 로그아웃 하시겠습니까? [y/n] : ");
		
		int a = 0;
		while (1)
		{
			char answer = getch();

			switch (answer)
			{
			case 'y':
				a++;
				login--;
				for (int i = 0; i < 20; i++)
				{
					username[i] = 0;
				}
				break;
			case 'Y':
				a++;
				login--;
				for (int i = 0; i < 20; i++)
				{
					username[i] = 0;
				}
				break;
			case 'n':
				a++;
				break;
			case 'N':
				a++;
				break;
			}

			if (a == 1)
			{
				break;
			}
		}
	}
	else //로그인이 되어있지 않은 경우
	{
		printf("로그인 되지 않았습니다. 다시 시도하세요.");
		char trash = getch();
	}

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 4번 옵션 관련 함수들

/*
* 이름: 파일 읽기 함수
* 기능: 파일 읽어서 linked list에 저장한다.
* 받는값: X
* 리턴값: 파일 내용을 저장한 linked list의 헤드 포인터의 값.
*/
int FileSave(void)
{
	FILE* fp_words;
	fp_words = fopen("dic.txt", "r");
	NODE* ptr_head = NULL; //헤드 포인터
	NODE* ptr_tail = NULL; //테일 포인터

	while (1)
	{
		//tmp에 문자열 저장
		char hangul[11] = { 0 };
		char tmp[A] = { 0 };
		fscanf(fp_words, "%s", tmp); //앞의 영단어 저장
		strcat(tmp, " ");
		char trash = getc(fp_words);
		fscanf(fp_words, "%s", hangul);
		strcat(tmp, hangul);
		trash = getc(fp_words); //개행문자 버리기

		if (trash == -1)
		{
			break;
		}


		//tmp를 linked list에 추가
		if (ptr_head == NULL) //노드가 추가되어 있지 않았던 경우
		{
			ptr_head = (NODE*)malloc(sizeof(NODE)); //헤드 포인터에 노드 연결
			for (int j = 0; j < A; j++)
			{
				ptr_head->word[j] = tmp[j];
			}
			ptr_head->ptr_next = NULL;
			ptr_tail = ptr_head;
		}
		else //노드가 추가되어 있던 경우
		{
			ptr_tail->ptr_next = (NODE*)malloc(sizeof(NODE));
			ptr_tail = ptr_tail->ptr_next;
			for (int j = 0; j < A; j++)
			{
				ptr_tail->word[j] = tmp[j];
			}
			ptr_tail->ptr_next = NULL;
		}
	}

	fclose(fp_words);

	return (int)ptr_head;
}

/*
* 이름: 문자열 정제 함수
* 기능: 첫 번쨰 인자의 포인터가 가리키는 문자열에서 아이디를 추출해 두 번째 인자의 배열에 저장한다.
* 받는값: 첫 번째 인자에 아이디를 가리키는 포인터, 두 번쨰 인자에 값을 저장할 배열
* 리턴값: X
*/
void StringRefine(NODE* ptr, char array[12])
{
	int i = 0;
	while (1)
	{
		array[i] = ptr->word[i];
		if (array[i] == ' ')
		{
			array[i] = 0;
			break;
		}
		i++;
	}

	return;
}

/*
* 이름: 사전순 정렬 함수
* 기능: linked list의 정보들을 사전순으로 정렬한다. (버블 정렬 사용)
* 받는값: linked list의 헤드 포인터 (ptr_head)
* 리턴값: X
*/
void AlpArray(NODE* ptr_head)
{
	NODE* ptr_start = ptr_head; //시작 값
	NODE* ptr_end = ptr_head;
	NODE* ptr_first; //두 개씩 묶어서 비교할 때 왼쪽 값
	NODE* ptr_second; //두 개씩 묶어서 비교할 때 오른쪽 값
	int num = 0; //포인터는 총 num 번 노드를 넘어온 것.

	while ((ptr_end->ptr_next) != NULL) //ptr_end에는 마지막 노드의 주소가 저장된다. (NULL 전 마지막 포인터)
	{
		ptr_end = ptr_end->ptr_next;
		num++;
	}

	while (1) //맨 뒷 칸을 한 칸 씩 앞으로. 맨 뒷 칸은 고정된다.
	{
		ptr_first = ptr_start;
		ptr_second = ptr_start->ptr_next;

		while (1) //두개씩 묶어서 비교. 둘 중에 사전순이 높은 것을 왼쪽으로 보낸다.
		{
			//비교
			char first[12] = { 0 };
			char second[12] = { 0 };

			StringRefine(ptr_first, first); //첫 번쨰 인자에 작성한 포인터가 가리키는 문자열에서 아이디를 추출해 first배열에 저장하는 함수.
			StringRefine(ptr_second, second);

			//교환
			int cmpvalue = strcmp(first, second);
			if (cmpvalue <= 0) //first에 저장된 문자열이 사전순으로 먼저이거나, 두 문자열의 사전순 순위가 같은 경우
			{
				;
			}
			else //second에 저장된 문자열이 사전순으로 먼저인 경우. 두 정보를 교환해 줘야 한다.
			{
				char tmp_array[A];

				strcpy(tmp_array, ptr_first->word);
				strcpy(ptr_first->word, ptr_second->word);
				strcpy(ptr_second->word, tmp_array);				
			}

			//주소 증가
			ptr_first = ptr_second;
			if (ptr_second == ptr_end)
			{
				break;
			}
			ptr_second = ptr_second->ptr_next;
		}

		//ptr_end에 이전 노드의 포인터를 대입 (전 순서의 포인터)
		num--;
		if (num == 0)
		{
			break;
		}
		NODE* ptr_end_before = ptr_head;
		for (int f = 0; f < num; f++)
		{
			ptr_end_before = ptr_end_before->ptr_next;
		}
	}

	return;
}

/*
* 이름: 게임 출력, 판단 함수
* 기능: 영단어 맞추기 게임을 구체적으로 진행한다. (코드가 길어져서 따로 뺐다.)
* 받는값: linked list의 헤드 포인터 (ptr_head)
* 리턴값: X
*/
void RunGame_Print(NODE* ptr_head, NODE_USER* ptr_user_head)
{
	NODE* p = ptr_head;

	int correct = 0; //정답을 맞힌 횟수
	int total = 0; //도전한 총 문제 수

	while (1)
	{
		//linked list에서 한글와 영어 가져와서 각각 저장하기
		char english[12] = { 0 };
		char korean[11] = { 0 };

		int i = 0;
		while (p->word[i] != ' ')
		{
			english[i] = p->word[i];
			i++;
		}
		i++;
		int j = 0;
		while (p->word[i] != 0)
		{
			korean[j] = p->word[i];
			j++;
			i++;
		}

		//한글 출력하기
		printf("\n%s -> ", korean);

		//사용자 값 입력받기
		char userin[15] = { 0 };
		scanf("%s", userin);

		if (strcmp(userin, ".quit") == 0) //입력한 문자열이 .quit인 경우
		{
			//점수 출력
			if (total == 0) //아직 푼 문제가 없는 경우
			{
				printf("\n점수를 출력할 수 없습니다. (푼 문제 : 0)\n프로그램을 종료합니다.\n");
			}
			else
			{
				printf("\n당신의 점수는 %.2f점입니다.", ((correct / (double)total) * 100));
				printf("\n프로그램을 종료합니다.\n");
			}

			//프로그램 종료
			LinkFree(ptr_head);
			LinkFree_User(ptr_user_head);
			exit(0);
		}
		else if (strcmp(userin, english) == 0) //올바른 답을 입력한 경우
		{
			printf("correct!\n");
			correct++;
			total++;
		}
		else //답을 맞추지 못한 경우
		{
			printf("incorrect!\n");
			total++;
		}

		//linked list의 다음 노드로 가기
		p = p->ptr_next;
		if (p == NULL)
		{
			LinkFree(ptr_head);
			LinkFree_User(ptr_user_head);
			printf("\n모든 문제를 풀었습니다!");
			printf("\n당신의 점수는 %.2f점입니다.", ((correct / (double)total) * 100));
			printf("\n프로그램을 종료합니다.\n");
			exit(0);
		}
	}

	return;
}

/*
* 이름: 게임 진행 함수
* 기능: 영단어 맞추기 게임을 진행한다.
* 받는값: linked list의 헤드 포인터 (ptr_head)
* 리턴값: X
*/
void RunGame(NODE* ptr_head, NODE_USER* ptr_user_head)
{
	//게임 인터페이스 출력
	while (1)
	{
		system("cls");
		printf(">> 영어 단어 맞추기 프로그램 <<\n1. 영어 단어 맞추기 2. 프로그램 종료\n\n번호를 선택하세요 : ");
		int option = getch();

		if (option == '1') //영어 단어 맞추기 시작
		{
			printf("1");
			//게임 진행
			RunGame_Print(ptr_head, ptr_user_head);
		}
		else if (option == '2') //프로그램 종료
		{
			LinkFree(ptr_head);
			LinkFree_User(ptr_user_head);
			printf("2\n\n프로그램을 종료합니다.\n");
			exit(0);
		}
		else //잘못된 옵션이 입력된 경우. 다시 입력받기
		{
			;
		}
	}

	return;
}

/*
* 이름: 영어 단어 맞추기 함수
* 기능: 4번 옵션 입력 시 작동할 함수들을 순서대로 호출한다.
* 받는값: X
* 리턴값: X
*/
void EnglishGame(NODE_USER* ptr_user_head)
{
	NODE *ptr_head; //헤드 포인터에 저장된 값을 저장할 포인터. 즉, 헤드 포인터와 동일함.
	ptr_head = (NODE*)FileSave(); //파일을 읽어서 linked list에 저장하는 함수. 헤드 포인터의 값을 리턴한다.
	AlpArray(ptr_head); //linked list에 저장된 값들을 알파벳 순서대로 정렬하는 함수.
	RunGame(ptr_head, ptr_user_head);

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 5번 옵션 관련 함수들

/*
* 이름: 회원 삭제 함수
* 기능: 기존의 파일을 회원 탈퇴 시 로그인 되어있던 사용자의 정보를 제거한 파일로 대체한다.
* 받는값; loginfile에 들어 있던 정보를 저장한 linked list의 헤드 포인터
* 리턴값: X
*/
void UserWithdraw_delete(NODE_USER* ptr_user_head)
{
	//linked list에서 현재 사용자의 정보가 들어있는 노드 탐색
	NODE_USER* p = ptr_user_head;
	NODE_USER* p_before = NULL; //p 직전 포인터

	char tmp_id[15] = { 0 };

	int u = 0;
	while (p->userdata[u] != ' ') //tmp_id에는 p가 가리키는 노드의 문자열이 저장된다.
	{
		tmp_id[u] = p->userdata[u];
		u++;
	}

	while (strcmp(username_id, tmp_id) != 0) //username_id에 저장된 문자열과 p가 가리키는 노드의 문자열이 같다면 깨지는 반복문
	{
		p_before = p;
		p = p->ptr_next; //p에는 반복문에 깨지는 순간의 반환할 노드의 주소가 저장되어 있다.
		
		int u2 = 0;
		while (p->userdata[u2] != ' ') //tmp_id에는 p가 가리키는 노드의 문자열이 저장된다.
		{
			tmp_id[u2] = p->userdata[u2];
			u2++;
		}
		tmp_id[u2] = 0;
	}

	//해당 노드를 반환하고, 해당 노드의 앞 뒤 노드를 서로 연결
	if (p == ptr_user_head) //p가 헤드인 경우
	{
		FILE* fp_loginfile;
		fp_loginfile = fopen("loginfile.txt", "w");
		NODE_USER* final2 = ptr_user_head;
		fprintf(fp_loginfile, "%s", final2->userdata);
		fclose(fp_loginfile);

		FILE* fp_loginfile2;
		fp_loginfile2 = fopen("loginfile.txt", "w");
		final2 = final2->ptr_next;
		while (final2 != NULL)
		{
			fprintf(fp_loginfile2, "%s", final2->userdata);

			final2 = final2->ptr_next;
		}
		fclose(fp_loginfile2);

		return;
	}
	else //p가 헤드가 아닌 경우
	{
		NODE_USER* value2;

		value2 = p;
		p_before->ptr_next = p->ptr_next;
		free(value2);
	}

	//w옵션을 사용해서 파일을 연 후, 변경된 linked list의 내용을 작성
	FILE* fp_loginfile;
	fp_loginfile = fopen("loginfile.txt", "w");

	NODE_USER* final = ptr_user_head;
	do
	{
		fprintf(fp_loginfile, "%s", final->userdata);

		final = final->ptr_next;
	} while (final != NULL);

	fclose(fp_loginfile);

	return;
}

/*
* 이름: 회원 탈퇴 함수
* 기능: 회원 탈퇴를 진행한다.
* 받는값; loginfile에 들어 있던 정보를 저장한 linked list의 헤드 포인터
* 리턴값: X
*/
void UserWithdraw(NODE_USER* ptr_user_head)
{
	if (login == 1) //로그인 되어있는 경우
	{
		system("cls");
		printf("정말 회원 탈퇴를 진행하시겠습니까? [y/n] : ");
		
		int a = 0;
		while (1)
		{
			char answer = getch();

			switch (answer)
			{
			case 'y':
				UserWithdraw_delete(ptr_user_head);
				login--;
				for (int i = 0; i < 20; i++)
				{
					username[i] = 0;
				}
				a++;
				break;
			case 'Y':
				UserWithdraw_delete(ptr_user_head);
				login--;
				for (int i = 0; i < 20; i++)
				{
					username[i] = 0;
				}
				a++;
				break;
			case 'n':
				a++;
				break;
			case 'N':
				a++;
				break;
			}

			if (a == 1)
			{
				break;
			}
		}
	}
	else //로그인 되어있지 않은 경우
	{
		system("cls");
		printf("로그인 상태가 아닙니다.\n");
		char trash = getch();
	}

	return;
}