#include <stdio.h>
#include <stdlib.h>

void join();
void english();

int main(void)
{
	int option;
	printf("================================\n");
	printf("========== 2021 SPLUG ==========\n");
	printf("================================\n");
	printf("================================\n");
	printf("=             �޴�             =\n");
	printf("================================\n");
	printf("         1. ȸ�� ����\n");
	printf("         2. �α���\n");
	printf("         3. �α׾ƿ�\n");
	printf("         4. ���� �ܾ� ���߱�\n");
	printf("         5. ȸ�� Ż��\n");
	printf("         6. ���α׷� ����\n");
	printf("================================\n");
	printf(":");
	scanf_s("%d", &option);
	if (option == 1)
	{
		join();
	}
}

void join()
{

	FILE* fp = NULL;
	fp = fopen("join.txt", "w");
	printf("ȸ������ ������");
	fprintf("���̵�: ");
	fscanf_s("%s", &)
}

void english();
{
	int eng;
	printf("<���� �ܾ� ���߱� ���α׷�>\n");
	printf("1. ���� �ܾ� ���߱� 2. ���α׷� ����\n");
	
	printf("��ȣ�� �����ϼ���: ");
	scanf("%d", &eng);
	if (eng == 1)
	{
	    
	}

}