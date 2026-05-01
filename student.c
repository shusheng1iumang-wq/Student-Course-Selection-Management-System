#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "show.h"
#include"major_code.h"

/*
本来想采用建立一个数据库，给每个学生的id都填上的，
并且设置初始密码，但是吧，要花很长时间，而且要都是重复的工作，
所以我选择在空链表上慢慢添加每一个注册的学生。
*/
static Major_Code_List mcl_head;
// function of inquiry for new users
S_Student_List *Inquiry_User(S_Student_List *ssl_head)
{	
	S_Student_List *p=NULL;
    lli s_id = 0;
    char key[KEY_LINE]={0};
    char out=0;
    int i,c=0;
    //check
    do{
    printf("Student ID:\n");
    scanf("%lld",&s_id);
    while((c=getchar())!='\n'&&c!=EOF);
	}while(s_id<STUDENT_ID_LINE);
	
	if(s_id==STUDENT_ID_LINE)p=ssl_head;
	else p = Search_Student_ID(ssl_head,s_id);
    
    if(p!=NULL){
    	i=0;
    	do{	
    		flag=OFF;
    		printf("Pass Word:\n");
    		while(!save_fgets(key,KEY_LINE)){
    			printf("fgets error!\n");
    			printf("Pass Word:");
			}
			flag=key2key(p->key,key);
			i++;
			if(!flag){
				if(i>=TIP_TIME){
					printf("Your have %d times to try!\n",THE_TRY_LINE-i);
					printf("Do you want to exit?(y/n)");
					scanf("%c",&out);
					while((c=getchar())!='\n'&&c!=EOF);
					if(out=='y'||out=='Y')exit(0);
				}
				if(i==THE_TRY_LINE){
					printf("Sorry!You can't try again!\n");
					exit(0);
				}
			}
    	}while(!flag);
    	
	}else{
		printf("I can't find your information.\n");
		printf("Do you want to create your account?(y/n)");
		scanf("%c",&out);
		while((c=getchar())!='\n'&&c!=EOF);
		if(out=='n'||out=='N'){
			printf("See you.");
			exit(0);
		}
		p = Set_Up_Student_Account(ssl_head,s_id);
	}
	return p;
};

S_Student_List *Search_Student_ID(S_Student_List* ssl_head,lli s_id){
	S_Student_List *p=NULL;
	S_Student_List *temp=ssl_head;
	while(temp!=NULL&&temp->ID!=s_id){
		temp=temp->next;
	}
	if(temp!=NULL)p=temp;
	return p;
}

S_Student_List* Set_Up_Student_Account(S_Student_List* ssl_head,lli s_id){
	S_Student_List *p=NULL;
	Major_Code_List *mcl_p=NULL;
	char key1[KEY_LINE]={0};
	char key2[KEY_LINE]={0};
	char out=0;
	int i=0,c=0;
	char major_code[CODE_LINE]={0}; 
	
	if((p = (S_Student_List*)malloc(sizeof(S_Student_List)))==NULL){
		printf("malloc error!\n");
		exit(0);
	};
	p->ID = s_id;
	again:
	flag=OFF;
	do{	
		printf("Your Password:\n");
		printf("Your password needs to be at least 12 characters long\n");
		printf("and contain uppercase and lowercase letters\n");
		printf("as well as other characters like\"#\"\n");
		while(!save_fgets(key1,KEY_LINE)){
			printf("fgets_error!\n");
			printf("input again:");
		}
		flag = password_security(key1);
	}while(!flag);
	
	cpystring(key1,p->key,KEY_LINE);
	i = 0;
	flag = OFF;
	do{
		printf("Confirm Password:");
		if(i>=TIP_TIME){
			printf("We can go back to set up password,do we?(Y/N)");
			scanf("%c",&out);
			while((c=getchar())!='\n'&&c!=EOF);
			if(out=='y'||out=='Y')goto again;
		}
		while(!save_fgets(key2,KEY_LINE)){
			printf("fgets error!\n");
			printf("input again:");
		}
		flag = key2key(key2,p->key);
		i++;
	}while(!flag);
	
	printf("Congratulation!\n");

	Read_major_code_list(&mcl_head,MCL_FILE);	
	
	do{
		printf("Your major code:");
		while(!save_fgets(major_code,CODE_LINE)){
			printf("fgets error!");
			printf("\nYour major code:");
		}
		mcl_p = Search_mcl_item_code(&mcl_head,major_code);
		if(mcl_p==NULL)printf("Could not find your major code.\n");
	}while(mcl_p==NULL);

//   这是again版本，但是我觉得不太舒服，写了上面的优化版本。		
//	again_2:	
//		printf("Your major code:");
//		fgets(major_code,CODE_LINE,stdin);
//		fgets_demo(major_code);
//		mcl_p=Search_mcl_item_code(&mcl_head,major_code);
//		if(mcl_p==NULL){
//			printf("Could not fine your major code.\n");
//			goto again_2;
//		}
	
	cpystring(major_code,p->major_code,CODE_LINE);
	cpystring(mcl_p->name,p->major_name,COURSE_NAME_LINE);
		
	give_elective_credits(mcl_p->Category,p);
		
	free_malloc_mcl(&mcl_head);
	
	clean_the_history(p);
	
	cpystring("",p->name,NAME_LINE);
	printf("Your name:");
	while(!save_fgets(p->name,NAME_LINE)){
		printf("fgets error!\n");
		printf("Your name:");
	}
	
	Insert_account(ssl_head,p);
	
	return p;
}

