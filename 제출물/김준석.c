#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#define B 30
int state=0;                                                                 //로그인 상태를 기록하는 전역변수
int score=0;                                                                 //점수
void sign_Up();                                                         //회원 가입 첫 화면 함수
void join_ID(char* ID);                                                 //회원가입 - 아이디
void join_PW(char* PW);                                                 //회원가입 - 비밀번호 입력
void join_NAME(char* name);                                             //회원가입 - 이름 입력
void log_start();                                                       //로그인 성공시 메뉴출력 함수
void start_nt_login();                                                  //로그인 상태가 아닐때 오류 출력 함수
void start();                                                           //로그인 전 메뉴출력 함수
void login();                                                           //로그인 함수
void newnode(char* ID,char* PW);                                        //로그인용 노드추가함수
void logout();                                                          //로그 아웃 함수
void sorting_words(char* words[]);                                      //단어를 알파벳 순으로 정렬
void playing();                                                         //정렬된 단어들을 가지고 게임을 진행
void next_order(int t);                                                 //playing함수에서 필요한 함수 - 중간 점검(점수출력/게임지속여부)
void check_again_withdraw();                                            //회원탈퇴 의사결정 함수
void withdraw();                                                        //회원탈퇴 함수
void clear_file();                                                      //login_info1.txt파일 초기화 함수
void retouch(char* ID,char* PW,char* NAME);                             //회원탈퇴하지 않을 정보 임시 저장하는 함수
void file_dispatch();                                                   //임시 파일(login_info1.txt)에서 본파일(login_info.txt)로 내용을 옮기는 함수
void end_of_program();                                                  //프로그램 끝내는 함수
int getch(void);                                                        //메뉴 화면에서 입력을 받는 함수
typedef struct NODE{                                                    //회원탈퇴에 쓰이는 구조체
        char id3[20];
        char pw3[20];
        struct NODE* next;
}node;
node* head;     //전역변수
char id[20]; //로그인 혹은 회원 가입시 저장하는 id
char pw[20]; //로그인 혹은 호원 가입시 저장하는 pw
int main()
{
        char command;
        if(state==0)
                start();
        if(state==1)
                log_start(id);
        if(state==2)
                start_nt_login();
        command=getch();
        switch(command){
                case '1':
                        sign_Up();
                        break;
                case '2':
                        login();
                        break;
                case '3':
                        if(state==1)
                                logout();
                        else{
                                state=2;
                                main();
                        }
                        break;
                case '4':
                        playing();
                        break;
                case '5':
                        if(state==1){
                                check_again_withdraw();
                                main();
                        }
                        else{
                                state=2;
                                main();
                        }
                        break;
                case '6':
                        end_of_program();
                        break;
                default:
                        printf("잘못입력하셨습니다.");
        }
        return 0;
}
void join_ID(char* ID)
{
        system("clear");
        printf("회원가입 페이지\n");
        while(1)
        {
                int i=0;
                char a;
                char temp[100];
                char name[20];
                printf("아이디 : ");
                scanf("%s",temp);
                getchar();
                ID=(char*)calloc(strlen(temp)+1,sizeof(char));
                strcpy(ID,temp);
                FILE* in;
                in=fopen("login_info.txt","r");
                while((a=getc(in))!=EOF){
                        if(a=='^'){
                                fscanf(in,"%s",name);
                        }
                        break;
                }
                fclose(in);
                i=strcmp(name,ID);
                if(i==0){
                        printf("이미 존재하는 아이디 입니다.\n");
                }
                else{
                        break;
                }
        }
        printf("사용가능한 아이디 입니다.\n");
        FILE* fp;
        fp=fopen("login_info.txt","a");
        fprintf(fp,"^");
        fprintf(fp,"%s",ID);
        fprintf(fp," ");
        fclose(fp);
        strcpy(id,ID);
        free(ID);
        return;
}
void join_PW(char* PW)
{
        char temp[100];
        printf("비밀번호 : ");
        scanf("%s",temp);
        getchar();
        PW=(char*)calloc(strlen(temp)+1,sizeof(char));
        strcpy(PW,temp);
        FILE* in;
        in=fopen("login_info.txt","a");
        fprintf(in,"-");      //%를 입력시킬 수 없다.
        fprintf(in,"%s",PW);
        fprintf(in," ");
        fclose(in);
        free(PW);
}
void join_NAME(char* name)
{
        char temp[100];
        printf("이름 : ");
        scanf("%s",temp);
        getchar();
        name=(char*)calloc(strlen(temp)+1,sizeof(char));
        strcpy(name,temp);
        FILE* in;
        in=fopen("login_info.txt","a");
        fprintf(in,"/");
        fprintf(in,"%s",name);
        fprintf(in," ");
        fprintf(in,"|");
        fclose(in);
        free(name);
}
void log_start()  //로그인을 성공했을 경우 출력할 화
{
        system("clear");
        int a,b;
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        for(int j=0;j<12;j++)
        {
                printf("=");
        }
        printf("SPLUG2021");
        for(int k=0;k<13;k++)
        {
                printf("=");
        }
        printf("\n");
        a=strlen(id);
        b=34-a;
        for(int h=0;h<b;h++)
        {
                printf("=");
        }
        for(int g=0;g<a+1;g++)
        {
                printf("%c",id[g]);
        }
        printf("\n");
        for(int j=0;j<34;j++)
        {
                printf("=");
        }
        printf("\n");
        printf("=");
        for(int l=0;l<14;l++)
        {
                printf(" ");
        }
        printf("메뉴");
        for(int i=0;i<14;i++)
        {
                printf(" ");
        }
        printf("=");
        printf("\n");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        printf("        1. 회원가입\n");
        printf("        2. 로그인\n");
        printf("        3. 로그아웃\n");
        printf("        4. 영어 단어 맞추기\n");
        printf("        5. 회원 탈퇴\n");
        printf("        6. 프로그램 종료\n");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        printf(":");

}
void start()                  //로그인 상태가 아닐때 출력하는 메뉴
{
        system("clear");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        for(int j=0;j<12;j++)
        {
                printf("=");
        }
        printf("SPLUG2021");
        for(int k=0;k<13;k++)
        {
                printf("=");
        }
        printf("\n");
        for(int h=0;h<34;h++)
        {
                printf("=");
        }
        printf("\n");
        for(int j=0;j<34;j++)
        {
                printf("=");
        }
        printf("\n");
        printf("=");
        for(int l=0;l<14;l++)
        {
                printf(" ");
        }
        printf("메뉴");
        for(int i=0;i<14;i++)
        {
                printf(" ");
        }
        printf("=");
        printf("\n");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        printf("        1. 회원가입\n");
        printf("        2. 로그인\n");
        printf("        3. 로그아웃\n");
        printf("        4. 영어 단어 맞추기\n");
        printf("        5. 회원 탈퇴\n");
        printf("        6. 프로그램 종료\n");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        printf(":");
}
void start_nt_login()
{
        system("clear");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        for(int j=0;j<12;j++)
        {
                printf("=");
        }
        printf("SPLUG2021");
        for(int k=0;k<13;k++)
        {
                printf("=");
        }
        printf("\n");
        for(int h=0;h<34;h++)
        {
                printf("=");
        }
        printf("\n");
        for(int j=0;j<34;j++)
        {
                printf("=");
        }
        printf("\n");
        printf("=");
        for(int l=0;l<14;l++)
        {
                printf(" ");
        }
        printf("메뉴");
        for(int i=0;i<14;i++)
        {
                printf(" ");
        }
        printf("=");
        printf("\n");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        printf("        1. 회원가입\n");
        printf("        2. 로그인\n");
        printf("        3. 로그아웃\n");
        printf("        4. 영어 단어 맞추기\n");
        printf("        5. 회원 탈퇴\n");
        printf("        6. 프로그램 종료\n");
        for(int i=0;i<34;i++)
        {
                printf("=");
        }
        printf("\n");
        printf(":");
        printf("\n로그인 상태가 아닙니다.");
}
void login()
{
        system("clear");
        char* ID;
        char* PW;
        char temp[100]={0},file_str[100];
        int q=0,a;
        char c;
        head=(node*)malloc(sizeof(node));
        head->next=NULL;
        printf("로그인\n");
        printf("아이디 : ");
        scanf("%s",temp);
        getchar();
        a=strlen(temp);
        ID=(char*)calloc(strlen(temp)+1,sizeof(char));
        strcpy(ID,temp);

        for(int i=0;i<a;i++)
        {
                temp[i]='\0';
        }
        printf("비밀번호 : ");
        scanf("%s",temp);
        getchar();
        PW=(char*)calloc(strlen(temp)+1,sizeof(char));
        strcpy(PW,temp);                                 //ID,PW저장
        newnode(ID,PW);
        struct NODE *curr=head->next;
        FILE* in;
        in=fopen("login_info.txt","r");
        if (in == NULL) {
                printf("파일 열기에 실패했습니다");
                return;
        }
        while ((c=getc(in))!=EOF)
        {
                if(c=='|')
                {
                if (strstr(file_str,curr->id3) != NULL) {
                        if(strstr(file_str,curr->pw3)!=NULL)
                        {
                                state=1;
                                strcpy(id,ID);
                                strcpy(pw,PW);
                                curr=head->next;
                                free(curr);
                                free(ID);
                                free(PW);
                                free(head);
                                main();
                                return;
                        }
                }
                for(int i=0;i<q;i++)
                {
                        file_str[i]='\0';
                }
                q=0;
                continue;
                }
                file_str[q]=c;
                q++;
        }
        fclose(in);
        printf("아이디나 비밀번호 입력이 잘못되었습니다.3초후 재시도 하십시오.\n");
        sleep(3);
        login();
        return;
}

