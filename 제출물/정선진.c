#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int count;
char log_detect[16];
int source;

struct Person{
    char ID[16];
    char NAME[10];
    char PASSWORD[11];
};

void enrollment(struct Person *num){

    printf("ȸ������ ������\n");
    FILE *USER_INFO = fopen("user.txt", "a");
    fputs("", USER_INFO);
    fclose(USER_INFO);
    
    char str[100],ans[100];
    int num_ = 0,pass=0;
    ONE:
        printf("���̵�: ");
        scanf("%s", num[count+1].ID);
        strcpy(ans, num[count+1].ID);

        num_ = 0;
        pass = 0;

        //���Ͽ���
        USER_INFO = fopen("user.txt", "r");
        if (USER_INFO == NULL) {
            printf("==ERROR==");
        }
        
        while (!feof(USER_INFO)) {
            num_++;
            fgets(str, 100, USER_INFO);

            if (strstr(str, ans) != NULL) {
                printf("�ߺ��� ���̵��Դϴ�.\n");
                pass++;
            }
            if(pass != 0){
                goto ONE;
            }
        }

        if (pass == 0) printf("��밡���� ���̵��Դϴ�.\n");
        fclose(USER_INFO);
    
    USER_INFO = fopen("user.txt", "a");
    fputs(num[count+1].ID, USER_INFO);
    fputs("\n",USER_INFO);
    fclose(USER_INFO);
    printf("\n��й�ȣ: ");
    scanf("%s", num[count+1].PASSWORD);
    printf("\n�̸�: ");
    scanf("%s", num[count+1].NAME);
    count++;
}

void log_in(struct Person *num){
    char *user_tmp;
    printf("ID: ");
    scanf("%s", user_tmp);
    for(int i = 0; i<100; i++){
        if(strcmp(user_tmp, num[i].ID)==0){
            char *hello = malloc(sizeof(char) * 10);
            while(1){
                printf("PASSWORD: ");
                scanf("%s", hello);
                if(strcmp(num[i].PASSWORD, hello)==0){
                    printf("�α��� ����! ����ȭ������ �̵��մϴ�.(3�� ���̵�)\n");
                    strcpy(log_detect, num[i].ID);
                    source = 1;
                    Sleep(3000);
                    break;
                }
                else{
                    printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
                }
            }
            break;
        }
    }

}
void drop_out(struct Person *num){
    printf("���� �������� ���� ����Դϴ�. ����ȭ������ ���ư��ϴ�.(3�ʵ� �̵�)\n");
    Sleep(3000);
}

void match_words(struct Person *num){
    printf("���� �������� ���� ����Դϴ�. ����ȭ������ ���ư��ϴ�.(3�ʵ� �̵�)\n");
    Sleep(3000);
}

int main(void){
    while(1){
        struct Person num[10];
        int sys = 0;
        //�ʱ�ȭ�� ����
        if(source == 0){
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
            printf(": ");
            scanf("%d", &sys);
        }
        if(source == 1){
            int a = strlen(log_detect);
            printf("==================================\n");
            printf("=========== 2021 SPLUG ===========\n");
            for(int i = 1; i < 30-strlen(log_detect); i++){
                printf("=");
            }
            printf("%s", log_detect);
            printf("\n");
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
            printf(": ");
            scanf("%d", &sys);
        }

        if(sys==1){
            enrollment(num);
        }
        else if(sys==2){
            log_in(num);
        }
        else if(sys==3){
            if(source == 0){
                printf("�α��� ���� �ʾҽ��ϴ�. �ٽ� �õ��ϼ���.(3�� �� ����ȭ������ �̵�)\n");
                Sleep(3000);
            }
            else{
                getchar();
                printf("���� �α׾ƿ� �Ͻðڽ��ϱ�? [y/n]: ");
                char a;
                scanf("%c", &a);
                
                if(a == 'y'){
                    printf("�α׾ƿ� �Ǿ����ϴ�.(3�� �� ����ȭ������ �̵�)\n");
                    Sleep(3000);
                    source = 0;
                }
                else{
                    printf("�α׾ƿ��� �����߽��ϴ�.(3�� �� ����ȭ������ �̵�)\n");
                    Sleep(3000);
                }
            }
        }
        else if(sys==5){
            drop_out(num);
        }
        else if(sys==4){
            match_words(num);
        }
        else if(sys==6){
            printf("���α׷��� ����˴ϴ�.\n");
            Sleep(2000);
            return 0;
        }
        else{
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        }
    }
}


/* �ߺ�Ȯ�� ����

1. �Է��� ���̵��� ���� �ԷµǾ��� �� �˻�.
2-1. ���ٸ� �״�� ���(��)
2-2. �ִٸ� 3���� �Ѿ
3. �ߺ�ó���� ���ڿ��� ����. �ش� ���ڿ� ���� �� ����ڰ� �Է��� ���ڿ� ���� ���� ��ġ.
4-1. ������ ���ڿ��� ������ �ߺ��˻� �ٽ� ����. ���ٸ� ���Ͽ� �ٽ� �Է�(��).
4-2. �ִٸ� �ߺ��� ���ɼ� ����.

==>> �ߺ� �˻� ����. �ʹ� ����� ���� ���� ����.
*/

/*�ߺ�Ȯ�� ���� Ver.2

1. txt���Ͽ��� ���ڿ��� �� �پ� �о�, �� ���ڿ��� ������ ���ڿ��� ����.
2. ù��° ���ڿ����� ���ʷ� ��.
3-1 strcmp�� ���� 0���� ������ ����, 4�� �̵�.
3-2 strcmp�� ���� ���� ������ ���.
4. "�ߺ��Դϴ�."�� ����ϸ�, ���̵� �ٽ� �Է¹޴´�.

==>> ��������. ������ ù ��° ������� ���ܵ� ���� �����ϴ�.
*/