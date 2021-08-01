#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<Windows.h>

/*���Ͽ��� ID, PW, name �޾ƿ��� �迭�� save_ID, save_PW, save_name�� ����*/

typedef struct member
{
	char ID[20];
	char PW[30];
	char name[30];
	struct member* next;
}member;
//���Ͽ��� ȸ������ ���Ḯ��Ʈ�� ����
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
//���ο� ȸ������ ���� ���Ḯ��Ʈ�� ����, ���Ͽ� ����
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
//���̵��ߺ�üũ
bool IDcheck(char check_ID[])//���̵� �ߺ� Ȯ��
{
	FILE* check = fopen("C:\\test\\IDPW.txt", "r");

	char save_ID[10];
	char save_PW[20];
	char save_name[20];

	if (check == NULL)
	{
		printf("��밡���� ���̵� �Դϴ�.\n");
		return true;
	}

	while (1)
	{
		if (feof(check)) break;

		fscanf(check, "%s %s %s\n", save_ID, save_PW, save_name);
		save_ID[strlen(save_ID) + 1] = '\0';

		if (strcmp(save_ID, check_ID) == 0)
		{
			printf("�̹� �����ϴ� ���̵� �Դϴ�.\n");
			return false;
		}
	}

	printf("��밡���� ���̵��Դϴ�.\n");
	fclose(check);
	return true;
}
//��й�ȣ �ߺ�üũ
bool namecheck(char check_name[])//�̸� �ߺ� Ȯ��
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
			printf("�̹� ������ ȸ���Դϴ�.\n");
			printf("�޴��� ���ư��ϴ�.\n");
			Sleep(10000);
			system("cls");
			return false;
		}
	}
	fclose(check);
	return true;
}
//�α���
bool logincheck = 0; // 0 : ��α���, 1 : �α���
void login(char login_ID[], char login_PW[]) // �α���
{
	FILE* check = fopen("C:\\test\\IDPW.txt", "r");

	char save_ID[20];
	char save_PW[30];
	char save_name[30];

	if (logincheck == true)
	{
		printf("�̹� �α��� �Ǿ��ֽ��ϴ�.\n");
		return;
	}

	if (check == NULL)
	{
		printf("������ ����־� ȸ�������� �������� �ʽ��ϴ�.\n");
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
	printf("�߸��� ���̵��̰ų� Ʋ�� ��й�ȣ�Դϴ�.\n");
	printf("ó��ȭ������ ���ư��ϴ�.\n");
	Sleep(500);
	system("cls");
	return;
}
//�α׾ƿ�
void logout()// �α׾ƿ�
{
	if (logincheck == false)
	{
		printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.\n");
		Sleep(500);
		system("cls");
	}
	else
	{
		printf("���� �α׾ƿ� �Ͻðڽ��ϳ�? [y/n]: ");
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
//�������α׷�
void quiz_start(char* word_eng[], char* word_mean[])
{
	double score = 0; //����
	int count = 0;//���� ����
	int correct = 0;//���� ���� ����

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
	printf("����� ������ %.1f���Դϴ�.\n", score);
	Sleep(1000);
	system("cls");
}
void quiz_setting()
{
	char* word_eng[101] = {0};
	char* word_mean[101] = {0};


	FILE* word = fopen("C:\\test\\dic.txt", "r");
	//�ܾ� ����
	while (1)
	{
		static int cnt = 0;
		char buffer_eng[40]; //���Ͽ� �ִ� �ܾ �ҷ��� ������ �迭, �ܾ�����ϱ� 40�ڰ� ������ �ʴ´�.
		char buffer_mean[40];

		if (feof(word))
		{
			break; //���� ���̸� ����
			cnt = 0;
		}
		fscanf(word, "%s %s\n", buffer_eng, buffer_mean); //���Ͽ� �ִ� �ܾ� ����

		char* input_eng = (char*)malloc((sizeof(char)) * (strlen(buffer_eng) + 1)); //�ܾ��� ���̸�ŭ ���� �Ҵ�
		strcpy(input_eng, buffer_eng);//�ܾ� ����
		word_eng[cnt] = input_eng; //�ܾ�����

		char* input_mean = (char*)malloc((sizeof(char)) * (strlen(buffer_mean) + 1));
		strcpy(input_mean, buffer_mean);
		word_mean[cnt] = input_mean;
		cnt++;
	}
	fclose(word);

	char* key_eng;
	char* key_mean;
	int i, j;
	// �������ķ� �ܾ� ����
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
	printf(">> ���� �ܾ� ���߱� ���α׷� <<\n");
	printf("1. ���� �ܾ� ���߱� 2. ���α׷� ����\n");
	printf("��ȣ�� �����ϼ���: ");
	scanf(" %c", &option);
	if (option == '1')
		quiz_start(word_eng, word_mean);
	else if (option == '2')
		return;
}

//ȸ��Ż��
void removemember(member* target, char ID[])
{
	char check;
	printf("���� ȸ���� Ż���Ͻðڽ��ϱ�? [y/n]: ");
	scanf(" %c", &check);
	if (check == 'n')
		return;

	member* deletemember = target->next; // ���� ����� ���� ��� �ּҸ� ���� - ���ϻ�����
	while (deletemember != NULL)
	{
		if (strcmp(deletemember->ID, ID) == 0)
		{
			target->next = deletemember->next; // ���� ����� ���� ��忡 ������ ����� ���� ��带 ����
			free(deletemember);
			logincheck = false;
			return;
		}
		target = target->next;
		deletemember = deletemember->next;
	}
	//�α��λ��¿��� ����Ǳ� ������ ���̵� �������� �ʴ� ���� ������� ����
	
}
//Ż���� ���� �ٽ� ����
void save(member* target)
{
	member* temp = target->next;// ���� ����� ���� ��� �ּҸ� ����
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
	member* firstmember = (member*)malloc(sizeof(member)); // head���
	firstmember->next = NULL;
	
	loadmember(firstmember);

	char input_ID[10]; //ȸ�����Խ� ID �Է�
	char input_PW[20]; //ȸ�����Խ� PW �Է�
	char input_name[10]; //ȸ�����Խ� �̸� �Է�

	char login_ID[10];
	char login_PW[20];

	char option = ' '; //�ɼǼ��� ����
	while (1)
	{
		if (logincheck == true)
		{
			system("cls");
			printf("====20211402 ��ǻ���к� ��ο�====\n");
			printf("==================================\n");
			printf("=========== 2021 SPLUG ===========\n");
			printf("======================== %-10s\n", login_ID);
			printf("==================================\n");
			printf("=              �޴�              =\n");
			printf("==================================\n");
			printf("        1. ȸ������\n");
			printf("        2. �α���\n");
			printf("        3. �α׾ƿ�\n");
			printf("        4. ���� �ܾ� ���߱�\n");
			printf("        5. ȸ�� Ż��\n");
			printf("        6. ���α׷� ����\n");
			printf("==================================\n");
			printf("-\n");
			printf("-");
		}
		else
		{
			printf("====20211402 ��ǻ���к� ��ο�====\n");
			printf("==================================\n");
			printf("=========== 2021 SPLUG ===========\n");
			printf("==================================\n");
			printf("==================================\n");
			printf("=              �޴�              =\n");
			printf("==================================\n");
			printf("        1. ȸ������\n");
			printf("        2. �α���\n");
			printf("        3. �α׾ƿ�\n");
			printf("        4. ���� �ܾ� ���߱�\n");
			printf("        5. ȸ�� Ż��\n");
			printf("        6. ���α׷� ����\n");
			printf("==================================\n");
			printf("-\n");
			printf("-");
		}
		scanf(" %c", &option);

		switch (option)
		{
		case '1':
			system("cls");
			printf("ȸ������ ������\n");
			while (1)
			{
				bool result_IDcheck = true; // �ߺ� : fasle, ���ߺ� : true
				printf("ID : ");
				scanf(" %s", input_ID);//���� ������ ��ĭ ���

				result_IDcheck = IDcheck(input_ID);
				if (result_IDcheck == true)
					break;
			}
			printf("PW : ");
			scanf("%s", input_PW);

			printf("�̸� : ");
			scanf("%s", input_name);
			{
				bool result_namecheck = true;
				result_namecheck = namecheck(input_name);
				if (result_namecheck == false)
					continue;
				else
					addmember(firstmember, input_ID, input_PW, input_name); // ȸ������ ���� ����
			}
			break;
		case '2':
			system("cls");

			if (logincheck == true)
			{
				printf("�̹� �α����ϼ̽��ϴ�.\n");
				Sleep(700);
				continue;
			}

			printf("�α���\n");
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
				printf("�α��� ���°� �ƴմϴ�.\n");
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
				printf("�α��� ���°� �ƴմϴ�.\n");
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
			printf("�����ϼ̽��ϴ�!\n");
			exit(0);
			break;
		default:
			{
				printf("�޴��� �����ϴپ�!!!!!!!\n");
				Sleep(700);
				system("cls");
			}
			break;
		}	
	}

	return 0;
}