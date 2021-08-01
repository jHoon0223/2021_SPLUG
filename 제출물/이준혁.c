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

typedef struct node //���ܾ ������ linked list�� ���� ����ü
{
	char word[A]; //������ ������ ����
	struct node* ptr_next; //���� ��带 ����Ű�� ������
} NODE;

typedef struct node_user //����� ������ ������ linked list�� ���� ����ü
{
	char userdata[USERDATASIZE]; //����� ������ ������ ����
	struct node_user* ptr_next; //���� ��带 ����Ű�� ������
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

int login; //�α��� ����
char username[20]; //�α��� ���� ������� �̸�
char username_id[15]; //�α��� ���� ������� ID

/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// main �Լ�

int main(void)
{
	if (_access("loginfile.txt", 0) == (-1)) //userfile.txt ������ �������� ���� ���
	{
		FILE* fp_tmp;
		fp_tmp = fopen("loginfile.txt", "w");
		fclose(fp_tmp);
	}

	while (1)
	{
		//����� ������ ����Ǿ� �ִ� linked list ����
		NODE_USER* ptr_user_head = (NODE_USER*)MakeUserList();

		//�ɼ� �Է¹ޱ�
		GameInterface();

		int option = (getch() - 48);

		switch (option) //----------------------------------�� ���̽��� �ش��ϴ� �Լ��� �ϳ��� ����� �ȴ�.
		{
		case 1:
			//ȸ������ �Լ� (�Ϸ�)
			UserRegister(ptr_user_head);
			break;
		case 2:
			//�α��� �Լ� (�Ϸ�)
			Userlogin(ptr_user_head);
			break;
		case 3:
			//�α׾ƿ� �Լ� (�Ϸ�)
			UserLogout();
			break;
		case 4:
			//���ܾ� ���߱� �Լ� (�Ϸ�)
			EnglishGame(ptr_user_head);
			break;
		case 5:
			//ȸ�� Ż�� �Լ� (�Ϸ�)
			UserWithdraw(ptr_user_head);
			break;
		case 6:
			//���� (�Ϸ�)
			LinkFree_User(ptr_user_head);
			system("cls");
			printf("���α׷��� �����մϴ�. ������ �� ������!!\n");
			exit(0);
			break;
		default:
			break;
		}
		system("cls"); //�ɼǿ� ���� ���� �Է��� ���, ȭ���� ����� �ٽ� ����Ѵ�.

		//����� ������ ������ linked list �ݳ�
		LinkFree_User(ptr_user_head);

	}

	return 0;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// ����� ���� ������ ���� linked list ���� �Լ�

/*
* �̸�: ����� liked list ���� �Լ�
* ���: ������ �о� ����� ������ linked list�� ����
*		-> ���Ͽ� ������ ���� ��� ���������� linked list�� ����ȴ�.
*		-> ���Ͽ� ������ ���� ��� ��� �����Ϳ� NULL���� ��� �ִ� ä�� �ƹ� �����͵� ������� �ʴ´�.
* �޴°�: X
* ���ϰ�: ����� ������ ������ linked list�� ��� ������ ��
*/
int MakeUserList()
{
	FILE* fp;
	fp = fopen("loginfile.txt", "r");
	NODE_USER* ptr_user_head = NULL;
	NODE_USER* ptr_user_tail = NULL;

	while (1)
	{
		//tmp�� ���ڿ� ����
		char tmp[USERDATASIZE] = { 0 };
		fgets(tmp, sizeof(tmp), fp);

		if (tmp[0] == 0)
		{
			break;
		}

		//tmp�� linked list�� �߰�
		if (ptr_user_head == NULL) //��尡 �߰��Ǿ� ���� �ʾҴ� ���
		{
			ptr_user_head = (NODE_USER*)malloc(sizeof(NODE_USER)); //��� �����Ϳ� ��� ����
			for (int j = 0; j < USERDATASIZE; j++)
			{
				ptr_user_head->userdata[j] = tmp[j];
			}
			ptr_user_head->ptr_next = NULL;
			ptr_user_tail = ptr_user_head;
		}
		else //��尡 �߰��Ǿ� �ִ� ���
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
* �̸�: linked list free �Լ� (LinkFree_User, LinkFree �̷��� �� ���� ������ �ִ�.)
* ���: �Ű������� ���� ��� �������� linked list�� free() ó���Ѵ�.
* �޴°�; ��� ������
* ���ϰ�: X
*/
void LinkFree_User(NODE_USER* ptr_user_head)
{
	NODE_USER* p = ptr_user_head;
	NODE_USER* tmp;

	if (ptr_user_head == NULL) //��尡 �߰��Ǿ� ���� ���� ���
	{
		free(ptr_user_head);
	}
	else //��尡 �߰��Ǿ� �ִ� ���
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

	if (ptr_user_head == NULL) //��尡 �߰��Ǿ� ���� ���� ���
	{
		free(ptr_user_head);
	}
	else //��尡 �߰��Ǿ� �ִ� ���
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
// �������̽� �Լ�

/*
* �̸�: �������̽� �Լ�
* ���: �ɼ� �Է� ȭ���� ���ǿ� ���� ����Ѵ�.
* �޴°�: X
* ���ϰ�: X
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
	printf("=                 �޴�                 =\n");
	printf("========================================\n");

	printf("            1. ȸ�� ����\n");
	printf("            2. �α���\n");
	printf("            3. �α׾ƿ�\n");
	printf("            4. ���� �ܾ� ���߱�\n");
	printf("            5. ȸ�� Ż��\n");
	printf("            6. ���α׷� ����\n");

	printf("========================================\n: ");

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 1�� �ɼ� ���� �Լ���

/*
* �̸�: ȸ������ �Լ�
* ���: ȸ�������� �����Ѵ�.
* �޴°�; loginfile�� ��� �ִ� ������ ������ linked list�� ��� ������
* ���ϰ�: X
*/
void UserRegister(NODE_USER* ptr_user_head)
{
	//ȸ������ �������̽� ���
	system("cls");
	printf("ȸ������ ������\n");

	//���̵�, ���, �̸� �Է¹ޱ�
	char tmp_id[15] = { 0 }; //���̵� ������ �ӽð���
	char tmp_pw[15] = { 0 }; //��й�ȣ�� ������ �ӽð���
	char tmp_username[15] = { 0 }; //����� �̸��� ������ �ӽð���

	while (1)
	{
		//���̵� �Է¹ޱ�
		printf("���̵� : ");
		scanf("%s", tmp_id);

		//���̵� �ߺ� ���� Ȯ���� ���� ����
		int joogbok = 0; //0�̸� �ߺ� X, 1�̸� �ߺ� O

		//linked list���� ���̵� �ϳ��� �ҷ��ͼ� ���ϱ�
		if (ptr_user_head == NULL) //���Ͽ� ������ ���� ��� -> �� ���� X
		{
			;
		}
		else //���Ͽ� ������ �ִ� ��� -> �� ����
		{
			NODE_USER* p = ptr_user_head;
			while (1)
			{
				//linked list���� ���� ��������
				char tmp_data_id[15] = { 0 }; //linked list�� ������ ������ �ӽð���
				int i = 0;
				while (p->userdata[i] != ' ')
				{
					tmp_data_id[i] = p->userdata[i];
					i++;
				}

				//�Է°��� ���ϱ�
				if (strcmp(tmp_data_id, tmp_id) == 0) //������ ���ڿ��� ���
				{
					joogbok++;
					break;
				}
				else //������ ���ڿ��� �ƴ� ��� -> ���� ���� �̵�
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
				printf("�̹� �����ϴ� ���̵��Դϴ�.\n");
				continue;
			}
		}
		printf("��� ������ ���̵� �Դϴ�.\n");

		//���, �̸� �Է¹ޱ�
		printf("��й�ȣ : ");
		scanf("%s", tmp_pw);
		printf("�̸� : ");
		scanf("%s", tmp_username);

		//���̵�, ���, �̸� ���Ͽ� �����ϱ� -> ������ �� ������ �ٿ� ����ȴ�.
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
// 2�� �ɼ� ���� �Լ���

/*
* �̸�: �α��� �Լ�
* ���: �α����� �����Ѵ�.
* �޴°�; loginfile�� ��� �ִ� ������ ������ linked list�� ��� ������
* ���ϰ�: X
*/
void Userlogin(NODE_USER* ptr_user_head)
{
	if (login == 1)
	{
		system("cls");
		printf("�̹� �α��εǾ� �ֽ��ϴ�.");
		char trash = getch();
		return;
	}

	//�α��� �������̽�
	system("cls");
	printf("�α���\n");

	while (1)
	{
		//���̵�, ��� �Է¹ޱ�
		char userid[15] = { 0 }; //�α����Ϸ��� ���̵�
		char userpw[15] = { 0 }; //�α����Ϸ��� ���̵��� ��й�ȣ
		char userdata[35] = { 0 }; //���̵�� ��й�ȣ�� �ϳ��� ���ڿ��� ��� ������ �迭

		printf("���̵� : ");
		scanf("%s", userid);
		printf("��й�ȣ : ");
		scanf("%s", userpw);

		strcat(userdata, userid);
		strcat(userdata, " ");
		strcat(userdata, userpw);
		

		//�Է��� ���� �´��� Ȯ��
		NODE_USER* p = ptr_user_head;
		if (p == NULL) //���Ͽ� ������ ���� ���
		{
			printf("ȸ�� ��Ͽ� ������ ����Ǿ� ���� �ʽ��ϴ�. ȸ�������� �Ŀ� �ٽ� �õ��ϼ���.\n\n�ƹ� Ű�� ������ ���� ȭ������ �̵��մϴ�.\n");
			char trash = getch();
			break;
		}
		else //���Ͽ� ������ �ִ� ���
		{
			//userdata �迭�� ����� ���ڿ��� ptr_user_head�� linked list �� ������� ��
			while (1)
			{
				char nameupload[15] = { 0 }; //�̸��� �����ص� �迭

				//linked list�� �� ����
				char listdata[35] = { 0 }; //������ ���� ������ �迭
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


				//��
				if (strcmp(listdata, userdata) == 0) //�ش� ����� ������ �Է� ������ ���� ���
				{
					login++;
					strcpy(username, nameupload);
					strcpy(username_id ,userid);
					break;
				}
				else //�ش� ����� ������ �Է� ������ �ٸ� ���
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
		printf("���̵� �Ǵ� ��й�ȣ�� ��ϵ��� �ʾҰų� Ʋ�Ƚ��ϴ�. �ٽ� �Է��ϼ���.\n");
	}

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 3�� �ɼ� ���� �Լ���

/*
* �̸�: �α׾ƿ� �Լ�
* ���: �α׾ƿ��� �����Ѵ�.
* �޴°�; X
* ���ϰ�: X
*/
void UserLogout(void)
{
	system("cls");

	if (login == 1) //�α��� �Ǿ��ִ� ���
	{
		printf("���� �α׾ƿ� �Ͻðڽ��ϱ�? [y/n] : ");
		
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
	else //�α����� �Ǿ����� ���� ���
	{
		printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.");
		char trash = getch();
	}

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 4�� �ɼ� ���� �Լ���

/*
* �̸�: ���� �б� �Լ�
* ���: ���� �о linked list�� �����Ѵ�.
* �޴°�: X
* ���ϰ�: ���� ������ ������ linked list�� ��� �������� ��.
*/
int FileSave(void)
{
	FILE* fp_words;
	fp_words = fopen("dic.txt", "r");
	NODE* ptr_head = NULL; //��� ������
	NODE* ptr_tail = NULL; //���� ������

	while (1)
	{
		//tmp�� ���ڿ� ����
		char hangul[11] = { 0 };
		char tmp[A] = { 0 };
		fscanf(fp_words, "%s", tmp); //���� ���ܾ� ����
		strcat(tmp, " ");
		char trash = getc(fp_words);
		fscanf(fp_words, "%s", hangul);
		strcat(tmp, hangul);
		trash = getc(fp_words); //���๮�� ������

		if (trash == -1)
		{
			break;
		}


		//tmp�� linked list�� �߰�
		if (ptr_head == NULL) //��尡 �߰��Ǿ� ���� �ʾҴ� ���
		{
			ptr_head = (NODE*)malloc(sizeof(NODE)); //��� �����Ϳ� ��� ����
			for (int j = 0; j < A; j++)
			{
				ptr_head->word[j] = tmp[j];
			}
			ptr_head->ptr_next = NULL;
			ptr_tail = ptr_head;
		}
		else //��尡 �߰��Ǿ� �ִ� ���
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
* �̸�: ���ڿ� ���� �Լ�
* ���: ù ���� ������ �����Ͱ� ����Ű�� ���ڿ����� ���̵� ������ �� ��° ������ �迭�� �����Ѵ�.
* �޴°�: ù ��° ���ڿ� ���̵� ����Ű�� ������, �� ���� ���ڿ� ���� ������ �迭
* ���ϰ�: X
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
* �̸�: ������ ���� �Լ�
* ���: linked list�� �������� ���������� �����Ѵ�. (���� ���� ���)
* �޴°�: linked list�� ��� ������ (ptr_head)
* ���ϰ�: X
*/
void AlpArray(NODE* ptr_head)
{
	NODE* ptr_start = ptr_head; //���� ��
	NODE* ptr_end = ptr_head;
	NODE* ptr_first; //�� ���� ��� ���� �� ���� ��
	NODE* ptr_second; //�� ���� ��� ���� �� ������ ��
	int num = 0; //�����ʹ� �� num �� ��带 �Ѿ�� ��.

	while ((ptr_end->ptr_next) != NULL) //ptr_end���� ������ ����� �ּҰ� ����ȴ�. (NULL �� ������ ������)
	{
		ptr_end = ptr_end->ptr_next;
		num++;
	}

	while (1) //�� �� ĭ�� �� ĭ �� ������. �� �� ĭ�� �����ȴ�.
	{
		ptr_first = ptr_start;
		ptr_second = ptr_start->ptr_next;

		while (1) //�ΰ��� ��� ��. �� �߿� �������� ���� ���� �������� ������.
		{
			//��
			char first[12] = { 0 };
			char second[12] = { 0 };

			StringRefine(ptr_first, first); //ù ���� ���ڿ� �ۼ��� �����Ͱ� ����Ű�� ���ڿ����� ���̵� ������ first�迭�� �����ϴ� �Լ�.
			StringRefine(ptr_second, second);

			//��ȯ
			int cmpvalue = strcmp(first, second);
			if (cmpvalue <= 0) //first�� ����� ���ڿ��� ���������� �����̰ų�, �� ���ڿ��� ������ ������ ���� ���
			{
				;
			}
			else //second�� ����� ���ڿ��� ���������� ������ ���. �� ������ ��ȯ�� ��� �Ѵ�.
			{
				char tmp_array[A];

				strcpy(tmp_array, ptr_first->word);
				strcpy(ptr_first->word, ptr_second->word);
				strcpy(ptr_second->word, tmp_array);				
			}

			//�ּ� ����
			ptr_first = ptr_second;
			if (ptr_second == ptr_end)
			{
				break;
			}
			ptr_second = ptr_second->ptr_next;
		}

		//ptr_end�� ���� ����� �����͸� ���� (�� ������ ������)
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
* �̸�: ���� ���, �Ǵ� �Լ�
* ���: ���ܾ� ���߱� ������ ��ü������ �����Ѵ�. (�ڵ尡 ������� ���� ����.)
* �޴°�: linked list�� ��� ������ (ptr_head)
* ���ϰ�: X
*/
void RunGame_Print(NODE* ptr_head, NODE_USER* ptr_user_head)
{
	NODE* p = ptr_head;

	int correct = 0; //������ ���� Ƚ��
	int total = 0; //������ �� ���� ��

	while (1)
	{
		//linked list���� �ѱۿ� ���� �����ͼ� ���� �����ϱ�
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

		//�ѱ� ����ϱ�
		printf("\n%s -> ", korean);

		//����� �� �Է¹ޱ�
		char userin[15] = { 0 };
		scanf("%s", userin);

		if (strcmp(userin, ".quit") == 0) //�Է��� ���ڿ��� .quit�� ���
		{
			//���� ���
			if (total == 0) //���� Ǭ ������ ���� ���
			{
				printf("\n������ ����� �� �����ϴ�. (Ǭ ���� : 0)\n���α׷��� �����մϴ�.\n");
			}
			else
			{
				printf("\n����� ������ %.2f���Դϴ�.", ((correct / (double)total) * 100));
				printf("\n���α׷��� �����մϴ�.\n");
			}

			//���α׷� ����
			LinkFree(ptr_head);
			LinkFree_User(ptr_user_head);
			exit(0);
		}
		else if (strcmp(userin, english) == 0) //�ùٸ� ���� �Է��� ���
		{
			printf("correct!\n");
			correct++;
			total++;
		}
		else //���� ������ ���� ���
		{
			printf("incorrect!\n");
			total++;
		}

		//linked list�� ���� ���� ����
		p = p->ptr_next;
		if (p == NULL)
		{
			LinkFree(ptr_head);
			LinkFree_User(ptr_user_head);
			printf("\n��� ������ Ǯ�����ϴ�!");
			printf("\n����� ������ %.2f���Դϴ�.", ((correct / (double)total) * 100));
			printf("\n���α׷��� �����մϴ�.\n");
			exit(0);
		}
	}

	return;
}

/*
* �̸�: ���� ���� �Լ�
* ���: ���ܾ� ���߱� ������ �����Ѵ�.
* �޴°�: linked list�� ��� ������ (ptr_head)
* ���ϰ�: X
*/
void RunGame(NODE* ptr_head, NODE_USER* ptr_user_head)
{
	//���� �������̽� ���
	while (1)
	{
		system("cls");
		printf(">> ���� �ܾ� ���߱� ���α׷� <<\n1. ���� �ܾ� ���߱� 2. ���α׷� ����\n\n��ȣ�� �����ϼ��� : ");
		int option = getch();

		if (option == '1') //���� �ܾ� ���߱� ����
		{
			printf("1");
			//���� ����
			RunGame_Print(ptr_head, ptr_user_head);
		}
		else if (option == '2') //���α׷� ����
		{
			LinkFree(ptr_head);
			LinkFree_User(ptr_user_head);
			printf("2\n\n���α׷��� �����մϴ�.\n");
			exit(0);
		}
		else //�߸��� �ɼ��� �Էµ� ���. �ٽ� �Է¹ޱ�
		{
			;
		}
	}

	return;
}

/*
* �̸�: ���� �ܾ� ���߱� �Լ�
* ���: 4�� �ɼ� �Է� �� �۵��� �Լ����� ������� ȣ���Ѵ�.
* �޴°�: X
* ���ϰ�: X
*/
void EnglishGame(NODE_USER* ptr_user_head)
{
	NODE *ptr_head; //��� �����Ϳ� ����� ���� ������ ������. ��, ��� �����Ϳ� ������.
	ptr_head = (NODE*)FileSave(); //������ �о linked list�� �����ϴ� �Լ�. ��� �������� ���� �����Ѵ�.
	AlpArray(ptr_head); //linked list�� ����� ������ ���ĺ� ������� �����ϴ� �Լ�.
	RunGame(ptr_head, ptr_user_head);

	return;
}


/*
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
* ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
// 5�� �ɼ� ���� �Լ���

/*
* �̸�: ȸ�� ���� �Լ�
* ���: ������ ������ ȸ�� Ż�� �� �α��� �Ǿ��ִ� ������� ������ ������ ���Ϸ� ��ü�Ѵ�.
* �޴°�; loginfile�� ��� �ִ� ������ ������ linked list�� ��� ������
* ���ϰ�: X
*/
void UserWithdraw_delete(NODE_USER* ptr_user_head)
{
	//linked list���� ���� ������� ������ ����ִ� ��� Ž��
	NODE_USER* p = ptr_user_head;
	NODE_USER* p_before = NULL; //p ���� ������

	char tmp_id[15] = { 0 };

	int u = 0;
	while (p->userdata[u] != ' ') //tmp_id���� p�� ����Ű�� ����� ���ڿ��� ����ȴ�.
	{
		tmp_id[u] = p->userdata[u];
		u++;
	}

	while (strcmp(username_id, tmp_id) != 0) //username_id�� ����� ���ڿ��� p�� ����Ű�� ����� ���ڿ��� ���ٸ� ������ �ݺ���
	{
		p_before = p;
		p = p->ptr_next; //p���� �ݺ����� ������ ������ ��ȯ�� ����� �ּҰ� ����Ǿ� �ִ�.
		
		int u2 = 0;
		while (p->userdata[u2] != ' ') //tmp_id���� p�� ����Ű�� ����� ���ڿ��� ����ȴ�.
		{
			tmp_id[u2] = p->userdata[u2];
			u2++;
		}
		tmp_id[u2] = 0;
	}

	//�ش� ��带 ��ȯ�ϰ�, �ش� ����� �� �� ��带 ���� ����
	if (p == ptr_user_head) //p�� ����� ���
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
	else //p�� ��尡 �ƴ� ���
	{
		NODE_USER* value2;

		value2 = p;
		p_before->ptr_next = p->ptr_next;
		free(value2);
	}

	//w�ɼ��� ����ؼ� ������ �� ��, ����� linked list�� ������ �ۼ�
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
* �̸�: ȸ�� Ż�� �Լ�
* ���: ȸ�� Ż�� �����Ѵ�.
* �޴°�; loginfile�� ��� �ִ� ������ ������ linked list�� ��� ������
* ���ϰ�: X
*/
void UserWithdraw(NODE_USER* ptr_user_head)
{
	if (login == 1) //�α��� �Ǿ��ִ� ���
	{
		system("cls");
		printf("���� ȸ�� Ż�� �����Ͻðڽ��ϱ�? [y/n] : ");
		
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
	else //�α��� �Ǿ����� ���� ���
	{
		system("cls");
		printf("�α��� ���°� �ƴմϴ�.\n");
		char trash = getch();
	}

	return;
}