void newnode(char* ID,char* PW)
{
        node* node1;
        node1=(node*)malloc(sizeof(node));
        head->next=node1;
        node1->next=NULL;
        strcpy(node1->id3,ID);
        strcpy(node1->pw3,PW);
        return;
}
void logout()
{
        char c;
        printf("정말 로그아웃하시겠습까? [y/n] : ");
        scanf("%c",&c);
        getchar();
        if(c=='y'){
                state=0;
                main();
                return;
        }
        if(c=='n'){
                return;
        }
}
void end_of_program()
{
        system("clear");
        printf("\n다음에 또 만나요!\n");
        exit(1);
}
void sorting_words(char* words[])
{
        int i,j;
        int num=0;
        char* tmp;
        char str[50];
        FILE* in;
        in=fopen("match_word.txt","r");
        while(!feof(in))
        {
                fgets(str,B,in);
                words[num]=(char*)calloc(strlen(str)+1,sizeof(char));
                strcpy(words[num],str);
                num++;
        }


        for(i=0;i<num;i++)
                for(j=num-1;j>i;j--)
                        if(strcmp(words[j-1],words[j])>0)
                        {
                                tmp=words[j-1];
                                words[j-1]=words[j];
                                words[j]=tmp;
                        }
        fclose(in);
        FILE* fp;
        fp=fopen("match_word.txt","w");
        for(int a=0;a<102;a++){
                fprintf(in,"%s",words[a]);
        }
        fclose(fp);
        return;                             //알파벳 순서대로 파일이 다시 써짐.
}
void playing()
{
        system("clear");
        char* words[40];
        int inp;
        printf(">>영어 단어 맞추기 프로그램<<\n");
        printf("1. 영어 단어 맞추기 2. 프로그램 종료\n");
        scanf("%d",&inp);
        if(inp==1)
        {
                printf(">>총 101문제로 20문제씩 풀어서 점수를 측정합니다.<<\n");
                printf(">>20문제를 다 풀기 전에 종료하면 한 문제당 5점으로, 나머지 문제는 0점 처리됩니다<<\n");
                sorting_words(words);    //알파벳 순서대로 정렬 됨.
        }
        else
                return;
        char english[20];
        char korean[20];
        char temp[20];
        int t=1;
        FILE* in;
        in=fopen("match_word.txt","r");
        while(!feof(in)){
                fscanf(in,"%s",english);
                fscanf(in,"%s",korean);
                printf("%d. ",t);
                printf("%s",korean);
                printf("->");
                scanf("%s",temp);
                getchar();
                if(strcmp(temp,".quit")==0){
                        printf("\n당신의 점수는 %d점입니다.\n",score);
                        exit(1);
                }
                if(strcmp(english,temp)==0){
                        printf("\ncorrect!\n");
                        score+=5;
                }
                else{
                        printf("\nincorrect!\n");
                }
                for(int i=0;i<20;i++){
                        for(int j=0;j<20;j++){
                                english[i]='\0';
                                korean[j]='\0';
                        }
                }
                switch(t){
                        case 20:
                        case 40:
                        case 60:
                        case 80:
                                next_order(t);
                                break;
                }
                if(t==102){
                        printf("수고하셨습니다.\n");
                        printf("당신의 점수는 %d점입니다",score);
                        exit(1);
                }
                ++t;
        }
        return;
}

