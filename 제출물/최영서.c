#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct People
{
        char ID[20];
        char PASS[20];
        char NAME[10];
        struct People *p_next;
           
} Person;

typedef struct EnglishWord
{
	char E_Word[20];
	char K_Word[20];
	struct EnglishWord *p_next2;
} Word;

typedef struct Temp
{
	char E_temp[20];
	char K_temp[20];
} temp;
Person *p_head = NULL, *p_tail = NULL;
Word *p_head2 = NULL, *p_tail2 = NULL;
Word *p2;
Person *p;
int L=0;
void AddWord(Word **pp_head2,Word **pp_tail2,char E_Word2[],char K_Word2[])
{
	if(NULL != *pp_head2)
	{
		(*pp_tail2) -> p_next2 = (Word *) malloc(sizeof(Word));
		*pp_tail2 = (*pp_tail2) -> p_next2;
	}

	else {
		*pp_head2 = (Word *)malloc(sizeof(Word));
		*pp_tail2 = *pp_head2;
	}
	strcpy((*pp_tail2) -> E_Word,E_Word2);
	strcpy((*pp_tail2) -> K_Word,K_Word2);
	(*pp_tail2) -> p_next2 = NULL;
}
 
void AddPeople(Person **pp_head,Person **pp_tail,char ID2[],char PASS2[], char NAME2[])
{
	if(NULL != *pp_head)
	{
		(*pp_tail) -> p_next = (Person *)malloc(sizeof(Person));
		*pp_tail = (*pp_tail) -> p_next;
	}
	else {
		*pp_head = (Person *)malloc(sizeof(Person));
		*pp_tail = *pp_head;
	}
	strcpy((*pp_tail)->ID, ID2);
	strcpy((*pp_tail)->PASS, PASS2);
	strcpy((*pp_tail)->NAME, NAME2);
	(*pp_tail) -> p_next = NULL;
}

void Make_WordList()
{
	FILE *p_file2 = fopen("dic.txt","r");
        char English_Word3[20],Korean_Word3[20];
	if(NULL != p_file2){
		while(EOF != fscanf(p_file2,"%s %s",&English_Word3,&Korean_Word3)){
			AddWord(&p_head2,&p_tail2,English_Word3,Korean_Word3);
			L++;
		}
	}
        fclose(p_file2);
}
	
void make_linkedlist()
	{
		while( NULL!=p_head){
                     p=p_head;
                     p_head = p_head->p_next;
                     free(p);
             }
             p_tail = p_head;

          FILE *p_file = fopen("LOGIN.txt","r");
          char ID3[20],PASS3[20],NAME3[20];
          if(NULL != p_file){

          while(EOF != fscanf(p_file,"%s %s %s",&ID3,&PASS3,&NAME3))
          AddPeople(&p_head,&p_tail,ID3,PASS3,NAME3);
          }

         fclose(p_file);

 }
void Make_RealWordList()
{
        p2 = p_head2;
	temp *k;
	k = (temp *)malloc(sizeof(temp));
	for(int i=0;i<L-1;i++){
	p2 = p_head2;
	while( p2->p_next2 != NULL){
		
		if(strcmp(p2->E_Word,p2->p_next2->E_Word)>0)
		{
		strcpy(k->E_temp, p2->E_Word);
		strcpy(p2->E_Word, p2->p_next2 ->E_Word);
		strcpy(p2->p_next2->E_Word , k-> E_temp);
		strcpy(k->K_temp, p2->K_Word);
		strcpy(p2->K_Word , p2 -> p_next2 -> K_Word);
		strcpy(p2->p_next2->K_Word , k -> K_temp);
			
		}
             p2= p2->p_next2;
	}
	}

     FILE *p_file3 = fopen("Realdic.txt","a");
     p2 = p_head2;
     while( NULL != p2){

     fprintf(p_file3,"%s %s\n",p2->E_Word,p2->K_Word);
     p2 = p2->p_next2;
     }
     fclose(p_file3);
}