void Insert_account(S_Student_List* ssl_head,S_Student_List *p){
	S_Student_List *r=ssl_head->next;
	S_Student_List *l=ssl_head;
	while(r){
		if(!r){
			break;
		}else if(r->ID > p->ID){
			break;
		}else{
			l = r;
			r = r->next;
		}
	}		
	l->next = p;
	p->next = r;
}

void free_malloc_ssl_list(S_Student_List* ssl_head){
	S_Student_List* r=ssl_head->next;
	
	while(r){
		S_Student_List* temp = r;
		r=r->next;
		free(temp);
	}
	ssl_head->next=NULL;
}

void fgets_demo(char* string){
	int length=strlen(string)-1;
	
	if(string[length]=='\n')string[length]=0;
}

Bool key2key(char *key,char *key_input){
	Bool flag=ON;
	int i;
	
	if(strlen(key)==strlen(key_input)){
		for(i=0;i<strlen(key);i++){
			if(key[i]!=key_input[i]){
				flag=OFF;
				break;
			}
		}
	}else flag=OFF;
	
	return flag;
}

Bool password_security(char* key){
	Bool flag=OFF;
	int i=0;
	Bool uppercase=OFF,
		lowercase=OFF,
		others=OFF;
		
	if(strlen(key)>=KEY_BOTTOM_LINE){
		for(i=0;i<strlen(key);i++){
			if(key[i]>='a'&&key[i]<='z')lowercase=ON;
			else if(key[i]>='A'&&key[i]<='Z')uppercase=ON;
			else others=ON;
			if(uppercase&&lowercase&&others){
				flag=ON;break;
			}
		}
	}
		
	return flag;
}

void cpystring(char *paste,char *wall,int size){
	int i=0;
	
	for(i=0;i<size;i++){                //我写了对wall的清空，可以用来清空很多东西
		wall[i]=0;
	}
	
	i=0;
	while(*paste){
		wall[i++]=*paste;
		paste++;
	}
}

void give_elective_credits(Bool category,S_Student_List*p){
	
	if(category){
		p->elective_credits[HSS][0]=MAX_SCORE;
		p->elective_credits[SS][0]=MIN_SCORE;
	}else{
		p->elective_credits[HSS][0]=(MIN_SCORE+MAX_SCORE)/2.0;
		p->elective_credits[SS][0]=(MIN_SCORE+MAX_SCORE)/2.0;
	}
}

void clean_the_history(S_Student_List *p){
	int i=0;
	for(i=0;i<10;i++){
		p->elective_record[0][i][0]=0;
		p->elective_record[1][i][0]=0;
		p->elective_record[0][i][1]=0;
		p->elective_record[1][i][1]=0;
	}
}

void show_ssl_item(S_Student_List *p){
	int i = 0;
	
	printf("Student ID:%lld\n",p->ID);
	printf("Name:%s\n",p->name);
	printf("Key:%s\n",p->key);
	printf("Major Code:%s\n",p->major_code);
	printf("Major NAME:%s\n",p->major_name);
	printf("HSS:%3.1lf/%3.1lf\n",p->elective_credits[HSS][1],p->elective_credits[HSS][0]);
	printf("SS:%3.1lf/%3.1lf\n",p->elective_credits[SS][1],p->elective_credits[SS][0]);
	printf("HSS record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[0][i][0]!=0){
			printf("Course Number:%d\n",p->elective_record[0][i][0]);
		}else break;
	}
	printf("SS record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[1][i][0]!=0){
			printf("Course Number:%d\n",p->elective_record[1][i][0]);
		}else break;
	}
}	

void del_ssl_item(S_Student_List *ssl_head,lli id){
	S_Student_List *r = ssl_head->next;
	S_Student_List *l = ssl_head;
	
	while(r!=NULL){
		if(r->ID==id){
			l->next = r->next;
			free(r);
			break;
		}
		l = r;
		r = r->next;
	}
}

void view_course_grades(S_Student_List *p){
	int i=0;
	
	printf("HSS course record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[HSS][i][0]!=0){
			printf("course_num:%d",p->elective_record[HSS][i][0]);
			if(p->elective_record[HSS][i][1]!=0){
				printf("--%d\n",p->elective_record[HSS][i][1]);
			}else{
				printf("--The course has not been completed.\n");
			}
		}else{
			break;
		}
	}
	if(i==0)printf("No course record.\n");
	
	printf("SS course record:\n");
	for(i=0;i<10;i++){
		if(p->elective_record[SS][i][0]!=0){
			printf("course_num:%d",p->elective_record[SS][i][0]);
			if(p->elective_record[SS][i][1]!=0){
				printf("--%d\n",p->elective_record[SS][i][1]);
			}else{
				printf("--The course has not been completed.\n");
			}
		}else{
			break;
		}
	}
	if(i==0)printf("No course record.\n");
	//可以函数优化的，看情况吧。
	
} 