void next_order(int t)
{
        char mid;
        char quit;
        if(t==20){
                system("clear");
                printf("총 20문제를 풀었습니다. 더 푸시겠습니까? y혹은n을 입력하세요\n");
                scanf("%c",&mid);
                if(mid=='y'){
                        printf("다음 20문제를 시작합니다\n");
                        printf("지금까지의 점수는 %d점 입니다.\n",score);
                        score=0;
                        return;
                }
                if(mid=='n'){
                        printf("점수는 %d점 입니다.\n",score);
                        exit(1);
                }
        }
        if(t==40){
                printf("총 40문제를 풀었습니다. 더 푸시겠습니까? y혹은n을 입력하세요\n");
                scanf("%c",&mid);
                if(mid=='y'){
                        printf("다음 20문제를 시작합니다\n");
                        printf("지금까지의 점수는 %d점 입니다.\n",score);
                        score=0;
                        return;
                }
                if(mid=='n'){
                        printf("점수는 %d점 입니다.\n",score);
                        score=0;
                        exit(1);
                }
        }
        if(t==60){
                printf("총 60문제를 풀었습니다. 더 푸시겠습니까? y혹은n을 입력하세요\n");
                scanf("%c",&mid);
                if(mid=='y'){
                        printf("다음 20문제를 시작합니다\n");
                        printf("지금까지의 점수는 %d점 입니다.\n",score);
                        score=0;
                        return;
                }
                if(mid=='n'){
                        printf("점수는 %d점 입니다.\n",score);
                        score=0;
                        exit(1);
                }
        }
        if(t==80){
                printf("총 80문제를 풀었습니다. 더 푸시겠습니까? y혹은n을 입력하세요\n");
                scanf("%c",&mid);
                if(mid=='y'){
                        printf("다음 21문제를 시작합니다\n");
                        printf("지금까지의 점수는 %d점 입니다.\n",score);
                        score=0;
                        return;
                }
                if(mid=='n'){
                        printf("점수는 %d점 입니다.\n",score);
                        score=0;
                        exit(1);
                }
        }
        else
                return;
}

