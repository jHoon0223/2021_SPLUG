#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student{
  char id[50];
  char password[50];
  char name[50];
  struct student* next;
};
struct students_linkedlist{
  int len;
  struct student* head;
  struct student* tail;
} students={0,NULL,NULL};
void free_student(struct student* x){
  if(x==NULL){
    students.len=0;
    students.head=students.tail=NULL;
    return;
  }
  free_student(x->next);
  free(x);
}
void read_student(){
  FILE *student_fp=fopen("id.txt","r");
  if(students.len>0)
    free_student(students.head);

  while(!feof(student_fp)){
    struct student* node=malloc(sizeof(struct student));
    if(fscanf(student_fp,"%s %s %s",node->id,node->password,node->name)<3)
      break;
    node->next=NULL;
    if(students.len==0){
      students.head=students.tail=node;
    }
    else{
      students.tail->next=node;
      students.tail=node;
    }
    students.len++;
  }
  fclose(student_fp);
}

struct word{
  char han[50];
  char eng[50];
  struct word* next;
};
struct words_linkedlist{
  int len;
  struct word* head;
  struct word* tail;
} words={0,NULL,NULL};
void free_word(struct word* x){
  if(x==NULL){
    words.len=0;
    words.head=words.tail=NULL;
    return;
  }
  free_word(x->next);
  free(x);
}
void read_word(){
  FILE *word_fp=fopen("dic.txt","r");
  if(words.len>0)
    free_word(words.head);

  while(!feof(word_fp)){
    struct word* node=malloc(sizeof(struct word));

    if(fscanf(word_fp,"%s %s",node->eng,node->han)<2)
      break;
    node->next=NULL;
    if(words.len==0){
      words.head=words.tail=node;
    }
    else{
      struct word* x=words.head;
      struct word* k=NULL;
      int check=0;
      while(x!=NULL){
        if(strcmp(node->eng,x->eng)<0){
          if(k==NULL){
            node->next=words.head;
            words.head=node;
          }
          else{
            k->next=node;
            node->next=x;
          }
          check=1;
          break;
        }
        k=x;
        x=x->next;
      }
      if(!check){
        words.tail->next=node;
        words.tail=node;
      }
    }
    words.len++;
  }
  fclose(word_fp);
}

void cls(){
  int i;
  for(i=0;i<100;i++)
    printf("\n");
}

void start(char* name){
  printf("==================================\n");
  printf("=========== 2021 SPLUG ===========\n");
  if(!strcmp("",name))
    printf("==================================\n");
  else{
    for(int i=0;i<34-strlen(name)-1;i++)
      printf("=");
    printf(" %s\n",name);
  }
  printf("==================================\n");
  printf("=              메뉴              =\n");
  printf("==================================\n");
  printf("\t1. 회원가입\n");
  printf("\t2. 로그인\n");
  printf("\t3. 로그아웃\n");
  printf("\t4. 영어 단어 맞추기\n");
  printf("\t5. 회원 탈퇴\n");
  printf("\t6. 프로그램 종료\n");
  printf("==================================\n");
  printf(":");
}

int login=0;
char my_id[50];

int main(){
  read_student();
  read_word();

  while(1){
    int choice;
    cls();
    start(my_id);
    scanf("%d%*c",&choice);
    cls();

    switch(choice) {

    case 1:
      printf("회원가입 페이지\n");
      while(1){
        int check=0;
        struct student* x=students.head;
        struct student* node=malloc(sizeof(struct student));
        printf("아이디 : ");
        scanf("%s",node->id);
        while(x!=NULL){
          if(!strcmp(x->id,node->id)){
            check=1;
            break;
          }
          x=x->next;
        }

        if(check){
          printf("이미 존재하는 아이디 입니다.\n");
          free(node);
          continue;
        }
        printf("사용가능한 아이디 입니다.\n");
        printf("비밀번호 : ");
        scanf("%s",node->password);
        printf("이름 : ");
        scanf("%s",node->name);

        node->next=NULL;
        if(students.len==0)
          students.head=students.tail=node;
        else{
          students.tail->next=node;
          students.tail=node;
        }
        students.len++;
        FILE* student_fp=fopen("id.txt","a");
        fprintf(student_fp,"%s %s %s\n",node->id,node->password,node->name);
        fclose(student_fp);
        break;
      }
      break;

    case 2:
      while(1){
        char id[50],password[50];
        printf("로그인\n");
        printf("아이디 : ");
        scanf("%s",id);
        printf("비밀번호 : ");
        scanf("%s",password);

        struct student* x=students.head;
        while(x!=NULL){
          if(!strcmp(x->id,id) && !strcmp(x->password,password)){
            login=1;
            strcpy(my_id,id);
            break;
          }
          x=x->next;
        }
        if(!login){
          printf("아이디나 비밀번호가 틀렸습니다. 다시 시도하세요.\n");
          continue;
        }
        break;
      }
      break;

    case 3:
      if(login){
        char k[10];
        printf("정말 로그아웃 하시겠습니까? [y/n]: ");
        scanf("%s",k);
        if(!strcmp(k,"y")){
          login=0;
          *my_id=0;
        }
      }
      else{
        printf("로그인 상태가 아닙니다.\n");
        scanf("%*c");
      }
      break;

    case 4:{
      if(!login){
        printf("로그인 상태가 아닙니다.\n");
        scanf("%*c");
        break;
      }
      printf(">> 영어 단어 맞추기 프로그램<<\n");
      printf("1. 영어 단어 맞추기 2. 프로그램 종료\n\n");
      printf("번호를 선택하세요: ");
      int correct=0,total=0,k;
      char ans[50];

      scanf("%d",&k);
      if(k==2)
        break;

      struct word* x=words.head;
      while(x!=NULL){
        printf("%s -> ",x->han);
        scanf("%s",ans);
        if(!strcmp(ans,".quit"))
          break;
        if(!strcmp(ans,x->eng)){
          correct++;
          printf("correct!\n");
        }
        else
          printf("incorrect!\n");
        total++;
        x=x->next;
      }
      printf("당신의 점수는 %.2f점입니다.\n",total?(float)correct/total*100:0);
      scanf("%*c%*c");
      break;
    }
    case 5:{
      if(login){
        char k[10];
        printf("정말 회원 탈퇴 하시겠습니까? [y/n]: ");
        scanf("%s",k);
        if(!strcmp(k,"n"))
          break;
      }
      else{
        printf("로그인 상태가 아닙니다.\n");
        scanf("%*c");
        break;
      }
      struct student* x=students.head;
      struct student* k=NULL;
      while(x!=NULL){
        if(!strcmp(my_id,x->id)){
          if(students.len==1)
            students.head=students.tail=NULL;
          else if(!strcmp(x->id,students.head->id))
            students.head=x->next;
          else if(!strcmp(x->id,students.tail->id)){
            students.tail=k;
            students.tail->next=NULL;
          }
          else
            k->next=x->next;
          free(x);
          break;
        }
        k=x;
        x=x->next;
      }

      x=students.head;
      FILE *student_fp=fopen("id.txt","w");
      while(x!=NULL){
        fprintf(student_fp,"%s %s %s\n",x->id,x->password,x->name);
        x=x->next;
      }
      login=0;
      *my_id=0;
      students.len--;
      fclose(student_fp);
      break;
    }
    case 6:
      free_student(students.head);
      free_word(words.head);
      printf("다음에 또 만나요!!\n");
      return 0;
    }
  }
}