void main()
{
        int num,LOGIN=0;
	char LOGIN_ID[20];
	
	FILE *p_file = fopen("LOGIN.txt","a");
	fclose(p_file);
	make_linkedlist();	
        while(1) {
			printf(" ================= \n");
			printf("====2021 SPLUG ====\n");
			printf("=========");
			if(LOGIN == 0)
				printf("========\n");
			if(LOGIN == 1)
				printf("%s\n",LOGIN_ID);
			printf("===================\n");
			printf("=       ??????      = \n");
			printf("===================\n");
			printf("1. ????????????        \n");
			printf("2. ?????????          \n");
			printf("3. ????????????        \n");
			printf("4. ?????? ?????? ?????????\n");
			printf("5. ?????? ??????       \n");
			printf("6. ???????????? ??????   \n");
			printf("===================\n");
			printf(" ?????? ??????: ");
			scanf("%d",&num);  
    	if(num==1){
		  int n=1;
	  char ID[20],PASS[20],NAME[10];
	  printf("???????????? ????????? \n");
	  while(n=1){
	      printf("?????????: ");
	     
	      scanf("%s",&ID);
	      p = p_head;
	      
	      while(NULL != p){
            
	            if(strcmp(p -> ID, ID)==0)
		    {
		            printf("?????? ???????????? ????????? ?????????.\n");
			    break;
		    }

		 
		    p = p->p_next;
	           } 
	       if(NULL ==p)
                      break;
	       
	      }
	   printf("??????????????? ????????? ?????????.\n");
	   printf("????????????: ");
           scanf("%s",&PASS);
           printf("??????: ");
           scanf("%s",&NAME);

           FILE *p_file= fopen("LOGIN.txt","a"); 	   
	   fprintf(p_file,"%s %s %s\n",ID,PASS,NAME);
	   fclose(p_file);

	   make_linkedlist();
	     
	}
        if(num == 2)
        {       
		char LOGIN_PASS[20];
		p=p_head;
		int t=1,k=0;
                while(t==1){
		if(k==1)
		{
			p=p_head;
		printf("???????????? ?????????????????????.????????? ?????? ?????????????????????\n");
		}
		printf("?????????\n");
		printf("?????????: ");
		scanf("%s",&LOGIN_ID);
		printf("????????????: ");
		scanf("%s",&LOGIN_PASS);	
		while(NULL != p){
		if(strcmp(p -> ID, LOGIN_ID)==0 && strcmp(p -> PASS, LOGIN_PASS)==0)
		{
		printf("???????????? ?????????????????????.\n");
		LOGIN =1;
		t--;
		break;
		
		}
                else
		p = p -> p_next;
        } 
		k =1;
		}
	}
      if(num ==3)
      {
	      if(LOGIN ==0)
		      printf("???????????? ???????????? ????????????.?????? ????????? ????????????");
	      if(LOGIN ==1)
	      {      
	      printf("?????? ???????????? ??????????????????? [y/n]: ");
	      char answer;
	      scanf("%s",&answer);
	      if(answer == 'y')
		      LOGIN = 0;
	      if(answer == 'n')
		      LOGIN = 1;
	      }
      }
     if(num == 4){
	     int a;
	     int i=0;
	     FILE *p_file3 = fopen("Realdic.txt","w");
	     fclose(p_file3);

	     
	     char temp5[20],temp6[20];
	     char answer2[60];
	     char quit[] =".quit";
	     Make_WordList();
                 

	     printf(">>???????????? ????????? ????????????<<\n");
	     printf("1.?????? ?????? ????????? 2. ???????????? ??????\n");
	     printf("????????? ???????????????: \n");
	     scanf("%d",&a); 
	     if(a==1)
	     {
		     Make_RealWordList();

		     FILE *p_file3 = fopen("Realdic.txt","r");
		     
		    
			     while(EOF != fscanf(p_file3,"%s %s",temp5,temp6))
			     {
			     printf("%s -> ",temp6);
			     scanf("%s",&answer2);
			     if(strcmp(answer2,temp5)==0)
			     {
				     printf("correct!\n");
				     i++;
			     }
			     if(strcmp(answer2,quit)==0)
				     break;
			     if(strcmp(answer2,temp5)!=0)
				     printf("incorerect!\n");
			     
			      }
			     printf("????????? ????????? %d????????????.\n",i);
		       fclose(p_file3);

		       
	     }

	     if(a==2)
		     break;

   }
        
 if(num == 5){
        char a;
        printf("?????? ????????? ????????????????????????? [y/n]: ");
        scanf("%s",&a);
           while(a=='y'){
                if(LOGIN != 1){
                        printf("????????? ????????? ????????????.\n");
			break;
                }
                if(LOGIN ==1){

                    FILE *p_file=fopen("LOGIN.txt","w");
                    p=p_head;
                    while(p!=NULL)
                    {
                            if(strcmp(p->ID,LOGIN_ID)!=0)
                            fprintf(p_file,"%s %s %s\n",p->ID,p->PASS,p->NAME);
                       p=p->p_next;
                    }
                  fclose(p_file);
		  LOGIN =0;
		  make_linkedlist();
                  break;
                }
        }
     }
     
     if(num ==6){
	     printf("????????? ??? ????????? !!!");
	     while( NULL!=p_head){
		     p=p_head;
		     p_head = p_head->p_next;
		     free(p);
	     }
	     p_tail = p_head;
             while( NULL!=p_head2){
		     p2=p_head2;
		     p_head2= p_head2->p_next2;
		     free(p2);
	     }
	     p_tail2 = p_head2;
	    
	     break;
        	     }
	}

}