void sign_Up()
{
        char* ID;
        char* PW;
        char* name;
        join_ID(ID);
        join_PW(PW);
        join_NAME(name);


        main();
}
void withdraw()
{
        clear_file();
        FILE* in;
        char a;
        char ID[20];
        char PW[20];
        char NAME[20];
        in=fopen("login_info.txt","r");
        while((a=getc(in))!=EOF){
                if(a=='^'){
                        fscanf(in,"%s",ID);
                }
                if(a=='-'){
                        fscanf(in,"%s",PW);
                }
                if(a=='/'){
                        fscanf(in,"%s",NAME);
                }
                if(a=='|'){
                        if(strcmp(id,ID)==0){
                                if(strcmp(pw,PW)==0){
                                        for(int j=0;j<20;j++){
                                                for(int k=0;k<20;k++){
                                                        for(int l=0;l<20;l++){
                                                                ID[j]='\0';
                                                                PW[k]='\0';
                                                                NAME[l]='\0';
                                                        }
                                                }
                                        }
                                }
                        }
                        else{
                                retouch(ID,PW,NAME);
                                for(int j=0;j<20;j++){
                                        for(int k=0;k<20;k++){
                                                for(int l=0;l<20;l++){
                                                        ID[j]='\0';
                                                        PW[k]='\0';
                                                        NAME[l]='\0';
                                                }
                                        }
                                }
                        }
                }
        }
        fclose(in);
        file_dispatch();
        return;
}
void check_again_withdraw()
{
        char a;
        printf("\n진짜 회원탈퇴 하시겠습니까? 복구불가 입니다. [y/n] : ");
        scanf("%c",&a);
        getchar();
        if(a=='y'){
                state=0;
                withdraw();
        }
        if(a=='n'){
                state=1;
                return;
        }
}
void clear_file()
{
        FILE* cl;
        cl=fopen("login_info1.txt","w");
        fclose(cl);
}
void retouch(char* ID,char* PW,char* NAME)
{
        char a;
        FILE* op;
        op=fopen("login_info1.txt","a");
        fprintf(op,"^");
        fprintf(op,"%s",ID);
        fprintf(op," ");
        fprintf(op,"-");
        fprintf(op,"%s",PW);
        fprintf(op," ");
        fprintf(op,"/");
        fprintf(op,"%s",NAME);
        fprintf(op,"|");
        fclose(op);
        return;
}
void file_dispatch()
{
        char c;
        char file[200];
        int f=0;
        FILE* rw;
        rw=fopen("login_info.txt","w");
        fclose(rw);
        FILE* fp;
        fp=fopen("login_info1.txt","r");
        while((c=fgetc(fp))!=EOF){
                file[f]=c;
                f++;
        }
        FILE* gg;
        gg=fopen("login_info.txt","a");
        for(int i=0;i<f;i++){
                fprintf(gg,"%c",file[i]);
        }
        fclose(fp);
        fclose(gg);
        return;
}
int getch() {

        int ch;
        struct termios buf;
        struct termios save;
        tcgetattr(0, &save);
        buf = save;
        buf.c_lflag &= ~(ICANON | ECHO);
        buf.c_cc[VMIN] = 1;
        buf.c_cc[VTIME] = 0;
        tcsetattr(0, TCSAFLUSH, &buf);
        ch = getchar();
        tcsetattr(0, TCSAFLUSH, &save);
        return ch;
}
